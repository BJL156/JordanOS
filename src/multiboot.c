#include "multiboot.h"

MultibootInfo *load_multiboot_info(uint32_t magic, uint32_t multiboot_info_addr) {
  if (magic != MULTIBOOT_HEADER_MAGIC) {
    println("Invalid Multiboot 1 magic number.");
    print_hex(magic);
    return NULL;
  }

  return (MultibootInfo *)multiboot_info_addr;
}
