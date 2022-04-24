#include "SAT.h"

extern int *mot; //variable globale utilisée pour le backtraking
extern ensemble tmp_sat; //la même pour notre ensemble
extern char entete[50];
int start = 1;

// Vérification et suppréssion des clauses unitaires
ensemble clause_unitaire(ensemble e){
  clause *clause_active = e.premier; // Conserve la clause concernée
  clause *clause_precedente = NULL;  // Conserve la clause précédente pour garder la chaine si la clause active est supprimée
  ensemble resultat;                 // Ensemble final

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
  return resultat = e; // Retourne le nouvel ensemble de clauses
}

// Vérification de la présence de litteraux purs et suppréssion des clauses associées
// en utilisant la structure valeur qui permet de garder une liste des littéraux à supprimer 
ensemble litteral_pur(ensemble e)
{
  ensemble resultat;
  clause *clause_active = e.premier;
  litteral *litteral_actif;
  valeurs *vals = initialiser_valeurs();
  valeurs *vals_actif;
  valeurs *vals_parcours;
  valeurs *vals_resultat;
  valeurs *vals_resultat_actif;
  int litteral_pur = 0;

  vals_actif = vals;

  // Premier parcours pour récupérer les littéraux
  while (clause_active != NULL)
  {
    litteral_actif = clause_active->premier;

    while (litteral_actif != NULL)
    {
      if (litteral_actif->signe == '1')
      {
        vals_actif->val = litteral_actif->position;
      }
      else
      {
        vals_actif->val = -litteral_actif->position;
      }

      vals_actif->nxt = initialiser_valeurs();
      vals_actif = vals_actif->nxt;

      litteral_actif = litteral_actif->nxt;
    }
    clause_active = clause_active->nxt;
  }

  vals_actif = vals;
  vals_resultat = initialiser_valeurs();
  vals_resultat_actif = vals_resultat;

  // Deuxième parcours pour ne garder que les littéraux purs
  while (vals_actif != NULL)
  {
    vals_parcours = vals;
    while (vals_parcours != NULL)
    {
      if (abs(vals_actif->val) == abs(vals_parcours->val))
      {
        if (vals_actif->val != vals_parcours->val)
        {
          litteral_pur = 1;
        }
      }
      vals_parcours = vals_parcours->nxt;
    }
    if (litteral_pur == 0)
    {
      vals_parcours = vals;

      while (vals_parcours != NULL)
      {
        if (abs(vals_actif->val) == abs(vals_parcours->val))
        {
          vals_resultat_actif->val = vals_actif->val;
          vals_resultat_actif->nxt = initialiser_valeurs();
          vals_resultat_actif = vals_resultat_actif->nxt;
          break;
        }

        vals_parcours = vals_parcours->nxt;
      }
    }
    litteral_pur = 0;
    vals_actif = vals_actif->nxt;
  }
  // suppression des littéraux et libération de mémoire
  resultat = supprimer_litteraux(e, vals_resultat);
  free_valeurs(vals);
  free_valeurs(vals_resultat);
  return resultat;
}

// Supprime les littéraux présents dans la structure valeurs
ensemble supprimer_litteraux(ensemble e, valeurs *vals)
{
  ensemble resultat;
  valeurs *vals_active = vals;
  clause *clause_active;
  litteral *litteral_actif;
  litteral *litteral_precedent = NULL;

  while (vals_active->nxt != NULL)
  {
    clause_active = e.premier;
    while (clause_active->nxt != NULL)
    {
      litteral_actif = clause_active->premier;
      litteral_precedent = NULL;
      while (litteral_actif->nxt != NULL)
      {
        if (abs(litteral_actif->position) == abs(vals_active->val))
        {
          if (litteral_actif == clause_active->premier)
          {

            clause_active->premier = clause_active->premier->nxt;
            litteral_actif = clause_active->premier;
          }
          else
          {
            litteral_actif = litteral_actif->nxt;
            litteral_precedent->nxt = litteral_actif;
          }
        }
        else
        {
          litteral_precedent = litteral_actif;
          litteral_actif = litteral_actif->nxt;
        }
      }
      clause_active = clause_active->nxt;
      litteral_actif = clause_active->premier;
      litteral_precedent = NULL;
    }
    vals_active = vals_active->nxt;
  }
  return resultat = e;
}

// Initialise un élément de la structure valeurs
valeurs *initialiser_valeurs()
{
  valeurs *val = malloc(sizeof(valeurs));

  val->val = 0;
  val->nxt = NULL;

  return val;
}

// Affiche les éléments de la structure valeurs
void afficher_valeurs(valeurs *val)
{
  valeurs *v1 = val;
  printf("\n###############\n");
  while (v1 != NULL)
  {
    printf("%d\n", v1->val);
    v1 = v1->nxt;
  }
  printf("###############\n");
}

// Libère la mémoire liée aux éléments de la structure valeurs
void free_valeurs(valeurs *val)
{
  valeurs *v1;
  valeurs *v2;

  v1 = val;
  while (v1 != NULL)
  {
    v2 = v1;
    v1 = v2->nxt;
    free(v2);
  }
  free(v1);
}

// Retourne le nombre de clauses de l'ensemble
int compter_clause(ensemble *e) {
  int i = 0;
  clause *c = e->premier;
  while(c->nxt != NULL) {
    i++;
    c = c->nxt;
  };

  return i;
}

// Retourne le nombre de littéraux de l'ensemble
int compter_litteral(ensemble *e) {
  int i = 0;
  clause *c = e->premier;
  while(c->nxt != NULL) {
    i+= c->nb_element;
    c = c->nxt;
  }
  return i;
}

//Permet la réduction d'un ensemble en vérifiant les clauses unitaires et les
//littéraux purs. Tant qu'il y a du changement (chose qu'on peut savoir en
//en comptant le nombre de clauses et de littéraux restants), on continue à
//réduire. L'algo s'arrête quand il n'y a pas eu de modification après un tour
//de boucle.
ensemble reduction_ensemble(ensemble e) {
  int p_nb_clauses = compter_clause(&e); //dépend du nb de clauses
  int p_nb_litteraux = compter_litteral(&e); //dépend du nb de clauses
  int s_nb_clauses = 0;
  int s_nb_litteraux = 0;
  ensemble resultat;

  resultat = clause_unitaire(e);
  resultat = litteral_pur(e);
  s_nb_clauses = compter_clause(&e); //dépend du nb de clauses
  s_nb_litteraux = compter_litteral(&e); //dépend du nb de clauses

  while(p_nb_clauses != s_nb_clauses || p_nb_litteraux != s_nb_litteraux) {
    p_nb_clauses = s_nb_clauses;
    p_nb_litteraux = s_nb_litteraux;
    resultat = clause_unitaire(e);
    resultat = litteral_pur(e);
    s_nb_clauses = compter_clause(&e); //dépend du nb de clauses
    s_nb_litteraux = compter_litteral(&e); //dépend du nb de clauses
  }

  return resultat;
}

// Fonction de backtracking si un ensemble n'est pas validé par
// la suppression des clauses unitaires et des litéraux purs
int backtraking(int pos) {
  if(start){
    if(pos == tmp_sat.lit_max){ 
      
      // Fonction incomplète
      
      start = 0;     
      return 1;
    } 
    mot[pos] = 0;
    backtraking(pos+1);
    mot[pos] = 1;
    backtraking(pos+1);
  }
}

//fonction permettant la copie d'une ensemble
ensemble copie_ensemble(ensemble e) {
  ensemble cp_ens;
  cp_ens.lit_max = e.lit_max;
  clause *cp_c = (clause *) malloc(sizeof(clause));
  clause *c = e.premier;

  cp_ens.premier = cp_c;

  while(c->nxt != NULL) {
    litteral *l = c->premier;
    litteral *cp_l = (litteral *) malloc(sizeof(litteral));
    cp_c->premier = cp_l;
    cp_c->nb_element = c->nb_element;

    while(l->nxt != NULL) {
      cp_l->signe = l->signe;
      cp_l->position = l->position;

      l = l->nxt;
      if(l == NULL){
        cp_l->nxt = NULL;
      }
      else {
        cp_l->nxt = calloc(1,sizeof(litteral));
        cp_l = cp_l->nxt;
      }
    }
    c = c->nxt;
    if(c == NULL) {
      cp_c->nxt = NULL;
    }
    else {
      cp_c->nxt = calloc(1,sizeof(clause));
      cp_c = cp_c->nxt;
    }
  }

  return cp_ens;
}

//selon le contenu du mot binaire, cela modifie les signes de nos littéraux
//ce qui va nous permettre par la suite de calculer la solution
void modification_signe(ensemble e) {
  clause *c = e.premier;
  while(c->nxt != NULL) {
    litteral *l = c->premier;
    while(l->nxt != NULL) {
      if(l->signe == '0'){
        if(mot[(l->position)-1]) {
          l->signe = '0';
        }
        else {
          l->signe = '1';
        }
      }
      else {
        l->signe = (char) mot[(l->position)-1];
      }
      l = l->nxt;
    }
    c = c->nxt;
  }
}

// Ecrit dans un fichier l'ensemble final
void ecriture_solution_sat(ensemble e) {
  FILE *src;
  int cpt = 0;

  src = fopen("resultat.sat", "w");
  fprintf(src, "c%s\n", entete);

  for(int i=1; i<e.lit_max+1; i++){
    if(cpt == 20){
      fprintf(src, "\n");
      cpt = 0;
    }
    if(mot[i-1] == 0) {
      fprintf(src, "%d ", -i);
    }
    else {
      fprintf(src, "%d ", i);
    }
    cpt++;
  }
  fclose(src);
}
