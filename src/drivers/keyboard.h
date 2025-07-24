#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "io.h"

#include "../utils/print.h"

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

void keyboard_init();
char keyboard_read_char();
size_t keyboard_read_line(char *buf, size_t max_len);

#endif
