#include <stdio.h>
#include <stdlib.h>

int caractoint(char c){
  return (c-(int)'0');
}

char inttocarac(int c) {
  return (c+(int)'0');
}

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

int cestquoim(int k) { // algo bourrin faute de formule
  int ic = 0;
  for(int im = 0; im < k ;) {
    if(puissance_de_2(ic) == ic+im+1)
      ic++;
    else 
      im++;
  }
  return ic;
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
  int m;
  if(n == 0) {
    m = cestquoim(k);
    n = k + m;
  } else {
    m = n - k;
  }
  printf("m = %d , k = %d , n = %d\n",m,k,n);


  char* C = (char*)malloc(sizeof(char)*(n));

  for(int i = 0 ; i < m ; i++) {
    for(int j = i ; j < n ; j++) {
      if(   (   (    j<<(m-i)     )      >>m       )        <<i !=0  )
        C[puissance_de_2(i)-1] ^= inttocarac(   caractoint(  C[puissance_de_2(i)-1]  ) ^ caractoint(C[j])    );
    }
  }

  
  
    

  // for(int i = 0 ; i < m ; i++) {
  //   for(int j = 0 ; j < k ; j++) {
  //     if(G[j*m+i] == 1)
  //       C[i] = C[i] ^ caractobin(argv[3][j]) ;
  //   }
  // }
  // int im = 0,ic = 0;
  // for(int i = 0; i < n ; i++) {
  //   if(puissance_de_2(ic) == i+1)
  //     printf("%d",C[ic++]);
  //   else 
  //     printf("%c",argv[3][im++]);
  // }
  // printf("\n");
  // free(G);

  for (int i = 0; i < n; i++)
    printf("%c",C[i]);
  printf("\n");

  free(C);
}