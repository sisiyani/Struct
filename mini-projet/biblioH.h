#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct livreh{
int clef;
int num;
char* auteur;
char* titre;
struct livreh *suivant;
} LivreH;

typedef struct table {
int nE;/*nombre d’elements contenus dans la table de hachage */
int m;/*taille de la table de hachage */
LivreH ** T;/*table de hachage avec resolution des collisions par chainage */
} BiblioH;

int fonctionClef_H(char* auteur);
LivreH* creer_livre_H(int num,char* titre,char* auteur);
void liberer_livre_H(LivreH* l);
BiblioH* creer_biblio_H(int m);
void liberer_biblio_H(BiblioH* b);
int fonctionHachage_H(int cle,int m);
void inserer_H(BiblioH* b,int num,char* titre, char *auteur);
void afficher_LivreH_H(LivreH *l);
void afficher_BiblioH_H(BiblioH *b);
BiblioH* charger_n_entrees_H(char* nomfic,int n);
void enregistrer_biblio_H(BiblioH *b,char *nomfic);
LivreH *recherche_num_H(int num,BiblioH* b);
LivreH *recherche_titre_H(char* titre,BiblioH* b);
BiblioH* recherche_auteur_H(char *auteur,BiblioH *b1);
void suppression_H(BiblioH* b,int num,char* titre,char* auteur);
BiblioH* recherche_plusieurs_exemplaire_H(BiblioH* b);
