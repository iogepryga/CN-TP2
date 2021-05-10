#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TAILLE_MSG 8

#define NB_STATE 4

#define STATE 0
#define OUTPUT 1

int string_length(char *s) {
  int result = 0;
  for(int i = 0; *(s+i) != 0 ; i++)
    result++;
  return result;
}

int caractoint(char c){
  return (c-(int)'0');
}

char inttocarac(int c) {
  return (c+(int)'0');
}

int main(int argc, char **argv) {
  if(argc != 2) {
    printf("pas assez d'argument\n");
    return -1;
  } else if(string_length(argv[1]) > TAILLE_MSG) {
    printf("trop long\n");
    return -1;
  } else if(string_length(argv[1]) < TAILLE_MSG) {
    printf("trop court\n");
    return -1;
  }


  int diag[NB_STATE][2][2]; // 4 state , 2 possibité , 0->state 1->output
  diag[0][0][STATE] = 0; 
  diag[0][0][OUTPUT] = 0;
  diag[0][1][STATE] = 2; 
  diag[0][1][OUTPUT] = 3;

  diag[1][0][STATE] = 0; 
  diag[1][0][OUTPUT] = 3;
  diag[1][1][STATE] = 2; 
  diag[1][1][OUTPUT] = 0;

  diag[2][0][STATE] = 1; 
  diag[2][0][OUTPUT] = 2;
  diag[2][1][STATE] = 3; 
  diag[2][1][OUTPUT] = 1;

  diag[3][0][STATE] = 1; 
  diag[3][0][OUTPUT] = 1;
  diag[3][1][STATE] = 3; 
  diag[3][1][OUTPUT] = 2;

  int state_courant = 0;
  for(int i = 0 ; i < TAILLE_MSG ; i ++) {
    int tmp = diag[state_courant][caractoint(argv[1][i])][OUTPUT];
    printf("%d%d ",tmp/2,tmp%2);
    state_courant = diag[state_courant][caractoint(argv[1][i])][STATE];
  }
  printf("\n");
}