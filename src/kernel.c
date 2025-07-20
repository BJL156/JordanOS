#include "drivers/vga.h"
#include "drivers/keyboard.h"

#include "cpu/gdt.h"
#include "cpu/idt.h"
#include "cpu/pic.h"
#include "cpu/interrupts.h"

#include "memory/paging.h"

#include "shell.h"

void kernel_main() {
  gdt_install();
  idt_install();
  pic_remap();
  paging_init();
  vga_init();
  keyboard_init();
  enable_interrupts();

  volatile uint32_t *test = (uint32_t*)0x200000;
  *test = 0xBEEF1234;

  shell();
}
