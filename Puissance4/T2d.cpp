/// @file T2d.cpp
#include <stdlib.h>
#include <stdio.h> 
#include <assert.h>
#include <malloc.h>

#include "commun.h"
#include "T2d.h"
#pragma warning(disable:4996)
//#pragma warning(disable:4018) //'<=' : incompatibilité signed / unsigned	Puissance4	/T2d.cpp	135


void init(T2d* t, unsigned int largeur, unsigned int hauteur) {
	assert((hauteur * largeur) <= (TAILLE_MAX_GRILLE));
	t->largeur = largeur;
	t->hauteur = hauteur;
	t->grille = (char*)malloc((largeur * hauteur)); //+1 n est pas necessaire car dans le for il y a i <  et non i <=
	assert(t->grille != NULL);
	for (unsigned int i = 0; i < largeur * hauteur; ++i)
		t->grille[i] = '.';
}

unsigned int getLargeur(const T2d* t) {
	return t->largeur;
}

unsigned int getHauteur(const T2d* t) {
	return t->hauteur;
}

char getSymbole(unsigned int i) {
	assert(i < 3);
	static const char symboles[3] = { '.', 'X', 'O' };// le premier élément représente le vide
	// le tableau est intialisé au premier appel
	// il n'est pas détruit en sortant de la fonction
	// il est stocké avec les variables globales
	// avant le main()
	return symboles[i];
}

void set(T2d* t, char col, unsigned int lig, char symbole) {
	t->grille[(lig - 1) * t->largeur + (col - 'a')] = symbole;
}

char get(const T2d* t, char col, unsigned int lig) {
	return t->grille[(lig - 1) * t->largeur + (col - 'a')];
}

void liberer(T2d* t) {
	free(t->grille);
}

void toString(const T2d* t, char* s) {
	*s = 0;
	unsigned int d = 0;
	for (unsigned int lig = getHauteur(t); lig >= 1; --lig) {
		d += sprintf(s + d, "%i ", lig);
		for (char col = 'a'; col <= 'g'; ++col)
			d += sprintf(s + d, "%c ", get(t, col, lig));
		d += sprintf(s + d, "\n");
	}
	d += sprintf(s + d, "  ");
	for (char col = 'a'; col <= 'g'; ++col)
		d += sprintf(s + d, "%c ", col);
	d += sprintf(s + d, "\n");
}


void viderGrille(T2d* t) {
	for (unsigned int i = 0; i < t->largeur * t->hauteur; ++i)
		t->grille[i] = '.';
}

bool estVictoire(const T2d* t, char col, unsigned int lig) {
	int sommeColonne, sommeLigne, sommeDiagDroite, sommeDiagGauche; // instanciation des différentes sommes utiles pour vérifier les 4 alignements possibles (--,|,/,\)
	sommeColonne = sommeLigne = sommeDiagDroite = sommeDiagGauche = 0; // initialisation des sommes à 0
	char symbole = get(t, col, lig); // on récupère le symbole du dernier jeton joué
	//verification verticale (|), on note qu'il n'y pas besoin de vérifier au dessus du dernier jeton joué.
	for (unsigned int i = 1; lig - i >= 1 && get(t, col, lig - i) == symbole; ++i, ++sommeColonne)
		;
	//verification horizontale (<-->), on recherche dans les deux sens.
	for (unsigned int i = 1; col + i <= 'g' && get(t, col + i, lig) == symbole; ++i, ++sommeLigne)
		;
	for (unsigned int i = 1; col - i >= 'a' && get(t, col - i, lig) == symbole; ++i, ++sommeLigne)
		;
	//verification diagonale montante (/)
	for (unsigned int i = 1; col + i <= 'g' && lig + i <= 6 && get(t, col + i, lig + i) == symbole; ++i, ++sommeDiagDroite)
		;
	for (unsigned int i = 1; col - i >= 'a' && lig - i >= 1 && get(t, col - i, lig - i) == symbole; ++i, ++sommeDiagDroite)
		;
	//verification diagonale descendante (\)
	for (unsigned int i = 1; col - i >= 'a' && lig + i <= 6 && get(t, col - i, lig + i) == symbole; ++i, ++sommeDiagGauche)
		;
	for (unsigned int i = 1; col + i <= 'g' && lig - i >= 1 && get(t, col + i, lig - i) == symbole; ++i, ++sommeDiagGauche)
		;
	if (sommeColonne >= 3 || sommeLigne >= 3 || sommeDiagGauche >= 3 || sommeDiagDroite >= 3) // si il y a un alignement (i.e 4 jetons alignés) on retourne vraie
		return true;
	return false;
}

bool estRemplie(T2d* t, char col) {
	return get(t, col, getHauteur(t)) != '.';
}
unsigned int placerJeton(T2d* t, char col, char symbole) {
	assert(!estRemplie(t, col));
	unsigned int i = 1;
	for (; i <= getHauteur(t) && get(t, col, i) != '.'; ++i)
		;
	set(t, col, i, symbole);
	return i;
}

char choixJoueur(T2d* t) { // nom de variables pas assez explicite
	char choixColonne;
	char largeMax = 'a' + getLargeur(t) - 1;
	char c; //c sert à vérifier que l'utilisateur entre un seul caractère, ex : "aaaa" non accepté.
	printf("Entrez une colonne svp\n");
	while ((((scanf("%c%c", &choixColonne, &c)) != 2 || c != '\n') && viderBuffer()) || choixColonne <'a' || choixColonne > largeMax || estRemplie(t, choixColonne)) {
		printf("Veuillez entrez une valeur valide :\a ");
	}
	return choixColonne;
}

void annulerCoup(T2d* t, char col) {
	unsigned int hauteur = getHauteur(t);
	for (; hauteur >= 1 && get(t, col, hauteur) == getSymbole(0); --hauteur)
		;
	set(t, col, hauteur, getSymbole(0));
}

char* coupsLegaux(T2d* t) {
	unsigned int largeur = getLargeur(t);
	char* listeCoups = (char*)malloc(largeur + 1);
	char col = 'a';
	unsigned int i = 0u;
	for (; col <= 'a' + largeur - 1; ++col) {
		if (!estRemplie(t, col))
			listeCoups[i++] = col;
	}
	listeCoups[i] = 0;
	return listeCoups;
}

int evaluerCoup(T2d* t, char col, unsigned int lig) {
	const unsigned int alignementsMax = 4; //toutes les directions possibles
	int sommmeAlignement[alignementsMax] = { 0 }; 
	char symbole = get(t, col, lig); // on récupère le symbole du dernier jeton joué
	for (unsigned int i = 1; lig - i >= 1 && get(t, col, lig - i) == symbole; ++i, ++sommmeAlignement[0])
		;
	//verification horizontale (<-->), on recherche dans les deux sens.
	for (unsigned int i = 1; col + i <= 'g' && get(t, col + i, lig) == symbole; ++i, ++sommmeAlignement[1])
		;
	for (unsigned int i = 1; col - i >= 'a' && get(t, col - i, lig) == symbole; ++i, ++sommmeAlignement[1])
		;
	//verification diagonale montante (/)
	for (unsigned int i = 1; col + i <= 'g' && lig + i <= 6 && get(t, col + i, lig + i) == symbole; ++i, ++sommmeAlignement[2])
		;
	for (unsigned int i = 1; col - i >= 'a' && lig - i >= 1 && get(t, col - i, lig - i) == symbole; ++i, ++sommmeAlignement[2])
		;
	//verification diagonale descendante (\)
	for (unsigned int i = 1; col - i >= 'a' && lig + i <= 6 && get(t, col - i, lig + i) == symbole; ++i, ++sommmeAlignement[3])
		;
	for (unsigned int i = 1; col + i <= 'g' && lig - i >= 1 && get(t, col + i, lig - i) == symbole; ++i, ++sommmeAlignement[3])
		;
	for (unsigned int i = 0; i < alignementsMax; ++i) {
		// si 0 renvoie 1
		// si 1 renvoie 5
		// si 2 renvoie 50
		//si 3 renvoie 1000
	}
	return 0;
}
