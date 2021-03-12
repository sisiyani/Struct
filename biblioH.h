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

int fonctionClef(char* auteur);
LivreH* creer_livre(int num,char* titre,char* auteur);
void liberer_livre(LivreH* l);
BiblioH* creer_biblio(int m);
void liberer_biblio(BiblioH* b);
int fonctionHachage(int cle,int m);
void inserer(BiblioH* b,int num,char* titre, char *auteur);
void afficher_LivreH(LivreH *l);
void afficher_BiblioH(BiblioH *b);
BiblioH* charger_n_entrees(char* nomfic,int n);
void enregistrer_biblio(BiblioH *b,char *nomfic);
LivreH *recherche_num(int num,BiblioH* b);
LivreH *recherche_titre(char* titre,BiblioH* b);
BiblioH* recherche_auteur(char *auteur,BiblioH *b1);
//void enregistrer_biblio(BiblioH *b, char* nomfic);
void suppression(BiblioH* b,int num,char* titre,char* auteur);
LivreH* recherche_plusieurs_exemplaire(BiblioH* b);
