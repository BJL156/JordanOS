#include "gdt.h"

typedef struct __attribute__((packed)) {
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t  base_middle;
  uint8_t  access;
  uint8_t  granularity;
  uint8_t  base_high;
} GdtEntry;

typedef struct __attribute__((packed)) {
  uint16_t limit;
  uint32_t base;
} GdtPtr;

static GdtEntry gdt[3];
static GdtPtr gdtp;

extern void gdt_flush(uint32_t);

static void set_gdt_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
  gdt[num].base_low = base & 0xFFFF;
  gdt[num].base_middle = (base >> 16) & 0xFF;
  gdt[num].base_high = (base >> 24) & 0xFF;

  gdt[num].limit_low = limit & 0xFFFF;
  gdt[num].granularity = (limit >> 16) & 0x0F;

  gdt[num].granularity |= gran & 0xF0;
  gdt[num].access = access;
}

void gdt_install() {
  gdtp.limit = (sizeof(GdtEntry) * 3) - 1;
  gdtp.base  = (uint32_t)&gdt;

  set_gdt_entry(0, 0, 0, 0, 0);
  set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
  set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

  gdt_flush((uint32_t)&gdtp);
}
