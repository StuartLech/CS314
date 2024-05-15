#include<stdio.h>
#include<stdlib.h>

typedef struct listnode {
  int data;
  struct listnode* next;
} ListNode;

ListNode* createNode(int data){
  ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

ListNode* findNthToLastElement(ListNode* head, int N){
  if (head == NULL || N < 1) {
    return NULL;
  }

  ListNode* main_ptr = head;
  ListNode* ref_ptr = head;

  for(int i = 0; i < N; i++){
    if(ref_ptr == NULL){
      return NULL;
    }
    ref_ptr = ref_ptr->next;
  }
  while(ref_ptr != NULL){
    main_ptr = main_ptr->next;
    ref_ptr = ref_ptr->next;
  }
  return main_ptr;
}
void printList(ListNode* head) {
  while(head != NULL){
    printf("%d -> ", head->data);
    head = head->next;
  }
  printf("NULL\n");
}

int main() {
  ListNode* head = createNode(1);
  head->next = createNode(2);
  head->next->next = createNode(3);
  head->next->next->next = createNode(4);
  head->next->next->next->next = createNode(5);

  printList(head);

  int N = 2;
  ListNode* res = findNthToLastElement(head, N);
  if (res != NULL){
    printf("The %dth to last element is: %d\n", N, res->data);
  } else {
    printf("The value of N is too large.\n");
  }
  return 0;
}
