#ifndef SHELL_H
#define SHELL_H

#include "drivers/vga.h"
#include "drivers/keyboard.h"

#include "cpu/interrupt_handlers.h"

#include "utils/string_utils.h"
#include "utils/utils.h"

#define LINE_BUFFER_SIZE 128

void shell();

#endif
