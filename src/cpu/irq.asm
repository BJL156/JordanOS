[BITS 32]

global irq0
global irq1

extern irq0_handler
extern irq1_handler

irq0:
  cli

  push ds
  push es

  pushad

  mov ax, 0x10
  mov ds, ax
  mov es, ax

  call irq0_handler

  popad
  pop es
  pop ds

  sti
  iretd
irq1:
  cli
  push ds
  push es
  pushad

  mov ax, 0x10
  mov ds, ax
  mov es, ax

  call irq1_handler

  popad
  pop es
  pop ds
  sti
  iretd
