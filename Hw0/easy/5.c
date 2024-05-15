#include<stdio.h>
#include<stdlib.h>

typedef struct listnode {
  int val;
  struct listnode* next;
} listnode;

void removeNthElement(listnode** head, int n) {
  if (!head || !*head) return;

  listnode* temp = *head;

  if (n == 0){
    *head = temp->next;
    free(temp);
    return;
  }
  for (int i = 0; temp != NULL && i < n - 1; ++i)
    temp = temp->next;
  if (!temp || !temp->next) return;

  listnode* next = temp->next->next;
  free(temp->next);
  temp->next = next;
}

void printList(listnode* head){
  while (head) {
    printf("%d -> ", head->val);
    head = head->next;
  }
  printf("NULL\n");
}

int main() {

  listnode* head = malloc(sizeof(listnode));
  head->val = 1;
  head->next = malloc(sizeof(listnode));
  head->next->val = 2;
  head->next->next = malloc(sizeof(listnode));
  head->next->next->val = 3;
  head->next->next->next = malloc(sizeof(listnode));
  head->next->next->next->val = 4;
  head->next->next->next->next = malloc(sizeof(listnode));
  head->next->next->next->next->next->val = 5;
  head->next->next->next->next->next = NULL;

  printf("Before removal:\n");
  printList(head);

  removeNthElement(&head, 2);

  printf("After removal:\n");
  printList(head);

  return 0;
}
