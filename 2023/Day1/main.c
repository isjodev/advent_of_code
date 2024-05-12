// TODO: Break into multiple files, improve comments and variable
// naming conventions, fix memset, finish part2 solution.
#include <ctype.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "input.txt"

char *substrings[] = {"zero", "one", "two",   "three", "four",
                      "five", "six", "seven", "eight", "nine"};

char *integers[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

// Function prototypes
int read_line(FILE *, char *, size_t);
int get_numeric_value(char *);
int part_one(char *);
char *str_replace(char *, char *, char *);

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

int part_two(char *line) {
  // Length of string, subtract one to get index of last character.
  int string_len = strlen(line);
  int first_numeric_value = 0;
  int second_numeric_value = 0;
  char *addr_1 = NULL;
  char *addr_2 = NULL;

  // Get first numeric value from string.
  for (int i = 0; i < string_len; i++) {
    if (isdigit(line[i]) > 0) {
      first_numeric_value = get_numeric_value(&line[i]);
      addr_1 = (line + i);
      break;
    }
  }

  // Get second numeric value from string.
  for (int j = string_len - 1; j >= 0; j--) {
    if (isdigit(line[j]) > 0) {
      second_numeric_value = get_numeric_value(&line[j]);
      addr_2 = (line + j);
      break;
    }
  }

  if (addr_1 == addr_2) {
    printf("%d %p %p\n", first_numeric_value, addr_1, addr_2);
    return first_numeric_value;
  } else {
    return (10 * first_numeric_value) + (second_numeric_value);
  }
}

char *str_replace(char *orig, char *rep, char *with) {
  char *result;  // the return string
  char *ins;     // the next insert point
  char *tmp;     // varies
  int len_rep;   // length of rep (the string to remove)
  int len_with;  // length of with (the string to replace rep with)
  int len_front; // distance between rep and end of last rep
  int count;     // number of replacements

  // sanity checks and initialization
  if (!orig || !rep)
    return NULL;
  len_rep = strlen(rep);
  if (len_rep == 0)
    return NULL; // empty rep causes infinite loop during count
  if (!with)
    with = "";
  len_with = strlen(with);

  // count the number of replacements needed
  ins = orig;
  for (count = 0; (tmp = strstr(ins, rep)); ++count) {
    ins = tmp + len_rep;
  }

  tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

  if (!result)
    return NULL;

  // first time through the loop, all the variable are set correctly
  // from here on,
  //    tmp points to the end of the result string
  //    ins points to the next occurrence of rep in orig
  //    orig points to the remainder of orig after "end of rep"
  while (count--) {
    ins = strstr(orig, rep);
    len_front = ins - orig;
    tmp = strncpy(tmp, orig, len_front) + len_front;
    tmp = strcpy(tmp, with) + len_with;
    orig += len_front + len_rep; // move to next "end of rep"
  }
  strcpy(tmp, orig);
  return result;
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
  fseek(fPtr, 0, SEEK_SET);
  while (read_line(fPtr, buf, 256) != -1) {
    char *str = buf;
    for (int i = 0; i < 10; i++) {
      if (strstr(str, substrings[i]) != NULL) {
        str = str_replace(str, substrings[i], integers[i]);
      }
    }
    int str_val = part_two(str);
    part_2_solution += str_val;
  }

  // Output first solution.
  printf("day1 part1: %d\n", part_1_solution);

  // TODO: Solve
  // 53539 is correct answer
  printf("day1 part2: %d\n", part_2_solution);
  exit(EXIT_SUCCESS);
}
