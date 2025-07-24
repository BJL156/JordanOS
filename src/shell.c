#include "shell.h"
#include "utils/print.h"

void shell() {
  char line[LINE_BUFFER_SIZE];

  while (1) {
    print("> ");
    keyboard_read_line(line, LINE_BUFFER_SIZE);

    if (jos_strcmp(line, "clear") == 0) {
      vga_clear();
    } else if (jos_strcmp(line, "help") == 0) {
      println("Available commands:");
      println("\thelp - Displays this message.");
      println("\tclear - Erases the entire screen and resets the cursor position.");
      println("\tabout - Displays information about JordanOS.");
      println("\tuptime - Displays how long the system has been running.");
    } else if (jos_strcmp(line, "about") == 0) {
      println("Welcome to Jordan OS.");
      print("\tIt's an operating system named after the most powerful person that I know. ");
      print("The operating system was written in x86 assembly and C. ");
      println("The source code is fully available at https://github.com/BJL156/JordanOS.");
    } else if (jos_strcmp(line, "uptime") == 0) {
      uint32_t total_seconds = ticks / 18;
      uint32_t hours = total_seconds / 3600;
      uint32_t minutes = (total_seconds / 60) % 60;
      uint32_t seconds = total_seconds % 60;

      char buffer[64];
      char temp[12];

      const char *prefix = "Uptime: ";

      size_t index = 0;
      for (; prefix[index] != '\0'; index++) {
        buffer[index] = prefix[index];
      }

      itoa(hours, temp, 10);
      for (size_t i = 0; temp[i] != '\0'; i++) {
        buffer[index++] = temp[i];
      }
      buffer[index++] = ':';

      if (minutes < 10) {
        buffer[index++] = '0';
      }
      itoa(minutes, temp, 10);
      for (size_t i = 0; temp[i] != '\0'; i++) {
        buffer[index++] = temp[i];
      }
      buffer[index++] = ':';

      if (seconds < 10) {
        buffer[index++] = '0';
      }
      itoa(seconds, temp, 10);
      for (size_t i = 0; temp[i] != '\0'; i++) {
        buffer[index++] = temp[i];
      }

      buffer[index++] = '\n';
      buffer[index++] = '\0';

      vga_put_string(buffer);
    } else {
      print("Unknown command: ");
      println(line);
    }
  }
}
