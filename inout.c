#include "inout.h"

clause* initialiser_clause() {
  clause *clause = malloc(sizeof(clause));

  clause->nb_element = 0;
  clause->nxt = NULL;

  return clause;
}

litteral* initialiser_litteral() {
  litteral *litteral = malloc(sizeof(litteral));

  litteral->signe = '1';
  litteral->position = 0;
  litteral->variable = ' ';
  litteral->nxt = NULL;

  return litteral;
}

ensemble lecture_fichier(FILE *f) {
  ensemble ensemble;
  clause *clause = initialiser_clause();
  litteral *litteral = initialiser_litteral();

  ensemble.premier = clause;
  clause->premier = litteral;

  char tmp;
  char buf[1024];
  char *str = (char *) malloc(sizeof(1));
  int cpt_nb = 0;

  while(1) {
    tmp = fgetc(f);
    switch (tmp) {
      case EOF:
        clause->nxt = NULL;
        free(str);
        free(litteral);
        return ensemble;
      case 'c':
        fgets(buf, 1024, f);
        break;
      case 'p':
        fgets(buf, 1024, f);
        break;
      case '0':
        litteral->nxt = NULL;
        clause->nb_element = cpt_nb;
        clause->nxt = initialiser_clause();
        clause = clause->nxt;
        clause->premier = initialiser_litteral();
        litteral = clause->premier;
        cpt_nb = 0;
        break;
      case '-':
        litteral->signe = '0';
        break;
      case '\n':
        break;
      case '%':
        fgetc(f);
        fgetc(f);
        break;
      default:
        cpt_nb ++;
        while(tmp != ' ' && tmp != EOF){
          str = realloc(str, strlen(str)+1);
          str[strlen(str)] = tmp;
          tmp = fgetc(f);
        }
        litteral->position = atoi(str);
        litteral->nxt = initialiser_litteral();
        litteral = litteral->nxt;
        free(str);
        str = (char *) malloc(sizeof(1));
        break;
    }
  }
}

void afficher_ensemble(ensemble ens) {
  clause *c;
  litteral *l;
  char signe;

  c = ens.premier;
  while(c->nxt != NULL) {
    printf("###############\n");
    printf("Clause à %d élément(s)\n", c->nb_element);
    printf("###############\n");
    l = c->premier;
    while(l->nxt != NULL) {
      signe = l->signe;
      if(signe == '1') {
        printf("%d\t", l->position);
      }
      else {
        printf("-%d\t", l->position);
      }
      l = l->nxt;
    }
    c = c->nxt;
    printf("\n");
  }
  printf("###############\n");
}

void free_ensemble(ensemble ens) {
  clause *c1;
  clause *c2;
  litteral *l1;
  litteral *l2;

  c1 = ens.premier;
  while(c1->nxt != NULL) {
    c2 = c1;
    c1 = c2->nxt;
    l1 = c2->premier;
    free(c2);
    while(l1->nxt != NULL) {
      l2 = l1;
      l1 = l2->nxt;
      free(l2);
    }
    free(l1);
  }
  free(c1);
}
