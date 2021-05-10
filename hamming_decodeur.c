#include <stdio.h>
#include <stdlib.h>

#define caractobin(c) (c-'0')

int string_length(char *s) {
  int result = 0;
  for(int i = 0; *(s+i) != 0 ; i++)
    result++;
  return result;
}

int puissance_de_2(int expo) {
  int result = 1;
  for(int i = 0 ; i < expo ; i++)
    result *= 2;
  return result;
}

int main(int argc, char **argv) {
  if(argc != 4) {
    printf("pas assez d'argument");
    return -1;
  }
  int n = atoi(argv[1]), k = atoi(argv[2]);
  if(string_length(argv[3]) != n) {
    printf("n != len(message)");
    return -1;
  }
  int m = n - k;
  printf("m = %d , k = %d , n = %d\n",m,k,n);

  printf("Reçu : \n");
  for(int i = 0 ; i < n ; i++) {
    printf("%c",argv[3][i]);
  }
  printf("\n");

  int syndrome = 0;
  for(int i = 1; i <= n ;i++)
    if(argv[3][i-1] == '1')
      syndrome += i;

  if(syndrome != 0) {
    if(argv[3][syndrome-1] == '0')
      argv[3][syndrome-1] = '1';
    else
      argv[3][syndrome-1] = '0';
  }

  printf("Apres correction : \n");
  for(int i = 0 ; i < n ; i++) {
    printf("%c",argv[3][i]);
  }
  printf("\n");

  printf("Msg : \n");
  for(int i = 1,expo = 0 ; i <= n ; i++) {
    if(puissance_de_2(expo) != i)
      printf("%c",argv[3][i-1]);
    else {
      expo++;
    }
  }
  printf("\n");







}