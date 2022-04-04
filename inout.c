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

  char tmp;
  char buf[1024];

  while(1) {
    tmp = fgetc(f);
    switch (tmp) {
      case EOF:
        clause->nxt = NULL;
        return ensemble;
      case 'c':
        fgets(buf, 1024, f);
        break;
      case 'p':
        fgets(buf, 1024, f);
        break;
      case '0':
        litteral->nxt = NULL;
        clause->nxt = initialiser_clause();
        clause = clause->nxt;
        break;
      case '-':
        litteral->signe = '0';
        break;
      default:
        while(isdigit(tmp)){
        printf("%c\n", tmp);
        tmp = fgetc(f);
        }
        litteral->nxt = initialiser_litteral();
        litteral = litteral->nxt;
        break;
    }
  }
  return ensemble;
}
