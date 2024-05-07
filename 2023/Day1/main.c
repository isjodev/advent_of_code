#include <memory.h>
#include <stdio.h>

#define FILENAME "input.txt"

int read_line(FILE *f, char *buffer, size_t len) {
  memset(buffer, 0, len);

  for (int i = 0; i < len; i++) {
    int c = fgetc(f);

    if (!feof(f)) {
      if (c == '\r') {
        buffer[i] = 0;
      } else if (c == '\n') {
        buffer[i] = 0;
        return i + 1;
      } else {
        buffer[i] = c;
      }
    }
  }
  return -1;
}

int process_line(char *line) { return 1; }

int main() {
  char const *const fileName = FILENAME;
  FILE *fPtr = fopen(fileName, "r");
  char buf[256];
  int total = 0;
  int line_val = 0;

  while (read_line(fPtr, buf, 256) != -1) {
    char *line = buf;
    line_val = process_line(line);
    total += line_val;
  }

  printf("%d\n", total);
  return 0;
}
