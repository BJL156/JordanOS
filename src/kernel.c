#include "vga.h"

void kernel_main() {
  vga_t vga;
  vga_init(&vga);

  vga_put_string(&vga, "Welcome to JordanOS.\nIf you found a copy of this, you're a true Jordan fan.");
}
