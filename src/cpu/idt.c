#include "idt.h"
#include <stdint.h>

#define IDT_ENTRIES 256

typedef struct __attribute__((packed)) {
  uint16_t offset_low;
  uint16_t selector;
  uint8_t zero;
  uint8_t type_attr;
  uint16_t offset_high;
} IdtEntry;

typedef struct __attribute__((packed)) {
  uint16_t limit;
  uint32_t base;
} IdtPtr;

static IdtEntry idt[IDT_ENTRIES];
static IdtPtr idtp;

extern void idt_flush(uint32_t);

static void set_idt_entry(int num, uint32_t base, uint16_t sel, uint8_t flags) {
  idt[num].offset_low = base & 0xFFFF;
  idt[num].selector = sel;
  idt[num].zero = 0;
  idt[num].type_attr = flags;
  idt[num].offset_high = (base >> 16) & 0xFFFF;
}

void idt_install() {
  idtp.limit = (sizeof(IdtEntry) * IDT_ENTRIES) - 1;
  idtp.base = (uint32_t)&idt;

  for (int i = 0; i < IDT_ENTRIES; i++) {
    set_idt_entry(i, 0, 0, 0);
  }

  extern void isr0();
  set_idt_entry(0, (uint32_t)isr0, 0x08, 0x8E);
  extern void isr14();
  set_idt_entry(14, (uint32_t)isr14, 0x08, 0x8E);

  extern void irq0();
  set_idt_entry(32, (uint32_t)irq0, 0x08, 0x8E);
  extern void irq1();
  set_idt_entry(33, (uint32_t)irq1, 0x08, 0x8E);

  idt_flush((uint32_t)&idtp);
}
