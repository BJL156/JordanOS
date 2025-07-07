[BITS 32]

global isr0

isr0:
  cli
  pusha

  mov dword [0xB8000], 0x4F004F00

  popa
  sti
  iretd 
