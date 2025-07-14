#include "interrupt_handlers.h"

void isr0_handler() {
  vga_put_string("Division by zero.\n");

  while (1) {
    halt();
  }
}

void irq0_handler() {
  outb(0x20, 0x20);
}
