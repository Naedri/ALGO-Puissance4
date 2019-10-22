/// @file joueur.cpp
#include <stdlib.h>
#include <stdio.h> //FILE structure est definie dans stdio.h
#include <string.h>

#include "joueur.h"

#define TAILLE_MAX_LIGNE 1000
#define TAILLE_MAX_CELLULE 100
#define FILEPATH_JOUEURS '/joueurs/joueurs.txt'

/*attention
le dossier dans lequel sont sauvegardes les details des joueurs doit avoir les details suivants :
	./joueurs
le fichier contenant les profils de chaque joueurs est appelé par leur nom
*/



//creationJoueur
//permet de verifier si le pseudo est déjà pris dans le fichier '/joueurs/joueurs.txt'
//permet de créer une variable Joueur avec le pseudo, nom et prénom
//initialise les statistiques des parties
void creationJoueur(Joueur* j, char pseudo, char nom, char prenom, const char* filepath_joueurs){
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
/*
 * int main(){
 * definiition pseudo
 * definir char pseduo[10]
 * fget
 * vider buffer 
 * verification pas d espaces
 * verifiaction taille character < 8+1 (9)
 * }
 */

//nombreLignesTable
//denombre le nombre de ligne pour un fichier dont le chemin est donne
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

//sauvegarderJoueur
//ecrit un fichier dont le nom est 'pseudo.txt' étant une sauvegarde de la structure Joueur
//les détails du joueur j doivent avoir été réalisés au préalable dans le main.cpp avec la fonction creationJoueur
void sauvegarderJoueur(Joueur* j){
	(char *) pseudo = j-> pseudo ;
	FILE *fichier = NULL;
	const char nomFichier = strcat(pseudo,".txt") 
	
	//ouverture du fichier pour ecriture
	fichier = fopen (nomfichier, "w");//writte only
	if (fichier == NULL) 
	{ 
		fprintf(stderr, "\nIL y a eu une erreur dans l'ouverture du fichier\n"); 
		exit (1); 
	} 

	// ecriture de la structure Joueur dans le fichier
	fwrite (&j, sizeof(struct Joueur), 1, fichier); //attention peut etre pas &j
	
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
Joueur chargementJoueur(const char pseudo, const char filepath){
	FILE *fichier = NULL; 
	
	const char nomFichier = strcat(filepath, pseudo) ;  
	nomFichier = strcat(nomFichier, ".txt") ;

	// ouverture du fichier pseudo.txt pour lecture
	fichier = fopen (nomFichier, "r"); //read only
	if (fichier == NULL) 
	{ 
		fprintf(stderr, "\nIL y a eu une erreur dans l'ouverture du fichier\n"); 
		exit (1); 
	} 
	
	// lecture du fichier pseudo.txt jusqu'à la fin du fichier 
	while(fread(&fichier, sizeof(struct Joueur), 1, fichier)){
		return j;
	}

	// fermeture du fichier
	fclose (fichier);
}

//affichageJoueur
//etapes
//fonction qui permet à partir du pseudo d'afficher les détails du profil du joueur associé
//deplacement dans le dossier des joueurs
//recherche du fichier du joueur i.e. pseudo.txt
//ouverture du fichier pseudo.txt
//chargement des donnees via chargementJoueur(pseudo)
//affichage des détails du profil avec une phrase
//fermeture du fichier pseudo.txt
void affichageJoueur(const char pseudo, const char filepath){	
	Joueur j = {"", "", "", 0, 0,0};
	j = chargementJoueur(const char pseudo, const char filepath);	
	if (j.pseudo == "") 
	{ 
		fprintf(stderr, "\nIL y a eu une erreur dans le chargement du fichier du Joueur associe.\n"); 
		exit (1); 
	} 
	printf("-%s s'appelle %s %s, il a joue %i parties, son taux de victoire est de %f.\n ", 
	j.pseudo, j.prenom, j.nom, j.partiesJouees, j.partiesRatio);
}

//afficherInfo
//n est plus utile
//affiche une chaine de caractere 
//a partir de string selectionnee a partir d'un ranginitial donne jusqu'a un separateur donne
//doit renvoyer un pointeur car on utilise un malloc ?
char *afficherInfo(const char * string, unsigned int ranginitial, char separateur){
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
//modifie le score de parties gagnées ou perdues et donc partiesRatio d'un joueur avec le pseudo donné
//mais il faut tut de meme utiliser la fonctoin sauvegarder joueur pour reecrire un fichier pseudo.txt
void matchJoueur(Joueur* j, char pseudo, bool victoire) {
	++(j->partiesJouees);

	if (victoire == true)
		++(j->partiesGagnees);
	if (victoire == false)
		++(j->partiesPerdues);

}

//elemnt composant Joueur
{	
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
