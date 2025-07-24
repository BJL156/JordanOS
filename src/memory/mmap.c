#include "mmap.h"

void print_memory_map(MultibootInfo *multiboot_info) {
  if (!(multiboot_info->flags & (1 << 6))) {
    println("Memory map not available.");
    return;
  }

  println("Memory map:");

  uint32_t mmap_length = multiboot_info->mmap_length;
  uint8_t *mmap_addr = (uint8_t *)multiboot_info->mmap_addr;

  uint8_t *end = mmap_addr + mmap_length;

  while (mmap_addr < end) {
    MultibootMmapEntry *entry = (MultibootMmapEntry *)mmap_addr;

    print("\tBase addr: ");
    print_hex64(entry->addr);
    print("\n\t\tLength: ");
    print_hex64(entry->len);
    print("\n\t\tType: ");
    print_hex(entry->type);
    putchar('\n');

    mmap_addr += entry->size + sizeof(entry->size);
  }
}
