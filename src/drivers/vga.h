#ifndef VGA_H
#define VGA_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define VGA_MEMORY 0xB8000
#define VGA_WIDTH  80
#define VGA_HEIGHT 25

typedef struct {
  uint16_t *buffer;
  uint8_t row;
  uint8_t col;
  uint8_t color;
} vga_t;

void vga_init(vga_t *vga);
void vga_put_char(vga_t *vga, char c);
void vga_put_string(vga_t *vga, const char *str);

#endif
