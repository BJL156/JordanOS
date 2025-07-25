#include "interrupt_handlers.h"

void isr0_handler() {
  println("\nDivision by zero.");

  while (1) {
    halt();
  }
}

void isr14_handler(uint32_t error_code) {
  println("\nPage fault.");

  uint32_t fault_addr;
  asm volatile("mov %%cr2, %0" : "=r"(fault_addr));

  print("\tAddr: ");
  print_hex(fault_addr);
  print("\n\tError Code: ");
  print_hex(error_code);
  putchar('\n');

  while (1) {
    halt();
  }
}

volatile uint32_t ticks = 0;

void irq0_handler() {
  ticks++;

  outb(0x20, 0x20);
}
