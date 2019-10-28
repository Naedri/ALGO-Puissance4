/// @file partie.cpp
#include <stdlib.h> //initialisation � NULL
#include <stdio.h> //FILE structure est definie dans stdio.h
#include <string.h>
#include <malloc.h>
#include <dirent.h> //opendir() renvoie un pointeur de type DIR
#include <time.h> //nom de la sauvegarde de la partie

#include "partie.h"
#include "joueur.h"
#include "T2d.h"


/*attention
le dossier dans lequel sont sauvegardes les parties doit avoir les details suivants :
	./parties
le fichier contenant une partie est appel� par les pseudos des deux joueurs et la date et l heure de creation de la partie :
	date-heure-joueur1-joueur2
*/

//creationPartie
//on assume qu il n y a pas besoin de verifier si la partie existe deja, car son nom varie en fonction de sa date de creation a l heure pres
//permet de cr�er une variable Partie avec les pseudos des deux joueurs, leurs symboles, les details du joueur actif, l'etat de la grille, le premier joueur a avoir joue et le nombre de tour effectu�
//initialise les d�tails de la partie 
//attention la sauvegade de la partie dans un fichier doit �tre toutefois realisee avec sauvegarderPartie
Partie creationPartie(char *joueur1, char *symbole1, char *joueur2, char *symbole2, unsigned int grilleLargeur, unsigned int grilleHauteur){

	//initialisation de la struct Partie
	Partie *p = NULL;
	strcpy(p->joueur1, joueur1);
	strcpy(p->symbole1, symbole1);
	strcpy(p->joueur2, joueur2);
	strcpy(p->symbole2, symbole2);

	//par default le joueur1 est le premier joueur donc le joueurActif lors de la creation du jeu
	strcpy(p->joueurActif, joueur1);
	strcpy(p->symboleActif, symbole1);
	strcpy(p->joueurInitial, joueur1);
	p->nbrTour = 0u;
	
	//date de creation
	char dateCreation[TAILLE_DATEHEURE]=""; 
    time_t temps = time(NULL); 
    strftime(dateCreation, sizeof(dateCreation), "%Y%m%d-%H%M%S", localtime(&temps));
    strcpy(p->dateCreation, dateCreation);
	
	//initialisation de la grille
	T2d g = NOUVELLE_GRILLE;
	init(&g, grilleLargeur, grilleHauteur);
	p->grille = &g; //m�me valeur m�me adresse
	
	return *p;
}

//sauvegarderPartie
//ecrit un fichier dont le nom est 'pseudo.txt' etant une sauvegarde de la partie Partie
//les d�tails de la partie j doivent avoir ete realises au pr�alable dans le main.cpp (exemple initialisation avec la fonction creationPartie)
void sauvegarderPartie(Partie p, const char *filepath_joueurs){
	
	//obtention du nom du fichier dans lequel sauvegarder la struct Partie
	//nom joueur
    char* joueur1 =NULL;
    strcpy(joueur1, p.joueur1);
    char* joueur2 =NULL;
    strcpy(joueur2, p.joueur2);
	//separateur pseudo
	char sep[] = "-";
	//type
	char typeFichier[] = ".txt";
	//heure
	char* dateCreation =NULL;
    strcpy(dateCreation, p.dateCreation);
    
    //concatenation pour nom Fichier
	//nomFichier
	char* nomFichier = NULL;
	nomFichier = (char*)malloc((strlen(filepath_joueurs) + strlen(joueur1) + (strlen(sep)*2) + strlen(joueur2) + strlen(dateCreation) + strlen(typeFichier) +1) * sizeof(char));
	strcpy(nomFichier, filepath_joueurs) ;
	strcat(nomFichier, joueur1) ;
	strcat(nomFichier, sep) ;
	strcat(nomFichier, joueur2) ;
	strcat(nomFichier, sep) ;
	strcat(nomFichier, dateCreation) ;
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
        int count = fwrite (&p, sizeof(Partie), 1, fichier);
		
		// if(fwrite != 0){
        if(count >= 1){
            printf("Le partie a �t� sauvegardee correctement sous le nom suivant : \n");
            printf("%s",nomFichier);
        }
        else{
            fprintf(stderr,"\nIl y a eu une erreur dans l'ecriture du fichier.\n");
        }
    }

	// fermeture du fichier
	fclose (fichier);
}

//chargementPartie
//permet de charger une structure Partie
//la liste des parties sauvegardees est accessbile avec la fonction affichagePartiesDispo
//renvoie la variable Partie pour le nom associ�
Partie chargementPartie(char *nomPartie, const char *filepath_parties){
	
	//obtention du nom du fichier � partir dulequel charger la struct Joueur
	char* nomFichier = NULL;
	//malloc +9pseudo1 +1separateur +9pseudo2 +1separateur +15dateHeure +4typeFichier +1\0
	nomFichier = (char*)malloc((strlen(filepath_parties)+NAME_MAX_PARTIE) * sizeof(char));
	strcpy(nomFichier, filepath_parties) ;
	strcat(nomFichier, nomPartie) ;

	// ouverture du fichier pseudo.txt pour lecture
    FILE *fichier = NULL;
	fichier = fopen (nomFichier, "rb"); //read only
	if (fichier == NULL){
		fprintf(stderr, "\nIL y a eu une erreur dans l'ouverture du fichier\n");
		exit (1);
	}


	// lecture du fichier pseudo.txt jusqu'� la fin du fichier
	Partie p = NOUVELLE_PARTIE;
	fread(&p, sizeof(Partie), 1, fichier);

	// fermeture du fichier
	fclose (fichier);
	return p;
}

//affichagePartiesDispo
//fonction qui d'afficher graphiquement le d�tails des parties sauvegarder en cours
//opendir 
//	https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.bpxbd00/rtoped.htm
//	Si succ�s renvoie un pointeur vers un objet DIR. Cet objet d�crit le r�pertoire et est utilis� dans les op�rations suivantes sur le r�pertoire, de la m�me mani�re que les objets FILE sont utilis�s dans les op�rations d'E/S de fichiers.
//readdir
//	https://www.ibm.com/support/knowledgecenter/SSLTBW_2.3.0/com.ibm.zos.v2r3.bpxbd00/rtread.htm#rtread
//	En cas de succ�s, readdir() renvoie un pointeur vers une structure de r�pertoire d�crivant l'entr�e de r�pertoire suivante dans le flux de r�pertoire. Quand readdir() atteint la fin du flux de r�pertoire, il retourne un pointeur NULL.
// struct dirent {
    // ino_t          d_ino;       /* inode number */
    // off_t          d_off;       /* offset to the next dirent */
    // unsigned short d_reclen;    /* length of this record */
    // unsigned char  d_type;      /* type of file; not supported
    // char           d_name[256]; /* filename */
// };
void affichagePartiesDispo(const char *filepath_parties){
	//dirent.h
    DIR *dossier = opendir(filepath_parties); // DIR *opendir(const char *dirname);
	struct dirent *fichier = NULL ; //struct dirent *readdir(DIR *dir);
	
	// opendir()
	// renvoie un pointeur NULL si le dossier n a pas ete trouve
    if (dossier == NULL) { 
		printf("\nIL y a eu une erreur dans l'ouverture du dossier /parties.\n");
		exit (1);
    }

    else {
		 // readdir()
		printf("\nLes parties enregistrees sont les suivantes :\n");
		unsigned int rank = 0u ; //rang utile pour choisir le fichier � la suite dans un scanf
		while ((fichier = readdir(dossier)) != NULL){
			//strcmp(fichier->d_name,'.') ne marche pas mais
			if( (strcmp(".", fichier->d_name)!=0) && (strcmp("..", fichier->d_name)!=0) ){
				++rank;				
				printf("[%i] - %s \n", rank, fichier->d_name) ;
			}
		}
		closedir(dossier);
	}
}

//choixPartieParmiDispo
//permet de renvoyer le nom d une partie prise � partir d'une liste de partie 
char choixPartieParmiDispo(unsigned int rang, const char *filepath_parties){
	char* nomFichier = NULL;
	nomFichier = (char*)malloc( (NAME_MAX_PARTIE)*sizeof(char) );
	//dirent.h
    DIR *dossier = opendir(filepath_parties); // DIR *opendir(const char *dirname);
	struct dirent *fichier = NULL ; //struct dirent *readdir(DIR *dir);
	
	// opendir()
    if (dossier == NULL) { 
		printf("\nIL y a eu une erreur dans l'ouverture du dossier /parties.\n");
		exit (1);
    }

    else {
		 // readdir()
		printf("\nLes parties enregistrees sont les suivantes :\n");
		unsigned int rank = 0u ;
		while ((fichier = readdir(dossier)) != NULL){
			if( (strcmp(".", fichier->d_name)!=0) && (strcmp("..", fichier->d_name)!=0) ){
				++rank;
				if (rank==rang){
					strcpy(nomFichier,fichier->d_name);
				}			
			}
		}
		closedir(dossier);
	}
	return *nomFichier;
}


/*
void play(joueur* player1, joueur* player2) {
	jeu j;  //instanciation du jeu
	initJeu(&j, getName(player1), getName(player2)); // initialisation des param�tres du jeu (cf jeu.h)
	T2d t; // creation de la grille (peut �tre int�gr� dans l'init jeu
	init(&t, 7u, 6u);
	char s[250];
	char col;
	unsigned int ligne;
	unsigned int nbreToursMax = getHauteur(&t) * getLargeur(&t);
	do {
		incrementTurn(&j);
		setSymboleActif(&j);//on met � jour les valeurs � chaque tour
		setJoueurActif(&j);//on met � jour les valeurs � chaque tour
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
