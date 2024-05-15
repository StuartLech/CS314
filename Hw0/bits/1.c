#include<stdio.h>

void printbits(unsigned int x){
  unsigned int mask = 1;

  for(int i = 0; i < 32; i++){
    if (i != 0 && !(i%4)) printf(" ");
    if (((x >> (31 - i)) & mask) == 1)
      printf("1");
    else
      printf("0");
  }
  printf("\n");
}
int bitcount(unsigned int x){
  unsigned int mask = 1;
  int count = 0;
  for(int i = 0; i < 32; i++){
      if(((x >> (31-i)) & mask) == 1)
	count++;
    }
	return count;
}

int main(){
  unsigned int x = 10;

  printf("%d %d\n", x, x^(1 << 2));

  x ^= 1 << 2;
  printf("%d %d\n", x, x^(1 << 2));

  printbits(x);
  printf("Bit count: %d\n", bitcount(x));

  return 0;
}
