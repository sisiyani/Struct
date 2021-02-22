#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioLC.h"

Biblio* charger_n_entrees(char* nomfic,int n){
  Biblio *b=creer_biblio();
  File *f=fopen(nomFic,"r");
  int num;
  char *titre;
  char *auteur;
  while(sscanf(f,"%d %s %s",num,titre,auteur)){
    inserer_en_tete(b,num,titre,auteur);
  }
  fclose(f);
  return b;
}

void enregistrer_biblio(Biblio *b, char* nomfic){
  if(b){
    File *f=fopen(nomFic,"w");
    Livre *l=b->L;
    while(l){
      fwrite(f,"%d %s %s \n",l->num,l->titre,l->auteur);
    }
    fclose(f);
  }
