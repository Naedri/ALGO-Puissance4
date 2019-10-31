/// @file partie.h
#ifndef PARTIE_H_INCLUDED
#define PARTIE_H_INCLUDED

#include <stdlib.h> //NULL

#define TAILLE_ID 10
#define TAILLE_DATEHEURE 16

#define FILEPATH_PARTIES "./parties/"
#define NAME_MAX_PARTIE 39 // longueur max du nom d une partie 9+1+9+1+15+4 	//malloc +9pseudo1 +1separateur +9pseudo2 +1separateur +15dateHeure +4typeFichier +1\0
#define NOUVELLE_PARTIE { "", "", "", "", "", 0u, 0u, 0u, 0u, 0u, 0u, NULL }

//adrien
struct Partie {
    char joueur1[TAILLE_ID] ; //pseudo du joueur1
    char joueur2[TAILLE_ID] ; //pseudo du joueur2
	char joueurActif[TAILLE_ID]; //pseudo du joueur qui doit inserer son jeton pour ce tour (cad joueur qui n est pas le dernier joueur a avoir inserer de jeton)
	char joueurInitial[TAILLE_ID];  //pseudo du joueur qui a été le premier joueur a mettre un jeton
	char dateCreation[TAILLE_DATEHEURE]; //necessaire pour sa sauvegarde YYYYMMDD-HHMMSS
	unsigned int symbole1 ; //symbole du joueur1
	unsigned int symbole2 ; //symbole du joueur2
	unsigned int symboleActif; //symbole du joueur qui doit inserer son jeton pour ce tour
    unsigned int nbrTour; // si pair  : joueurActif est le joueurPREMIER ; si impair : joueurActif est le joueurSECOND
	unsigned int grilleLargeur; //T2d structure
	unsigned int grilleHauteur;
	char *grilleChar; //on ne sauvegarde pas T2d* car elle contient elle même des pointeurs
};
typedef struct Partie Partie;

void creationPartie(Partie* p, char* joueur1, unsigned int symbole1, char* joueur2, unsigned int symbole2,
	char* joueurActif, unsigned int symboleActif,
	char* joueurInitial, unsigned int nbrTour,
	unsigned int grilleLargeur, unsigned int grilleHauteur, char* grilleChar);
void sauvegarderPartie(Partie p, const char* filepath_joueurs);
Partie chargementPartie(char* nomPartie, const char* filepath_parties);
void affichagePartiesDispo(const char* filepath_parties);
unsigned int nombreParties(const char* filepath_parties);
int choixPartie(unsigned int maxPartie);
void getNomPartieSelonID(char* chainePourNomPartie, unsigned int id, const char* filepath_parties);

Partie menuPartie(Partie p);

/*vincent
struct jeu {
	char SymboleActif;
	char* joueurActif;
	unsigned int nbretours;
	char* j1Pseudo;
	char* j2Pseudo;
	T2d* grille;
};

void play(Joueur*, Joueur*); // la fonction play prend en paramètre les deux joueurs qui vont s'affronter

void initJeu(jeu*,char* joueurUn, char* joueurDeux); // doit initialiser le jeu (mettre les pseudos des joueurs, la grille vide, le nbretour à 0, le joueur actif comme j1)
unsigned int getNbreTours(jeu*); // retourne le nbre de tour du jeu à l'instant t
void setSymboleActif(jeu*); // permet de mettre à jour le symbole actif
char getSymboleActif(jeu*);// permet de retourner le symbole actif
void incrementTurn(jeu*); // augmente de un le nbre de tour du jeu
void setJoueurActif(jeu*); // met à jour le joueur actif
char* getJoueurActif(jeu*); // retourne le joueur actif
*/
#endif // PARTIE_H_INCLUDED
