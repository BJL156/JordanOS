#include "keyboard.h"

#define KEYBOARD_BUFFER_SIZE 128

static const char keyboard_en_us[] = {
  0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
  '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
  0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
  0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};

static const char keyboard_en_us_shift[] = {
  0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
  '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
  0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
  0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' '
};

static char buffer[KEYBOARD_BUFFER_SIZE];
static size_t buffer_head = 0;
static size_t buffer_tail = 0;

static bool shift = false;
static bool extended = false;

static void buffer_push(char c) {
  size_t next = (buffer_head + 1) % KEYBOARD_BUFFER_SIZE;
  if (next != buffer_tail) {
    buffer[buffer_head] = c;
    buffer_head = next;
  }
}

void keyboard_init() {
  while (inb(0x64) & 1) {
    inb(0x60);
  }

  uint8_t mask = inb(0x21) & ~(1 << 1);
  outb(0x21, mask);
}

char keyboard_read_char() {
  while (buffer_head == buffer_tail) {
    asm __volatile ("hlt");
  }

  char c = buffer[buffer_tail];
  buffer_tail = (buffer_tail + 1) % KEYBOARD_BUFFER_SIZE;
  return c;
}

void irq1_handler() {
  uint8_t scancode = inb(0x60);

  if (scancode == 0xE0) {
    extended = true;

    outb(0x20, 0x20);
    return;
  }

  if (extended) {
    extended = false;

    outb(0x20, 0x20);
    return;
  }

  if (scancode == 0x2A || scancode == 0x36) {
    shift = true;

    outb(0x20, 0x20);
    return;
  }

  if (scancode == 0xAA || scancode == 0xB6) {
    shift = false;

    outb(0x20, 0x20);
    return;
  }

  bool released = scancode & 0x80;
  uint8_t keycode = scancode & 0x7F;

  if (!released && keycode < sizeof(keyboard_en_us)) {
    char c = shift ? keyboard_en_us_shift[keycode] : keyboard_en_us[keycode];

    if (c) {
      buffer_push(c);
    }
  }

  outb(0x20, 0x20);
}
