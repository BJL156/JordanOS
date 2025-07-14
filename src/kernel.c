#include "drivers/vga.h"
#include "drivers/keyboard.h"

#include "cpu/gdt.h"
#include "cpu/idt.h"
#include "cpu/pic.h"
#include "cpu/interrupts.h"

#include "shell.h"

void kernel_main() {
  gdt_install();
  idt_install();
  pic_remap();
  vga_init();
  keyboard_init();
  enable_interrupts();

  shell();
}
