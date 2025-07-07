[BITS 32]

global irq0

extern irq0_handler

irq0:
  cli
  pusha
  call irq0_handler
  popa
  sti
  iretd
