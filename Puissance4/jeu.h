/// @file jeu.h
#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

//vincent
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

//adrien
struct EtatJeu {
    char joueur1 ;
    char joueur2 ;
    char symbole1 ; //symbole du joueur1
    char symbole2 ; //symbole du joueur2
    char joueurinitial ;  // qui a été le premier joueur a mettre un jeton
    char * grille;
    char tour ; //qui doit insérer le prochain jeton


#endif // JEU_H_INCLUDED


