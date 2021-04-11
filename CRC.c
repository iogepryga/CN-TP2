#include <stdio.h>
#include <stdlib.h>

#define caractobin(c) (c-'0')

int string_length(const char *s) {
  int result = 0;
  for(int i = 0; *(s+i) != 0 ; i++)
    result++;
  return result;
}

long puissance_de_2(int expo) {
  long result = 1;
  for(long i = 0 ; i < expo ; i++)
    result *= 2;
  return result;
}

long stringbintolonglong (const char* s) {
  int len = string_length(s);
  long result = 0;
  for(int i = len - 1 ; i >= 0 ; i--)
    result += puissance_de_2(i) * (s[len-1-i] - '0');
  return result;
}

void print_bin (long nb, int len) {
  for(int i = len - 1; i >= 0 ; i--) {
    printf("%ld", (nb >> i));
    if((nb >> i))
      nb -= puissance_de_2(i);
  }
  printf("\n");
}


int main(int argc, char **argv) {
  if(argc != 3) {
    printf("pas assez d'argument");
    return -1;
  }
  int d = string_length(argv[2]) - 1;
  int lenmessage = string_length(argv[1]);
  long G = stringbintolonglong(argv[2]);
  long D = stringbintolonglong(argv[1]);

  printf("D : %s\n",argv[1]);
  printf("%ld\n",D);
  print_bin(D, lenmessage);
  printf("G : %s\n",argv[2]);
  printf("%ld\n",G);
  print_bin(G,d+1);
  printf("\n\n");
  D <<= d;
  long final = D;
  printf("final : ");
  print_bin(final,lenmessage+d);
  printf("D : ");
  print_bin(D,lenmessage+d);

  for(int i = lenmessage; i >= 0; i--) {
    if(D >> (i+d)) {
      D ^= (G << i);
    }
  }
  printf("D : ");
  print_bin(D,lenmessage+d);
  printf("final : ");
  print_bin(final,lenmessage+d);

  final += D;
  printf("final : ");
  print_bin(final,lenmessage+d);

  return 0;
}