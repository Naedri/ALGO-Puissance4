#include <stdlib.h>
#include <stdio.h>


#include <assert.h>
#include <malloc.h>
#include <unittest.h>

#include "joueur.h"
#pragma warning(disable:4996)

/*attention
le fichier dans lequel sont sauvegard�s les d�tails des joueurs doit avoir les d�tails suivants :
./repertoire/joueurs.csv
*/

/*
	"r": lecture seule. Vous pourrez lire le contenu du fichier, mais pas y �crire. Le fichier doit avoir �t� cr�� au pr�alable.

	"w": �criture seule. Vous pourrez �crire dans le fichier, mais pas lire son contenu. Si le fichier n'existe pas, il sera cr��.

	"a": mode d'ajout. Vous �crirez dans le fichier, en partant de la fin du fichier. Vous ajouterez donc du texte � la fin du fichier. Si le fichier n'existe pas, il sera cr��.

	"r+": lecture et �criture. Vous pourrez lire et �crire dans le fichier. Le fichier doit avoir �t� cr�� au pr�alable.

	"w+": lecture et �criture, avec suppression du contenu au pr�alable. Le fichier est donc d'abord vid� de son contenu, vous pouvez y �crire, et le lire ensuite. Si le fichier n'existe pas, il sera cr��.

	"a+": ajout en lecture / �criture � la fin. Vous �crivez et lisez du texte � partir de la fin du fichier. Si le fichier n'existe pas, il sera cr��.
*/

void creationJoueur(Joueur * j, char pseudo, char nom, char prenom){
	j-> pseudo = pseudo;
	j-> nom = nom;
	j-> prenom = prenom ;

	//initialisation des parties � 0
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
	FILE* fichier = NULL; //Cette structure est d�finie dans stdio.h
	fichier = fopen("repertoire/joueurs.txt", "r"); //"r": lecture seule
	
    int caraActuel = 0;
	if (fichier != NULL)
	{
		//lecture des caract�res du fichier joueur 1 � 1
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