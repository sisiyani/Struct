#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entreeSortieLC.h"

//#include "entreeSortieH.h"

void menu(){
  printf(" M E N U : \n");
  printf("0 - Sortir du programme\n");
  printf("1 - Afficher la bibliotheque\n");
  printf("2 - Inserer un ouvrage\n");
  printf("3 - Rechercher un ouvrage par son numéro\n");
  printf("4 - Rechercher un ouvrage par son titre\n");
  printf("5 - Rechercher les livres d'un auteur\n");
  printf("6 - Supprimer un ouvrage\n");
  printf("7 - Fusionner deux bibliotheque\n");
  printf("8 - Rechercher tous les ouvrages avec plusieurs exemplaires\n");
  printf("9 - Libérer la bibliotheque\n");
  printf("Que voulez-vous faire ?\n");
}

int main(int argc, char const *argv[]) {
  Biblio* b1=creer_biblio();
  afficher_bibliotheque(b1);
  inserer_en_tete(b1,1,"Salut","a");
  inserer_en_tete(b1,15,"Salut","a");
  inserer_en_tete(b1,2,"c","ab");
  inserer_en_tete(b1,9,"o","ecrivain");
  afficher_livre(recherche_ouvrage_titre("Salut",b1));
  int rep;
  Biblio* a=creer_biblio();
  Biblio* b=creer_biblio();
  int num ;
  char titre [256];
  char auteur [256];
  char ligne[550];
  do{
  menu();
  char s[10];
  fgets(s,10*sizeof(char),stdin);
  if(sscanf(s,"%d",&rep)==1);
  else rep=-1;
  printf("%d\n",rep);
  switch (rep) {
      case 1:
        printf("Affichage :\n");
        afficher_bibliotheque(b);
        fflush(stdin);
        break;
      case 2:
        printf("Veuillez ecrire le numero, le titre et l'auteur de l'ouvrage.\n");
        /* On suppose que le titre et l’auteur ne contiennent pas d’espace*/
       if (fgets(ligne,sizeof(char)*550,stdin )&& sscanf(ligne,"%d %s %s",&num,titre,auteur)==3) {
          inserer_en_tete (b, num, titre, auteur) ;
          printf("Ajout fait.\n");
        } else {
          printf("Erreur format\n");
        }
        fflush(stdin);
        break ;
      case 3:
        printf("Veuillez donner le numéro du livre recherché : \n");
        if (fgets(ligne,sizeof(char)*550, stdin) && sscanf(ligne,"%d ",&num)==1 ){
          afficher_livre(recherche_ouvrage_numero(num,b));
        }else{
          printf("Le numero n'existe pas.\n");
        }
        fflush(stdin);
        break;
      case 4:
        printf("Veuillez donner le titre du livre recherché : \n");
        if (fgets(titre, sizeof(char)*256, stdin)){
          printf("-------%s--------\n",titre);
            afficher_livre(recherche_ouvrage_titre(titre,b));
        }else{
          printf("Le livre n'existe pas.\n");
        }
        fflush(stdin);
        break;
      case 5:
        printf("Veuillez donner le nom de l'auteur : \n");
        if (fgets(auteur, sizeof(char)*256, stdin)){
            Biblio *bibli = creer_biblio();
            bibli = recherche_livres_auteur(auteur,b);
            afficher_bibliotheque(bibli);
            liberer_biblio(bibli);
        }else{
            printf("L'auteur n'existe pas.\n");
        }
        fflush(stdin);
        break;
      case 6:
        printf("Veuillez ecrire le numero puis le titre et enfin l'auteur de l'ouvrage.\n");
        if (fgets(ligne, 550*sizeof(char), stdin) && sscanf(ligne,"%d %s %s",&num,titre,auteur)==3 ){
            suppression_ouvrage(b, num, titre, auteur);
            printf("l'ouvrage a été suprimé\n");
        }else{
            printf("Erreur format\n");
        }
        fflush(stdin);
        break;
      case 7:
        fusion_bibliotheques(b,a);
        printf("Affichage :\n");
        afficher_bibliotheque(b);
        break;
      case 8:
        printf("Les ouvrages avec plusieurs exemplaire:");
        Biblio *bibli = creer_biblio();
        bibli = recherche_plusieurs_exemplaires(b);
        afficher_bibliotheque(bibli);
        break;
      case 9:
        liberer_biblio(b);
        printf("La bibliotheque a été liberee\n");
        break;
      default:
        printf("Erreur de saisie\n");
        break;
    }
  }while(rep!=0);
  printf("Merci et au revoir.\n");
  if(a)
  liberer_biblio(a);
  if(b)
  liberer_biblio(b);
  return 0;
}
