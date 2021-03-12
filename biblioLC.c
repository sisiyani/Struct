#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioLC.h"

Livre* creer_livre(int num,char* titre,char* auteur){
  Livre *l=(Livre *)malloc(sizeof(Livre));
  if(!l){
    printf("Erreur d'allocation de l\n");
    return NULL;
  }
  l->num=num;
  l->titre=(char *)malloc((strlen(titre)+1)*sizeof(char));
  if (!l->titre){
    printf("Erreur d'allocation de titre de l\n");
    free(l);
    return NULL;
  }
  strcpy(l->titre,titre);
  l->auteur=(char *)malloc((strlen(auteur)+1)*sizeof(char));
  if (!l->auteur){
    printf("Erreur d'allocation de auteur de l\n");
    free(l->titre);
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
    printf("Erreur d'allocation de la mémoire pour Biblio\n");
  return NULL;
  }
  b->L=NULL;
  return b;
}

void liberer_biblio(Biblio *b){
  if(b){
    Livre *p=b->L;
    while(p){
      b->L=p->suiv;
      liberer_livre(p);
      p=b->L;
    }
    free(b);
  }
}

void inserer_en_tete(Biblio *b, int num,char *titre,char * auteur){
  if(b){
     Livre *l=creer_livre(num,titre,auteur);
     if (!l){
       printf("Erreur\n");
       return;
     }
     l->suiv=b->L;
     b->L=l;
  }
}

void afficher_livre(Livre *l){
  if(l==NULL){
    printf("Le livre n'existe pas\n");
  }else{
    printf("Livre\t");
    printf("titre : %s\t",l->titre);
    printf("auteur : %s\t",l->auteur);
    printf("num : %d\n",l->num);
  }
}

void afficher_bibliotheque(Biblio *b){
  if(b==NULL){
    printf("La bibliotheque n'existe pas\n");
  }else{
    printf("Bibliotheque\n");
    Livre *tmp=b->L;
    while (tmp){
      afficher_livre(tmp);
      tmp=tmp->suiv;
    }
  }
}

Livre* recherche_ouvrage_numero(int num, Biblio *b){
  if(b==NULL){
    printf("La bibliotheque n'existe pas\n");
    return NULL;
  }else{
    Livre *tmp=b->L;
    while(tmp){
      if(num==tmp->num){
        return tmp;
      }
    tmp=tmp->suiv;
    }
    return NULL;
  }
}

Livre* recherche_ouvrage_titre(char* titre, Biblio *b){
  if(b==NULL){
    printf("La bibliotheque n'existe pas\n");
  }else{
    Livre *tmp=b->L;
    while(tmp){
      if(strcmp(titre,tmp->titre)==0){
        return tmp;
      }
    tmp=tmp->suiv;
    }
  }
  return NULL;
}

Biblio* recherche_livres_auteur(char *auteur, Biblio*b){
  if(b==NULL){
    printf("La bibliotheque n'existe pas\n");
    return NULL;
  }else{
    Biblio *recherche = creer_biblio();
    while (b->L){
      if (strcmp(b->L->auteur, auteur) == 0){
          inserer_en_tete(recherche, b->L->num, b->L->titre, b->L->auteur);
      }
      b->L = b->L->suiv;
    }
    return recherche;
  }
}

void suppression_ouvrage(Biblio *b, int num, char* titre, char* auteur){
  if(b==NULL){
    printf("La bibliotheque n'existe pas\n");
  }
  else{
    Livre *l=b->L;
    if((l->num == num) && (strcmp(l->titre, titre)==0) && (strcmp(l->auteur, auteur)==0)){
            b->L=b->L->suiv;
            liberer_livre(l);
            return;
    }
    else{
      while(l->suiv){
        if((l->suiv->num == num) && (strcmp(l->suiv->titre, titre)==0) && (strcmp(l->suiv->auteur, auteur)==0)){
            Livre *suivant=l->suiv->suiv;
            liberer_livre(l->suiv);
            l->suiv=suivant;
            return;
          }
        l=l->suiv;
      }
    }
  }
}



void fusion_bibliotheques(Biblio *b1, Biblio *b2){
  if (b1 == NULL){
      b1 = b2;
  }else{
    Livre* l=b2->L;
    while (l){
      inserer_en_tete(b1,l->num,l->titre,l->auteur);
      l=l->suiv;
    }
    liberer_biblio(b2);
  }
}



Livre* recherche_plusieurs_exemplaires(Biblio *b,int n){
  Biblio* res=creer_biblio();
  Biblio* traite= creer_biblio();
  int i=0;
  Livre* l=b->L;
  while(l && i<n){
    Livre* ltraite=traite->L;
    /*on vérifie si tmp est délè dans les ouvrages traités */
    while(ltraite && strcmp(l->auteur,ltraite->auteur) != 0 && strcmp(l->auteur, ltraite->auteur) != 0 ){
      ltraite=ltraite->suiv;
    }

    /*Si l'on a parcourut toute la liste alors l'ouvrage n'est pas encore traités*/
    if(ltraite==NULL){
      inserer_en_tete(traite,l->num,l->titre,l->auteur);
      i=i+1;
      Livre* lsuiv=l->suiv;
      int c=0;
      /*On parcourt la liste jusqu'à que tout les éléments sont traités*/
      while(lsuiv){
        /*Si le nom de l'auteur et le titre sont le même alors*/
        if(strcmp(l->auteur,lsuiv->auteur) == 0 && strcmp(l->auteur,lsuiv->auteur) == 0 ){
          c++;
          i++;
          inserer_en_tete(res,lsuiv->num,lsuiv->titre,lsuiv->auteur);
        }
        lsuiv=lsuiv->suiv;
      }
      if(c!=0){//S'il y a plusieurs exemplaire
        inserer_en_tete(res,l->num,l->titre,l->auteur);//On rajoute dans la liste résultat
      }
      c=0;
    }
    l=l->suiv;
  }
  liberer_biblio(traite);
  Livre* s=res->L;
  free(res);
  return s;
}


/*int main(){
  Livre *l1=creer_livre(1,"Salut","a");
  afficher_livre(l1);
  liberer_livre(l1);
  Biblio* b1=creer_biblio();
  afficher_bibliotheque(b1);
  inserer_en_tete(b1,1,"Salut","a");
  inserer_en_tete(b1,15,"Salut","a");
  inserer_en_tete(b1,2,"c","ab");
  inserer_en_tete(b1,9,"o","ecrivain");*/
  /*afficher_bibliotheque(b1);
  afficher_livre(recherche_ouvrage_numero(0,b1));
  afficher_livre(recherche_ouvrage_numero(1,b1));
  afficher_livre(recherche_ouvrage_titre("c",b1));
  afficher_livre(recherche_ouvrage_titre("b",b1));
  afficher_bibliotheque(recherche_livres_auteur("a",b1));
  afficher_bibliotheque(recherche_livres_auteur("aute",b1));
  Biblio* b2=creer_biblio();*/
/*  inserer_en_tete(b1,12,"Salut","a");
  inserer_en_tete(b1,150,"Salut","a");
  inserer_en_tete(b1,20,"c","ab");
  inserer_en_tete(b1,91,"o","ecrivain");
  afficher_bibliotheque(b1);
  suppression_ouvrage(b1,91,"o","ecrivain");
  afficher_bibliotheque(b1);
  suppression_ouvrage(b1,9,"Salut","a");
  afficher_bibliotheque(b1);*/
  /*fusion_bibliotheques(b1,b2);
  afficher_bibliotheque(b1);
  liberer_biblio(b1);
  Biblio* b1=charger_n_entrees("GdeBiblio.txt",10);
  afficher_bibliotheque(b1);
  Biblio* b2=creer_biblio();
  inserer_en_tete(b1,150,"Salut","a");
  inserer_en_tete(b1,20,"c","ab");
  enregistrer_biblio(b1,"GdeBiblio.txt");
  liberer_biblio(b1);
  liberer_biblio(b2);*/
/*Biblio *b3=creer_biblio();
  b3->L=recherche_plusieurs_exemplaires(b1,8);
  afficher_bibliotheque(b3);
  liberer_biblio(b3);
  liberer_biblio(b1);

  return 0;
}*/
