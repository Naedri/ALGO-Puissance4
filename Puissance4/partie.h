/// @file partie.h
#ifndef PARTIE_H_INCLUDED
#define PARTIE_H_INCLUDED

#define TAILLE_ID 10
#define TAILLE_SYMBOLE 2
#define TAILLE_DATEHEURE 16

#define FILEPATH_PARTIES "./parties/"
#define NAME_MAX_PARTIE 40 // longueur max du nom d une partie 9+1+9+1+15+4 +1
#define NOUVELLE_PARTIE { "", "", "", "", "", "", "", 0u,"", NULL}

#include "T2d.h"
#include "joueur.h"

//adrien
struct Partie {
    char joueur1[TAILLE_ID] ; //pseudo du joueur1
    char joueur2[TAILLE_ID] ; //pseudo du joueur2
    char symbole1[TAILLE_SYMBOLE] ; //symbole du joueur1
    char symbole2[TAILLE_SYMBOLE] ; //symbole du joueur2
    
    char joueurActif[TAILLE_ID] ; //pseudo du joueur qui doit inserer son jeton pour ce tour
    char symboleActif[TAILLE_SYMBOLE]; //symbole du joueur qui doit inserer son jeton pour ce tour

    char joueurInitial[TAILLE_ID] ;  //pseudo du joueur qui a été le premier joueur a mettre un jeton
    unsigned int nbrTour;
    char dateCreation[TAILLE_DATEHEURE]; //necessaire pour sa sauvegarde YYYYMMDD-HHMMSS

    T2d *grille;
};

typedef struct Partie Partie;

Partie creationPartie(char *joueur1, char *symbole1, char *joueur2, char *symbole2, unsigned int grilleLargeur, unsigned int grilleHauteur);
void sauvegarderPartie(Partie p, const char *filepath_parties);
Partie chargementPartie(char *nomPartie,const char *filepath_parties);
void affichagePartiesDispo(const char *filepath_parties);
char choixPartieParmiDispo(unsigned int rang, const char *filepath_parties)

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
