#include "T2d.h"
#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#pragma warning(disable:4996)

void init(T2d* t, unsigned int largeur,
	unsigned int hauteur) {
	t->largeur = largeur;
	t->hauteur = hauteur;
	t->grille = (char*)malloc(largeur * hauteur);
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
	static const char symboles[3] = { '.', 'X', 'O' };
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
//version non optimisé
//bool estVictoire(const T2d* t, char col, unsigned int lig) {
//	//verification verticale, il n'y pas besoin de vérifier au dessus du dernier jeton joué.
//	int sommeColonne, sommeLigneDroite, sommeLigneGauche, sommeDiagoHautDroit, sommeDiagoBasGauche, sommeDiagoHautGauche, sommeDiagoBasDroit; // instanciation des différentes sommes utiles
//	sommeColonne = sommeLigneDroite = sommeLigneGauche = sommeDiagoHautDroit = sommeDiagoBasGauche = sommeDiagoHautGauche = sommeDiagoBasDroit = 0; // initialisation des sommes à 0
//	char symbole = get(t, col, lig);
//	unsigned int y = lig;
//	for (y; y >= 1 && get(t, col, y) == symbole; --y, ++sommeColonne)
//		;
//	//verification horizontale, pour des soucis de lisibilité du code, on commence sur la case du dernier jeton joué.
//	for (char i = col; i <= 'g' && get(t, i, lig) == symbole; ++i, ++sommeLigneDroite)
//		;
//	for (char i = col; i >= 'a' && get(t, i, lig) == symbole; --i, ++sommeLigneGauche)
//		;
//	//verification diagonale (/)
//	y = lig; // on reinitialise y car il a été manipulé dans les boucles for précédentes
//	for (char i = col; i <= 'g' && y <= 6 && get(t, i, y) == symbole; ++i, ++y, ++sommeDiagoHautDroit)
//		;
//	y = lig;
//	for (char i = col; i >= 'a' && y >= 1 && get(t, i, y) == symbole; --i, --y, ++sommeDiagoBasGauche)
//		;
//	//verification dagionale (\)
//	y = lig;
//	for (char i = col; i >= 'a' && y <= 6 && get(t, i, y) == symbole; --i, ++y, ++sommeDiagoHautGauche)
//		;
//	y = lig;
//	for (char i = col; i <= 'g' && y >= 1 && get(t, i, y) == symbole; ++i, --y, ++sommeDiagoBasDroit)
//		;
//	if (sommeColonne >= 4 || sommeLigneDroite + sommeLigneGauche >= 4 || sommeDiagoBasGauche + sommeDiagoHautDroit >= 4 || sommeDiagoBasDroit + sommeDiagoHautGauche >= 4)
//		return true;
//	return false;
//}

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
	if (sommeColonne >= 3 || sommeLigne >= 3 || sommeDiagGauche >= 3 || sommeDiagDroite  >= 3) // si il y a un alignement (i.e 4 jetons alignés) on retourne vraie
		return true;
	return false;
}
int viderBuffer() {
	while (getchar() != '\n');
	return 1;
}
bool estRemplie(T2d* t,char col){
	return get(t,col,getHauteur(t)) != '.';
}
unsigned int placerJeton(T2d* t, char col, char symbole){
	assert(!estRemplie(t, col));
	unsigned int i = 1;
	for (; i <= getHauteur(t) && get(t, col, i) != '.'; ++i)
		;
	set(t, col, i, symbole);
	return i;
}
//char choixJoueur(T2d* t) {
//	char choixColonne = 0;
//	char c;
//	int a;
//	do{
//		printf("Entrez la colonne dans laquelle vous souhaitez jouer \n");
//		a = scanf("%c %c",&choixColonne,&c);
//		if (choixColonne < 'a' || choixColonne >'g' || a !=1) // il faut aussi vérifier que la colonne n'est pas pleine
//			printf("Ce n'est pas une valeur valide, la colonne doit etre comprise entre a et g\n");
//		viderBuffer();
//	} while (choixColonne < 'a' || choixColonne >'g' || a != 1);
//	return choixColonne;
//}

char choixJoueur(T2d* t) {
	char choixColonne;
	char largeMax = 'a' + getLargeur(t) - 1;
	char c; //c sert à vérifier que l'utilisateur entre un seul caractère, ex : "aaaa" non accepté.
	printf("Entrez une colonne svp\n");
	while (((scanf("%c%c", &choixColonne, &c)) != 2 || c != '\n') && viderBuffer() || choixColonne <'a' || choixColonne > largeMax || estRemplie(t,choixColonne)) { 
		printf("Veuillez entrez une valeur valide : ");
	}
	return choixColonne;
}


