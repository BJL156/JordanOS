#ifndef PRINT_H
#define PRINT_H

#include "../drivers/vga.h"
#include "utils.h"

void print(const char *msg);
void println(const char *msg);

void putchar(char c);

void print_hex(uint32_t value);
void print_hex64(uint64_t value);

void print_dec(uint32_t value);

#endif
