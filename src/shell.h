#ifndef SHELL_H
#define SHELL_H

#include "drivers/keyboard.h"

#include "cpu/interrupt_handlers.h"

#include "memory/mmap.h"

#include "utils/string_utils.h"
#include "utils/utils.h"
#include "utils/print.h"

#include "multiboot.h"

#define LINE_BUFFER_SIZE 128

void shell(MultibootInfo *multiboot_info);

#endif
