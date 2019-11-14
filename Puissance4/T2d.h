/// @file T2d.h
#ifndef T2D_H_INCLUDED
#define T2D_H_INCLUDED

#define NOUVELLE_TABLE { 0u, 0u, NULL }
#define TAILLE_MAX_GRILLE 144 //12*12
#define PROFONDEUR 8 //cout d avance observe par l IA

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
typedef T2d T2d;

void init(T2d* , unsigned int largeur, unsigned int hauteur);

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

bool grillePleine(T2d* t);

/* FONCTIONS POUR L'IA*/
void annulerCoup(T2d*, char col); // annule le dernier jeton placé dans col.
char* coupsLegaux(T2d*); // retourne la liste des coups légaux pour un état du jeu
int evaluerCoup(T2d*, char col, unsigned int lig);

char checkWin(const T2d* t);// renvoie le vainqueur si un alignement de 4 existe dans la grille, sinon renvoie la case vide '.'
const T2d copy(const T2d* t);// effectue une copie de l'état de la grille t pour simuler les coups de l'ia.
void initSeed();
int heuristicFaible(T2d* t, char symbole, int prof);// Simplement basée sur gagné, nul ou perdu
char choixIA(T2d* jeu, int prof, char symboleAdverse, char symboleIA);// renvoie la meilleure colonne
int Min(T2d* grille, int prof, int alpha, int beta, char symboleAdverse, char symboleIA);
int Max(T2d* grille, int prof, int alpha, int beta, char symboleAdverse, char symboleIA);
void melangeColonnes(char* tableauColonnes);// permet de diversifier un peu les coups de l'ia entre les parties
unsigned int cmptJetons(const T2d* t, char col, unsigned int lig, unsigned int deltacol, unsigned int deltalig, char symbole);
int evalJetons(int nbJetons);
int evalGrille(T2d* grille, char symbole, int prof);
void playIA();


#endif // T2D_H_INCLUDED
