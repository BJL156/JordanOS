[BITS 32]

global isr0
global isr14

extern isr0_handler
extern isr14_handler

isr0:
  cli
  pusha
  call isr0_handler
  popa
  sti
  iretd
isr14:
  cli
  push ds
  push es
  pushad

  mov ax, 0x10
  mov ds, ax
  mov es, ax

  mov eax, [esp + 36]
  push eax
  call isr14_handler
  add esp, 4

  popad
  pop es
  pop ds
  sti
  iretd
