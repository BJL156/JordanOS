#include "drivers/vga.h"

void kernel_main() {
  Vga vga;
  vga_init(&vga);

  for (int i = 0; i < 50; i++) {
    vga_put_string(&vga, "Wow. This is a line alright.\n");
  }

  vga_set_color(&vga, 0x4F);

  vga_put_string(&vga, "Welcome to JordanOS.\nIf you found a copy of this, you're a true Jordan fan.\n");

  vga_set_color(&vga, 0x0F);

  vga_put_string(&vga, "Testing.\n");
}
