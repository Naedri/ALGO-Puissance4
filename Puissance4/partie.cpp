/// @file partie.cpp
#include <stdlib.h> //initialisation à NULL
#include <stdio.h> //FILE structure est definie dans stdio.h
#include <string.h>
#include <malloc.h>
#include <cassert>
#include <time.h> //nom de la sauvegarde de la partie

#include "commun.h"
#include "partie.h"
#include "joueur.h"
#include "T2d.h"

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
le dossier dans lequel sont sauvegardes les parties doit avoir les details suivants :
	./parties
le fichier contenant une partie est appelé par les pseudos des deux joueurs et la date et l heure de creation de la partie :
	date-heure-joueur1-joueur2
*/

//creationPartie
//on assume qu il n y a pas besoin de verifier si la partie existe deja, car son nom varie en fonction de sa date de creation a l heure pres
//permet de créer une variable Partie avec les pseudos des deux joueurs (chaines), leurs symboles(caracteres), les details du joueur actif, l'etat de la grille, le premier joueur a avoir joue et le nombre de tour effectué
//initialise les détails de la partie 
//attention la sauvegade de la partie dans un fichier doit être toutefois realisee avec sauvegarderPartie
void creationPartie(Partie* p,char *joueur1, unsigned int symbole1, char *joueur2, unsigned int symbole2, char *joueurActif, unsigned int symboleActif, char *joueurInitial, unsigned int nbrTour, unsigned int grilleLargeur, unsigned int grilleHauteur, char* grilleChar){
	//assert
	assert(p != NULL);
	assert(*joueur1 != NULL && *joueur2 != NULL && *joueurActif != NULL && *joueurInitial != NULL);
	assert(grilleLargeur != 0 && grilleHauteur != 0 && *grilleChar != NULL);
	assert(symbole1 < 3 && symbole2 < 3 && symboleActif < 3);
	assert( (grilleLargeur * grilleHauteur) <= TAILLE_MAX_GRILLE);

	//initialisation de la struct Partie
	strcpy(p->joueur1, joueur1);
	p->symbole1 = symbole1;
	strcpy(p->joueur2, joueur2);
	p->symbole2=symbole2;

	//par default le joueur1 est le premier joueur donc le joueurActif lors de la creation du jeu
	strcpy(p->joueurActif, joueurActif);
	p->symboleActif = symboleActif;
	strcpy(p->joueurInitial, joueurInitial);
	p->nbrTour = 0u;
	
	//date de creation
	char date[TAILLE_DATEHEURE]=""; 
    time_t temps = time(NULL); 
    strftime(date, sizeof(date), "%Y%m%d-%H%M%S", localtime(&temps));
    strcpy(p->dateCreation, date);
	
	//initialisation de la grille
	T2d g = NOUVELLE_TABLE;
	init(&g, grilleLargeur, grilleHauteur);
	p->grilleChar = g.grille; //même valeur même adresse
}

//sauvegarderPartie
// attention seules les parties non finies peuvent être sauvegardees
//ecrit un fichier dont le nom est 'pseudo.txt' etant une sauvegarde de la partie Partie
//les détails de la partie j doivent avoir ete realises au préalable dans le main.cpp (exemple initialisation avec la fonction creationPartie)
void sauvegarderPartie(Partie p, const char *filepath_joueurs){
	//assert
	assert(p.joueur1 != "" && p.joueur2 != "" && p.dateCreation != "" );
	assert(*filepath_joueurs != NULL);

	//obtention du nom du fichier dans lequel sauvegarder la struct Partie
	//separateur pseudo
	char sep[] = "-";
	//type
	char typeFichier[] = ".txt";

	//nomFichier
	char* nomFichier = NULL;
	//malloc
	nomFichier = (char*)malloc((strlen(filepath_joueurs) + strlen(p.joueur1) + (strlen(sep)*2) + strlen(p.joueur2) + strlen(p.dateCreation) + strlen(typeFichier) +1) * sizeof(char));
	if (nomFichier == NULL)
	{
		printf("Probleme d'allocation de la memoire pour le sauvegardePartie");
		exit(1);
	}
	assert(nomFichier != NULL);

	//concatenation pour nom Fichier
	strcat(nomFichier, filepath_joueurs) ;
	strcat(nomFichier, p.joueur1) ;
	strcat(nomFichier, sep) ;
	strcat(nomFichier, p.joueur2) ;
	strcat(nomFichier, sep) ;
	strcat(nomFichier, p.dateCreation) ;
	strcat(nomFichier, typeFichier) ;

	//ouverture du fichier pour sauvegarde
	FILE *fichier = NULL;
	fichier = fopen (nomFichier, "wb");//writte only but binaire as we want to save struture Joueur
	if (fichier == NULL){
        fprintf(stderr, "\nIL y a eu une erreur dans l'ouverture du fichier\n");
		exit(1);
	}

    else {
        // ecriture de la structure Joueur dans le fichier
        int count = fwrite (&p, sizeof(Partie), 1, fichier);
		
		// if(fwrite != 0){
        if(count >= 1){
            printf("La partie a été sauvegardee correctement sous le nom suivant : \n");
            printf("%s",nomFichier);
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

//chargementPartie
//permet de charger une structure Partie
//la liste des parties sauvegardees est accessbile avec la fonction affichagePartiesDispo
//renvoie la variable Partie pour le nom associé
Partie chargementPartie(char *nomPartie, const char *filepath_parties){
	//assert
	assert(*nomPartie != NULL);
	assert(*filepath_parties != NULL);

	//initialisation
	char* nomFichier = NULL;
	char typeFichier[] = ".txt";
	//malloc
	nomFichier = (char*)malloc((strlen(filepath_parties)+ NAME_MAX_PARTIE + strlen(typeFichier) +1) * sizeof(char));
	if (nomFichier == NULL)
	{
		printf("Probleme d'allocation de la memoire pour le chargementPartie");
		exit(1);
	}
	assert(nomFichier != NULL);

	//obtention du nom du fichier à partir dulequel charger la struct Partie
	strcat(nomFichier, filepath_parties);
	strcat(nomFichier, nomPartie);
	strcat(nomFichier, typeFichier);

	// ouverture du fichier pseudo.txt pour lecture
    FILE *fichier = NULL;
	fichier = fopen (nomFichier, "rb"); //read only
	if (fichier == NULL){
		fprintf(stderr, "\nIL y a eu une erreur dans l'ouverture du fichier\n");
		exit(1);
	}


	// lecture du fichier  pseudo1-pseudo2-dateHeure.txt
	Partie p = NOUVELLE_PARTIE;
	fread(&p, sizeof(Partie), 1, fichier);

	// fermeture du fichier
	fclose (fichier);
	free(nomFichier);
	return p;
}

//affichagePartiesDispo
//fonction qui d'afficher graphiquement le détails des parties sauvegarder en cours
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
void affichagePartiesDispo(const char *filepath_parties){
	//assert
	assert(filepath_parties != NULL);
	//initialisation
	unsigned int nbrFichier = 0u;

	//dirent.h
    DIR *dossier = opendir(filepath_parties); // DIR *opendir(const char *dirname);
	struct dirent *fichier = NULL ; //struct dirent *readdir(DIR *dir);
	
	// opendir()
	// renvoie un pointeur NULL si le dossier n a pas ete trouve
    if (dossier == NULL) { 
		printf("\nIL y a eu une erreur dans l'ouverture du dossier /parties.\n");
		exit(1);
    }

    else {
		 // readdir()
		printf("\nLes parties enregistrees sont les suivantes :\n");
		while ((fichier = readdir(dossier)) != NULL){
			//strcmp(fichier->d_name,'.') ne marche pas mais
			if( (strcmp(".", fichier->d_name)!=0) && (strcmp("..", fichier->d_name)!=0) ){
				++nbrFichier;
				printf("[%i] - %s \n", nbrFichier, fichier->d_name) ;
			}
		}
		if (nbrFichier == 0u)
		{
			printf("*\n");
			printf("Vous n avez pas encore creer de partie veuillez en creer une.\n");
			printf("*\n");
		}
		closedir(dossier);
	}
}


//nombreParties
//affiche le nombre de fichiers ici partie présente dans un dossier donné
// peut être utilisée à la suite par la fonction choixPartie pour limiter le choix de l utilisateur
unsigned int nombreParties(const char* filepath_parties) {
	//assert
	assert(*filepath_parties != NULL);
	//initialisation
	unsigned int nbrFichier = 0u;

	//dirent.h
	DIR* dossier = opendir(filepath_parties); // DIR *opendir(const char *dirname);
	struct dirent* fichier = NULL; //struct dirent *readdir(DIR *dir);

	// opendir()
	// renvoie un pointeur NULL si le dossier n a pas ete trouve
	if (dossier == NULL) {
		printf("\nIL y a eu une erreur dans l'ouverture du dossier /parties.\n");
		exit(1);
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

//choixPartie
//permet a l utilisateur de rentrer un nombre correspondant à l ID de partie
//securise le choix des parties
//maxPartie doit être obtenu nombreParties
int choixPartie(unsigned int maxPartie) {
	//assert
	assert(maxPartie != 0);
	//initialisation
	unsigned int choixPartie = 0u;
	char c = NULL; //verif du dernier caractere est un retour chariot.
	printf("Entrez le numero de la partie que vous souhaitez continuer.\n");
	while ((((scanf("%i%c", &choixPartie, &c)) != 2 || c != '\n') && viderBuffer()) || choixPartie <= maxPartie) {
		printf("Veuillez entrez un numero valide.");
	}
	return choixPartie;
}

//getNomPartieSelonID
//necessite l'initiation au préalable de chainePourNomPartie
//mettera le nomPartie associe a l id indique dans la chainePourNomPartie
void getNomPartieSelonID(char* chainePourNomPartie, unsigned int id, const char* filepath_parties) {
	//assert
	assert(*filepath_parties != NULL);
	assert(id != 0u);

	//initialisation
	const unsigned int tailleAvecTyp = (TAILLE_ID + 4); //strlen(".txt") pour nomPartie.txt
	char nomPartieAvecTyp[tailleAvecTyp] = "";
	unsigned int nbrFichier = 0u;

	//dirent.h
	DIR* dossier = opendir(filepath_parties); // DIR *opendir(const char *dirname);
	struct dirent* fichier = NULL; //struct dirent *readdir(DIR *dir);

	// opendir()
	// renvoie un pointeur NULL si le dossier n a pas ete trouve
	if (dossier == NULL) {
		printf("\nIL y a eu une erreur dans l'ouverture du dossier /parties.\n");
		exit(1);
	}
	else {
		// readdir()
		printf("\nLes nomParties des parties enregistres sont les suivants :\n");
		while ((fichier = readdir(dossier)) != NULL) {
			if ((strcmp(".", fichier->d_name) != 0) && (strcmp("..", fichier->d_name) != 0)) {
				++nbrFichier;
				if (nbrFichier == id) {
					strcpy(nomPartieAvecTyp, fichier->d_name);
				}
			}
		}
		closedir(dossier);
	}
	//troncature du nomPartie
	const unsigned int tailleSansTyp = (strlen(nomPartieAvecTyp) - 4);
	nomPartieAvecTyp[tailleSansTyp] = 0;
	strcpy(chainePourNomPartie, nomPartieAvecTyp);
}

// menuPartie
// permet d'afficher les nomParties disponibles, 
// attention seules les parties non finies peuvent être sauvegardees
// donc pas besoin de verifier si la partie est terminee ou non
// d'y selectionner et charger pour ensuite continuer la partie
// de sortir de la boucle menuPartie
// Partie partie = NOUVELLE_PARTIE; //a faire avant
// partie = menuPartie(partie); //a faire avant
Partie menuPartie(Partie p) {
	int choixChargementP = 0;
	int choixJouerP = 0;

	affichagePartiesDispo(FILEPATH_PARTIES);
	printf("Souhaitez vous : \n");
	printf("Retourner au Menu Principal : entrez 1.\n");
	printf("Charger une partie parmi les parties en cours sauvegardees pour la continuer : entrez 2.\n");
	char c = NULL; //verif du dernier caractere est un retour chariot.
	while ((((scanf("%i%c", &choixChargementP, &c)) != 2 || c != '\n') && viderBuffer()) || choixChargementP != 1 || choixChargementP != 2) {
		printf("Veuillez entrez un numero valide.\n");
	}
	if (choixChargementP == 1) {
		printf("Retour au Menu Principal.\n");
	}
	if (choixChargementP == 2) {
		unsigned int nbrPartieMAX = 0u;
		nbrPartieMAX = nombreParties(FILEPATH_PARTIES); //scan des Parties pour avoir le nombre de Partie max enregistreesnbr
		unsigned int nomPartieXID = 0u;
		nomPartieXID = choixPartie(nbrPartieMAX); //numero de la Partie choisi par l user obtenu

		char nomPartie[TAILLE_ID] = "";
		getNomPartieSelonID(nomPartie, nomPartieXID, FILEPATH_PARTIES);

		p = chargementPartie(nomPartie, FILEPATH_PARTIES); //chargement de la Partie x
		printf("Preparez vous.\n");
	}

	return p;
}
//if (partie.grilleChar != NULL){ //a faire apres
//	play(p)
	////// pas forcement cela
	////Joueur j1 = NOUVEAU_JOUEUR;
	////Joueur j2 = NOUVEAU_JOUEUR;
	////j1 = chargementJoueur(p->joueur1,FILEPATH_JOUEURS);
	////j2 = chargementJoueur(p->joueur2,FILEPATH_JOUEURS);
	////play(&j1, &j2);
//}
/*
void play(joueur* player1, joueur* player2) {
	jeu j;  //instanciation du jeu
	initJeu(&j, getName(player1), getName(player2)); // initialisation des paramètres du jeu (cf jeu.h)
	T2d t; // creation de la grille (peut être intégré dans l'init jeu
	init(&t, 7u, 6u);
	char s[250];
	char col;
	unsigned int ligne;
	unsigned int nbreToursMax = getHauteur(&t) * getLargeur(&t);
	do {
		incrementTurn(&j);
		setSymboleActif(&j);//on met à jour les valeurs à chaque tour
		setJoueurActif(&j);//on met à jour les valeurs à chaque tour
		printf("Tour : %i ## Au tour du joueur %s qui joue les %c##\n", getNbreTours(&j), getJoueurActif(&j), getSymboleActif(&j));
		col = choixJoueur(&t);
		ligne = placerJeton(&t, col, getSymboleActif(&j));
		toString(&t, s);
		printf("%s\n", s);
	} while (getNbreTours(&j) < nbreToursMax && !estVictoire(&t, col, ligne));
	if (getNbreTours(&j) < nbreToursMax)
		printf("Felications au joueur %s qui remporte la partie !\n", getJoueurActif(&j));
	else
		puts("Dommage ! Match nul !");
}

Jeu creationJeu(){
	;
}

void setSymboleActif(jeu* j) {
	getNbreTours(j) % 2 != 0 ? j->SymboleActif = getSymbole(1) : j->SymboleActif = getSymbole(2); // le nombre de tour est impair ? c'est le tour du joueur 1 (le premier tour est pour le joueur 1), sinon c'est le tour du joueur 2.
}

char getSymboleActif(jeu* j) {
	return j->SymboleActif;
}

void incrementTurn(jeu* j) {

	++(j->nbretours);
}

unsigned int getNbreTours(jeu* j) {
	return j->nbretours;
}

void setJoueurActif(jeu* j) {
	getSymboleActif(j) == getSymbole(1) ? j->joueurActif = j->j1Pseudo : j->joueurActif = j->j2Pseudo; // On se fie au symbole actif, si c'est une 'X' c'est j1 sinon c'est j2
}

char* getJoueurActif(jeu* j) {
	return j->joueurActif;
}
*/
