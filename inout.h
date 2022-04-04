#ifndef INOUT_H
#define INOUT_H

#include <stdio.h>
#include <stdlib.h>



typedef struct litteral {
  char signe;
  int position;
  char variable;
  struct litteral *nxt;
} litteral;

typedef struct clause {
  int nb_element;
  struct litteral *premier;
  struct clause *nxt;
} clause;

typedef struct ensemble {
  struct clause *premier;
} ensemble;

//  permet de lire dans un fichier .sat et d'écrire son contenu dans une structure ensemble
ensemble lecture_fichier(FILE *);

// permet d'afficher le contenu d'une structure ensemble
void afficher_ensemble(ensemble);

clause* initialiser_clause();

litteral* initialiser_litteral();

// supression propre d'un ensemble
void free_ensemble(ensemble);

#endif
