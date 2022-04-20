#ifndef SUDOKU_ENCODER
#define SUDOKU_ENCODER

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

//Ce fichier permet de convertir une grille de sudoku en une instance de SAT
//On récupérère d'abord la grille via un fichier txt avant de le convertir
//en un problème de l'instance SAT et de l'exporter dans un fichier.

typedef struct grille {
  int nb; // N x N
  int bloc; // N
  int nb_sol; //nombre de solution dans le certificat
  int** matrice;
} grille;

grille* charger_grille(FILE *);

grille* init_grille(int);

void afficher_grille(grille *);

void supprimer_grille(grille *);

//fonction permettant d'obtenir un littéral en fonction de sa ligne, de sa
//colonne ainsi que de sa valeur effective
int val_lit(int, int, int, int);

//traduire un probleme de sudoku en un probleme SAT
int** encode(grille *);

//écrire le probleme SAT dans un fichier .sat
void ecriture_sat(int **, int);
#endif
