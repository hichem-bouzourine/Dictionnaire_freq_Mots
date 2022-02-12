#ifndef LISTE_FREQ_H_
#define LISTE_FREQ_H_

#define TAILLE_MAX 32

// la liste est une liste chainée simple
typedef struct a_liste_freq {
	char mot[TAILLE_MAX];
	double freq;
	int compte_total;
	struct a_liste_freq * freq_suivante; 
} * _listeFreq;

typedef struct listeFreq {
	int taille;
	_listeFreq liste;
} listeFreq;

listeFreq frequencesDe(char* t); // retourne une la liste de mots d'un texte donnée
_listeFreq trouverMot(_listeFreq liste, const char * mot); // renvoie la frenquence (_listeFreq) du mot donné en entrée
int motEstDansListeFreq(_listeFreq liste, const char* mot); // renvoie vrai si le mot est dans la liste, faux sinon
void ajouterFreq(listeFreq * liste_freq, _listeFreq nouv_freq); // ajoute un élément (de tel sorte à garder la croissance)
void detruit_liste_freq(_listeFreq liste); // détruit la liste
listeFreq contexte(char* t, char* m); // retourne la liste des contextes d'ordre 1 tu mot m dans le texte t
void afficher_liste_freq(listeFreq liste); // affiche une liste

#endif // LISTE_FREQ_H_