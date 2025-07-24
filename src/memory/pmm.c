#include "pmm.h"
#include <stdint.h>

static uint8_t *bitmap = NULL;
static size_t total_pages = 0;

void pmm_init(MultibootInfo *multiboot_info) {
  extern uint32_t kernel_end;
  bitmap = (uint8_t *)((uintptr_t)&kernel_end);

  for (size_t i = 0; i < BITMAP_SIZE; i++) {
    bitmap[i] = 0xFF;
  }

  uint32_t mmap_length = multiboot_info->mmap_length;
  uint8_t *mmap_addr = (uint8_t *)multiboot_info->mmap_addr;
  uint8_t *mmap_end = mmap_addr + mmap_length;

  while (mmap_addr < mmap_end) {
    MultibootMmapEntry *entry = (MultibootMmapEntry *)mmap_addr;

    if (entry->type == 1) {
      uint64_t base = entry->addr;
      uint64_t length = entry->len;

      for (uint64_t addr = base; addr < base + length; addr += PAGE_SIZE) {
        size_t page_index = addr / PAGE_SIZE;

        if (page_index < TOTAL_PAGES) {
          bitmap[page_index / 8] &= ~(1 << (page_index % 8));
          total_pages++;
        }
      }
    }

    mmap_addr += entry->size + sizeof(entry->size);
  }

  uint32_t bitmap_end = (uint32_t)(uintptr_t)bitmap + BITMAP_SIZE;

  for (uint32_t addr = 0; addr < bitmap_end; addr += PAGE_SIZE) {
    size_t page = addr / PAGE_SIZE;
    bitmap[page / 8] |= (1 << (page % 8));
  }

  vga_put_string("PMM initialized. ");
  char buf[20];
  itoa(total_pages, buf, 10);
  vga_put_string(buf);
  vga_put_string(" pages available.\n");
}

void *pmm_alloc_page() {
  for (size_t i = 0; i < TOTAL_PAGES; i++) {
    if (!(bitmap[i / 8] & (1 << (i % 8)))) {
      bitmap[i / 8] |= (1 << (i % 8));

      return (void *)(i * PAGE_SIZE);
    }
  }

  return NULL;
}

void pmm_free_page(void *ptr) {
  uintptr_t addr = (uintptr_t)ptr;
  size_t page = addr / PAGE_SIZE;

  if (page < TOTAL_PAGES) {
    bitmap[page / 8] &= ~(1 << (page % 8));
  }
}
