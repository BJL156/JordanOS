#include "utils.h"

size_t itoa(int value, char *buffer, int base) {
  char temp[32];

  char *p_temp = temp;
  int i = 0;
  unsigned int v;

  bool negative = (base == 10 && value < 0);

  if (negative) {
    v = -value;
  } else {
    v = (unsigned int)value;
  }

  while (v || p_temp == temp) {
    i = v % base;
    v /= base;

    if (i < 10) {
      *p_temp++ = i + '0';
    } else {
      *p_temp++ = i + 'a' - 10;
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
