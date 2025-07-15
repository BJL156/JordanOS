#include "utils.h"

size_t itoa(int value, char *buffer, int base) {
  char temp[32];
  char *p_temp = temp;
  unsigned int v;
  bool negative = (base == 10 && value < 0);

  if (negative) {
    v = (unsigned int)(-value);
  } else {
    v = (unsigned int)value;
  }

  if (v == 0) {
    *p_temp++ = '0';
  } else {
    while (v != 0) {
      int digit = v % base;
      v /= base;

      if (digit < 10) {
        *p_temp++ = digit + '0';
      } else {
        *p_temp++ = digit + 'a' - 10;
      }
    }
  }

  size_t len = p_temp - temp;

  if (negative) {
    *buffer++ = '-';
    len++;
  }

  while (p_temp > temp) {
    *buffer++ = *--p_temp;
  }

  *buffer = '\0';

  return len;
}
