#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct a {
  struct a* pere;
  int poids;
  int origin;
} noeud , *p_noeud;

#define TAILLE_MSG 8
#define TAILLE_RECU (2*TAILLE_MSG)

#define NB_STATE 4

#define STATE 0
#define OUTPUT 1

int distance_hamm_bin_de_lg2(int a, int b) {
  return ((a&1) != (b&1)) + ((a&2) != (b&2));
}

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
  }
  if(string_length(argv[1]) > TAILLE_RECU) {
    printf("trop long\n");
    return -1;
  }else if(string_length(argv[1]) < TAILLE_RECU) {
    printf("trop court\n");
    return -1;
  }

  int msg[TAILLE_MSG];
  //On convertie en int par tranche de 2 bit,ex : 10 -> 2 - > msg[i]
  for(int i = 0; i < TAILLE_RECU ; i+=2) {
    int tmp = caractoint(argv[1][i]);
    int tmp2 = caractoint(argv[1][i+1]);
    if(tmp > 1 || tmp < 0 || tmp2 > 1 || tmp2 < 0)
      return -1;
    msg[i/2] = tmp*2+tmp2;
  }


  // POUR Go(1 1)
  //        (1 0)
  //        (1 1)
  // !!!!!!!!!!!!!!!!
  // Diagramme correspondant à G0
  int diag[4][2][2]; // 4 state , 2 possibité , 0->state 1->output
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


  // Initialisation
  noeud trellis[TAILLE_MSG+1][NB_STATE];
  for (int i = 0; i < TAILLE_MSG+1; i++) {
    for(int j = 0 ; j < NB_STATE ; j++) {
      trellis[i][j].pere=NULL;
      trellis[i][j].poids=INT_MAX;
      trellis[i][j].origin=-1;

    }
  }
  trellis[0][0].pere=(p_noeud)1;
  trellis[0][0].poids=0;

  // On construit les chemins (=viterbi)
  for (int imsg = 0; imsg < TAILLE_MSG; imsg++) {
    for(int istate = 0 ; istate < NB_STATE ; istate++) {
      if(trellis[imsg][istate].pere!=NULL) {
        for(int i = 0 ; i < 2 ; i++) {
          int dist = distance_hamm_bin_de_lg2(diag[istate][i][OUTPUT],msg[imsg]);
          int dest = diag[istate][i][STATE];
          if(trellis[imsg+1][dest].poids > (trellis[imsg][istate].poids + dist)  ) {
            trellis[imsg+1][dest].pere = &trellis[imsg][istate];
            trellis[imsg+1][dest].poids = trellis[imsg][istate].poids + dist;
            trellis[imsg+1][dest].origin = i;
          }
        }
      }
    }
  }

  //Quel est le meilleur chemin ?
  int select = 0;
  for(int i = 1 ; i < NB_STATE ;i++) {
    if(trellis[TAILLE_MSG][i].poids < trellis[TAILLE_MSG][select].poids)
      select = i;
  }

  //On remonte le chemin
  p_noeud courant = &trellis[TAILLE_MSG][select];
  int j = 0;
  while(courant->pere != (p_noeud)1) {
    msg[(TAILLE_MSG-1)-(j++)] = courant->origin;
    courant = courant->pere;
  }

  // On affiche
  for (int imsg = 0; imsg < TAILLE_MSG; imsg++)
    printf("%d",msg[imsg]);
  printf("\n");
}