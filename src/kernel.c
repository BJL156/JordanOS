#include "drivers/vga.h"
#include "cpu/gdt.h"
#include "cpu/idt.h"
#include "cpu/pic.h"

#include <stdbool.h>

static bool is_shift_pressed = false;
static bool is_extended = false;

static const char keyboard_en_us[] = {
  0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
  '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
  0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
  0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};

static const char keyboard_en_us_shift[] = {
  0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
  '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
  0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
  0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' '
};

void isr0_handler() {
  vga_put_string("Division by zero.\n");
}

void irq0_handler() {
  // vga_put_char('.');
  outb(0x20, 0x20);
}

void irq1_handler() {
  uint8_t scancode = inb(0x60);

  if (scancode == 0xE0) {
    is_extended = true;

    outb(0x20, 0x20);
    return;
  }

  if (is_extended) {
    const uint8_t current_col = vga_get_col();

    switch (scancode) {
    case 0x48: vga_put_string("Up key not supported yet.\n"); break;
    case 0x4B: vga_set_col(current_col - 1); break;
    case 0x50: vga_put_string("Down key not supported yet.\n"); break;
    case 0x4D: vga_set_col(current_col + 1); break;
    }

    is_extended = false;

    outb(0x20, 0x20);
    return;
  }

  if (scancode == 0x2A || scancode == 0x36) {
    is_shift_pressed = true;

    outb(0x20, 0x20);
    return;
  }

  if (scancode == 0xAA || scancode == 0xB6) {
    is_shift_pressed = false;

    outb(0x20, 0x20);
    return;
  }

  if (scancode < sizeof(keyboard_en_us)) {
    char c = is_shift_pressed ? keyboard_en_us_shift[scancode] : keyboard_en_us[scancode];
    if (c) {
      vga_put_char(c);
    }
  }

  outb(0x20, 0x20);
}

void kernel_main() {
  gdt_install();
  idt_install();
  pic_remap();
  vga_init();

  outb(0x21, 0xFC);
  outb(0xA1, 0xFF);

  vga_put_string("JordanOS\n");

  __asm__ volatile ("sti");

  while (1) {
    __asm__ volatile ("hlt");
  }
}
