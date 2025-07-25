#ifndef PMM_H
#define PMM_H

#include "../multiboot.h"
#include "../utils/print.h"
#include "../utils/utils.h"

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

void pmm_init(MultibootInfo *multiboot_info);
void *pmm_alloc_page();
void pmm_free_page(void *ptr);

void pmm_print_info();

#endif
