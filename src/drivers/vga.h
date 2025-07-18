#ifndef VGA_H
#define VGA_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "io.h"

void vga_init();
void vga_set_color(uint8_t color);
void vga_put_char(char c);
void vga_put_string(const char *str);
void vga_clear();
uint8_t vga_get_row();
uint8_t vga_get_col();
void vga_set_row(uint8_t row);
void vga_set_col(uint8_t col);

#endif
