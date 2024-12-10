#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

Node *create_node(int data) {
  Node *node;
  node = malloc(sizeof(*node));
  node->data = data;
  node->next = NULL;
  return node;
}

Node *list_from_array(int *data, int size) {
  Node *head = create_node(data[0]);
  Node *current = head;

  for (int i = 1; i < size; ++i) {
    current->next = create_node(data[i]);
    current = current->next;
  }

  return head;
}

void free_list(Node *head) {
  Node *current;
  while (head != NULL) {
    current = head;
    head = head->next;
    free(current);
  }
}

void print_nodes(Node *head) {
  Node *current = head;
  int i = 0;

  printf("Index\tData\n");
  while (current != NULL) {
    printf("%d\t%d\n", i, current->data);
    current = current->next;
    i++;
  }
}

Node *reverse_nodes(Node *head) {
  Node *prev = NULL;
  Node *current = head;
  Node *next = head;

  while (current != NULL) {
    next = next->next;
    current->next = prev;
    prev = current;
    current = next;
  }

  return prev;
}

Node *reverse_between(Node *head, int m, int n) {
  if (m == n) {
    return head;
  }

  // Mark the start of the reversal (index m)
  Node *reverse_start = NULL;

  // node just before reverse_start
  Node *reverse_prev = NULL;

  // Mark the end of the reverse (index n)
  Node *reverse_end = NULL;

  // node just after reverse_end
  Node *reverse_next = NULL;

  int i = 1;
  Node *current = head;
  while (current && i <= n) {
    if (i < m) {
      reverse_prev = current;
    } else if (i == m) {
      reverse_start = current;
    } else if (i == n) {
      reverse_end = current;
      reverse_next = current->next;
    }
    current = current->next;
    i++;
  }

  // detach after point n
  reverse_end->next = NULL;

  // reverse everything between start and end
  reverse_end = reverse_nodes(reverse_start);

  // point the node before the reverse to the reversed list
  if (reverse_prev) {
    reverse_prev->next = reverse_end;
  } else {
    head = reverse_end;
  }

  // reattach last node
  reverse_start->next = reverse_next;

  return head;
}

int main(void) {
  int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  Node *head = list_from_array(data, 10);

  printf("Original list:\n");
  print_nodes(head);

  int m = 2;
  int n = 5;

  printf("\nReversed list (between positions %d and %d):\n", m, n);
  head = reverse_between(head, m, n);
  print_nodes(head);

  free_list(head);
  printf("\nDone.\n");
  return 0;

}
