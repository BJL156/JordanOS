#ifndef PMM_H
#define PMM_H

#include "../multiboot.h"
#include "../drivers/vga.h"
#include "../utils/utils.h"

#include <stdint.h>
#include <stddef.h>

#define MAX_MEMORY_BYTES (32ULL * 1024 * 1024 * 1024)
#define PAGE_SIZE 4096
#define TOTAL_PAGES (MAX_MEMORY_BYTES / PAGE_SIZE)
#define BITMAP_SIZE (TOTAL_PAGES / 8)

void pmm_init(MultibootInfo *multiboot_info);
void *pmm_alloc_page();
void pmm_free_page(void *ptr);

#endif
