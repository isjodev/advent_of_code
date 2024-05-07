#include <ctype.h>
#include <memory.h>
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

int process_line(char *line) {
  int length = strlen(line);
  char *ptr_1 = line;
  char *ptr_2 = ptr_1 + length - 1;
  int val = 1;
  char num[2];

  while (ptr_1 != ptr_2) {
    if (isdigit(*ptr_1)) {
      // val *= atoi(ptr_1);
      num[0] = *ptr_1;
      break;
    }

    if (isdigit(*ptr_2)) {
      // val += atoi(ptr_2);
      num[1] = *ptr_2;
      break;
    }
    ptr_1++;
    --ptr_2;
  }

  val = atoi(num);
  return val;
}

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
