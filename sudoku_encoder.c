#include "sudoku_encoder.h"

grille* charger_grille(FILE *f) {
  grille *g;
  int nb_grille;
  fscanf(f, "%d", &nb_grille);
  int taille_ligne = nb_grille*nb_grille;

  g = init_grille(taille_ligne);
  g->bloc = nb_grille;

  int **mat = g->matrice;

  int i=0, j=0, nombre;
  while(fscanf(f, "%d", &nombre) != EOF) {
    mat[i][j] = nombre;
    if(mat[i][j] != 0)
      g->nb_sol++;

    j++;

    if(j == taille_ligne) {
      j = 0;
      i += 1;
    }
  }
  return g;
}

grille* init_grille(int nb) {
  grille *g;

  g = malloc(sizeof(grille));
  g->matrice = calloc(nb,sizeof(int *));

  g->nb = nb;

  g->nb_sol = 0;

  for(int i=0; i<nb; i++) g->matrice[i] = calloc(nb, sizeof(int));

  return g;

}

void supprimer_grille(grille *g) {
  for(int i=0; i<g->nb; i++) free(g->matrice[i]);
  free(g->matrice);
  free(g);
}

void afficher_grille(grille *g) {
  for(int i=0; i<g->nb; i++){
    for(int j=0; j<g->nb; j++)
      printf("%d\t", g->matrice[i][j]);
    printf("\n");
    }
}

int val_lit(int ligne, int colonne, int valeur, int nb) {
  return (ligne-1)*nb*nb+(colonne-1)*nb+valeur;
}

//le nombre de clauses totales sans les clauses du certificat
int nb_clauses(int nb) {
  //nb de clauses à n littéraux
  int b1 = 6*nb*nb;
  //nb de clauses à 2 littéraux
  int b2 = (nb*nb)*((nb*(nb-1))/2);
  return b1+b2;
}

//Ceci est une fonction d'un code python dont je me suis fortement inspiré
//On sépare les clauses en 6 grandes familles de clause :
//C1 = la case a au moins une valeur
//C2 = la case a au plus une valeur
//C3 = chaque ligne a une valeur
//C4 = chaque colonne a une valeur
//C5 = chaque bloc a une valeur
//C6 = la solution respecte le certificat donné
//Source : https://users.aalto.fi/~tjunttil/2020-DP-AUT/notes-sat/solving.html
int** encode(grille *g) {
  int **res = (int **)calloc(nb_clauses(g->nb)+(g->nb_sol)+1,sizeof(int*));
  int *tmp;
  int cpt_lit = 1;
  int cpt_clause = 0;

  //C1 | C2
  for(int l=1; l< (g->nb)+1; l++){
    for(int c=1; c<(g->nb)+1; c++) {
      //si une cellule (l,c) a au moins une valeur
      tmp = calloc((g->nb)+1, sizeof(int));
      tmp[0] = g->nb;
      for(int v=1; v<(g->nb)+1; v++) {
        tmp[cpt_lit] = val_lit(l, c, v, g->nb);
        cpt_lit++;
      }
      //ajout de la clause à n éléments dans res
      res[cpt_clause] = tmp;
      cpt_clause++;
      cpt_lit = 1;
      //si une cellule (l,c) a au plus une valeur
      for(int v=1; v<(g->nb)+1; v++) {
        for(int w=v+1; w<(g->nb)+1; w++) {
          tmp = calloc(3, sizeof(int));
          tmp[0] = 2;
          tmp[1] = -val_lit(l, c, v, g->nb);
          tmp[2] = -val_lit(l, c, w, g->nb);

          //ajout dans res et libération de tmp
          res[cpt_clause] = tmp;
          cpt_clause++;
        }
      }
    }
  }
  printf("%d %d\n", nb_clauses(g->nb)+g->nb_sol, cpt_clause);
  //C3 | C4 | C5
  for(int v=1; v<(g->nb)+1; v++) {
    //si chaque ligne a une valeur v
    for(int l=1; l< (g->nb)+1; l++){
      tmp = calloc((g->nb)+1, sizeof(int));
      tmp[0] = g->nb;
      for(int c=1; c<(g->nb)+1; c++) {
          tmp[cpt_lit] = val_lit(l, c, v, g->nb);
          cpt_lit++;
      }
      //ajout de la clause à n éléments dans res
      res[cpt_clause] = tmp;
      cpt_clause++;
      cpt_lit = 1;
    }
    //si chaque colonne a une valeur v
    for(int c=1; c< (g->nb)+1; c++){
      tmp = calloc((g->nb)+1, sizeof(int));
      tmp[0] = g->nb;
      for(int l=1; l<(g->nb)+1; l++) {
          tmp[cpt_lit] = val_lit(l, c, v, g->nb);
          cpt_lit++;
      }
      //ajout de la clause à n éléments dans res
      res[cpt_clause] = tmp;
      cpt_clause++;
      cpt_lit = 1;
    }
    //si chaque bloc a une valeur v
    //on sélectionne chaque bloc un par un
    for(int bl=0; bl<(g->bloc); bl++) {
      for(int bc=0; bc<(g->bloc); bc++) {
        //on crée la condition de valeur à chaque case du bloc sélectionné
        for(int lb=1; lb<(g->bloc)+1; lb++) {
          tmp = calloc((g->nb)+1, sizeof(int));
          tmp[0] = g->nb;
          for(int cb=1; cb<(g->bloc)+1; cb++){
            tmp[cpt_lit] = val_lit(bl*(g->bloc)+lb, bc*(g->bloc)+cb,v, g->nb);
            cpt_lit++;
          }
          //ajout de la clause à n éléments dans res
          res[cpt_clause] = tmp;
          cpt_clause++;
          cpt_lit = 1;
        }
      }
    }
  }
  printf("%d %d\n", nb_clauses(g->nb)+g->nb_sol, cpt_clause);
  //C6
  //Notre problème doit respecter le certificat, on écrit alors des clauses
  //unitaires faisait référence aux littéraux concernés
  for(int l=1; l< (g->nb)+1; l++){
    for(int c=1; c<(g->nb)+1; c++) {
      if(g->matrice[l-1][c-1] != 0){
        tmp = calloc(2, sizeof(int));
        tmp[0] = 1;
        tmp[1] = val_lit(l, c, g->matrice[l-1][c-1], g->nb);
        res[cpt_clause] = tmp;
        cpt_clause++;
      }
    }
  }
  printf("%d %d\n", nb_clauses(g->nb)+g->nb_sol, cpt_clause);
  res[nb_clauses(g->nb)+g->nb_sol] = NULL;
  return res;
}

void ecriture_sat(int **sat, int nb){
  FILE *f = NULL;
  int i=0;
  f = fopen("tmp.sat", "w");
  fprintf(f, "c sudoku %d x %d en une instance SAT\n", nb, nb);
  while(sat[i] != NULL) {
    if(sat[i][0] == nb*nb) {
      for(int j=1; j<nb*nb; j++)
        fprintf(f, "%d ", sat[i][j]);
      fprintf(f, "0\n");
    }
    if(sat[i][0] == 2) {
      fprintf(f, "%d %d 0\n", sat[i][1], sat[i][2]);
    }
    if(sat[i][0] == 1) {
      fprintf(f, "%d 0\n", sat[i][1]);
    }
    i++;
  }
  fclose(f);
}

void supprimer_sat(int **sat){
  int i=0;
  while(sat[i] != NULL){
    free(sat[i]);
  }
  free(sat);
}

int main(int argc, char const *argv[]) {
  grille *g;
  FILE *f = fopen(argv[1], "r");

  //chargement du fichier de la grille
  if(f){
    g = charger_grille(f);
    afficher_grille(g);
  }
  fclose(f);

  //encodage en instance de SAT et écriture dans un ficher .sat
  int **sat;
  sat = encode(g);
  ecriture_sat(sat, g->bloc);

  //suppression de la mémoire
  supprimer_sat(sat);
  supprimer_grille(g);
  return 0;
}
