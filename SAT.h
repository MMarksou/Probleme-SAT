#ifndef SAT_H
#define SAT_H

#include "inout.h"

int *mot;
ensemble tmp_sat;

// Liste chainée représentant les littéraux purs à supprimer
typedef struct valeurs{
  int val;
  struct valeurs *nxt;
} valeurs;

ensemble clause_unitaire(ensemble);

ensemble litteral_pur(ensemble);

ensemble supprimer_litteraux(ensemble, valeurs*);

valeurs* initialiser_valeurs();

void afficher_valeurs(valeurs*);

void free_valeurs(valeurs*);

int compter_clause(ensemble *);

int compter_litteral(ensemble *);

int sat(ensemble);

ensemble reduction_ensemble(ensemble);

int backtraking(int);

#endif
