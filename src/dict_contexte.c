#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/liste_mots.h"
#include "../include/liste_freq.h"
#include "../include/dict_contexte.h"

/**
 * Cette fonction créer le dictionnaire des contexte de la chaîne de caractère t passée en entrée
 */
dictContexte init_dictContexte(char* t) {

	int i = 0;

	listeFreq liste_freq = frequencesDe(t);
	_listeFreq freq_cour = liste_freq.liste;

	// allocation de l'espace mémoire
	dictContexte nouv_dict = malloc(sizeof(struct a_dictContexte));
	dictContexte contexte_cour = nouv_dict;

	printf("Création du dictionnaire de contexte..\n");

	while (freq_cour->freq_suivante!=NULL) {

		i++;

		contexte_cour->contexte = contexte(t, freq_cour->mot);
		strcpy(contexte_cour->mot, freq_cour->mot);

		dictContexte nouv_contexte = malloc(sizeof(struct a_dictContexte));
		strcpy(nouv_contexte->mot, "\0");
		contexte_cour->suivant = nouv_contexte;

		// ajout d'un contexte
		contexte_cour = nouv_contexte;
		freq_cour = freq_cour->freq_suivante;
	}

	nouv_dict->taille = i;

	detruit_liste_freq(liste_freq.liste);
	return nouv_dict;
}

/**
 * Cette fonction affiche le dictionnaire des contexte passé en entrée. Pour chaque mot, on affiche le mot suivi du premier
 * mot dans la liste de ses contextes
 */
void afficher_dict(dictContexte dict){

	dictContexte contexte_cour = dict;
	while (contexte_cour->suivant!=NULL) {
		printf("%s: %s\n", contexte_cour->mot, contexte_cour->contexte.liste->mot);
		contexte_cour = contexte_cour->suivant;
	}
	return;
}

/**
 * Cette fonction renvoie le la liste des contexte du mot passé en entrée, dans le dictionnaire d
 * REMARQUE: on part du principe que le mot à bel et bien on contexte dans d
 */
dictContexte get_contexte(dictContexte d, char* m) {

	dictContexte cour = d;
	while (strcmp(cour->mot, m)) {
		cour = cour->suivant;
	}
	return cour;
}

/**
 * Cette fonction renvoie le mot le plus présent dans le dictionnaire des contexte du mot m
 * REMARQUE: on part du principe que le mot à bel et bien on contexte dans d
 */
char* maxContexte(dictContexte d, char* m) {


	dictContexte cont = get_contexte(d, m);

	_listeFreq contexte_cour = cont->contexte.liste;

	return contexte_cour->mot;
}

/**
 * Cette fonction renvoie le nombre de fois qu'apparaît de mot n dans le dinctionnaire des contextes de m
 */
int freqCont(dictContexte d, char* m, char* n) {

	dictContexte cont = get_contexte(d, m);

	_listeFreq contexte_cour = cont->contexte.liste;

	// tant que l'on trouve pas le mot n dans le contexte courant
	while (strcmp(contexte_cour->mot, n)) {
		contexte_cour = contexte_cour->freq_suivante;
		if (contexte_cour->freq_suivante==NULL) {
			contexte_cour = NULL;
		}
	}

	if (contexte_cour==NULL) // si on a rien trouvé
		return 0;
	else
		return contexte_cour->compte_total;
}


/**
 * Cette fonction génere le texte tel qu'il est demandé dans le dernier exercice du projet
 * REMARQUE: on suppose que n < taille du dictionnaire
 */
void genererTexte(dictContexte d, int n) {

	// on initialise la seed
	srand(time(0));

	int k = 0;
	int r = rand() % d->taille;

	dictContexte d_cour = d;

	// on cherche le premier mot
	while (k<r){
		d_cour = d_cour->suivant;
		k++;
	}

	char mot[TAILLE_MAX];
	char* premier_mot = d_cour->contexte.liste->mot;
	strcpy(mot, premier_mot);

	int i = 0;
	while (i<n) {
		printf("%s ", mot);
		strcpy(mot, maxContexte(d, mot)); // mot du contexte suivant
		i++;
	}
	printf("\n");
	return;

}
