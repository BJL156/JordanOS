#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "io.h"

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

void keyboard_init();
char keyboard_read_char();

#endif
