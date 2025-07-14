#include "shell.h"

void shell() {
  char line[LINE_BUFFER_SIZE];

  while (1) {
    vga_put_string("> ");
    keyboard_read_line(line, LINE_BUFFER_SIZE);

    if (jos_strcmp(line, "clear") == 0) {
      vga_clear();
    } else if (jos_strcmp(line, "help") == 0) {
      vga_put_string("Available commands:\n");
      vga_put_string("       help - Displays this message.\n");
      vga_put_string("       clear - Erases the entire screen and resets the cursor position.\n");
      vga_put_string("       about - Displays information of JordanOS.\n");
    } else if (jos_strcmp(line, "about") == 0) {
      vga_put_string("Welcome to Jordan OS.\n");
      vga_put_string("It's an operating system named after the most powerful person that I know.\n");
      vga_put_string("The operating system was written in x86 assembly and C.\n");
      vga_put_string("The source code is fully available at https://github.com/bjl156/jordanos.\n");
    } else {
      vga_put_string("Unknown command: ");
      vga_put_string(line);
      vga_put_char('\n');
    }
  }
}
