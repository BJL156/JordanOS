#include "string_utils.h"

int jos_strcmp(const char *s0, const char *s1) {
  while (*s0 && (*s0 == *s1)) {
    s0++;
    s1++;
  }

  return *(const unsigned char *)s0 - *(const unsigned char *)s1;
}
