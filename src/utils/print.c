#include "print.h"

void print(const char *msg) {
  vga_put_string(msg);
}

void println(const char *msg) {
  vga_put_string(msg);
  vga_put_char('\n');
}

void putchar(char c) {
  vga_put_char(c);
}

void print_hex(uint32_t value) {
  char buf[11];
  buf[0] = '0';
  buf[1] = 'x';

  itoa(value, &buf[2], 16);
  vga_put_string(buf);
}

void print_hex64(uint64_t value) {
  char buf[19];
  buf[0] = '0';
  buf[1] = 'x';

  for (int i = 0; i < 16; i++) {
    uint8_t nibble = (value >> ((15 - i) * 4)) & 0xF;

    if (nibble < 10)
      buf[2 + i] = '0' + nibble;
    else
      buf[2 + i] = 'a' + (nibble - 10);
  }

  buf[18] = '\0';
  vga_put_string(buf);
}

void print_dec(uint32_t value) {
  char buf[20];
  itoa(value, buf, 10);
  vga_put_string(buf);
}
