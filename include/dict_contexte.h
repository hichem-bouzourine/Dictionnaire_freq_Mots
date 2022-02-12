#ifndef DICT_CONTEXTE_H_
#define DICT_CONTEXTE_H_

typedef struct a_dictContexte {
	char mot[TAILLE_MAX];
	listeFreq contexte;
	struct a_dictContexte * suivant;
	int taille; // premiet élément contient la taille du dictionnaire
} * dictContexte;


dictContexte init_dictContexte(char* t); //créer le dictionnaire des contextes
void afficher_dict(dictContexte dict); // affiche le dictionnaire
char* maxContexte(dictContexte d, char* m); // retourne le mot le plus fréquent du contexte de m
dictContexte get_contexte(dictContexte d, char* m); // retourne le contexte du mot m
int freqCont(dictContexte d, char* m, char* n); // retourne le nombre d'apparition de n dans le contexte de m
void genererTexte(dictContexte d, int n); // génère le texte demandé dans le sujet

#endif // DICT_CONTEXTE_H_ 