#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entreeSortieLC.h"

Biblio* charger_n_entrees(char* nomFic,int n){
  Biblio *b=creer_biblio();
  FILE *f=fopen(nomFic,"r");
  int num;
  int i=0;
  char ligne[550];
  char auteur[300];
  char titre[200];
  while(i<n && fgets(ligne,550*sizeof(char),f) && sscanf(ligne,"%d %s %s",&num,titre,auteur)==3){
    inserer_en_tete(b,num,titre,auteur);
    i=i+1;
  }
  fclose(f);
  if(i==n)
    return b;
  else{
    printf("Erreur \n");
    liberer_biblio(b);
    return NULL;
  }
}


void enregistrer_biblio(Biblio *b, char* nomFic){
  if(b){
    FILE *f=fopen(nomFic,"a");
    Livre *l=b->L;
    while(l){
      fprintf(f,"%d %s %s \n",l->num,l->titre,l->auteur);
      l=l->suiv;
    }
    fclose(f);
  }
}

/*int main(){
  Biblio* b1=charger_n_entrees("GdeBiblio.txt",10);
  afficher_bibliotheque(b1);
  Biblio* b2=creer_biblio();
  inserer_en_tete(b1,150,"Salut","a");
  inserer_en_tete(b1,20,"c","ab");
  enregistrer_biblio(b1,"GdeBiblio.txt");
  liberer_biblio(b1);
  liberer_biblio(b2);
  return 0;
}*/
