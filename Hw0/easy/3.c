#include<stdio.h>

void swapPtrs(int** ptr1, int** ptr2){
  int* temp = *ptr1;
  *ptr1 = *ptr2;
  *ptr2 = temp;
}

int main(){
  int x = 5;
  int y = 10;
  int* ptr_x = &x;
  int* ptr_y = &y;

  printf("Before swap:\n");
  printf("Value pointed by ptr_x: %d\n", *ptr_x);
  printf("Value pointed by ptr_y: %d\n", *ptr_y);

  swapPtrs(&ptr_x, &ptr_y);

  printf("After swap:\n");
  printf("Value pointed by ptr_x: %d\n", *ptr_x);
  printf("Value pointed by ptr_y: %d\n", *ptr_y);

  return 0;
}
