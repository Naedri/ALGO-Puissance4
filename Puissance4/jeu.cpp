#include "jeu.h"
#include "joueur.h"
#include <stdio.h>

//void play(joueur* player1, joueur* player2) {
//	jeu j;  //instanciation du jeu
//	initJeu(&j, getName(player1), getName(player2)); // initialisation des paramètres du jeu (cf jeu.h)
//	T2d t; // creation de la grille (peut être intégré dans l'init jeu
//	init(&t, 7u, 6u);
//	char s[250];
//	char col;
//	unsigned int ligne;
//	unsigned int nbreToursMax = getHauteur(&t) * getLargeur(&t);
//	do {
//		incrementTurn(&j);
//		setSymboleActif(&j);//on met à jour les valeurs à chaque tour
//		setJoueurActif(&j);//on met à jour les valeurs à chaque tour
//		printf("Tour : %i ## Au tour du joueur %s qui joue les %c##\n", getNbreTours(&j), getJoueurActif(&j), getSymboleActif(&j));
//		col = choixJoueur(&t);
//		ligne = placerJeton(&t, col, getSymboleActif(&j));
//		toString(&t, s);
//		printf("%s\n", s);
//	} while (getNbreTours(&j) < nbreToursMax && !estVictoire(&t, col, ligne));
//	if (getNbreTours(&j) < nbreToursMax)
//		printf("Felications au joueur %s qui remporte la partie !\n", getJoueurActif(&j));
//	else
//		puts("Dommage ! Match nul !");
//}

//void initJeu(jeu* j, char* j1Pseudo, char* j2Pseudo) {
//	j->j1Pseudo = j1Pseudo;
//	j->j2Pseudo = j2Pseudo;
//	j->nbretours = 0;
//}



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