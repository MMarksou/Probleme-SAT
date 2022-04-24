#include <stdio.h>
#include <stdlib.h>
#include "inout.h"
#include "SAT.h"

extern int *mot; //variable globale utilisée pour le backtraking
extern ensemble tmp_sat; //la même pour notre ensemble

int main(int argc, char const *argv[]) {
  FILE *src;

  //étape de lecture de fichier et d'écriture en mémoire
  src = fopen(argv[1], "r");
  if(!src) {
    perror("Lecture fichier : Pas de fichier sat\n");
    return -1;
  }

  ensemble ens = lecture_fichier(src);
  fclose(src);

  afficher_ensemble(&ens);

  //étape de vérification du problème

  // tmp_sat = ens;
  mot = calloc(ens.lit_max, sizeof(int));
  modification_signe(ens);
  printf("\nAffichage après modif \n");
  afficher_ensemble(&ens);
  //étape de suppression propre des structures

  // printf("%d", backtraking(0));

  // printf("\nAffichage après suppression des clauses unitaires : \n");
  // afficher_ensemble(&ensemble);
  // printf("%d\n", compter_clause(&ensemble));
  // printf("%d\n", compter_litteral(&ensemble));

  // free_ensemble(&tmp_sat);
  free_ensemble(&ens);
  // free(mot);

  return 0;
}
