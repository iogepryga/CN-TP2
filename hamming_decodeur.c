#include <stdio.h>
#include <stdlib.h>

#define caractobin(c) (c-'0')

int string_length(char *s) {
  int result = 0;
  for(int i = 0; *(s+i) != 0 ; i++)
    result++;
  return result;
}

// int puissance_de_2(int expo) {
//   int result = 1;
//   for(int i = 0 ; i < expo ; i++)
//     result *= 2;
//   return result;
// }

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







}