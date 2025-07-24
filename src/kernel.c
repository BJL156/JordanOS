#include "drivers/vga.h"
#include "drivers/keyboard.h"

#include "cpu/gdt.h"
#include "cpu/idt.h"
#include "cpu/pic.h"
#include "cpu/interrupts.h"

#include "memory/pmm.h"
#include "memory/paging.h"

#include "multiboot.h"
#include "shell.h"

void kernel_main(uint32_t magic, uint32_t multiboot_info_addr) {
  vga_init();

  MultibootInfo *multiboot_info = load_multiboot_info(magic, multiboot_info_addr);
  if (!multiboot_info) {
    println("Failed to load the Multiboot 1 information.");
    return;
  }

  pmm_init(multiboot_info);

  gdt_install();
  idt_install();
  pic_remap();

  paging_init();

  keyboard_init();
  enable_interrupts();

  shell(multiboot_info);
}
