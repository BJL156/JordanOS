#include "vga.h"

#define VGA_MEMORY 0xB8000
#define VGA_WIDTH  80
#define VGA_HEIGHT 25

#define CURSOR_COMMAND_PORT 0x3D4
#define CURSOR_DATA_PORT    0x3D5

static void vga_update_cursor(const Vga *vga) {
  uint16_t index = vga->row * VGA_WIDTH + vga->col;

  outb(CURSOR_COMMAND_PORT, 0x0F);
  outb(CURSOR_DATA_PORT, (uint8_t)(index & 0xFF));

  outb(CURSOR_COMMAND_PORT, 0x0E);
  outb(CURSOR_DATA_PORT, (uint8_t)((index >> 8) & 0xFF));
}

static void vga_scroll(Vga *vga) {
  for (size_t row = 1; row < VGA_HEIGHT; row++) {
    for (size_t col = 0; col < VGA_WIDTH; col++) {
      size_t prev_row_index = (row - 1) * VGA_WIDTH + col;
      size_t current_row_index = row * VGA_WIDTH + col;

      vga->buffer[prev_row_index] = vga->buffer[current_row_index];
    }
  }

  uint16_t blank_entry = (0x0F << 8) | ' ';
  for (size_t col = 0; col < VGA_WIDTH; col++) {
    size_t last_row_index = (VGA_HEIGHT - 1) * VGA_WIDTH + col;
    vga->buffer[last_row_index] = blank_entry;
  }

  vga->row = VGA_HEIGHT - 1;
  vga->col = 0;
}

static bool vga_handle_escape_char(Vga *vga, char c) {
  switch (c) {
  case '\n':
    vga->col = 0;
    vga->row++;

    if (vga->row >= VGA_HEIGHT) {
      vga_scroll(vga);
    }

    return true;
  case '\r':
    vga->col = 0;

    return true;
  default:
    return false;
  }
}

void vga_init(Vga *vga) {
  vga->buffer = (uint16_t *)VGA_MEMORY;
  vga->row = 0;
  vga->col = 0;
  vga->color = 0x0F;
}

void vga_set_color(Vga *vga, uint8_t color) {
  vga->color = color;
}

void vga_put_char(Vga *vga, char c) {
  if (!vga_handle_escape_char(vga, c)) {
    size_t index = vga->row * VGA_WIDTH + vga->col;
    vga->buffer[index] = (vga->color << 8) | c;
    vga->col++;

    if (vga->col >= VGA_WIDTH) {
      vga->col = 0;
      vga->row++;

      if (vga->row >= VGA_HEIGHT) {
        vga_scroll(vga);
      }
    }
  }

  vga_update_cursor(vga);
}

void vga_put_string(Vga *vga, const char *str) {
  for (size_t i = 0; str[i] != '\0'; i++) {
    vga_put_char(vga, str[i]);
  }
}
