#include "drivers/vga.h"

#include "utils/utils.h"

void kernel_main() {
  Vga vga;
  vga_init(&vga);

  for (int i = 0; i < 50; i++) {
    char buf[32];
    itoa(i, buf, 2);

    vga_put_string(&vga, buf);
    vga_put_char(&vga, '\n');
  }

  vga_set_color(&vga, 0x4F);

  vga_put_string(&vga, "Welcome to JordanOS.\nIf you found a copy of this, you're a true Jordan fan.\n");

  vga_set_color(&vga, 0x0F);

  vga_put_string(&vga, "Testing.\n");
}
