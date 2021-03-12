#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "entreeSortieLC.h"
#include "entreeSortieH.h"
int main(int argc,char** argv){
  /*Création de deux bibliothèque*/
  Biblio* b1=creer_biblio();
  BiblioH* b2=creer_biblio_H(5);

  /*Insertion d'ouvrage*/
  inserer_en_tete(b1, 1,"titre1","auteur1");
  inserer_H(b2,1,"titre1", "auteur1");
  inserer_en_tete(b1, 2,"titre2","auteur2");
  inserer_H(b2,2,"titre2", "auteur2");
  inserer_en_tete(b1, 3,"titre2","auteur2");
  inserer_H(b2,3,"titre2", "auteur2");
  inserer_en_tete(b1, 4,"titre3","auteur3");
  inserer_H(b2,4,"titre3","auteur3");
  inserer_en_tete(b1, 5,"titre3","auteur3");
  inserer_H(b2,5,"titre3","auteur3");
  inserer_en_tete(b1, 6,"titre7","auteur4");
  inserer_H(b2,6,"titre7","auteur4");
  inserer_en_tete(b1, 7,"titre3","auteur3");
  inserer_H(b2,7,"titre3","auteur3");
  inserer_en_tete(b1, 8,"titre7","auteur4");
  inserer_H(b2,8,"titre7","auteur4");
  inserer_en_tete(b1, 9,"titre7","auteur4");
  inserer_H(b2,9,"titre7","auteur4");
  inserer_en_tete(b1, 10,"titre7","auteur4");
  inserer_H(b2,10,"titre7","auteur4");

  printf("recherche\tliste\ttable de hachage\n");
  int i;
  clock_t  temps_initial;
  clock_t  temps_final;
  clock_t  temps_initial2;
  clock_t  temps_final2;
  double temps_cpu;
  double temps_cpu2;
  printf("----------------------execrice 3 question 1-------------------------\n");
  for(i=0;i<10;i++){
    temps_initial = clock();
    recherche_ouvrage_numero(1,b1);
    temps_final = clock();
    temps_cpu =   (( double)(temps_final  - temps_initial));
    temps_initial2 = clock();
    recherche_num_H(1,b2);
    temps_final2 = clock();
    temps_cpu2 =   (( double)(temps_final2  - temps_initial2));
    printf("num présent\t%f\t%f\n",temps_cpu,temps_cpu2);

    temps_initial = clock();
    recherche_ouvrage_numero(15,b1);
    temps_final = clock();
    temps_cpu =   (( double)(temps_final  - temps_initial));
    temps_initial2 = clock();
    recherche_num_H(15,b2);
    temps_final2 = clock();
    temps_cpu2 =   (( double)(temps_final2  - temps_initial2));
    printf("num abscent\t%f\t%f\n",temps_cpu,temps_cpu2);

    temps_initial = clock();
    recherche_livres_auteur("titre2",b1);
    temps_final = clock();
    temps_cpu =   (( double)(temps_final  - temps_initial));
    temps_initial2 = clock();
    recherche_auteur_H("auteur1",b2);
    temps_final2 = clock();
    temps_cpu2 =   (( double)(temps_final2  - temps_initial2));
    printf("titre présent\t%f\t%f\n",temps_cpu,temps_cpu2);

    temps_initial = clock();
    recherche_ouvrage_titre("titre2",b1);
    temps_final = clock();
    temps_cpu =   (( double)(temps_final  - temps_initial));
    temps_initial2 = clock();
    recherche_titre_H("titre6",b2);
    temps_final2 = clock();
    temps_cpu2 =   (( double)(temps_final2  - temps_initial2));
    printf("titre abscent\t%f\t%f\n",temps_cpu,temps_cpu2);

    temps_initial = clock();
    recherche_livres_auteur("auteur3",b1);
    temps_final = clock();
    temps_cpu =   (( double)(temps_final  - temps_initial));
    temps_initial2 = clock();
    recherche_auteur_H("auteur3",b2);
    temps_final2 = clock();
    temps_cpu2 =   (( double)(temps_final2  - temps_initial2));
    printf("auteur présent\t%f\t%f\n",temps_cpu,temps_cpu2);

    temps_initial = clock();
    recherche_livres_auteur("auteur7",b1);
    temps_final = clock();
    temps_cpu =   (( double)(temps_final  - temps_initial));
    temps_initial2 = clock();
    recherche_auteur_H("auteur7",b2);
    temps_final2 = clock();
    temps_cpu2 =   (( double)(temps_final2  - temps_initial2));
    printf("auteur abscent\t%f\t%f\n",temps_cpu,temps_cpu2);

    printf("\n\n");

    }
    printf("----------------------execrice 3 question 2-------------------------\n");

    printf("taille modifié\n");
    for(i=5;i<11;i++){
      BiblioH* b3=creer_biblio_H(i);
      fusion_H(b3,b2);
      printf("taille=%d--------------\n",i);

      temps_initial = clock();
      recherche_num_H(1,b3);
      temps_final = clock();
      temps_cpu =   (( double)(temps_final  - temps_initial));
      printf("num présent\t%f\n",temps_cpu);

      temps_initial = clock();
      recherche_num_H(15,b3);
      temps_final = clock();
      temps_cpu =   (( double)(temps_final  - temps_initial));
      printf("num abscent\t%f\n",temps_cpu);

      temps_initial = clock();
      recherche_titre_H("titre2",b3);
      temps_final = clock();
      temps_cpu =   (( double)(temps_final  - temps_initial));
      printf("titre présent\t%f\n",temps_cpu);

      temps_initial = clock();
      recherche_titre_H("titre2",b3);
      temps_final = clock();
      temps_cpu =   (( double)(temps_final  - temps_initial));
      printf("titre abscent\t%f\n",temps_cpu);

      temps_initial = clock();
      recherche_auteur_H("auteur3",b3);
      temps_final = clock();
      temps_cpu =   (( double)(temps_final  - temps_initial));
      printf("auteur présent\t%f\n",temps_cpu);

      temps_initial = clock();
      recherche_auteur_H("auteur7",b3);
      temps_final = clock();
      temps_cpu =   (( double)(temps_final  - temps_initial));
      printf("auteur abscent\t%f\n",temps_cpu);

      b2=b3;
      }
      liberer_biblio_H(b2);
      printf("----------------------execrice 3 question 3-------------------------\n");
      FILE *f=fopen("Resultatstemps.txt","w");
      printf("taille\tliste_t table de hachage\n");
      for(i=1000;i<=30000;i=i+1000){
        if(!argv[1])argv[1]="GdeBiblio.txt";
        b1=charger_n_entrees(argv[1],i);
        b2=charger_n_entrees_H(argv[1],i);
        temps_initial = clock();
        recherche_livres_auteur("auteur7",b1);
        temps_final = clock();
        temps_cpu =   (( double)(temps_final  - temps_initial));

        temps_initial2 = clock();
        recherche_auteur_H("auteur7",b2);
        temps_final2 = clock();
        temps_cpu2 =   (( double)(temps_final2  - temps_initial2));
        printf("%d\t%f\t%f\n",i,temps_cpu,temps_cpu2);
        fprintf(f,"%d\t%f\t%f\n",i,temps_cpu,temps_cpu2);
        i=i+100;
        liberer_biblio(b1);
        liberer_biblio_H(b2);
      }
      fclose(f);
      return 0;

}
