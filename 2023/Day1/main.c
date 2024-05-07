#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#define FILENAME "input.txt"

typedef struct Node {
  char *line;
  struct Node *next;
} Node;

void insert_end(Node **root, char *value) {
  Node *new_node = malloc(sizeof(Node));

  if (new_node == NULL) {
    exit(EXIT_FAILURE);
  }

  new_node->next = NULL;
  new_node->line = value;

  if (*root == NULL) {
    *root = new_node;
    return;
  }

  Node *curr = *root;
  while (curr->next != NULL) {
    curr = curr->next;
  }

  curr->next = new_node;
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

void print_list(Node **root) {
  for (Node *curr = *root; curr != NULL; curr = curr->next) {
    printf("%s\n", curr->line);
  }
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

int main() {
  char const *const fileName = FILENAME;
  FILE *fPtr = fopen(fileName, "r");
  char buf[256];

  while (read_line(fPtr, buf, 256) != -1) {
    char *line = buf;
    printf("%s\n", line);
  }

  return 0;
}
