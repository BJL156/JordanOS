#include "paging.h"

__attribute__((aligned(4096))) uint32_t page_directory[1024];
__attribute__((aligned(4096))) uint32_t page_table[1024];

extern void load_page_directory(uint32_t *);
extern void enable_paging();

void paging_init() {
  for (size_t i = 0; i < 1024; i++) {
    page_table[i] = (i * 0x1000) | 3;
  }

  page_directory[0] = ((uint32_t)page_table) | 3;
  for (size_t i = 1; i < 1024; i++) {
    page_directory[i] = 0;
  }

  load_page_directory(page_directory);
  enable_paging();
}
