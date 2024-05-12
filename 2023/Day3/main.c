#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  FILE *file = fopen("input.txt", "r");
  int max_line_size = 0;
  int count = 0;
  char c;

  int n_lines = 1;
  while ((c = fgetc(file)) != EOF) {
    if (c == '\n' && count > max_line_size)
      max_line_size = count;
    if (c == '\n') {
      count = 0;
      n_lines++;
    }
    count++;
  }
  rewind(file);

  char(*M)[n_lines][max_line_size];

  for (size_t i = 0; i <= n_lines; i++) {
    for (size_t j = 0; j <= max_line_size; j++) {
      M[i][j] = strcp("a");
    }
  }

  for (size_t i = 0; i <= 10; i++) {
    for (size_t j = 0; j <= 10; j++) {
      printf("%s", M[i][j]);
    }
  }

  free(M);
  fclose(file);
  exit(EXIT_SUCCESS);
}
