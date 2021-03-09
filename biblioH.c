#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioH.h"
#include <math.h>

int fonctionClef(char* auteur){
  if (auteur){
    int res=0;
    int i;
    for(i=0;auteur[i]!='\0';i++){
      res+=auteur[i];
    }
    return res;
  }
  return -1;
}

LivreH* creer_livre(int num,char* titre,char* auteur){
  if(titre && auteur){
    LivreH* res=(LivreH*)malloc(sizeof(LivreH));
    if (!res){
      printf("erreur d'allocution de livreH\n");
      return NULL;
    }
    res->clef=fonctionClef(auteur);
    res->num=num;
    res->titre=(char*)malloc(sizeof(char)*(strlen(titre)+1));
    res->auteur=(char*)malloc(sizeof(char)*(strlen(auteur)+1));
    res->suivant=NULL;
    strcpy(res->titre,titre);
    strcpy(res->auteur,auteur);
    return res;
  }
  printf("problèmes de paramètre\n");
  return NULL;
}

void liberer_livre(LivreH* l){
  if(l){
    free(l->titre);
    free(l->auteur);
    free(l);
  }
}

BiblioH* creer_biblio(int m){
  BiblioH *b=malloc(sizeof(BiblioH));
  if (!b){
    printf("erreur d'allocution de biblioH\n");
    return NULL;
  }
  b->nE=0;
  b->m=m;
  b->T=(LivreH**)malloc(sizeof(LivreH*)*m);
  int i;
  for(i=0;i<m;i++){
    b->T[i]=NULL;
  }
  return b;
}

void liberer_biblio(BiblioH* b){
  if (b){
    int i;
    for(i=0;i<b->m;i++){
      LivreH *suiv;
      while(b->T[i]){
        suiv=b->T[i]->suivant;
        liberer_livre(b->T[i]);
        b->T[i]=suiv;
      }
    }
    free(b->T);
    free(b);
  }
}

int fonctionHachage(int cle,int m){
  double v=cle*(sqrt(5)-1)/2;
  return m*(v-(int)v);
}

void inserer(BiblioH* b,int num,char* titre, char *auteur){
  LivreH* l=creer_livre(num,titre,auteur);
  if(l){
    int a=fonctionHachage(l->clef,b->m);
    if(!b->T[a]){
      b->T[a]=l;
    }
    else{
      LivreH* c=b->T[a];
      while(c->suivant){
        c=c->suivant;
      }
      c->suivant=l;
    }
    b->nE=b->nE+1;
  }
}

void afficher_LivreH(LivreH *l){
    printf("LivreH clef=%d num=%d titre=%s auteur=%s\n",l->clef,l->num,l->titre,l->auteur);
}

void afficher_BiblioH(BiblioH* b){
  printf("BiblioH nE=%d m=%d\n",b->nE,b->m);
    int i;
    for(i=0;i<b->m;i++){
      printf("%d ",i);
      LivreH *l=b->T[i];
      while(l){
        afficher_LivreH(l);
        l=l->suivant;
      }
    }
    printf("\n");
}

BiblioH* charger_n_entrees(char* nomfic,int n){
  File *f=fopen(nomfic,'r');
  BiblioH *b=creer_biblio(n);
  int c;
  char *auteur;
  char *titre;
  int i;
  char ligne[500];
  for(i=0;i<n && fgets(ligne,500*sizeof(char),f)!=NULL;i++){
    if(sscanf(ligne,"%d %s %s",num,auteur,titre)==3){
      inserer(b,num,auteur,titre);
    }
    else{
      printf("Erreur \n");
      liberer_biblio(b);
      return NULL;
    }
  }
  if(i==n)
    return b;
  else{
    printf("Erreur \n");
    liberer_biblio(b);
    return NULL;
  }
}

void enregistrer_biblio
int main (){
  char* a="a";
  char* b="Salut";
  printf("%d \n",fonctionClef(a));
  printf("%d \n",fonctionClef(b));
  LivreH* l1=creer_livre(4,"abc","coucou");
  LivreH* l2=creer_livre(5,"abcd","coucou");
  LivreH* l3=creer_livre(18,"a","Bonjour");
  afficher_LivreH(l1);
  afficher_LivreH(l2);
  afficher_LivreH(l3);
  liberer_livre(l1);
  liberer_livre(l2);
  liberer_livre(l3);
  BiblioH *b1=creer_biblio(5);
  BiblioH *b2=creer_biblio(10);
  afficher_BiblioH(b1);
  afficher_BiblioH(b2);
  inserer(b1,4,"abc","coucou");
  inserer(b1,5,"abcd","coucou");
  inserer(b1,18,"a","Bonjour");
  afficher_BiblioH(b1);
  afficher_BiblioH(b2);
  liberer_biblio(b1);
  liberer_biblio(b2);
  printf("%d\n",fonctionHachage(fonctionClef("a"),10));
  printf("%d\n",fonctionHachage(fonctionClef("Salut"),10));
  printf("%d\n",fonctionHachage(500,4));
  return 0;
}
