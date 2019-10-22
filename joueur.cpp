/// @file joueur.cpp
#include <stdlib.h>
#include <stdio.h> //FILE structure est d�finie dans stdio.h

#include <string.h>

#include <assert.h>
#include <malloc.h>
#include <unittest.h>

#include "joueur.h"
#pragma warning(disable:4996)

#define TAILLE_MAX_LIGNE 1000
#define TAILLE_MAX_CELLULE 100
#define FILEPATH_JOUEURS "repertoire/joueurs.txt"

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

int nombreLignesTable(char FILEPATH_JOUEURS) {
	FILE* fichier = NULL;
	fichier = fopen(FILEPATH_JOUEURS, "r");

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
		printf("Impossible d'ouvrir le fichier %s .",FILEPATH_JOUEURS);
	}
	return ligne;
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
	if (fichier != NULL) {
		fseek(fichier, 0, SEEK_END); // on se place � la fin du document
		unsigned int id = nombreLignesTable("repertoire/joueurs.txt") ; //le nom des colonnes doit �tre compt� car on souhaite ID>0
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

void affichageTableJoueurs(char FILEPATH_JOUEURS){
	FILE* fichier = NULL; 
	fichier = fopen(FILEPATH_JOUEURS, "r"); //"r": lecture seule

    //unsigned int totallignes = 0;
    //totallignes = nombreLignesTable(filepath);

	fseek(fichier, 84, SEEK_SET); //84 caracteres de nom de colonnes plus retour-chariot
	if (fichier != NULL)
	{
	    char ligne[TAILLE_MAX_LIGNE] = "";
		while (fgets(ligne, TAILLE_MAX_LIGNE, fichier) != NULL) 
        {
			//solution1 strchr
			char id[TAILLE_MAX_CELLULE] = "";
			char pseudo[TAILLE_MAX_CELLULE] = "";
			char nom[TAILLE_MAX_CELLULE] = "";
			char prenom[TAILLE_MAX_CELLULE] = "";
			char partiesJouees[TAILLE_MAX_CELLULE] = "";
			char partiesGagnees[TAILLE_MAX_CELLULE] = "";
			char partiesPerdues[TAILLE_MAX_CELLULE] = "";
			char partiesRatio[TAILLE_MAX_CELLULE] = "";
			
			id = afficherInfo(ligne, 0, ';');
			char * chaine = strchr(ligne, ';');
			if (chaine != NULL)
			{
				pseudo=afficherInfo(chaine, 0, ';');
				chaine=strchr(chaine+1,';');
				nom=afficherInfo(chaine, 0, ';');
				chaine=strchr(chaine+1,';');
				prenom=afficherInfo(chaine, 0, ';');
				chaine=strchr(chaine+1,';');
				partiesJouees=afficherInfo(chaine, 0, ';');
				chaine=strchr(chaine+1,';');
				partiesGagnees=afficherInfo(chaine, 0, ';');
				chaine=strchr(chaine+1,';');
				partiesPerdues=afficherInfo(chaine, 0, ';');
				chaine=strchr(chaine+1,';');
				partiesRatio=afficherInfo(chaine, 0, ';');
			}

			printf("%s s'appelle %s %s, il a joue %s parties, son taux de victoire est de %s.\n ", 
			pseudo, prenom, nom, partiesJouees, partiesRatio);
		}
		/*
					//solution1 strchr
			char * chaine = strchr(ligne, ';');
			while (chaine != NULL)
			{
				printf ("found at %d\n",chaine-ligne+1);
    			chaine=strchr(chaine+1,'s');
			}
					//solution2 strtok
			char * chaine = strtok(ligne,";");
			while (chaine != NULL)
			{
			    printf ("%s\n",chaine);
			    chaine = strtok (NULL, ";");				
			}
		*/
		//lecture de indices
		/*
			char * chaine = strchr(ligne, ';');
			char id = 
			char pseudo = [chaine-ligne+1;]
			while (chaine != NULL)
			{
				printf ("found at %d\n",chaine-ligne+1);
    			chaine=strchr(chaine+1,'s');
			}
		*/

		//lecture de tokens (groupe de mots)
		/*
			char * chaine = strtok(ligne,";");

			printf ("%s\n",chaine)
			while (chaine != NULL)
			{
			    printf ("%s\n",chaine);
			    chaine = strtok (NULL, ";");				
			}
		*/
	//https://openclassrooms.com/forum/sujet/comprendre-strtok


		//lecture des caract�res du fichier joueur 1 � 1
		/*
		do {
			caraActuel = fgetc(fichier);
			char =
			printf("%s", chaine);
		} while (caraActuel != EOF);
		*/
	}

	else
	{
		printf("Impossible d'ouvrir le fichier repertoire/joueurs.txt");
	}
	fclose(fichier);
}

//afficherInfo
//affiche une chaine de caractère d une autre chaine de caractère string à partir d'un ranginitial donné jusqu'à un separateur
char afficherInfo(char * string, unsigned int ranginitial, char separateur){
	char* info = NULL ;
	info = (char*)malloc(TAILLE_MAX_CELLULE * sizeof(char));
	unsigned int i = 0 ;
	while (string[ranginitial] != separateur){
		info[i] = string[ranginitial];
		++ranginitial;
		++i;
	}
	info[i]='\0'; // on termine le mot par ce caractère pour indiquer qu il est fini
	return info ;
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
