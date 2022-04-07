#ifndef SAT_H
#define SAT_H

#include "inout.h"

ensemble clause_unitaire(ensemble);
void litteral_pur(ensemble);
void supprimer_litteraux(ensemble, int);
int sat(ensemble);

#endif
