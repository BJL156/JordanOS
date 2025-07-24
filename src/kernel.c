#include "drivers/vga.h"
#include "drivers/keyboard.h"

#include "cpu/gdt.h"
#include "cpu/idt.h"
#include "cpu/pic.h"
#include "cpu/interrupts.h"

#include "utils/print.h"

#include "memory/pmm.h"
#include "memory/paging.h"

#include "multiboot.h"
#include "shell.h"

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

MultibootInfo *load_multiboot_info(uint32_t magic, uint32_t multiboot_info_addr) {
  if (magic != MULTIBOOT_HEADER_MAGIC) {
    println("Invalid Multiboot 1 magic number.");
    print_hex(magic);
    return NULL;
  }

  return (MultibootInfo *)multiboot_info_addr;
}

void kernel_main(uint32_t magic, uint32_t multiboot_info_addr) {
  vga_init();

  MultibootInfo *multiboot_info = load_multiboot_info(magic, multiboot_info_addr);
  if (multiboot_info) {
    print_memory_map(multiboot_info);
  }

  pmm_init(multiboot_info);

  gdt_install();
  idt_install();
  pic_remap();
  paging_init();
  keyboard_init();
  enable_interrupts();

  shell();
}
