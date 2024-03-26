#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FILENAME "input.txt"

int main() {
  FILE* fPtr = fopen(FILENAME, "r");

  if (!fPtr) {
    fprintf(stderr, "Failed to open file\n");
    exit(EXIT_FAILURE);
  }

  printf("Hello, Advent of Code!\n");
  return 0;
}
