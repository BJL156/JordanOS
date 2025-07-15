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

  if (ticks % 18 == 0) {
    uint8_t row = vga_get_row();
    uint8_t col = vga_get_col();
    vga_set_row(20);
    vga_set_col(0);

    char buffer[12];
    itoa(ticks / 18, buffer, 10);
    vga_put_string("Uptime: ");
    vga_put_string(buffer);
    vga_put_char('s');
    vga_put_char(' ');

    vga_set_row(row);
    vga_set_col(col);
  }

  outb(0x20, 0x20);
}
