#include "interrupts.h"

void enable_interrupts() {
    __asm__ volatile ("sti");
}

void disable_interrupts() {
    __asm__ volatile ("cli");
}

void halt() {
  __asm__ volatile ("hlt");
}
