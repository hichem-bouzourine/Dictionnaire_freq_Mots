#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/liste_freq.h"
#include "../include/liste_mots.h"

/**
 * Cette fonction créer la liste des fréquences pour la chaîne de caractère t donnée en entrée
 */
listeFreq frequencesDe(char* t) {
	int total_mot = 1;

	// allocation de la mémoire et initialisation des variables
	listeMots liste_mots = motsDe(t);
	_listeFreq liste_freq = malloc(sizeof(struct a_liste_freq));
	liste_freq->freq = 0;
	liste_freq->compte_total = 0;
	liste_freq->freq_suivante = NULL;

	listeMots mot_courant = liste_mots;
	while (mot_courant->mot_suivant != NULL) {
		if (motEstDansListeFreq(liste_freq, mot_courant->mot)) { // pas besoin d' ajouter le mot, on incrément le compte
			_listeFreq mot_existant = trouverMot(liste_freq, mot_courant->mot);
			mot_existant->compte_total++;
			mot_existant->freq = (mot_existant->compte_total)/total_mot;
		}
		else { // on doit ajouter le mot
			_listeFreq nouv_freq = malloc(sizeof(struct a_liste_freq));

			if (nouv_freq==NULL) {
				fprintf(stderr,"malloc\n");
				exit(EXIT_FAILURE);
			}

			strcpy(nouv_freq->mot, mot_courant->mot);
			nouv_freq->compte_total = 1;
			nouv_freq->freq = 1/total_mot;

			// ajout du mot à la liste
			_listeFreq temp = liste_freq;
			nouv_freq->freq_suivante = temp;
			liste_freq = nouv_freq;
		}

		mot_courant = mot_courant->mot_suivant;
		total_mot++;
	}

	// on replace les éléments dans la liste en les triant
	listeFreq * liste_freq_triee = malloc(sizeof(listeFreq));
	liste_freq_triee->taille = 0;
	liste_freq_triee->liste = NULL;

	_listeFreq freq_cour = liste_freq;

	// tri de la liste
	while (freq_cour->freq_suivante != NULL) {
		ajouterFreq(liste_freq_triee, freq_cour);
		freq_cour = freq_cour->freq_suivante;
	}

	detruit_liste_mots(liste_mots);
	return *liste_freq_triee;
}

/**
 * Cette fonction créer la liste des contextes du mot m, par ordre croissant
 */
listeFreq contexte(char* t, char* m) {

	int total_mot = 1;

	listeMots liste_mots = motsDe(t);

	// allocation de la mémoire
	_listeFreq liste_contextes = malloc(sizeof(struct a_liste_freq));
	liste_contextes->freq = 0;
	liste_contextes->compte_total = 0;
	liste_contextes->freq_suivante = NULL;

	listeMots mot_courant = liste_mots;

	while (mot_courant->mot_suivant != NULL) {
		// si le mot n'est pas celui passé en entrée, on saute cette étape
		if (strcmp(mot_courant->mot, m)){
			mot_courant = mot_courant->mot_suivant;
			continue;
		}
		else {
			char mot_a_ajouter[TAILLE_MAX];
			strcpy(mot_a_ajouter, mot_courant->mot_suivant->mot);
			if (motEstDansListeFreq(liste_contextes, mot_a_ajouter)) { // pas besoin d' ajouter le mot
				total_mot++;
				_listeFreq mot_existant = trouverMot(liste_contextes, mot_a_ajouter);
				mot_existant->compte_total++;
				mot_existant->freq = (mot_existant->compte_total)/total_mot;
			}
			else { // on doit ajouter le mot
				total_mot++;
				_listeFreq nouv_contexte = malloc(sizeof(struct a_liste_freq));

				if (nouv_contexte==NULL) {
					fprintf(stderr,"malloc\n");
					exit(EXIT_FAILURE);
				}

				strcpy(nouv_contexte->mot, mot_a_ajouter);
				nouv_contexte->compte_total = 1;
				nouv_contexte->freq = 1/total_mot;

				// ajout du mot dans la liste
				_listeFreq temp = liste_contextes;
				nouv_contexte->freq_suivante = temp;
				liste_contextes = nouv_contexte;
			}
			mot_courant = mot_courant->mot_suivant;
		}
	}

	// on replace les éléments dans la liste en les triant
	listeFreq * contextes = malloc(sizeof(listeFreq));
	contextes->taille = 0;
	contextes->liste = NULL;

	_listeFreq freq_cour = liste_contextes;

	// tri de la liste
	while (freq_cour->freq_suivante != NULL) {
		ajouterFreq(contextes, freq_cour);
		freq_cour = freq_cour->freq_suivante;
	}

	detruit_liste_mots(liste_mots);
	return *contextes;
}

/**
 * Cette fonction retourne vrai si le mot donnée en entrée est dans la liste des fréquences donnée en entrée
 */
int motEstDansListeFreq(_listeFreq liste, const char * mot) {
	_listeFreq mot_courant = liste;

	while (mot_courant->freq_suivante != NULL) {
		if (!strcmp(mot_courant->mot, mot))
			return 1;
		mot_courant = mot_courant->freq_suivante;
	}

	return 0;
}

/**
 * Cette fonction renvoie le mot donnée en entrée dans la liste des fréquences
 * REMARQUE: on suppose que le mot donné en entrée est bien dans la liste
 */
_listeFreq trouverMot(_listeFreq liste, const char * mot) {
	_listeFreq mot_courant = liste;

	while (mot_courant->freq_suivante != NULL) {
		if (!strcmp(mot_courant->mot, mot))
			return mot_courant;
		mot_courant = mot_courant->freq_suivante;
	}

	return NULL; // ne devrait pas arriver
}

/**
 * Cette fonction ajoute un élément à la liste des fréquences donnée en entrée
 * REMARQUE: cette fonction préserve l'ordre décroissant
 */
void ajouterFreq(listeFreq * liste_freq, _listeFreq freq_a_trie) {;

	// allocation de la mémoire
	_listeFreq nouv_freq = malloc(sizeof(struct a_liste_freq));
	memcpy(nouv_freq, freq_a_trie, sizeof(struct a_liste_freq));
	nouv_freq->freq_suivante = NULL;

	// cas où la list est nulle
	if (liste_freq->liste == NULL) {
		liste_freq->liste = nouv_freq;
	}
	else {

		_listeFreq freq_cour = liste_freq->liste;
		_listeFreq freq_prec = NULL;

		// cas ou le fréquence de l'élément à ajouter est inférieur àtout les autres
		if (nouv_freq->compte_total > freq_cour->compte_total){
			nouv_freq->freq_suivante = freq_cour;
			liste_freq->liste = nouv_freq;
		}

		// sinon, on cherche l'endroit à partir duquel la fréquence de l'élément à ajouter devient inférieure
		while (nouv_freq->compte_total <= freq_cour->compte_total) {
			if (freq_cour->freq_suivante == NULL)
				break;
			freq_prec = freq_cour;
			freq_cour = freq_cour->freq_suivante;
		}

		if (freq_prec == NULL){
			nouv_freq->freq_suivante = freq_cour;
			liste_freq->liste = nouv_freq;
		}
		else {
			freq_prec->freq_suivante = nouv_freq;
			nouv_freq->freq_suivante = freq_cour;
		}
	}

}


/**
 * Cette fonction permet de libérer l'espace mémoire d'une liste de fréquence
 */
void detruit_liste_freq(_listeFreq liste){
	if (liste->freq_suivante == NULL)
		free(liste);
	else {
		_listeFreq temp = liste->freq_suivante;
		free(liste);
		detruit_liste_freq(temp);
	}
}

/**
 * Cette fonction affiche la list des fréquences passée en entrée
 */
void afficher_liste_freq(listeFreq liste){
	_listeFreq freq_cour = liste.liste;

	while (freq_cour!=NULL) {
		printf("%s: %d\n", freq_cour->mot, freq_cour->compte_total);
		freq_cour = freq_cour->freq_suivante;
	}

	return;
}
