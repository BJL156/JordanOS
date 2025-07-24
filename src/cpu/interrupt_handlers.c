#include "interrupt_handlers.h"

void isr0_handler() {
  vga_put_string("Division by zero.\n");

  while (1) {
    halt();
  }
}

volatile uint32_t ticks = 0;

void irq0_handler() {
  ticks++;

  outb(0x20, 0x20);
}
