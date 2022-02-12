#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/liste_mots.h"
#include "../include/liste_freq.h"
#include "../include/dict_contexte.h"

char* chargerFichier(const char* path) {

	FILE* fichier;
	if ((fichier = fopen(path, "r"))==NULL)
		raler("fopen");

	if(fseek( fichier , 0L , SEEK_END))
		raler("fseek");
	long taille_fichier = ftell(fichier);
	rewind(fichier);

	char* texte = calloc(1, taille_fichier+1);
	if (texte == NULL){
		fclose(fichier);
		raler("calloc");
	}

	if(fread(texte, taille_fichier, 1, fichier)!=1){
		fclose(fichier);
		free(texte);
		raler("fread");
	}

	return texte;
}

int main(void) {
	
	char* texte;
	char chemin[128];

	printf("Quel est le chemin vers votre fichier texte ?\n");
	scanf("%s", chemin);

	texte = chargerFichier(chemin);

	int choix;
	while (1) {
		choix = 0;

		printf("Quelle opération voulez-vous effectuer ?\n");
		printf("1) Afficher la liste des mots\n");
		printf("2) Afficher la liste de fréquences (ordre décroissant)\n");
		printf("3) Afficher la liste des contexte d'ordre 1 d'un mot de votre choix\n");
		printf("4) Afficher le mot le plus fréquent d'un contexte du mot de votre choix\n");
		printf("5) Afficher le nombre d'apparition d'un mot dans le contexte d'un autre\n");
		printf("6) Afficher le texte généré\n");
		printf("7) Changer de fichier texte\n");
		printf("8) Quitter\n");

		printf("Entrez votre choix: ");
		scanf("%d", &choix);

		if (choix < 1 || choix > 8) {
			printf("Vous n'avez pas entré un choix correct!\n");
			continue;
		}

		unsigned int n;
		char mot[35];
		char second_mot[35];
		listeFreq contexte_mot;

		switch (choix) {
			case 1:;
				listeMots liste;
				liste = motsDe(texte);
				afficher_liste(liste);
				break;
			case 2:;
				listeFreq liste_freq = frequencesDe(texte);
				afficher_liste_freq(liste_freq);
				break;
			case 3:;
				printf("Chossissez un mot\n");
				scanf("%s", mot);
				lower_mot(mot);
				contexte_mot = contexte(texte, mot);
				afficher_liste_freq(contexte_mot);
				break;
			case 4:;
				printf("Chossissez un mot\n");
				scanf("%s", mot);
				lower_mot(mot);
				contexte_mot = contexte(texte, mot);
				printf("Le mot le plus fréquent du contexte de \"%s\" est \"%s\"\n", mot, contexte_mot.liste->mot);
				break;
			case 5:;
				printf("Chossissez un mot\n");
				scanf("%s", mot);
				lower_mot(mot);
				contexte_mot = contexte(texte, mot);

				printf("Chossissez un second mot\n");
				scanf("%s", second_mot);

				_listeFreq seconde_liste = trouverMot(contexte_mot.liste, second_mot);
				if (seconde_liste == NULL) {
					printf("\"%s\" n'est pas de le contexte de \"%s\"\n", second_mot, mot);
				}
				else {
					printf("\"%s\" apparait %d fois dans le contexte de \"%s\"\n", second_mot, seconde_liste->compte_total, mot);
				}
				break;
			case 6:;
				printf("Entrez le nombre de mot que vous souhaitez\n");
				scanf("%ud", &n);
				dictContexte dict_contexte = init_dictContexte(texte);
				genererTexte(dict_contexte, n);
				break;
			case 7:;
				printf("Quel est le chemin vers votre fichier texte ?\n");
				scanf("%s", chemin);
				texte = chargerFichier(chemin);
				break;
			case 8:;
				printf("fermeture du programme\n");
				exit(EXIT_SUCCESS);
		}
	}
	
	return 0;
}