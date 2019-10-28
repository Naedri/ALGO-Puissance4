/// @file joueur.cpp
#include <stdlib.h> //initialisation à NULL
#include <stdio.h> //FILE structure est definie dans stdio.h
#include <string.h>
#include <malloc.h>
#include <dirent.h> //opendir() renvoie un pointeur de type DIR

#include "joueur.h"

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
Joueur creationJoueur(char *pseudo, char *nom, char *prenom, const char *filepath_joueurs){

	//obtention du nom du fichier dans lequel sauvegarder la struct Joueur
	char* nomFichier = NULL;
	char typeFichier[] = ".txt";
	nomFichier = (char*)malloc((strlen(filepath_joueurs) + strlen(pseudo) + strlen(typeFichier) +1) * sizeof(char));
	strcpy(nomFichier, filepath_joueurs) ;
	strcat(nomFichier, pseudo) ;
	strcat(nomFichier, typeFichier) ;

	//verifier si pseudo deja pris
	FILE *fichier = NULL;
	fichier = fopen(nomFichier, "r"); //"r": lecture seule n est pas creer si le fichier n existe pas

	//le fichier existe i.e le pseudo est deja pris
	if (fichier != NULL) {
		fprintf(stderr, "\nIL y a deja un Joueur qui porte le meme nom.\n");
		fclose(fichier); //on a ferme le fichier car on a du l ouvrir
		exit (1);
	}
	//le fichier n existe pas cad le pseudo n est pas pris
    //definition des donnees d identites
	else {
	     //initialisation de la struct Joueur
        Joueur *j = NULL;
		strcpy(j->pseudo , pseudo);
		strcpy(j->nom , nom);
		strcpy(j->prenom , prenom);
		return *j;
	}
}

//nombreLignesTable
//denombre le nombre de ligne pour un fichier dont le chemin est donne
int nombreLignesTable(char *filePathName){
	FILE *fichier = NULL;

    const char* temp = NULL; // Prepare temporary string.
    temp = (const char*)malloc((strlen(filePathName)+1) * sizeof(const char));

    temp = filePathName;  // Move our scanned string.
    fichier = fopen (temp, "r");//read only

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
		printf("Impossible d'ouvrir le fichier %c .",*filePathName);

	return ligne;
}

//sauvegarderJoueur
//ecrit un fichier dont le nom est 'pseudo.txt' etant une sauvegarde de la structure Joueur
//les détails du joueur j doivent avoir ete realises au préalable dans le main.cpp avec la fonction creationJoueur
void sauvegarderJoueur(Joueur j, const char *filepath_joueurs){

    //creation pointeur sur pseudo de Joueur j
    char* pseudo =NULL;
    strcpy(pseudo, j.pseudo);

    //Joueur *j = NULL;
    //strcpy(j->pseudo , pseudo);
    //pseudo= &j.pseudo;

	//obtention du nom du fichier dans lequel sauvegarder la struct Joueur
	char* nomFichier = NULL;
	char typeFichier[] = ".txt";
	nomFichier = (char*)malloc((strlen(filepath_joueurs) + strlen(pseudo) + strlen(typeFichier) +1) * sizeof(char));
	strcpy(nomFichier, filepath_joueurs) ;
	strcat(nomFichier, pseudo) ;
	strcat(nomFichier, typeFichier) ;


	//ouverture du fichier pour sauvegarde
	FILE *fichier = NULL;
	fichier = fopen (nomFichier, "wb");//writte only but binaire as we want to save struture Joueur
	if (fichier == NULL){
        fprintf(stderr, "\nIL y a eu une erreur dans l'ouverture du fichier\n");
		exit (1);
	}

    else {
        // ecriture de la structure Joueur dans le fichier
        int count = fwrite (&j, sizeof(Joueur), 1, fichier);
		
		// if(fwrite != 0){
        if(count >= 1){
            printf("Le profil du joueur a été sauvegarde correctement.\n");
        }
        else{
            fprintf(stderr,"\nIl y a eu une erreur dans l'ecriture du fichier.\n");
        }
    }

	// fermeture du fichier
	fclose (fichier);
}

//chargementJoueur
//permet en indiquant le nom pseudo et le chemin path de retrouver le fichier suivant ./path/pseudo.txt
//afin de charger les details de la variable struct Joueur qui y sont sauvegarder
//renvoie la variable Joueur pour le pseudo associé
Joueur chargementJoueur(char *pseudo,const char *filepath_joueurs){

	//obtention du nom du fichier à partir dulequel charger la struct Joueur
	char* nomFichier = NULL;
	char typeFichier[] = ".txt";
	nomFichier = (char*)malloc((strlen(filepath_joueurs) + strlen(pseudo) + strlen(typeFichier) +1) * sizeof(char));
	strcpy(nomFichier, filepath_joueurs) ;
	strcat(nomFichier, pseudo) ;
	strcat(nomFichier, typeFichier) ;

	// ouverture du fichier pseudo.txt pour lecture
    FILE *fichier = NULL;
	fichier = fopen (nomFichier, "rb"); //read only
	if (fichier == NULL){
		fprintf(stderr, "\nIL y a eu une erreur dans l'ouverture du fichier\n");
		exit (1);
	}

	// lecture du fichier pseudo.txt jusqu'à la fin du fichier
	Joueur j = NOUVEAU_JOUEUR;
	fread(&j, sizeof(Joueur), 1, fichier);

	// fermeture du fichier
	fclose (fichier);
	return j;
}

//affichageJoueur
//fonction qui permet à partir du pseudo d'afficher les details du profil du joueur associe
void affichageJoueur(char *pseudo, const char *filepath_joueurs){
	Joueur j = NOUVEAU_JOUEUR;
	j = chargementJoueur(pseudo,filepath_joueurs); //chargement des donnees via chargementJoueur(pseudo)

	if (strcmp(j.pseudo,"") != 1)
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
void matchJoueur(Joueur* j, bool partieNulle, bool victoire){
	++(j->partiesJouees);
	
	if (partieNulle == false) {
		if (victoire == true){
			++(j->partiesGagnees);
		}

		else{
			++(j->partiesPerdues);	
		}		
	}

	j->partiesRatio = j->partiesGagnees/j->partiesJouees;	
}

//getPseudo
//renvoie un pointeur de chaine de caracteres
//du pseudo de la varaible j de type struct Joueur
char* getPseudo(Joueur* j){
	return j->pseudo ;
}

//affichageJoueursDispo
//fonction qui permet de lister les fichiers qui sont dans le dossier filepath_joueurs et donc d'afficher les pseudos des joueurs enregistres
//opendir 
//	https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.bpxbd00/rtoped.htm
//	Si succès renvoie un pointeur vers un objet DIR. Cet objet décrit le répertoire et est utilisé dans les opérations suivantes sur le répertoire, de la même manière que les objets FILE sont utilisés dans les opérations d'E/S de fichiers.
//readdir
//	https://www.ibm.com/support/knowledgecenter/SSLTBW_2.3.0/com.ibm.zos.v2r3.bpxbd00/rtread.htm#rtread
//	En cas de succès, readdir() renvoie un pointeur vers une structure de répertoire décrivant l'entrée de répertoire suivante dans le flux de répertoire. Quand readdir() atteint la fin du flux de répertoire, il retourne un pointeur NULL.
// struct dirent {
    // ino_t          d_ino;       /* inode number */
    // off_t          d_off;       /* offset to the next dirent */
    // unsigned short d_reclen;    /* length of this record */
    // unsigned char  d_type;      /* type of file; not supported
    // char           d_name[256]; /* filename */
// };
void affichageJoueursDispo(const char *filepath_joueurs){
	//dirent.h
    DIR *dossier = opendir(filepath_joueurs); // DIR *opendir(const char *dirname);
	struct dirent *fichier = NULL ; //struct dirent *readdir(DIR *dir);
	
	// opendir()
	// renvoie un pointeur NULL si le dossier n a pas ete trouve
    if (dossier == NULL) { 
		printf("\nIL y a eu une erreur dans l'ouverture du dossier /joueurs.\n");
		exit (1);
    }
    else {
		 // readdir()
		printf("\nLes pseudos des joueurs enregistres sont les suivants :\n");
		while ((fichier = readdir(dossier)) != NULL)
				printf("- '%s'\n", fichier->d_name);
		closedir(dossier);
	}
}
