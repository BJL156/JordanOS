#include "vga.h"

#include <stddef.h>

void vga_init(vga_t *vga) {
  vga->buffer = (uint16_t *)VGA_MEMORY;
  vga->row = 0;
  vga->col = 0;
  vga->color = 0x0F;
}

void vga_put_char(vga_t *vga, char c) {
  if (c == '\n') {
    vga->row++;
    vga->col = 0;

    if (vga->row >= VGA_HEIGHT) {
      vga->row = 0;
    }

    return;
  }

  uint16_t index = vga->row * VGA_WIDTH + vga->col;
  vga->buffer[index] = (vga->color << 8) | c;
  vga->col++;

  if (vga->col >= VGA_WIDTH) {
    vga->col = 0;
    vga->row++;

    if (vga->row >= VGA_HEIGHT) {
      vga->row = 0;
    }
  }
}

void vga_put_string(vga_t *vga, const char *str) {
  for (size_t i = 0; str[i] != '\0'; i++) {
    vga_put_char(vga, str[i]);
  }
}
