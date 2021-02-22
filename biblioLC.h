typedef struct livre{
  int num;
  char *titre;
  char *auteur;
  struct livre *suiv;
} Livre;

typedef struct {/*Tete fictive*/
  Livre * L;/*Premier element*/
}Biblio;

//création d'un livre
Livre* creer_livre(int num,char* titre,char* auteur);

//libération de la mémoire
void liberer_livre(Livre *l);

//création d'une bibliothèque vide
Biblio* creer_biblio();

//ajoute un nouveau livre à la bibliothèque
void inserer_en_tete(Biblio *b, int num,char *titre,char * auteur);
