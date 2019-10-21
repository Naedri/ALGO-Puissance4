#pragma once

// La structure T2d représente un tableau
// de char à 2 dimensions
// '.' case vide
// 'X' joueur 1
// 'O' joueur 2

struct T2d {
	unsigned int largeur;
	unsigned int hauteur;
	char* grille;
};

void init(T2d* , unsigned int largeur,
			     unsigned int hauteur);
unsigned int getLargeur(const T2d*);
unsigned int getHauteur(const T2d*);
char getSymbole(unsigned int);
void set(T2d*, char col, unsigned int lig, char symbole);
char get(const T2d*, char col, unsigned int lig);
void liberer(T2d*);
void toString(const T2d*, char*);
bool estVictoire(const T2d*, char col, unsigned int lig); // cette fonction prend en paramètre les coordonnées du dernier jeton joué et évalue les jetons qui l'entourent.
void viderGrille(T2d*);
char choixJoueur(T2d*);// retourne la colonne choisie
int viderBuffer();
bool estRemplie(T2d*,char col);
unsigned int placerJeton(T2d*, char col, char symbole); // retourne la ligne dans laquelle le jeton est placée