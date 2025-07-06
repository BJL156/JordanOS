#ifndef VGA_H
#define VGA_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "io.h"

typedef struct {
  uint16_t *buffer;
  uint8_t row;
  uint8_t col;
  uint8_t color;
} Vga;

void vga_init(Vga *vga);
void vga_set_color(Vga *vga, uint8_t color);
void vga_put_char(Vga *vga, char c);
void vga_put_string(Vga *vga, const char *str);

#endif
