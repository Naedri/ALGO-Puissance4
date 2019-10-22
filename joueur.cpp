/// @file joueur.cpp
#include <stdlib.h>
#include <stdio.h> //FILE structure est definie dans stdio.h
#include <string.h>
#include <malloc.h>

#include "joueur.h"

#define TAILLE_MAX_LIGNE 1000
#define TAILLE_MAX_CELLULE 100
#define FILEPATH_JOUEURS '/joueurs/joueurs.txt'

/*attention
le fichier dans lequel sont sauvegardes les details des joueurs doit avoir les details suivants :
./joueurs/joueurs.txt
*/

/* parametres de manipulation des fichiers
	"r": lecture seule. Vous pourrez lire le contenu du fichier, mais pas y ecrire. Le fichier doit avoir ete cree au prealable.
	"w": ecriture seule. Vous pourrez ecrire dans le fichier, mais pas lire son contenu. Si le fichier n'existe pas, il sera cree.
	"a": mode d'ajout. Vous ecrirez dans le fichier, en partant de la fin du fichier. Vous ajouterez donc du texte a la fin du fichier. Si le fichier n'existe pas, il sera cr��.
	"r+": lecture et ecriture. Vous pourrez lire et ecrire dans le fichier. Le fichier doit avoir ete cree au prealable.
	"w+": lecture et ecriture, avec suppression du contenu au préalable. Le fichier est donc d'abord vide de son contenu, vous pouvez y ecrire, et le lire ensuite. Si le fichier n'existe pas, il sera cr��.
	"a+": ajout en lecture / ecriture a la fin. Vous ecrivez et lisez du texte a partir de la fin du fichier. Si le fichier n'existe pas, il sera cree.
*/

//creationJoueur
//permet de verifier si le pseudo est déjà pris dans le fichier '/joueurs/joueurs.txt'
//permet de créer une variable Joueur avec le pseudo, nom et prénom
//initialise les statistiques des parties

void creationJoueur(Joueur * j, char pseudo, char nom, char prenom, const char* filepath_joueurs){
	FILE* fichier = NULL; 
	fichier = fopen(filepath, "r"); //"r": lecture seule
	j-> pseudo = pseudo;
	j-> nom = nom;
	j-> prenom = prenom ;

	//initialisation des parties a 0
	j->partiesJouees = 0;
	j->partiesGagnees = 0;
	j->partiesPerdues = 0;
	
}

/* definiition pseudo
 * definir char pseduo[10]
 * fget
 * vider buffer 
 * verification pas d espaces
 * verifiaction taille character < 8+1 (9)
 */

int nombreLignesTable(const char* filepath) {
	FILE* fichier = NULL;
	fichier = fopen(filepath, "r");

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
		printf("Impossible d'ouvrir le fichier %s .",filepath);
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
	float partiesRatio = j->partiesRatio;

	FILE* fichier = NULL; 
	fichier = fopen("joueurs/joueurs.txt", "a+");
	if (fichier != NULL) {
		fseek(fichier, 0, SEEK_END); // on se place a la fin du document
		unsigned int id = nombreLignesTable("joueurs/.txt") ; //le nom des colonnes doit etre compte car on souhaite ID>0
		fprintf(fichier,"%i;%c;%c;%c;%i;%i;%i;%f;", id, pseudo, nom, prenom, partiesJouees, partiesGagnees, partiesPerdues, partiesRatio) ;
	}
	else
	{
		printf("Impossible d'ouvrir le fichier repertoire/joueurs.txt");
	}
}

Joueur chargementJoueur( ){
	
	return j;
}

void affichageTableJoueurs(const char* filepath){	
	FILE* fichier = NULL; 
	fichier = fopen(filepath, "r"); //"r": lecture seule

	fseek(fichier, 84, SEEK_SET); //84 caracteres de nom de colonnes plus retour-chariot
	if (fichier != NULL)
	{
		char* ligne = NULL ;
		ligne = (char*)malloc(TAILLE_MAX_LIGNE * sizeof(char));

		while (fgets(ligne, TAILLE_MAX_LIGNE, fichier) != NULL) 
        {
			//on doit travailler sur des pointeurs car c est comme ca que la fonction AfficherInfo a ete ecrites
			
			char* id = NULL ;
			char* pseudo = NULL ;
			char* nom = NULL ;
			char* prenom = NULL ;
			char* partiesJouees = NULL ;
			char* partiesGagnees = NULL ;
			char* partiesPerdues = NULL ;
			char* partiesRatio = NULL ;
			
			*id = afficherInfo(ligne, 0, ';');
			char* chaine = strchr(ligne, ';');
			if (chaine != NULL)
			{
				*pseudo=afficherInfo(chaine, 0, ';');
				
				chaine=strchr(chaine+1,';');
				*nom=afficherInfo(chaine, 0, ';');
				
				chaine=strchr(chaine+1,';');
				*prenom=afficherInfo(chaine, 0, ';');
				
				chaine=strchr(chaine+1,';');
				*partiesJouees=afficherInfo(chaine, 0, ';');
				
				chaine=strchr(chaine+1,';');
				*partiesGagnees=afficherInfo(chaine, 0, ';');
				
				chaine=strchr(chaine+1,';');
				*partiesPerdues=afficherInfo(chaine, 0, ';');
				
				chaine=strchr(chaine+1,';');
				*partiesRatio=afficherInfo(chaine, 0, ';');
			}

			printf("%s s'appelle %s %s, il a joue %s parties, son taux de victoire est de %s.\n ", 
			pseudo, prenom, nom, partiesJouees, partiesRatio);
		}
	}

	else
	{
		printf("Impossible d'ouvrir le fichier repertoire/joueurs.txt");
	}
	fclose(fichier);
}

//afficherInfo
//affiche une chaine de caractere 
//a partir de string selectionnee a partir d'un ranginitial donne jusqu'a un separateur donne
char * afficherInfo(const char * string, unsigned int ranginitial, char separateur){
	char* info = NULL ;
	info = (char*)malloc(TAILLE_MAX_CELLULE * sizeof(char));
	unsigned int i = 0 ;
	while (string[ranginitial] != separateur){
		info[i] = string[ranginitial];
		++ranginitial;
		++i;
	}
	info[i]='\0'; // on termine le mot par ce caractère pour indiquer qu il est fini
	return info;
}

//matchJoueur
//modifie le score de parties gagnées ou perdues et donc partiesRatio d'un joueur pseudo donné
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
