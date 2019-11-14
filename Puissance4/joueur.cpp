/// @file joueur.cpp
#include <stdlib.h> //initialisation à NULL
#include <stdio.h> //FILE structure est definie dans stdio.h
#include <malloc.h>
#include <cassert>
#include <string.h>

#include "commun.h"
#include "joueur.h"
#include "menu.h"

//ubuntu
/*
#include <dirent.h>
*/
//windows
/**/
#include "dirent.h" //windows opendir() renvoie un pointeur de type DIR https://codeyarns.com/2014/06/06/how-to-use-dirent-h-with-visual-studio/
#pragma warning(disable : 4996) //ouverture de fichier et manipulation de chaine et d heure
#pragma warning(suppress : 4996) //ouverture de fichier et manipulation de chaine et d heure


/*attention
le dossier dans lequel sont sauvegardes les details des joueurs doit avoir les details suivants :
	./joueurs
le fichier contenant les profils de chaque joueurs est appelé par leur pseudo
*/


//creationJoueur
//permet de verifier si le pseudo est déjà pris dans le dossier accessible au chemin filepath_joueurs cad '/joueurs/'
//permet de créer une variable Joueur avec le pseudo, nom et prénom
//attention la sauvegade du joueur dans un fichier doit être toutefois realisee avec sauvegarderJoueur
void creationJoueur(Joueur* j, char *pseudo, char *nom, char *prenom, const char *filepath_joueurs, bool *redondance){
	//assert
	assert(j != NULL);
	assert(*redondance != false);
	assert(*pseudo != NULL && *nom != NULL && *prenom != NULL && *filepath_joueurs != NULL);
	//initialisation
	char typeFichier[] = ".txt";
	char* nomFichier = NULL;
	
	//malloc
	nomFichier = (char*)malloc((strlen(pseudo) + strlen(typeFichier) +1 ) * sizeof(char));
	if (nomFichier == NULL)
	{
		printf("\nProbleme d'allocation de la memoire pour la creationJoueur\n");
		exit(1);
	}
	assert(nomFichier != NULL);

	//obtention du nom du fichier dans lequel sauvegarder la struct Joueur
	strcpy(nomFichier, pseudo) ;
	strcat(nomFichier, typeFichier) ;

	//verifier si pseudo deja pris
	/*
	FILE *fichier = NULL;
	fichier = fopen(nomFichier, "r"); //"r": lecture seule n est pas creer si le fichier n existe pas

	//le fichier existe i.e le pseudo est deja pris

	if (fichier != NULL) {
	fprintf(stderr, "\nIL y a deja un Joueur qui porte le meme pseudo.\n");
	fclose(fichier); //on a ferme le fichier car on a du l ouvrir
	free(nomFichier);
	redondance = true;
	exit (1);
	}
	*/
	*redondance = fichierExiste(nomFichier, filepath_joueurs);

	if (*redondance == true){
		printf("\nIL y a deja un Joueur qui porte le meme pseudo.\n");
	}

	//le fichier n existe pas cad le pseudo n est pas pris
    //definition des donnees d identites
	if (*redondance == false) {
		//initialisation de la struct Joueur
		strcpy(j->pseudo , pseudo);
		strcpy(j->nom , nom);
		strcpy(j->prenom , prenom);
	}
}

//nombreLignesTable
//denombre le nombre de ligne pour un fichier dont le chemin est donne
int nombreLignesTable(char *filePathName){
	//assert
	assert(*filePathName != NULL);

	//initialisation
	FILE *fichier = NULL;
	const char* temp = NULL; // preparation de la chaine temporaire temporary string.

	//malloc
    temp = (const char*)malloc((strlen(filePathName)+1) * sizeof(const char));

	//attribution 
    temp = filePathName; //de la chaine temporaire a fichier d interet
    fichier = fopen (temp, "r");//lecture seulement

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
	//assert
	assert(j.pseudo != "" && *filepath_joueurs != NULL);
	
	//initilisation
	char* nomFichier = NULL;
	char typeFichier[] = ".txt";
	//malloc
	nomFichier = (char*)malloc((strlen(filepath_joueurs) + strlen(j.pseudo) + strlen(typeFichier) +1) * sizeof(char));
	if (nomFichier == NULL)
	{
		printf("\nProbleme d'allocation de la memoire pour la sauvegardeJoueur.\n");
		exit(1);
	}
	assert(nomFichier != NULL);

	//obtention du nom du fichier dans lequel sauvegarder la struct Joueur
	strcpy(nomFichier, filepath_joueurs) ;
	strcat(nomFichier, j.pseudo) ;
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
            printf("\nLe profil du joueur a ete sauvegarde correctement sous le nom suivant.");
			printf("\n%s", nomFichier);
        }
        else{
            fprintf(stderr,"\nIl y a eu une erreur dans l'ecriture du fichier.\n");
			printf("%s", nomFichier);
        }
    }

	// fermeture du fichier
	fclose (fichier);
	free(nomFichier);
}

//chargementJoueur
//permet en indiquant le nom pseudo et le chemin path de retrouver le fichier suivant ./path/pseudo.txt
//afin de charger les details de la variable struct Joueur qui y sont sauvegarder
//renvoie la variable Joueur pour le pseudo associé
Joueur chargementJoueur(char *pseudo,const char *filepath_joueurs){
	//assert
	assert(*pseudo != NULL && *filepath_joueurs != NULL);
	//initialisation
	char* nomFichier = NULL;
	char typeFichier[] = ".txt";

	//malloc
	nomFichier = (char*)malloc((strlen(filepath_joueurs) + strlen(pseudo) + strlen(typeFichier) +1) * sizeof(char));
	if (nomFichier == NULL)
	{
		printf("\nProbleme d'allocation de la memoire pour le chargementJoueur.\n");
		exit(1);
	}
	assert(nomFichier != NULL);

	//obtention du nom du fichier à partir dulequel charger la struct Joueur
	strcpy(nomFichier, filepath_joueurs) ;
	strcat(nomFichier, pseudo) ;
	strcat(nomFichier, typeFichier) ;

	// ouverture du fichier pseudo.txt pour lecture
    FILE *fichier = NULL;
	fichier = fopen (nomFichier, "rb"); //read only
	if (fichier == NULL){
		fprintf(stderr, "\nIL y a eu une erreur dans l'ouverture du fichier ou le pseudo indique ne correspond a aucun profil.\n");
		exit (1);
	}

	// lecture du fichier pseudo.txt jusqu'à la fin du fichier
	Joueur j = NOUVEAU_JOUEUR;
	fread(&j, sizeof(Joueur), 1, fichier);
	
	// fermeture du fichier
	fclose (fichier);
	free(nomFichier);
	return j;
}

//affichageJoueur
//fonction qui permet à partir du pseudo d'afficher les details du profil du joueur associe
void affichageJoueur(char *pseudo, const char *filepath_joueurs){
	//assert
	assert(*pseudo != NULL && *filepath_joueurs != NULL);
	//initialisation
	Joueur j = NOUVEAU_JOUEUR;
	j = chargementJoueur(pseudo,filepath_joueurs); //chargement des donnees via chargementJoueur(pseudo)

	if (strcmp(j.pseudo,"") != 1)
	{
		fprintf(stderr, "\nIL y a eu une erreur dans le chargement du fichier du Joueur associe.\n");
		exit (1);
	}

	//affichage des details du profil avec une phrase
	printf("\n-%s s'appelle %s %s, il a joue %i parties, son taux de victoire est de %f.\n ",
	j.pseudo, j.prenom, j.nom, j.partiesJouees, j.partiesRatio);
}

//matchJoueur
//modifie le score de parties gagnees ou perdues et donc partiesRatio d'un joueur avec le pseudo donne
//mais il faut tut de meme utiliser la fonctoin sauvegarder joueur pour reecrire un fichier pseudo.txt
void matchJoueur(Joueur* j, bool partieNulle, bool victoire){
	//assert
	assert(j->pseudo != NULL);
	//une partie vient d etre joue
	++(j->partiesJouees);
	
	if (partieNulle == false) {
		if (victoire == true){
			++(j->partiesGagnees);
		}

		else{
			++(j->partiesPerdues);	
		}		
	}
	//cast pour forcer le type
	j->partiesRatio = (float) j->partiesGagnees/j->partiesJouees;	
}

//getPseudo
//renvoie un pointeur de chaine de caracteres
//du pseudo de la varaible j de type struct Joueur
char* getPseudo(Joueur* j){
	//assert
	assert(j->pseudo != NULL);
	return j->pseudo ;
}

//affichageJoueursDispo
//fonction qui permet de lister les fichiers qui sont dans le dossier filepath_joueurs 
//et donc d'afficher les pseudos des joueurs enregistres
//prend en compte la possibilité qu il n a y ait pas de joueur
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
bool affichageJoueursDispo(const char *filepath_joueurs){
	//assert
	assert(*filepath_joueurs != NULL);
	//initialisation
	unsigned int nbrFichier = 0u;

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
		while ((fichier = readdir(dossier)) != NULL) {
			if ((strcmp(".", fichier->d_name) != 0) && (strcmp("..", fichier->d_name) != 0)) {
				++nbrFichier;
				printf("[%i] - '%s'\n", nbrFichier, fichier->d_name);
			}
		}
		if (nbrFichier == 0u)
		{
			printf("*\n");
			printf("Vous n avez pas encore creer de joueur veuillez en creer un.\n");
			printf("Vous allez etre redirige vers le menu principal.\n");
			printf("*\n");
			closedir(dossier);
			return false;
		}
		else {
			closedir(dossier);
			return true;
		}
	}
}

//nombreProfils
//affiche le nombre de fichiers ici profil présent dans un dossier donné
// peut être utilisée à la suite par la fonction choixProfil pour limiter le choix de l utilisateur
int nombreProfils(const char* filepath_joueurs){
	//assert
	assert( *filepath_joueurs != NULL);
	//initialisation
	int nbrFichier = 0 ;

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
		while ((fichier = readdir(dossier)) != NULL) {
			if ((strcmp(".", fichier->d_name) != 0) && (strcmp("..", fichier->d_name) != 0)) {
				++nbrFichier;
			}
		}
		closedir(dossier);
	}
	return nbrFichier;
}

//choixProfil
//permet a l utilisateur de rentrer un nombre correspondant à l ID de profil
//securise le choix des profils de joueurs
//maxProfil doit être obtenu nombreProfils
int choixProfil(int maxProfil) {
	//assert
	assert(maxProfil > 0);

	//initialisation
	int choix = 0;
	char c ; //verif du dernier caractere est un retour chariot.
	int nbrCaraEntres = 0;

	//while ((( (scanf("%d%c", &choixProfil, &c)) != 2 || c != '\n') && viderBuffer()) || choixProfil <= maxProfil) {
	//	printf("Veuillez entrez un numero valide.");
	//}
	while (choix <= 0 || nbrCaraEntres > 3 || c != '\n' || choix > maxProfil)
	{
		printf("Veuillez entrer le numero du profil que vous souhaitez selectionner pour affichage de ses details.\n");
		nbrCaraEntres = scanf("%d%c", &choix, &c);
	}
	printf("Le numero selectionne est %d", choix);
	return choix;
}

//getPseudoSelonID
//necessite l'initiation au préalable de chainePourPseudo
//mettera le pseudo associe a l id indique dans la chainePourPseudo
void getPseudoSelonID(char * chainePourPseudo, int id, const char* filepath_joueurs) {
	//assert
	assert(*filepath_joueurs != NULL);
	assert(id > 0);

	//initialisation
	const unsigned int tailleAvecTyp = (TAILLE_ID + 4); //strlen(".txt") pour pseudo.txt
	char pseudoAvecTyp[tailleAvecTyp] = "";
	int nbrFichier = 0u;

	//dirent.h
	DIR* dossier = opendir(filepath_joueurs); // DIR *opendir(const char *dirname);
	struct dirent* fichier = NULL; //struct dirent *readdir(DIR *dir);

	// opendir()
	// renvoie un pointeur NULL si le dossier n a pas ete trouve
	if (dossier == NULL) {
		printf("\nIL y a eu une erreur dans l'ouverture du dossier /joueurs.\n");
		exit(1);
	}
	else {
		// readdir()
		while ((fichier = readdir(dossier)) != NULL) {
			if ((strcmp(".", fichier->d_name) != 0) && (strcmp("..", fichier->d_name) != 0)) {
				++nbrFichier;
				if (nbrFichier == id) {
					strcpy(pseudoAvecTyp, fichier->d_name);
				}
			}
		}
		closedir(dossier);
	}
	//troncature du pseudo
	const unsigned int tailleSansTyp = (strlen(pseudoAvecTyp)-4);
	pseudoAvecTyp[tailleSansTyp] = 0;
	//assert(strlen(chainePourPseudo) >= strlen(pseudoAvecTyp));
	strcpy(chainePourPseudo,pseudoAvecTyp);
}

//menuProfil
// permet d'afficher les profils disponibles, 
// d'y selectionner et charger pour afficher le detail du profil selectionne
//de sortir de la boucle menuProfil
void menuProfil() {
	bool joueurDispo = false;
	joueurDispo = affichageJoueursDispo(FILEPATH_JOUEURS);
	if (joueurDispo == true){
		printf("Souhaitez vous : \n");
		printf("Tapez < 1 > : Pour retourner au Menu Principal.\n");
		printf("Tapez < 2 > : Pour afficher le profil detaille d'un joueur.\n");
		//initialisation
		int choixAfficheJ = 0;
		int nbrCaraEntres = 0;
		int choixMax = 2;
		//choix
		while (choixAfficheJ <= 0 || nbrCaraEntres > 3 || choixAfficheJ > choixMax)
		{
			printf("Veuillez entrer un numero valide.\n");
			nbrCaraEntres = scanf_s("%d", &choixAfficheJ);
		}

		if (choixAfficheJ == 1) {
			printf("Retour au Menu Principal.\n");
		}
		if (choixAfficheJ == 2) {
			int nbrProfilMAX = 0;
			nbrProfilMAX = nombreProfils(FILEPATH_JOUEURS); //scan des profil pour avoir nbr profil max
			int profilXID = 0;
			profilXID = choixProfil(nbrProfilMAX); //numero du profil choisi par l user obtenu

			char profilPseudo[TAILLE_ID] = "";
			getPseudoSelonID(profilPseudo, profilXID, FILEPATH_JOUEURS);//ecrit dans ProfilPseudo le pseudo associé à profilXID

			affichageJoueur(profilPseudo, FILEPATH_JOUEURS); //affichage du profil x
			menuProfil();
		}
	}
}

//menuCreationProfil
void menuCreationProfil() {
	printf("\n\n***** Creation d'un nouveau profil *****\n\n");
	Joueur j = NOUVEAU_JOUEUR;
	Joueur* pj = &j;
	char pseudo[TAILLE_ID]="";
	char nom[TAILLE_ID]="";
	char prenom[TAILLE_ID]="";
	bool redondanceProfil = true;
	bool* predondanceProfil = &redondanceProfil;
	do {
		printf("Saisissez le PSEUDO du joueur : ");
		scanf_s("%9s", pseudo, (unsigned)_countof(j.pseudo));
		viderBuffer();

		printf("Saisissez le PRENOM du joueur : ");
		scanf_s("%9s", prenom, (unsigned)_countof(j.prenom));
		viderBuffer();

		printf("Saisissez le NOM du joueur : ");
		scanf_s("%9s", nom, (unsigned)_countof(j.nom));
		viderBuffer();

		creationJoueur(pj, pseudo, nom, prenom, FILEPATH_JOUEURS, predondanceProfil);

	} while (prenom != "" && nom != "" && pseudo != "" && redondanceProfil != false);

	//affichage des details du profil avec une phrase
	printf("\n-%s s'appelle %s %s, il a joue %i parties, son taux de victoire est de %f.\n ",
		j.pseudo, j.prenom, j.nom, j.partiesJouees, j.partiesRatio);
	sauvegarderJoueur(j, FILEPATH_JOUEURS);
	
	//affichage des nouveau profil
	printf("\nAffichage des modifications\n.");
	affichageJoueursDispo(FILEPATH_JOUEURS);
	printf("Vous allez etre redirige vers le menu principal.\n");
}
