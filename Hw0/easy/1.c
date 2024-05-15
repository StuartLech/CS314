#include<stdio.h>

void set(int* a, int val){
  *a = val;
}

int main(){
  int a = 5;

  printf("Value of a before calling set: %d\n", a);

  set(&a, 10);

  printf("Value of a after calling set: %d\n", a);

  return 0;
}
