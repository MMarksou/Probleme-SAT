#ifndef INOUT_H
#define INOUT_H

struct {
  char signe;
  char variable;
  litteral *nxt;
} litteral;

struct {
  int nb_element;
  clause *nxt;
} clause;

struct {
  clause *premier;
} ensemble;

//  permet de lire dans un fichier .sat et d'écrire son contenu dans une structure ensemble
ensemble lecture_fichier(FILE *);

// permet d'afficher le contenu d'une structure ensemble
void afficher_ensemble(ensemble);

// supression propre d'un ensemble
void free_ensemble(ensemble);

#endif
