#include "SAT.h"

// Vérification et suppréssion des clauses unitaires
ensemble clause_unitaire(ensemble e)
{
  clause *clause_active = e.premier; // Conserve la clause concernée
  clause *clause_precedente = NULL;         // Conserve la clause précédente pour garder la chaine si la clause active est supprimée
  ensemble resultat; // Ensemble final

  while (clause_active->nxt != NULL)
  { // Parcours des clauses de la chaine
    if (clause_active->nb_element <= 1)
    { // Cas d'une clause unitaire
      if (clause_active == e.premier)
      { // Cas de la première clause vide (pas de précédent)
        // On enlève la première clause de la chaine
        e.premier = e.premier->nxt;
        clause_active = e.premier;
        /* Libérer la mémoire de la clause */
      }
      else
      { // On enlève la clause active de la chaine
        clause_active = clause_active->nxt;
        clause_precedente->nxt = clause_active;
        /* Libérer la mémoire de la clause */
      }
    }
    else
    {
      // La clause active devient la précédente et on passe à la clause suivante
      clause_precedente = clause_active;
      clause_active = clause_precedente->nxt;
    }
  }
  // free(clause_active);
  // free(clause_precedente);
  return resultat = e; // Retourne le nouvel ensemble de clauses
}

// Vérification de la présence de litteraux purs et suppréssion des clauses associées
void litteral_pur(ensemble e)
{
  /*
  clause* clause_active = ensemble->premier;
  clause* clause_precedente = NULL;
  litteral* litteral_actif, litteral_precedent;

  while(clause_active != NULL){
    litteral_actif = clause_active->premier;

    Si pas déjà apparu
      Conserver litteral_actif.valeur pour plus tard
      Parcourir les autres clauses
        Pour chaque litteral dans la clause
          Si litteral == litteral_actif
            Si litteral.signe != litteral_actif.signe
              Remettre à zéro le tableau des clauses concernées
              Passer au litteral_actif suivant
            Sinon conserver la clause concernée

      supprimer_litteraux(ensemble, litteral_actif->valeur);
      Remettre à zéro le tableau des clauses concernées
      Passer au litteral_actif suivant
  }
    */
  printf("OK");
}

void supprimer_litteraux(ensemble e, int valeur)
{
  //   clause *c;
  //   litteral *l;
  //   litteral *l_precedent;
  //
  //   c = ens.premier;
  //   while(c->nxt != NULL) {
  //     l = c->premier;
  //     while(l->nxt != NULL) {
  //       if(valeur == l->valeur) {
  //
  //       }
  //       else {
  //         printf("-%d\t", l->position);
  //       }
  //       l = l->nxt;
  //     }
  //     c = c->nxt;
  //     printf("\n");
  //   }
  //
  // }
  printf("###############\n");
}

// Prototype Algo SAT //
int sat(ensemble e)
{
  /*
  Pour chaque clause
    clause_unitaire(ensemble);
    litteral_pur(ensemble);

    Si plus de clauses
      return 1;
    Sinon Pour chaque litteral de la clause
      Si hypothèse de litteral == 1
        Si Appel récursif == 1
          return 1;
        Sinon hypothèse de litteral == 0
          Si Appel récursif == 1
            return 1;
          Sinon
            return 0;

    Si parcours de tous les litteraux
      return 0;
  */
  return 0;
}

int compter_clause(ensemble *e) {
  int i = 0;
  clause *c = e->premier;
  while(c->nxt != NULL) {
    i++;
    c = c->nxt;
  };

  return i;
}

int compter_litteral(ensemble *e) {
  int i = 0;
  clause *c = e->premier;
  while(c->nxt != NULL) {
    i+= c->nb_element;
    c = c->nxt;
  }
  return i;
}
