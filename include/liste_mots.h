#ifndef LISTE_MOTS_H_
#define LISTE_MOTS_H_

#define TAILLE_MAX 32

// la liste est une liste chainée simple
typedef struct a_liste_mots {
	char mot[TAILLE_MAX];
	struct a_liste_mots * mot_suivant; 
	int lg;
} * listeMots;

void raler(const char * message); // affiche un message d'erreur et exit

listeMots motsDe(char* t); // retourne une la liste de mots d'un texte donnée
int motEstDansListeMots(listeMots liste, const char * mot); // renvoie vrai si le mot est dans la liste, faux sinon
void afficher_liste(listeMots liste); // affiche la liste
void lower_mot(char* mot); // rend un mot minuscule
void detruit_liste_mots(listeMots liste); // détruit liste

#endif // LISTE_MOTS_H_