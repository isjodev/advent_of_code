#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "input.txt"

// You must free the result if result is non-NULL.
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

int main(void) {
  char const *const fileName = FILENAME;
  FILE *fPtr = fopen(fileName, "r");

  // Error handling for fileName.
  if (!fPtr) {
    fprintf(stderr, "Error opening %s\n", fileName);
    exit(EXIT_FAILURE);
  }

  // char buf[256];

  /* while (read_line(fPtr, buf, 256) != -1) { */
  /*   char *line = buf; */
  /*   printf("%s\n", line); */
  /* } */
  char *substrings[] = {"zero", "one", "two",   "three", "four",
                        "five", "six", "seven", "eight", "nine"};
  char *integers[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

  char *string = "56four4one2";

  // Close but not quite right...
  for (int i = 0; i <= 10; i++) {
    if (strstr(string, substrings[i]) != NULL) {
      printf("current: %s\n", string);
      string = str_replace(string, substrings[i], integers[i]);
      printf("new: %s\n", string);
      // part_2_solution += part_one(string)
    }
  }
  return 0;
}
