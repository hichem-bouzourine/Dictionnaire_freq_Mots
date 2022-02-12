#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "../include/liste_mots.h"


void raler(const char * message) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}


/**
 * Cette fonction permet de créer la liste des mots d'une chaine de caractère t
 */
listeMots motsDe(char* t) {
	// on alloue la mémoire de la liste de mot
	listeMots liste_nouv = (listeMots) malloc(sizeof(struct a_liste_mots));
	liste_nouv->mot_suivant = NULL;
	liste_nouv->lg = 0;

	listeMots liste_mot_courant = liste_nouv;

	char char_courant = t[0];
	char * mot_courant = (char *)calloc(0, TAILLE_MAX*sizeof(char));
	int cpmt_mot = 0;
	int i = 0;

	while (char_courant != '\0') {
		// caractères "spéciaux" devant compter comme des mots à part
		if (char_courant == '.' || char_courant=='\'' || char_courant == ';'      \
			|| char_courant == '?' || char_courant == '!' || char_courant == ','  \
			|| char_courant == '(' || char_courant == ')' || char_courant == '['  \
			|| char_courant == '[' || char_courant == '-' || char_courant == '\"' \
			|| char_courant == '_' || !strcmp(&char_courant, "“")){

			listeMots mot_suivant = (listeMots) malloc(sizeof(struct a_liste_mots));

			if (mot_suivant == NULL)
				raler("malloc");

			lower_mot(mot_courant);

			// on ajoute le mot courant à la liste
			strcpy(mot_suivant->mot, mot_courant);

			listeMots mot_suivant_2 = (listeMots) malloc(sizeof(struct a_liste_mots));

			if (mot_suivant_2 == NULL)
				raler("malloc");

			cpmt_mot=0;

			mot_courant[0] = char_courant;
			mot_courant[1] = '\0';

			strcpy(mot_suivant_2->mot, mot_courant);

			// on ajoute le caractère spécial à la liste
			liste_mot_courant->mot_suivant = mot_suivant;
			mot_suivant->mot_suivant = mot_suivant_2;
			liste_mot_courant = mot_suivant_2;

			mot_courant[0] = '\0';
			liste_nouv->lg = liste_nouv->lg+2;
		}
		else {
			// si on reconctre un espace ou un saut de ligne
			if (char_courant == ' ' || char_courant == '\n')
			{
				listeMots mot_suivant = (listeMots) malloc(sizeof(struct a_liste_mots));

				if (mot_suivant == NULL)
					raler("malloc");

				mot_courant[cpmt_mot] = '\0';
				lower_mot(mot_courant);

				strcpy(mot_suivant->mot, mot_courant);

				// on ajout le mot à la liste
				liste_mot_courant->mot_suivant = mot_suivant;
				liste_mot_courant = mot_suivant;

				cpmt_mot = 0;
				mot_courant[cpmt_mot] = '\0';

				liste_nouv->lg++;
			}
			else {
				mot_courant[cpmt_mot] = char_courant;
				mot_courant[cpmt_mot+1] = '\0';
				cpmt_mot++;
			}
		}
		if ((char_courant = t[++i])=='\0')
			break;
	}
	// on libère l'espace mémoire du mot
	free(mot_courant);

	// on supprimes les mots vides ("\0" si il y en a)
	liste_mot_courant = liste_nouv;
	while (liste_mot_courant->mot_suivant!=NULL) {
		if (!strcmp(liste_mot_courant->mot_suivant->mot, "\0") || !strcmp(liste_mot_courant->mot_suivant->mot, "\n") || \
			!strcmp(liste_mot_courant->mot_suivant->mot, "\t") || !strcmp(liste_mot_courant->mot_suivant->mot, " "))
		{
			listeMots temp = liste_mot_courant->mot_suivant;
			liste_mot_courant->mot_suivant = liste_mot_courant->mot_suivant->mot_suivant;
			free(temp);
		}
		liste_mot_courant = liste_mot_courant->mot_suivant;
	}

	return liste_nouv;
}


/**
 * Cette fonction retourne vrai si le mot passé en entrée est dans la liste passée en entrée, faux sinon
 */
int motEstDansListeMots(listeMots liste, const char * mot) {

	listeMots mot_courant = liste;

	while (mot_courant->mot_suivant != NULL) {
		if (!strcmp(mot_courant->mot, mot))
			return 1;
		mot_courant = mot_courant->mot_suivant;
	}

	return 0;
}

/**
 * Cette fonction affiche tout les mots de la liste passée en entrée
 */
void afficher_liste(listeMots liste) {
	listeMots cour = liste;
	int i = 0;

	while (cour->mot_suivant != NULL) {
		printf("%d: %s\n", i++, cour->mot);
		cour = cour->mot_suivant;
	}
	return;
}

/**
 * Cette fonction permet de rendre minuscule le mot passé en entrée
 */
void lower_mot(char* mot) {
	for(int i = 0; mot[i]; i++){
  		mot[i] = tolower(mot[i]);
	}
}


/**
 * Cette fonction détruit et libère l'espace mémoire de la liste
 */
void detruit_liste_mots(listeMots liste){
	if (liste->mot_suivant == NULL)
		free(liste);
	else {
		listeMots temp = liste->mot_suivant;
		free(liste);
		detruit_liste_mots(temp);
	}
}
