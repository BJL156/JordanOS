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

int jos_strcmp(const char *s0, const char *s1) {
  while (*s0 && (*s0 == *s1)) {
    s0++;
    s1++;
  }

  return *(const unsigned char *)s0 - *(const unsigned char *)s1;
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

    if (jos_strcmp(line, "clear\n") == 0) {
      vga_clear();
    } else if (jos_strcmp(line, "help\n") == 0) {
      vga_put_string("Available commands:\n       help - Displays this message.\n       clear - Erases the entire screen and resets the cursor position.\n       about - Displays information of JordanOS.\n");
    } else if (jos_strcmp(line, "about\n") == 0) {
      vga_put_string("Welcome to Jordan OS.\nIt's an operating system named after the most powerful person that I know.\nThe operating system was written in x86 assembly and C.\nThe source code is fully available at https://github.com/bjl156/jordanos.\n");
    } else {
      vga_put_string("Unknown command: ");
      vga_put_string(line);
    }
  }
}
