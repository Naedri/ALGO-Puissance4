/// @file joueur.cpp
#include <stdlib.h> //initialisation à NULL
#include <stdio.h> //FILE structure est definie dans stdio.h
#include <string.h>

#include "joueur.h"

#define TAILLE_MAX_LIGNE 1000
#define TAILLE_MAX_CELLULE 100
#define FILEPATH_JOUEURS "/joueurs/"

/*attention
le dossier dans lequel sont sauvegardes les details des joueurs doit avoir les details suivants :
	./joueurs
le fichier contenant les profils de chaque joueurs est appelé par leur nom
*/


//creationJoueur
//permet de verifier si le pseudo est déjà pris dans le dossier accessible au chemin filepath_joueurs cad '/joueurs/'
//permet de créer une variable Joueur avec le pseudo, nom et prénom
//initialise les statistiques des parties
//attention la sauvegade du joueur dans un fichier doit être toutefois realisee avec sauvegarderJoueur
Joueur creationJoueur(char pseudo, char nom, char prenom, const char filepath_joueurs){
	//verifier si pseudo deja pris
	FILE *fichier = NULL; 
	
	//obtention du nom du fichier dans lequel sauvegarder la struct Joueur
	char* nomFichier = NULL;
	char typeFichier[] = ".txt";
	nomFichier = (char*)malloc((strlen(filepath_joueurs) + strlen(pseudo) + strlen(typeFichier) +1) * sizeof(char));
	strcpy(*nomFichier, filepath_joueurs) ;
	strcatPerso(*nomFichier, pseudo) ;
	strcatPerso(*nomFichier, typeFichier) ;
	fichier = fopen(*nomFichier, "r"); //"r": lecture seule n est pas creer si le fichier n existe pas
	
	//le fichier existe i.e le pseudo est deja pris
	if (fichier != NULL) {
		fprintf(stderr, "\nIL y a deja un Joueur qui porte le meme nom.\n");
		fclose(fichier); //on a ferme le fichier car on a du l ouvrir
		exit (1); 
	}
	
	//le fichier n existe pas cad le pseudo n est pas pris
	else (fichier == NULL) {
		//initialisation de la struct Joueur
		Joueur j = {"","","",0,0,0};
		
		//definition des donnees d identites
		j-> pseudo = pseudo;
		j-> nom = nom;
		j-> prenom = prenom;
		
		return j;
	}
}


//nombreLignesTable
//denombre le nombre de ligne pour un fichier dont le chemin est donne
int nombreLignesTable(const char filepath_table, char nomTable) {
	FILE *fichier = NULL; 
	
	//obtention du nom du fichier dans lequel sauvegarder la struct Joueur
	char nomFichier = strcat(filepath_table, nomTable) ;  
	nomFichier = strcat(nomFichier, ".txt") ;
	
	int caraActuel = 0; //fgetc renvoi un int et non un char
	int ligne = 0;
	if (fichier != NULL) {
		while (caraActuel != EOF)
		{
			caraActuel = fgetc(fichier);
			if (caraActuel == '\n')
				++ligne;
		}
	}
	else
		printf("Impossible d'ouvrir le fichier %s .",nomFichier);
	
	return ligne;
}

//sauvegarderJoueur
//ecrit un fichier dont le nom est 'pseudo.txt' etant une sauvegarde de la structure Joueur
//les détails du joueur j doivent avoir ete realises au préalable dans le main.cpp avec la fonction creationJoueur
void sauvegarderJoueur(Joueur j, const char filepath_joueurs){
	//obtention du nom du fichier dans lequel sauvegarder la struct Joueur
	(char *) ppseudo = j-> pseudo ;
	char nomFichier[20] = "";  
	nomFichier = strcat(filepath_joueurs, *ppseudo) ;  
	nomFichier = strcat(nomFichier, ".txt") ;
	
	//ouverture du fichier pour sauvegarde
	FILE *fichier = NULL;
	fichier = fopen (nomfichier, "wb");//writte only but binaire as we want to save struture Joueur
	if (fichier == NULL)
		fprintf(stderr, "\nIL y a eu une erreur dans l'ouverture du fichier\n"); 
		exit (1); 

	// ecriture de la structure Joueur dans le fichier
	fwrite (&j, sizeof(Joueur), 1, fichier);
	
	if(fwrite != 0) 
		printf("Le profil du joueur a été sauvegarder correctement.\n"); 
	else
		fprintf(stderr,"\nIl y a eu une erreur dans l'ecriture du fichier.\n"); 

	// fermeture du fichier
	fclose (fichier);
}

//chargementJoueur
//permet en indiquant le nom pseudo et le chemin path de retrouver le fichier suivant ./path/pseudo.txt
//afin de charger les details de la variable struct Joueur qui y sont sauvegarder
//renvoie la variable Joueur pour le pseudo associé
Joueur chargementJoueur(char pseudo,const char filepath_joueurs){
	FILE *fichier = NULL; 
	
	const char nomFichier = strcat(filepath_joueurs, pseudo) ;  
	nomFichier = strcat(nomFichier, ".txt") ;

	// ouverture du fichier pseudo.txt pour lecture
	fichier = fopen (nomFichier, "rb"); //read only
	if (fichier == NULL) 
		fprintf(stderr, "\nIL y a eu une erreur dans l'ouverture du fichier\n"); 
		exit (1);
	
	// lecture du fichier pseudo.txt jusqu'à la fin du fichier 
	while(fread(&fichier, sizeof(Joueur), 1, fichier)){
		return j;
	}

	// fermeture du fichier
	fclose (fichier);
}

//affichageJoueur
//fonction qui permet à partir du pseudo d'afficher les details du profil du joueur associe
void affichageJoueur(char pseudo, const char filepath_joueurs){	
	Joueur j = {"", "", "", 0, 0,0};
	j = chargementJoueur(pseudo,filepath_joueurs); //chargement des donnees via chargementJoueur(pseudo)

	if (j.pseudo == "") 
	{ 
		fprintf(stderr, "\nIL y a eu une erreur dans le chargement du fichier du Joueur associe.\n"); 
		exit (1); 
	}
	
	//affichage des details du profil avec une phrase
	printf("-%s s'appelle %s %s, il a joue %i parties, son taux de victoire est de %f.\n ", 
	j.pseudo, j.prenom, j.nom, j.partiesJouees, j.partiesRatio);
}

//matchJoueur
//modifie le score de parties gagnees ou perdues et donc partiesRatio d'un joueur avec le pseudo donne
//mais il faut tut de meme utiliser la fonctoin sauvegarder joueur pour reecrire un fichier pseudo.txt
void matchJoueur(Joueur* j, bool victoire) {
	++(j->partiesJouees);

	if (victoire == true)
		++(j->partiesGagnees);
		j->partiesRatio = j->partiesGagnees/j->partiesJouees;
	if (victoire == false)
		++(j->partiesPerdues);
		j->partiesRatio = j->partiesGagnees/j->partiesJouees;
}
