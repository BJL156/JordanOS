#ifndef INTERRUPT_HANDLERS_H
#define INTERRUPT_HANDLERS_H

#include "interrupts.h"
#include "../drivers/io.h"
#include "../drivers/vga.h"

void isr0_handler();
void irq0_handler();

#endif
