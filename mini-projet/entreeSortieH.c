#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entreeSortieH.h"




BiblioH* charger_n_entrees_H(char* nomfic,int n){
  FILE *f=fopen(nomfic,"r");
  BiblioH *b=creer_biblio_H(n);
  int num;
  char auteur[300];
  char titre[200];
  int i=0;
  char ligne[500];
  while(i<n && fgets(ligne,500*sizeof(char),f) && sscanf(ligne,"%d %s %s",&num,titre,auteur)==3){
    inserer_H(b,num,auteur,titre);
    i=i+1;
  }
  fclose(f);
  if(i==n)
    return b;
  else{
    printf("Erreur \n");
    liberer_biblio_H(b);
    return NULL;
  }
}

void enregistrer_biblio_H(BiblioH *b,char *nomfic){
  FILE *f=fopen(nomfic,"a");
  int i;
  for(i=0;i<b->m;i++){
    LivreH *l=b->T[i];
    while(l){
      fprintf(f,"%d %s %s\n",l->num,l->titre,l->auteur);
      l=l->suivant;
    }
  }
  fclose(f);
}
