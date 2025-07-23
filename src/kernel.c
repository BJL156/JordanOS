#include "drivers/vga.h"
#include "drivers/keyboard.h"

#include "cpu/gdt.h"
#include "cpu/idt.h"
#include "cpu/pic.h"
#include "cpu/interrupts.h"

#include "memory/paging.h"

#include "multiboot.h"
#include "shell.h"

void print_hex(uint32_t value) {
  char buf[11];
  buf[0] = '0';
  buf[1] = 'x';

  itoa(value, &buf[2], 16);
  vga_put_string(buf);
}

void print_hex64(uint64_t value) {
  char buf[19];
  buf[0] = '0';
  buf[1] = 'x';

  for (int i = 0; i < 16; i++) {
    uint8_t nibble = (value >> ((15 - i) * 4)) & 0xF;

    if (nibble < 10)
      buf[2 + i] = '0' + nibble;
    else
      buf[2 + i] = 'a' + (nibble - 10);
  }

  buf[18] = '\0';
  vga_put_string(buf);
}

void print_dec(uint32_t value) {
  char buf[20];
  itoa(value, buf, 10);
  vga_put_string(buf);
}

void print_memory_map(MultibootInfo *multiboot_info) {
  if (!(multiboot_info->flags & (1 << 6))) {
    vga_put_string("Memory map not available.\n");
    return;
  }

  vga_put_string("Memory map:\n");

  uint32_t mmap_length = multiboot_info->mmap_length;
  uint8_t *mmap_addr = (uint8_t *)multiboot_info->mmap_addr;

  uint8_t *end = mmap_addr + mmap_length;

  while (mmap_addr < end) {
    MultibootMmapEntry *entry = (MultibootMmapEntry *)mmap_addr;

    vga_put_string("\tBase addr: ");
    print_hex64(entry->addr);
    vga_put_string("\n\t\tLength: ");
    print_hex64(entry->len);
    vga_put_string("\n\t\tType: ");
    print_hex(entry->type);
    vga_put_char('\n');

    mmap_addr += entry->size + sizeof(entry->size);
  }
}

MultibootInfo *load_multiboot_info(uint32_t magic, uint32_t multiboot_info_addr) {
  if (magic != MULTIBOOT_HEADER_MAGIC) {
    vga_put_string("Invalid Multiboot 1 magic number.\n");
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

  gdt_install();
  idt_install();
  pic_remap();
  paging_init();
  keyboard_init();
  enable_interrupts();

  shell();
}
