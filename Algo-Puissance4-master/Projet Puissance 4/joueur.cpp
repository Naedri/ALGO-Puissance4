#include <stdlib.h>
#include <stdio.h>


#include <assert.h>
#include <malloc.h>
#include <unittest.h>

#include "joueur.h"
#pragma warning(disable:4996)

/*attention
le fichier dans lequel sont sauvegardés les détails des joueurs doit avoir les détails suivants :
./repertoire/joueurs.csv
*/

/*
	"r": lecture seule. Vous pourrez lire le contenu du fichier, mais pas y écrire. Le fichier doit avoir été créé au préalable.

	"w": écriture seule. Vous pourrez écrire dans le fichier, mais pas lire son contenu. Si le fichier n'existe pas, il sera créé.

	"a": mode d'ajout. Vous écrirez dans le fichier, en partant de la fin du fichier. Vous ajouterez donc du texte à la fin du fichier. Si le fichier n'existe pas, il sera créé.

	"r+": lecture et écriture. Vous pourrez lire et écrire dans le fichier. Le fichier doit avoir été créé au préalable.

	"w+": lecture et écriture, avec suppression du contenu au préalable. Le fichier est donc d'abord vidé de son contenu, vous pouvez y écrire, et le lire ensuite. Si le fichier n'existe pas, il sera créé.

	"a+": ajout en lecture / écriture à la fin. Vous écrivez et lisez du texte à partir de la fin du fichier. Si le fichier n'existe pas, il sera créé.
*/

void creationJoueur(Joueur * j, char pseudo, char nom, char prenom){
	j-> pseudo = pseudo;
	j-> nom = nom;
	j-> prenom = prenom ;

	//initialisation des parties à 0
	j->partiesJouees = 0;
	j->partiesGagnees = 0;
	j->partiesPerdues = 0;
}

/*
chargementJoueurs{
	fopen()
}
*/

int nombreLigneTableJoueur() {
	FILE* fichier = NULL;
	fichier = fopen("repertoire/joueurs.txt", "r");

	int caraActuel = 0; //fgetc renvoi un int et non un char
	int ligne = 0;
	if (fichier != NULL) {
		while (caraActuel != EOF) 
		{
			caraActuel = fgetc(fichier);
			if (caraActuel == '\n')
			{
				++ligne;
			}
		}
	}
	else
	{
		printf("Impossible d'ouvrir le fichier repertoire/joueurs.txt");
	}
}

void ecritureJoueurs(Joueur* j){
	char pseudo = j->pseudo;
	char nom = j->nom;
	char prenom = j->prenom;
	int partiesJouees = j->partiesJouees;
	int partiesGagnees = j->partiesGagnees;
	int partiesPerdues = j->partiesPerdues;
	int partiesRatio = j->partiesRatio;

	FILE* fichier = NULL;
	fichier = fopen("repertoire/joueurs.txt", "a+");
	for
	if (fichier != NULL) {
		fseek(fichier, 0, SEEK_END);
		int id =  ;
		fprintf(
			fichier, 
			"%i;%c;%c;%c;%i;%i;%i;%f;",
			id, pseudo, nom, prenom, partiesJouees, partiesGagnees, partiesPerdues, partiesRatio
			);
	}
	else
	{
		printf("Impossible d'ouvrir le fichier repertoire/joueurs.txt");
	}
}

void affichageJoueurs(){
	FILE* fichier = NULL; //Cette structure est définie dans stdio.h
	fichier = fopen("repertoire/joueurs.txt", "r"); //"r": lecture seule
	
    int caraActuel = 0;
	if (fichier != NULL)
	{
		//lecture des caractères du fichier joueur 1 à 1
		do {
			caraActuel = fgetc(fichier);
			char = 
			printf("%s", chaine);
		} while (caraActuel != EOF);

		fclose(fichier);
	}

	else
	{
		printf("Impossible d'ouvrir le fichier repertoire/joueurs.txt");
	}
}



void matchJoueur(Joueur* j, char pseudo, bool victoire) {
	++(j->partiesJouees);

	if (victoire == true)
		++(j->partiesGagnees);
	if (victoire == false)
		++(j->partiesPerdues);

}

void sauvegarderJoueur(){
	;
}