#include "inout.h"

ensemble lecture_fichier(FILE *f) {
  ensemble ensemble;
  clause *clause = calloc(1,sizeof(clause));
  litteral *litteral = calloc(1,sizeof(litteral));
  litteral->signe = '1';

  ensemble.premier = clause;
  clause->premier = litteral;

  char tmp;
  char buf[1024];
  char *str = calloc(1,sizeof(char));
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
        clause->nxt = calloc(1,sizeof(clause));
        clause = clause->nxt;
        clause->premier = calloc(1,sizeof(litteral));
        litteral = clause->premier;
        litteral->signe = '1';
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
        litteral->nxt = calloc(1,sizeof(litteral));
        litteral = litteral->nxt;
        litteral->signe = '1';
        free(str);
        str = calloc(1,sizeof(char));
        break;
    }
  }
}

void afficher_ensemble(ensemble *ens) {
  clause *c = ens->premier;
  while(c->nxt != NULL) {
    printf("###############\n");
    printf("Clause à %d élément(s)\n", c->nb_element);
    printf("###############\n");
    litteral *l = c->premier;
    while(l->nxt != NULL) {
      if(l->signe == '1') {
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

void free_ensemble(ensemble *ens) {
  clause *c_actu;
  clause *c_nxt;
  litteral *l_actu;
  litteral *l_nxt;

  c_actu = ens->premier;

  while(c_actu->nxt != NULL) {
    c_nxt = c_actu->nxt;
    l_actu = c_actu->premier;
    free(c_actu);
    while(l_actu->nxt != NULL) {
      l_nxt = l_actu->nxt;
      free(l_actu);
      l_actu = l_nxt;
    }
    free(l_actu);
    c_actu = c_nxt;
  }
  free(c_actu);
}
