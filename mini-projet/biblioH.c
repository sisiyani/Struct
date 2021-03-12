#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "biblioH.h"

int fonctionClef_H(char* auteur){
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

LivreH* creer_livre_H(int num,char* titre,char* auteur){
  if(titre && auteur){
    LivreH* res=(LivreH*)malloc(sizeof(LivreH));
    if (!res){
      printf("erreur d'allocution de livreH\n");
      return NULL;
    }
    res->clef=fonctionClef_H(auteur);
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

void liberer_livre_H(LivreH* l){
  if(l){
    free(l->titre);
    free(l->auteur);
    free(l);
  }
}

BiblioH* creer_biblio_H(int m){
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

void liberer_biblio_H(BiblioH* b){
  if (b){
    int i;
    for(i=0;i<b->m;i++){
      LivreH *suiv;
      while(b->T[i]){
        suiv=b->T[i]->suivant;
        liberer_livre_H(b->T[i]);
        b->T[i]=suiv;
      }
    }
    free(b->T);
    free(b);
  }
}

int fonctionHachage_H(int cle,int m){
  double v=cle*(sqrt(5)-1)/2;
  return m*(v-(int)v);
}

void inserer_H(BiblioH* b,int num,char* titre, char *auteur){
  LivreH* l=creer_livre_H(num,titre,auteur);
  if(l){
    int a=fonctionHachage_H(l->clef,b->m);
    l->suivant=b->T[a];
    b->T[a]=l;
    }
    b->nE=b->nE+1;
}


void afficher_LivreH_H(LivreH *l){
  if(l){
    printf("LivreH clef=%d num=%d titre=%s auteur=%s\n",l->clef,l->num,l->titre,l->auteur);
  }
}

void afficher_BiblioH_H(BiblioH* b){
  printf("BiblioH nE=%d m=%d\n",b->nE,b->m);
    int i;
    for(i=0;i<b->m;i++){
      printf("%d ----------------------\n",i);
      LivreH *l=b->T[i];
      while(l){
        afficher_LivreH_H(l);
        l=l->suivant;
      }
    }
    printf("\n");
}



LivreH *recherche_num_H(int num,BiblioH* b){
    int i;
    for(i=0;i<b->m;i++){
      LivreH *l=b->T[i];
      while(l){
        if(l->num==num)
          return l;
        l=l->suivant;
      }
    }
    printf("Il n'y a pas d'ouvrage avec ce numéro\n");
    return NULL;
}

LivreH *recherche_titre_H(char* titre,BiblioH* b){
    int i;
    for(i=0;i<b->m;i++){
      LivreH *l=b->T[i];
      while(l){
        if(strcmp(l->titre,titre)==0)
          return l;
        l=l->suivant;
      }
    }
    printf("Il n'y a pas d'ouvrage avec ce titre\n");
    return NULL;
}

BiblioH* recherche_auteur_H(char *auteur,BiblioH *b1){
  if(b1){
    BiblioH* b=creer_biblio_H(1);
    int n=fonctionHachage_H(fonctionClef_H(auteur),b1->m);
    LivreH* l=b1->T[n];
    while(l){
      if(strcmp(l->auteur,auteur)==0){
        inserer_H(b,l->num,l->titre,l->auteur);
      }
      l=l->suivant;
    }
    return b;
  }
  return NULL;
}

void suppression_H(BiblioH* b,int num,char* titre,char* auteur){
  if(b){
    int n=fonctionHachage_H(fonctionClef_H(auteur),b->m);
    LivreH* l=b->T[n];
    if(l){
      if( l->num==num && strcmp(l->auteur,auteur)==0 && strcmp(l->titre,titre)==0){
        b->T[n]=l->suivant;
        liberer_livre_H(l);
        b->nE=b->nE-1;
        return ;
      }
      LivreH* suivant=l->suivant;
      while(suivant){
        if(suivant->num==num && strcmp(suivant->auteur,auteur)==0 && strcmp(suivant->titre,titre)==0){
          l->suivant=suivant->suivant;
          liberer_livre_H(suivant);
          b->nE=b->nE-1;
          return ;
        }
        l=suivant;
        suivant=suivant->suivant;
      }
    }
  }
}

void fusion_H(BiblioH* b1,BiblioH* b2){
  int i;
  for(i=0;i<b2->m;i++){
    LivreH *l=b2->T[i];
    while(l){
      inserer_H(b1,l->num,l->titre,l->auteur);
      l=l->suivant;
    }
  }
  liberer_biblio_H(b2);
}



BiblioH* recherche_plusieurs_exemplaire_H(BiblioH* b){
  BiblioH* res=creer_biblio_H(1);
  int i=0;
  int cpt=0;
  for(i=0;i<b->m && cpt<b->nE;i++){
    BiblioH* traite= creer_biblio_H(1);
    LivreH* l=b->T[i];
    while(l && cpt<b->nE){
      LivreH* ltraite=traite->T[0];
      /*on vérifie si tmp est délè dans les ouvrages traités */
      while(ltraite && (strcmp(l->auteur,ltraite->auteur) != 0 || strcmp(l->titre, ltraite->titre) != 0 )){
        ltraite=ltraite->suivant;
      }
      /*Si l'on a parcourut toute la liste alors l'ouvrage n'est pas encore traités*/
      if(ltraite==NULL){
        inserer_H(traite,l->num,l->titre,l->auteur);
        cpt=cpt+1;
        LivreH* lsuiv=l->suivant;
        int c=0;
        /*On parcourt la liste jusqu'à que tout les éléments sont traités*/
        while(lsuiv){
          /*Si le nom de l'auteur et le titre sont le même alors*/
          if(strcmp(l->auteur,lsuiv->auteur) == 0 && strcmp(l->titre,lsuiv->titre) == 0 ){
            c++;
            cpt++;
            inserer_H(res,lsuiv->num,lsuiv->titre,lsuiv->auteur);
            afficher_LivreH_H(lsuiv);
          }
          lsuiv=lsuiv->suivant;
        }
        if(c!=0){//S'il y a plusieurs exemplaire
          inserer_H(res,l->num,l->titre,l->auteur);//On rajoute dans la liste résultat
          afficher_LivreH_H(lsuiv);
        }
        c=0;
      }
    }
    liberer_biblio_H(traite);
  }
  return res;
}


/*int main (){
  printf("Hello World !\n");
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
  //afficher_BiblioH(b1);
  //afficher_BiblioH(b2);
  inserer(b1,10,"abc","coucou");
  inserer(b1,9,"abc","coucou");
  inserer(b1,4,"abc","coucou");
  inserer(b1,5,"abcd","coucou");
  inserer(b1,18,"a","Bonjour");
  afficher_BiblioH(b1);
  recherche_plusieurs_exemplaire(b1);
  afficher_BiblioH(b2);
  printf("%d\n",fonctionHachage(fonctionClef("a"),10));
  printf("%d\n",fonctionHachage(fonctionClef("Salut"),10));
  printf("%d\n",fonctionHachage(500,4));*/
/*BiblioH *b3=charger_n_entrees("GdeBiblio.txt",10);
  afficher_BiblioH(b3);*/
  /*enregistrer_biblio(b1,"GdeBiblio.txt");
  LivreH* l4=recherche_num(4,b1);
  LivreH* l5=recherche_num(9,b1);
  LivreH* l6=recherche_titre("abcd",b1);
  LivreH* l7=recherche_titre("abcde",b1);
  afficher_LivreH(l4);
  afficher_LivreH(l5);
  afficher_LivreH(l6);
  afficher_LivreH(l7);
  BiblioH *b4=recherche_auteur("coucou",b1);
  afficher_BiblioH(b4);
  BiblioH *b5=recherche_auteur("a",b1);
  afficher_BiblioH(b5);*/
  /*suppression(b1,18,"a","Bonjour");
  afficher_BiblioH(b1);
  suppression(b1,92,"a","Bonjour !");
  afficher_BiblioH(b1);
  suppression(b1,4,"abc","coucou");
  afficher_BiblioH(b1);
  fusion(b1,b3);
  afficher_BiblioH(b1);*/
  //liberer_biblio(b1);
  //liberer_biblio(b2);
  /*liberer_biblio(b3);
  liberer_biblio(b4);
  liberer_biblio(b5);*/
//  return 0;
//}
