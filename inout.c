#include "inout.h"

extern char entete[50];

ensemble lecture_fichier(FILE *f) {
  ensemble ensemble;
  clause *c = (clause *) malloc(sizeof(clause));
  litteral *l = (litteral *) malloc(sizeof(litteral));
  l->signe = '1';

  ensemble.premier = c;
  c->premier = l;

  char tmp;
  char buf[1024];
  char *str = calloc(1,sizeof(char));
  int cpt_nb = 0;

  while(1) {
    tmp = fgetc(f);
    switch (tmp) {
      case EOF:
        c->nxt = NULL;
        free(str);
        free(l);
        return ensemble;
      case 'c':
        fgets(entete, 50, f);
        break;
      case 'p':
        // fgets(buf, 1024, f);
        fscanf(f, "%s %d", buf, &ensemble.lit_max);
        break;
      case '0':
        l->nxt = NULL;
        c->nb_element = cpt_nb;
        c->nxt = calloc(1,sizeof(clause));
        c = c->nxt;
        c->premier = calloc(1,sizeof(litteral));
        l = c->premier;
        l->signe = '1';
        cpt_nb = 0;
        break;
      case '-':
        l->signe = '0';
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
        l->position = atoi(str);
        l->nxt = calloc(1,sizeof(litteral));
        l = l->nxt;
        l->signe = '1';
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
