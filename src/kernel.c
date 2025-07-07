#include "drivers/vga.h"
#include "cpu/gdt.h"
#include "cpu/idt.h"
#include "cpu/pic.h"

void irq0_handler() {
    vga_put_char('.');
    outb(0x20, 0x20);
}

void kernel_main() {
  gdt_install();
  idt_install();
  pic_remap();
  vga_init();

  vga_put_string("JordanOS\n");

  __asm__ volatile ("sti");

  while (1) {
    __asm__ volatile ("hlt");
  }
}
