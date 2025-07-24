#ifndef MMAP_H
#define MMAP_H

#include "../multiboot.h"

#include "../utils/print.h"

#include <stdint.h>
#include <stddef.h>

void print_memory_map(MultibootInfo *multiboot_info);

#endif
