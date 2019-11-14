/// @file T2d.cpp
#include <stdlib.h>
#include <stdio.h> 
#include <assert.h>
#include <malloc.h>
#include <string.h>

#include "menu.h"
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
		for (char col = 'a'; col <= 'a'+getLargeur(t)-1; ++col)
			d += sprintf(s + d, "%c", get(t, col, lig));
		d += sprintf(s + d, "\n");
	}
	d += sprintf(s + d, "  ");
	for (char col = 'a'; col <= 'a'+getLargeur(t)-1; ++col)
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
	printf("Entrez une colonne svp, ou entrer '#' pour sauvegarder et quitter.\n");
	printf("Attention vous ne pouvez pas sauvegarder une partie lorsqu'elle est jouee contre l'IA.\n");
	//while (((scanf("%c%c", &choixColonne, &c)) != 2 || c != '\n') && viderBuffer() || (choixColonne != '#' && choixColonne <'a') || choixColonne > largeMax || estRemplie(t, choixColonne)) {
	//	printf("Veuillez entrez une valeur valide :\a ");
	//}
	while (((scanf("%c%c", &choixColonne, &c)) != 2 || c != '\n') && viderBuffer() || choixColonne != '#' && (choixColonne <'a' || choixColonne > largeMax || estRemplie(t, choixColonne))) {
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

const T2d copy(const T2d* t) {
	T2d copie;
	copie.largeur = t->largeur;
	copie.hauteur = t->hauteur;
	copie.grille = (char*)malloc(copie.largeur * copie.hauteur);
	for (unsigned int i = 0; i < copie.largeur * copie.hauteur; ++i)
		copie.grille[i] = t->grille[i];
	return copie;
}


char checkWin(const T2d* t) {
	unsigned hauteur = getHauteur(t);
	unsigned largeur = getLargeur(t);
	int caseVide = '.';
	char largeMax = 'a' + largeur - 1;
	for (int r = 1; r <= hauteur; r++) { // on itère les lignes du bas vers le haut
		for (char c = 'a'; c <= largeMax; c++) { // on itère les colonnes de la gauche vers la droite
			char player = get(t, c, r);
			if (player == caseVide)
				continue; // on ne veut pas vérifier les cases vides

			if (c + 3 <= largeMax &&
				player == get(t, c + 1, r) && // verif droite
				player == get(t, c + 2, r) &&
				player == get(t, c + 3, r))
				return player;
			if (r + 3 <= hauteur) {
				if (player == get(t, c, r + 1) && // verif haut
					player == get(t, c, r + 2) &&
					player == get(t, c, r + 3))
					return player;
				if (c + 3 <= largeMax &&
					player == get(t, c + 1, r + 1) && // verif haut et droite
					player == get(t, c + 2, r + 2) &&
					player == get(t, c + 3, r + 3))
					return player;
				if (c - 3 >= 'a' &&
					player == get(t, c - 1, r + 1) && // verif haut et gauche
					player == get(t, c - 2, r + 2) &&
					player == get(t, c - 3, r + 3))
					return player;
			}
		}
	}
	return caseVide; // pas de gagnant
}




bool grillePleine(T2d* t) {
	char col = 'a';
	for (; col < 'a' + getLargeur(t) && estRemplie(t, col); ++col) // si toutes les colonnes sont remplies, col vaut 'a' + largeur de t
		;
	return  col == 'a' + getLargeur(t);
}

int heuristicFaible(T2d* t, char symbole, int profondeur) {
	char winner = checkWin(t);
	if (winner == symbole)
		return 1000 + profondeur;
	if (winner == '.')
		return 0;
	return -1000 - profondeur;
}

char choixIA(T2d* grille, int prof, char symboleAdversaire, char symboleIA)
{
	int tmp;
	int meilleur_colonne = 'z';
	int alpha = -100000;
	int beta = 100000;
	char col = 'z';
	//Si la profondeur est nulle ou la partie est finie, 
	//on ne fait pas le calcul
	if ((prof != 0) || (checkWin(grille) == '.'))
	{
		//On range dans s tous les coups possibles
		char* s = coupsLegaux(grille);
		//On mélange les coups aléatoirement pour diversifier un peu les coups de l'IA entre les parties
		melangeColonnes(s);
		//On parcourt les colonnes
		for (unsigned int i = 0; s[i]; ++i)
		{
			col = s[i];
			////Si la colonne n'est pas remplie
			//if (!estRemplie(grille, col))
			//{
				//On simule qu'on joue cette case
			T2d copie_grille = copy(grille);
			placerJeton(&copie_grille, col, symboleIA);
			//On appelle la fonction Min pour lancer l'IA
			tmp = Min(&copie_grille, prof - 1, alpha, beta, symboleAdversaire, symboleIA);

			//Si ce score est plus grand
			if (alpha < tmp)
			{
				//On le choisit
				alpha = tmp;
				meilleur_colonne = col;
			}

			//On libère la mémoire
			free(copie_grille.grille);
			/*}*/
		}
	}
	//On jouera le coup maximal
	return meilleur_colonne;
}

int Min(T2d* grille, int prof, int alpha, int beta, char symboleAdversaire, char symboleIA)
{
	int tmp;
	char largeMax = 'a' + getLargeur(grille) - 1;
	//Si on est à la profondeur voulue, on retourne l'évaluation
	if (prof == 0)
	{
		tmp = evalGrille(grille, symboleIA, prof);
		return tmp;
	}

	//Si la partie est finie, on retourne l'évaluation de jeu
	if (checkWin(grille) != '.')
	{
		tmp = evalGrille(grille, symboleIA, prof);
		return tmp;
	}

	//On parcourt le plateau de jeu et on le joue si la colonne n'est pas remplie
	for (char col = 'a'; col <= largeMax; ++col)
	{
		if (!estRemplie(grille, col))
		{
			//On joue le coup
			T2d copie_grille = copy(grille);
			placerJeton(&copie_grille, col, symboleAdversaire);
			tmp = Max(&copie_grille, prof - 1, alpha, beta, symboleAdversaire, symboleIA);
			//On annule le coup
			free(copie_grille.grille);

			//Mis a jour de beta
			if (beta > tmp)
			{
				beta = tmp;
			}

			if (beta <= alpha)
			{
				return beta;
			}
		}
	}
	return beta;
}

int Max(T2d* grille, int prof, int alpha, int beta, char symboleAdversaire, char symboleIA)
{
	int tmp;
	char largeMax = 'a' + getLargeur(grille) - 1;

	if (prof == 0)
	{
		tmp = evalGrille(grille, symboleIA, prof);
		return tmp;
	}

	//Si la partie est finie, on retourne l'évaluation de jeu
	if (checkWin(grille) != '.')
	{
		tmp = evalGrille(grille, symboleIA, prof);
		return tmp;
	}

	for (char col = 'a'; col <= largeMax; ++col)
	{
		if (!estRemplie(grille, col))
		{
			//On joue le coup
			T2d copie_grille = copy(grille);
			placerJeton(&copie_grille, col, symboleIA);
			tmp = Min(&copie_grille, prof - 1, alpha, beta, symboleAdversaire, symboleIA);

			free(copie_grille.grille);

			//Mis a jour de la valeur de alpha
			if (alpha < tmp)
			{
				alpha = tmp;
			}

			if (beta <= alpha)
			{
				return alpha;
			}
		}
	}

	return alpha;
}

void melangeColonnes(char* tableauColonnes) {
	for (unsigned int i = 0; tableauColonnes[i]; ++i) {
		int k = rand() % (strlen(tableauColonnes) - i) + i;
		int tmp = tableauColonnes[i];
		tableauColonnes[i] = tableauColonnes[k];
		tableauColonnes[k] = tmp;
	}
}

unsigned int cmptJetons(const T2d* t, char col, unsigned int lig, unsigned int deltacol, unsigned int deltalig, char symbole) {
	// delta représente la direction, par exemple pour deltacol = 1 et deltalig = 0, on cherche vers la droite
	// on va alors parcourir la grille dans le sens donnée et rechercher des alignements de jetons (de même symbole que l'IA)
	// on veut retourner la somme des scores des alignements trouvés dans la direction donnée
	// imaginons une grille 12*12, on pourrait avoir plusieurs alignements de 3 sur une même ligne
	// ou bien plusieurs alignements de 2 et un alignement de 3 etc ...
	unsigned int compteur = 0;
	unsigned int cmptVides = 0;
	char largeMax = 'a' + getLargeur(t) - 1;
	int hauteurMax = getHauteur(t);
	char symboleAdverse;
	int somme = 0;
	symbole == 'X' ? symboleAdverse = 'O' : symboleAdverse = 'X';
	for (; col + deltacol >= 'a' && col + deltacol <= largeMax && lig + deltalig >= 1
		&& lig + deltalig <= hauteurMax; col += deltacol, lig += deltalig) {
		char actual = get(t, col, lig);
		if (actual == symbole)
			++compteur;
		// si on tombe sur un jeton adverse
		if (actual == symboleAdverse) {
			// s'il y a assez d'espace avant pour poser 4 jetons identiques
			// on garde trace de l'alignement qu'on avait jusqu'ici
			// en ajoutant à la somme le score de cet alignement
			if (compteur + cmptVides >= 4) {
				somme += evalJetons(compteur);
			}
			// on reset les compteurs puisqu'on est tombé sur un jeton adverse
			compteur = 0;
			cmptVides = 0;
		}
		if (actual == '.')
			++cmptVides;
	}
	if (compteur + cmptVides >= 4)
		somme += evalJetons(compteur);

	return somme;
}

int evalGrille(T2d* grille, char symbole, int prof) {
	char r = checkWin(grille);
	if (r == symbole) {
		return 1000000 + prof;

	}
	if (r != symbole && r != '.') {
		return -1000000 - prof;
	}


	else {
		// comptabiliser tous les alignements dans toutes les directions possibles
		char largeMax = 'a' + getLargeur(grille) - 1;
		int hauteurMax = getHauteur(grille);
		// toutes les colonnes
		int compteur = 0;
		for (char col = 'a'; col <= largeMax; ++col) {
			compteur += cmptJetons(grille, col, 1, 0, 1, symbole);
		}
		// toutes les lignes
		for (unsigned int i = 1; i <= hauteurMax; ++i) {
			compteur += cmptJetons(grille, 'a', i, 1, 0, symbole);
		}
		// ttes les diagos 
		for (unsigned int i = 1; i <= hauteurMax; ++i) {
			compteur += cmptJetons(grille, 'a', i, 1, -1, symbole);
		}
		for (char col = 'a'; col <= largeMax; ++col) {
			compteur += cmptJetons(grille, col, hauteurMax, 1, -1, symbole);
		}
		// ttes les diagos 
		for (char col = 'a'; col <= largeMax; ++col) {
			compteur += cmptJetons(grille, col, 1, 1, 1, symbole);
		}
		for (unsigned int i = 1; i <= hauteurMax; ++i) {
			compteur += cmptJetons(grille, 'a', i, 1, 1, symbole);
		}
		return  compteur;
	}
}
int evalJetons(int nbJetons) {
	switch (nbJetons)
	{
	case 1:
		return 0;
	case 2:
		return 1;
	case 3:
		return 100;
	case 4:
		return 10000;
	default:
		return 0;
	}
}

void playIA() {
	viderBuffer();
	char s[1000];
	T2d t;
	init(&t, 7u, 6u);
	char col;
	char symboleCourant;
	unsigned int ligne;
	int score;
	unsigned int nbreToursMax = getHauteur(&t) * getLargeur(&t);
	unsigned int tour = 0;
	do {
		++tour;
		tour % 2 == 1 ? symboleCourant = 'X' : symboleCourant = 'O';
		printf("Tour : %i ## Au tour du joueur %s qui joue les %c##\n\n", tour, symboleCourant == 'X' ? "GLaDOS" : "Humain banal", symboleCourant);
		if (symboleCourant == 'X') {
			col = choixIA(&t, PROFONDEUR, 'O', 'X');
			ligne = placerJeton(&t, col, symboleCourant);
		}
		else {
			col = choixJoueur(&t);
			ligne = placerJeton(&t, col, symboleCourant);
		}
		toString(&t, s);
		printf("%s\n", s);
	} while (tour < nbreToursMax && !estVictoire(&t, col, ligne));
	if (tour < nbreToursMax)
		printf("Felications au joueur %s qui remporte la partie !\n", symboleCourant == 'X' ? "GLaDOS" : "Humain banal");
	else
		puts("Dommage ! Match nul !");
	accueilJeu();
}
