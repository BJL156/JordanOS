ALIGNMENT       equ 1 << 0
MEMORY_INFO     equ 1 << 1
FLAGS           equ ALIGNMENT | MEMORY_INFO
MAGIC_NUMBER    equ 0x1BADB002
MULTIBOOT_CHECK equ -(MAGIC_NUMBER + FLAGS)

section .multiboot
align 4
  dd MAGIC_NUMBER
  dd FLAGS
  dd MULTIBOOT_CHECK

section .bss
align 16
  stack_bottom: resb 16384
  stack_top:

section .text
global _start
_start:
  mov esp, stack_top

  extern kernel_main
  call kernel_main

  cli
  .hang:
    hlt
  jmp .hang
