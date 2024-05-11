#include <assert.h>
#include <ctype.h>
#include <memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "input.txt"

struct node {
  char *string;
  struct node *next;
};

typedef struct node Node;

// Function prototypes.
char *strdup(const char *);
char *substr(char *, int, int);
int get_game_id(char *s);
void print_list(Node **);
void deallocate(Node **);
int read_line(FILE *, char *, size_t);
int extract_str_id(char *);
int day_two(Node **);

char *strdup(const char *src) {
  char *dst = malloc(strlen(src) + 1);
  if (dst == NULL)
    return NULL;
  strcpy(dst, src);
  return dst;
}

char *substr(char *s, int x, int y) {
  char *ret = malloc(strlen(s) + 1);
  char *p = ret;
  char *q = &s[x];

  assert(ret != NULL);

  while (x < y) {
    *p++ = *q++;
    x++;
  }
  *p++ = '\0';
  return ret;
}

int get_numeric_value(char *str_idx) {
  // Return thing...
  return (int)*str_idx - 48;
}

int extract_str_id(char *str) {
  int str_len = strlen(str);
  int fnm = 0;
  int snm = 0;
  char *addr_1 = NULL;
  char *addr_2 = NULL;

  // Get first numeric value from string.
  for (int i = 0; i < str_len; i++) {
    if (isdigit(str[i]) > 0) {
      fnm = get_numeric_value(&str[i]);
      addr_1 = (str + i);
      break;
    }
  }

  // Get second numeric value from string.
  for (int j = str_len - 1; j >= 0; j--) {
    if (isdigit(str[j]) > 0) {
      snm = get_numeric_value(&str[j]);
      addr_2 = (str + j);
      break;
    }
  }

  if (addr_1 == addr_2) {
    printf("%d %p %p\n", fnm, addr_1, addr_2);
    return fnm;
  } else {
    return (10 * fnm) + (snm);
  }
}

// Return game ID if valid game, else return 0...
int get_game_id(char *s) {
  int idx_id_delimiter = (int)strcspn(s, ":");
  char *id_str = substr(s, 0, idx_id_delimiter);
  int id = extract_str_id(id_str);

  char *token = strtok(s, ";");
  while (token) {
    printf("%s\n", token);
    token = strtok(NULL, ",");
  }
  printf("%d\n", id);

  return id;
}

void print_list(Node **root) {
  for (Node *curr = *root; curr != NULL; curr = curr->next) {
    printf("%s\n", curr->string);
  }
  printf("\n");
}

void deallocate(Node **root) {
  Node *curr = *root;
  while (curr != NULL) {
    Node *aux = curr;
    curr = curr->next;
    free(aux);
  }

  *root = NULL;
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

int day_two(Node **head) {
  int total = 0;
  int game_id = 0;

  // Begin work on thing.
  Node *curr = *head;
  while (curr != NULL) {
    char *game_string = curr->string;
    game_id = get_game_id(game_string);
    total += game_id;
    curr = curr->next;
  }

  return total;
}

int main(void) {
  // Handle input file.
  char const *const fileName = FILENAME;
  FILE *fPtr = fopen(fileName, "r");

  // Error handling for fileName.
  if (!fPtr) {
    fprintf(stderr, "Error opening %s\n", fileName);
    exit(EXIT_FAILURE);
  }

  char line[256];
  Node *current, *head;
  head = current = NULL;

  // Read data from fPtr and store in linked list.
  while (read_line(fPtr, line, 256) != -1) {
    Node *node = malloc(sizeof(Node));
    node->string = strdup(line);
    node->next = NULL;

    if (head == NULL) {
      current = head = node;
    } else {
      current = current->next = node;
    }
  }

  // Work on list...
  int total = day_two(&head);

  printf("%d\n", total);
  deallocate(&head);

  // Close file pointer and return.
  fclose(fPtr);
  exit(EXIT_SUCCESS);
}
