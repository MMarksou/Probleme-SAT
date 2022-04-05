#include "SAT.h"

// Vérification et suppréssion des clauses unitaires
void clause_unitaire(ensemble ensemble)
{

  clause *clause_active = ensemble.premier; // Conserve la clause concernée
  clause *clause_precedente = NULL;         // Conserve la clause précédente pour garder la chaine si la clause active est supprimée

  while (clause_active->nxt != NULL)
  { // Parcours des clauses de la chaine
    if (clause_active->nb_element <= 1)
    { // Cas d'une clause unitaire
      if (clause_active == ensemble.premier)
      { // Cas de la première clause vide (pas de précédent)

        // On enlève la première clause de la chaine
        ensemble.premier = clause_active->nxt;
        free(clause_active);
        clause_precedente = ensemble.premier;
      }
      else
      {

        // On enlève la clause active de la chaine
        clause_precedente->nxt = clause_active->nxt;
        free(clause_active);
        clause_active = clause_precedente;
      }
    }

    // La clause active devient la précédente et on passe à la clause suivante
    clause_precedente = clause_active;
    clause_active = clause_active->nxt;
  }
}

// Vérification de la présence de litteraux purs et suppréssion des clauses associées
void litteral_pur(ensemble ensemble)
{
  /*
  clause clause_active = ensemble->premier;
  clause clause_precedente = NULL;

  while(clause_active != NULL){
    litteral litteral_actif = clause_active->premier_litteral;

    Si pas déjà apparu
      Conserver litteral_actif.valeur pour plus tard
      Parcourir les autres clauses
        Pour chaque litteral dans la clause
          Si litteral == litteral_actif
            Si litteral.signe != litteral_actif.signe
              Remettre à zéro le tableau des clauses concernées
              Passer au litteral_actif suivant
            Sinon conserver la clause concernée

      Supprimer les litteraux dans les clauses concernées
      Remettre à zéro le tableau des clauses concernées
      Passer au litteral_actif suivant
  }
    */
  printf("OK");
}

// Prototype Algo SAT //
int sat(ensemble ensemble)
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
