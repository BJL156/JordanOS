#ifndef INTERRUPT_HANDLERS_H
#define INTERRUPT_HANDLERS_H

#include "interrupts.h"

#include "../drivers/io.h"

#include "../utils/print.h"
#include "../utils/utils.h"

extern volatile uint32_t ticks;

void isr0_handler();
void isr14_handler(uint32_t error_code);

void irq0_handler();

#endif
