typedef struct livre {
int num ;
char * titre ;
char * auteur ;
struct livre * suiv ;
} Livre ;

typedef struct { /* Tete fictive */
Livre * L ; /* Premier element */
} Biblio;
