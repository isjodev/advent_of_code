#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "input.txt"

typedef struct {
  char *line;
  int length;
  int converted_numeric_value;
} line_info_t;

typedef struct node_t {
  line_info_t *line_t;
  struct node_t *next;
} node_t;

// Function prototypes
void insert_end(node_t **root, line_info_t);
void print_list(node_t **root);
void deallocate(node_t **root);

void insert_end(node_t **root, line_info_t value) {
  node_t *new_node = malloc(sizeof(node_t));

  if (new_node == NULL) {
    exit(EXIT_FAILURE);
  }

  new_node->next = NULL;
  new_node->line_t = &value;

  if (*root == NULL) {
    *root = new_node;
    return;
  }

  node_t *curr = *root;
  while (curr->next != NULL) {
    curr = curr->next;
  }
  curr->next = new_node;
}

void print_list(node_t **root) {
  for (node_t *curr = *root; curr != NULL; curr = curr->next) {
    printf("%s %d %d\n", curr->line_t->line, curr->line_t->length,
           curr->line_t->converted_numeric_value);
  }
}

void deallocate(node_t **root) {
  node_t *curr = *root;
  while (curr != NULL) {
    node_t *aux = curr;
    curr = curr->next;
    free(aux);
  }
  *root = NULL;
}

// Main
int main() {
  FILE *fPtr = fopen(FILENAME, "r");
  node_t *root = NULL;

  if (!fPtr) {
    fprintf(stderr, "Failed to open file\n");
    exit(EXIT_FAILURE);
  }

  print_list(&root);
  deallocate(&root);

  return 0;
}
