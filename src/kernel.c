#include "drivers/vga.h"
#include "drivers/keyboard.h"

#include "cpu/gdt.h"
#include "cpu/idt.h"
#include "cpu/pic.h"

void isr0_handler() {
  vga_put_string("Division by zero.\n");

  while (1) {
    __asm__ volatile ("sti");
  }
}

void irq0_handler() {
  // vga_put_char('.');
  outb(0x20, 0x20);
}

void kernel_main() {
  gdt_install();
  idt_install();
  pic_remap();
  vga_init();
  keyboard_init();

  __asm__ volatile ("sti");

  vga_put_string("Welcome to JordanOS!\n");

  while (1) {
    char c = keyboard_read_char();
    vga_put_char(c);
  }
}
