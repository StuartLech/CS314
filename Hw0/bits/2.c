#include <stdio.h>
void printbits(unsigned int x){
  unsigned int mask =  1U;

  for(int i = 0; i < 32; i++) {
    if (i != 0 && i % 4 == 0) printf(" ");
    if((x >> (31 - i)) & mask)
      printf("1");
    else
      printf("0");
  }
  printf("\n");
}

int bitcount(unsigned int x) {
  unsigned int mask = 1U;
  int count = 0;
  for(int i=0; i < 32; i++){
    if ((x >> (31 - i)) & mask)
      count++;
  }
  return count;
}

unsigned int invert(unsigned int x, int p, int n) {
  unsigned int mask =((1U << n) - 1) << (p - n + 1);
  return x ^ mask;
}

int main() {
  unsigned int x = 0x0FABAA;
  unsigned int result = invert(x, 7, 5);
  printbits(x);
  printbits(result);

  printf("%d %d\n", x, x^(1U << 2));
  x ^= 1U << 2;
  printf("%d %d\n", x, x^(1U << 2));
  printbits(x);
  printf("Bit count: %d\n", bitcount(x));

  return 0;
}
