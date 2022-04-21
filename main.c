#include <stdio.h>
#include <stdlib.h>
#include "inout.h"
#include "SAT.h"


int main(int argc, char const *argv[]) {
  FILE *src;

  //étape de lecture de fichier et d'écriture en mémoire
  src = fopen(argv[1], "r");
  if(!src) {
    perror("Lecture fichier : Pas de fichier sat\n");
    return -1;
  }

  ensemble ensemble = lecture_fichier(src);
  fclose(src);

  afficher_ensemble(&ensemble);

  ensemble = clause_unitaire(ensemble);

  ensemble = litteral_pur(ensemble);

  //étape de vérification du problème

  //étape de suppression propre des structures

  printf("\nAffichage après suppression des clauses unitaires : \n");
  afficher_ensemble(&ensemble);
  // printf("%d\n", compter_clause(&ensemble));
  // printf("%d\n", compter_litteral(&ensemble));

  free_ensemble(&ensemble);

  return 0;
}
