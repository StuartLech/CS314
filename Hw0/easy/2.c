#include<stdio.h>

void swapInts(int* a, int* b){
  int temp = *a;
  *a = *b;
  *b = temp;
}

int main(){
  int x = 5, y = 10;

  printf("Before swap:\nx = %d\ny = %d\n", x, y);

  swapInts(&x, &y);

  printf("\nAfter swap:\nx = %d\ny = %d\n", x, y);

  return 0;
}
