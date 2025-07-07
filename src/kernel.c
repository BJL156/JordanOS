#include "drivers/vga.h"
#include "cpu/gdt.h"
#include "cpu/idt.h"

void kernel_main() {
  gdt_install();
  idt_install();

  vga_init();
  vga_put_string("JordanOS\n");

  while (1) {
    __asm__ volatile ("hlt");
  }
}
