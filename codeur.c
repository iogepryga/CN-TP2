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
  if(string_length(argv[3]) != k) {
    printf("k != len(message)");
    return -1;
  }
  int m = n - k;
  int* G = (int*)malloc(sizeof(int)*m*k);
  int* C = (int*)malloc(sizeof(int)*m);
  for(int i = 0 ; i < m*k; i++)
    G[i] = 1;
  for(int i = 0 ; i < m ; i++)
    G[i*m+(m-1-i)] = 0;


  printf("G =\n");
  for (int i = 0; i < k; i++) {
    for (size_t j = 0; j < m; j++)
      printf("%d ", G[m*i+j]);
    printf("\n");
  }
  

  for(int i = 0 ; i < m ; i++) {
    for(int j = 0 ; j < k ; j++) {
      if(G[j*m+i] == 1)
        C[i] = C[i] ^ caractobin(argv[3][j]) ;
    }
  }

  int im = 0,ic = 0;
  for(int i = 0; i < n ; i++) {
    if(puissance_de_2(ic) == i+1)
      printf("%d",C[ic++]);
    else 
      printf("%c",argv[3][im++]);
  }
  printf("\n");

  free(G);
  free(C);
}