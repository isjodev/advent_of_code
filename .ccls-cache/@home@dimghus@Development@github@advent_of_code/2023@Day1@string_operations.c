// Performing search and replace operations on
// strings. Replacing substrings which are numbers
// with their numeric values.
// Input: zoneeight234, 7pqrstsixteen
// Output: z18234, 7pqrs16

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *words[] = {
    "zero", "one", "two",   "three", "four",
    "five", "six", "seven", "eight", "nine",
};

char *word1 = "56four4one2";
char *word2 = "cqmzbxzfvonevmmmlxsnjr5zfg";

char *word1_conv = "56412";
char *word2_conv = "cqmzbxzfv1vmmmlxsnjr5zfg";

int main() {
  printf("%s\n", word1);
  printf("%s\n", words[4]);

  exit(EXIT_SUCCESS);
}
