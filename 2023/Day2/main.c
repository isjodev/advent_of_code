#include <ctype.h>
#include <memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void parse_game(char *line) { printf("%s\n", line); }

int main(void) {
  // Handle input file.
  char const *const fileName = FILENAME;
  FILE *fPtr = fopen(fileName, "r");

  // Error handling for fileName.
  if (!fPtr) {
    fprintf(stderr, "Error opening %s\n", fileName);
    exit(EXIT_FAILURE);
  }

  char buf[256];
  char *line;
  while (read_line(fPtr, buf, 256) != -1) {
    line = buf;
    parse_game(line);
  }

  printf("Done.\n");
  exit(EXIT_SUCCESS);
}
