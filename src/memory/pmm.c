#include "pmm.h"

#define PAGE_SIZE 4096

static uint8_t *bitmap = NULL;
static size_t total_pages = 0;
static size_t bitmap_size = 0; 

static uint64_t get_max_usable_memory(MultibootInfo *multiboot_info) {
  uint32_t mmap_length = multiboot_info->mmap_length;
  uint8_t *mmap_addr = (uint8_t *)multiboot_info->mmap_addr;
  uint8_t *mmap_end = mmap_addr + mmap_length;

  uint64_t max_addr = 0;

  while (mmap_addr < mmap_end) {
    MultibootMmapEntry *entry = (MultibootMmapEntry *)mmap_addr;

    if (entry->type == 1) {
      uint64_t base = entry->addr;
      uint64_t length = entry->len;

      uint64_t current_max_addr = base + length;
      if (current_max_addr > max_addr) {
        max_addr = current_max_addr;
      }
    }

    mmap_addr += entry->size + sizeof(entry->size);
  }

  return max_addr;
}

static inline void set_page_used(size_t page_index) {
  bitmap[page_index / 8] |= (1 << (page_index % 8));
}

static inline void set_page_free(size_t page_index) {
  bitmap[page_index / 8] &= ~(1 << (page_index % 8));
}

static inline bool is_page_used(size_t page_index) {
  return bitmap[page_index / 8] & (1 << (page_index % 8));
}

static void mark_pages_used(uintptr_t start_addr, uintptr_t end_addr) {
  for (uintptr_t addr = start_addr; addr < end_addr; addr += PAGE_SIZE) {
    set_page_used(addr / PAGE_SIZE);
  }
}

static void mark_pages_free(uintptr_t start_addr, uintptr_t end_addr) {
  for (uintptr_t addr = start_addr; addr < end_addr; addr += PAGE_SIZE) {
    set_page_free(addr / PAGE_SIZE);
  }
}

static void mark_memory_map_free(MultibootInfo *multiboot_info) {
  uint32_t mmap_length = multiboot_info->mmap_length;
  uint8_t *mmap_addr = (uint8_t *)multiboot_info->mmap_addr;
  uint8_t *mmap_end = mmap_addr + mmap_length;

  while (mmap_addr < mmap_end) {
    MultibootMmapEntry *entry = (MultibootMmapEntry *)mmap_addr;

    if (entry->type == 1) {
      mark_pages_free(entry->addr, entry->addr + entry->len);
    }

    mmap_addr += entry->size + sizeof(entry->size);
  }
}

void pmm_init(MultibootInfo *multiboot_info) {
  extern uint32_t kernel_end;
  extern uint32_t kernel_start;

  uint64_t max_addr = get_max_usable_memory(multiboot_info);
  total_pages = (size_t)((max_addr + PAGE_SIZE - 1) / PAGE_SIZE);
  bitmap_size = total_pages / 8;

  bitmap = (uint8_t *)((uintptr_t)&kernel_end);
  for (size_t i = 0; i < bitmap_size; i++) {
    bitmap[i] = 0xFF;
  }

  mark_memory_map_free(multiboot_info);

  mark_pages_used((uintptr_t)&kernel_start, (uintptr_t)&kernel_end);
  mark_pages_used((uintptr_t)bitmap, (uintptr_t)bitmap + bitmap_size);
}

void *pmm_alloc_page() {
  for (size_t page_index = 0; page_index < total_pages; page_index++) {
    if (!is_page_used(page_index)) {
      bitmap[page_index / 8] |= (1 << (page_index % 8));

      return (void *)(page_index * PAGE_SIZE);
    }
  }

  return NULL;
}

void pmm_free_page(void *ptr) {
  uintptr_t addr = (uintptr_t)ptr;
  size_t page = addr / PAGE_SIZE;

  if (page < total_pages) {
    bitmap[page / 8] &= ~(1 << (page % 8));
  }
}

void pmm_print_info() {
  size_t free_pages = 0;
  for (size_t page_index = 0; page_index < total_pages; page_index++) {
    if (!is_page_used(page_index)) {
      free_pages++;
    }
  }

  println("PPM info:");

  print("\tTotal pages: ");
  print_dec(total_pages);
  putchar('\n');

  print("\tFree pages: ");
  print_dec(free_pages);
  putchar('\n');

  print("\tUsed pages: ");
  print_dec(total_pages - free_pages);
  putchar('\n');

  print("\tBitmap addr: ");
  print_hex((uint32_t)(uintptr_t)bitmap);
  putchar('\n');

  print("\tBitmap size: ");
  print_dec(bitmap_size);
  putchar('\n');
}
