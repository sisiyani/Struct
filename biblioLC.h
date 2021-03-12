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

void liberer_biblio(Biblio *b);

//ajoute un nouveau livre à la bibliothèque
void inserer_en_tete(Biblio *b, int num,char *titre,char * auteur);

void afficher_livre(Livre *l);
void afficher_bibliotheque(Biblio *b);
Livre* recherche_ouvrage_numero(int num, Biblio *b);
Livre* recherche_ouvrage_titre(char* titre, Biblio *b);
Biblio* recherche_livres_auteur(char *auteur, Biblio*b);
void suppression_ouvrage(Biblio *b, int num, char* titre, char* auteur);
void fusion_bibliotheques(Biblio *b1, Biblio *b2);
Livre * recherche_plusieurs_exemplaires(Biblio *b,int n);
