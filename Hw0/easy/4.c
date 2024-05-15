#include<stdio.h>
#include<stdlib.h>

typedef struct listnode{
  int val;
  struct listnode* next;
} listnode;

listnode* createNode(int val){
  listnode* newNode = (listnode*)malloc(sizeof(listnode));
  newNode->val = val;
  newNode->next = NULL;
  return newNode;
}
listnode* findNthElement(listnode* head, int N) {
  listnode* current = head;
  for(int i = 0;i < N; i++){
    if(current == NULL){
      printf("Index out of bounds\n");
      return NULL;
    }
    current = current->next;
  }
  return current;
}
void printList(listnode* head){
  listnode* current = head;
  while(current != NULL){
    printf("%d", current->val);
    current = current->next;
  }
  printf("\n");
}
int main(){
  listnode* head = createNode(1);
  head->next =  createNode(2);
  head->next->next = createNode(3);
  head->next->next->next = createNode(4);
  head->next->next->next->next = createNode(5);

  printList(head);

  listnode* nthNode = findNthElement(head, 2);
  if(nthNode != NULL){
    printf("The value of the 2nd element is: %d\n", nthNode->val);
  }
  return 0;
}
