#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioLC.h"

Livre* creer_livre(int num,char* titre,char* auteur){
  Livre *l=(Livre *)malloc(sizeof(Livre));
  if(!l){
    printf("Erreur d'allocution de l\n");
    return NULL;
  }
  l->num=num;
  l->titre=(char *)malloc((strlen(titre)+1)*sizeof(char));
  if (!l->titre){
    printf("Erreur d'allocution de titre de l\n");
    free(l);
    return NULL;
  }
  strcpy(l->titre,titre);
  l->auteur=(char *)malloc((strlen(auteur)+1)*sizeof(char));
  if (!l->auteur){
    printf("Erreur d'allocution de auteur de l\n");
    free(l->titre)
    free(l);
    return NULL;
  }
  strcpy(l->auteur,auteur);
  l->suiv=NULL;
  return l;
}

void liberer_livre(Livre *l){
  if(l){
    free(l->auteur);
    free(l->titre);
    free(l);
  }
}

Biblio* creer_biblio(){
  Biblio *b=(Biblio *)malloc(sizeof(Biblio));
  if(!b){
    printf("Erreur d'allocution de la mémoire pour Biblio\n");
    printf NULL;
  }
  b->L=NULL;
  return b;
}

void liberer_biblio(Biblio *b){
  if(b){
    Livre *p=b->L->suiv;
    while(p){
      free(L);
      L=p;
      p=p->suiv;
    }
    free(b);
  }
}

void inserer_en_tete(Biblio *b, int num,char *titre,char * auteur){
  if(!b){
     Livre *l=creer_livre(num,titre,auteur);
     if (!l) return;
     Livre *p=b->L;
     l->suiv=*p;
     b->L=l;
  }
}
