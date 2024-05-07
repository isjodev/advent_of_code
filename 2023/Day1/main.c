#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "input.txt"

typedef struct Node {
  struct {
    char *line;
    int len;
    int conv_num_val;
  } line_val;
  struct Node *next;
} Node;

void insert_end(Node **root, char *line, int len, int val) {
  Node *new_node = malloc(sizeof(Node));

  if (new_node == NULL) {
    exit(EXIT_FAILURE);
  }

  new_node->next = NULL;

  new_node->line_val.line = line;
  new_node->line_val.len = len;
  new_node->line_val.conv_num_val = 0;

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

void print_list(Node **root) {
  for (Node *curr = *root; curr != NULL; curr = curr->next) {
    printf("%s %d %d\n", curr->line_val.line, curr->line_val.len,
           curr->line_val.conv_num_val);
  }
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

// Main
int main() {
  char const *const fileName = FILENAME;
  FILE *fPtr = fopen(fileName, "r");
  char line[256];
  Node *root = NULL;

  while (fgets(line, 256, fPtr)) {
    insert_end(&root, line, strlen(line) - 1, 0);
  }

  print_list(&root);
  deallocate(&root);
  return 0;
}
