#ifndef SAT_H
#define SAT_H

#include "inout.h"

ensemble clause_unitaire(ensemble);

void litteral_pur(ensemble);

void supprimer_litteraux(ensemble, int);

int compter_clause(ensemble *);

int compter_litteral(ensemble *);

int sat(ensemble);

#endif
