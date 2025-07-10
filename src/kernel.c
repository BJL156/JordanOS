#include "drivers/vga.h"
#include "drivers/keyboard.h"

#include "cpu/gdt.h"
#include "cpu/idt.h"
#include "cpu/pic.h"
#include "cpu/interrupts.h"

#define LINE_BUFFER_SIZE 128

void isr0_handler() {
  vga_put_string("Division by zero.\n");

  while (1) {
    halt();
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
  enable_interrupts();

  vga_put_string("Welcome to JordanOS!\n");

  char line[LINE_BUFFER_SIZE];

  while (1) {
    vga_put_string("> ");
    keyboard_read_line(line, LINE_BUFFER_SIZE);

    vga_put_string("You typed: ");
    vga_put_string(line);
  }
}
