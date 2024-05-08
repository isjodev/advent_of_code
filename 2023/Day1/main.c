// TODO: Break into multiple files, improve comments and variable
// naming conventions, fix memset
#include <ctype.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "input.txt"

// Function prototypes
int read_line(FILE *, char *, size_t);
int get_numeric_value(char *);
int part_one(char *);

// Read fPtr into char[256] buffer, return -1 on error.
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

// Cast a char to an int and subtract 48 (ascii value of 0) to determine
// decimal value.
int get_numeric_value(char *line_idx) { return (int)*line_idx - 48; }

// Process each line, and return the combined value of the first
// and last integers of each line.
int part_one(char *line) {
  // Length of string, subtract one to get index of last character.
  int string_len = strlen(line);
  int first_numeric_value = 0;
  int second_numeric_value = 0;

  // Get first numeric value from string.
  for (int i = 0; i < string_len; i++) {
    if (isdigit(line[i]) > 0) {
      first_numeric_value = get_numeric_value(&line[i]);
      break;
    }
  }

  // Get second numeric value from string.
  for (int j = string_len - 1; j >= 0; j--) {
    if (isdigit(line[j]) > 0) {
      second_numeric_value = get_numeric_value(&line[j]);
      break;
    }
  }

  return (10 * first_numeric_value) + (second_numeric_value);
}

int main() {
  // Handle input file.
  char const *const fileName = FILENAME;
  FILE *fPtr = fopen(fileName, "r");

  // Error handling for fileName.
  if (!fPtr) {
    fprintf(stderr, "Error opening %s\n", fileName);
    exit(EXIT_FAILURE);
  }

  // Char buffer for reading individual lines from file.
  char buf[256];
  // Part One of problem statement.
  int part_1_solution = 0;
  // Part Two of problem statement.
  int part_2_solution = 0;

  // Read a single line from file into buf, then process it
  // to determine numeric value of each line, as provided
  // by the problem spec. Completes day_1.
  while (read_line(fPtr, buf, 256) != -1) {
    char *line = buf;
    part_1_solution += part_one(line);
  }

  // Read line from file into buff, perform search and replace
  // operations, then process in same fashion as part_1.
  // TODO: Implement.
  // REWIND fPtr.
  // Seach and Replace.
  // Process.

  // Output first solution.
  printf("day1 part1: %d\n", part_1_solution);

  // TODO: Solve
  printf("day1 part2: %d\n", part_2_solution);
  exit(EXIT_SUCCESS);
}
