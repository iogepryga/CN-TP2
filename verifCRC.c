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
  long C = stringbintolonglong(argv[1]);

  printf("C : %s\n",argv[1]);
  printf("%ld\n",C);
  print_bin(C, lenmessage);
  printf("G : %s\n",argv[2]);
  printf("%ld\n",G);
  print_bin(G,d+1);
  printf("\n\n");


  for(int i = lenmessage; i >= 0; i--) {
    if(C >> (i+d)) {
      C ^= (G << i);
    }
  }
  printf("C : ");
  print_bin(C,lenmessage);

  if(C == 0)
    printf("C'EST BON , TOUT EST OK\n");
  else
    printf("IL Y A UNE ERREUR !!\n");

  return 0;
}