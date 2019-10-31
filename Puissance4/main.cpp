/// @file main.cpp
#include <time.h>
#include <assert.h>
#include <string.h>
#include "unittest.h"
#include "T2d.h"
#include "partie.h"
#include "joueur.h"

#define MAX 20 //attention nom a changer
//attention c est qlq fois utile d avoir des variables constantes mais encore faut il qu on sache a quoi elles correspondent, ici le nom ne donne pas assez d indication et en general dans le main il n y en a pas besoin

int tirage(int min, int max);
void initSeed();
void testerT2d();

int main() {
	// d'abord prendre les infos des joueurs, sauvegarder etc
	// ensuite lancer le jeu
	/*char s[MAX];
	lirePseudo(s, MAX);
	joueur j1;
	setName(&j1, s);
	char s2[MAX];
	lirePseudo(s2, MAX);
	joueur j2;
	setName(&j2, s2);
	printf("Bienvenue %s et %s\n", getName(&j1), getName(&j2));*/
	//puts("###### LET'S PLAY ######!");
	//play(&j1, &j2);
	
	Partie partie = NOUVELLE_PARTIE;
	partie = menuPartie(partie); 
	if (partie.grilleChar != NULL){ //a faire apres
	//play(p)
	
	//// pas forcement cela
	//joueur j1 = nouveau_joueur;
	//joueur j2 = nouveau_joueur;
	//j1 = chargementjoueur(p->joueur1,filepath_joueurs);
	//j2 = chargementjoueur(p->joueur2,filepath_joueurs);
	//play(&j1, &j2);
}
	
	return 0;
}

void testerT2d() {
	assertEquals('.', getSymbole(0), "case vide");
	assertEquals('X', getSymbole(1), "symbole joueur 1");
	assertEquals('O', getSymbole(2), "symbole joueur 2");
	T2d t = NOUVELLE_TABLE; //initialisation tous les paramètre à 0 meme la largeur
	init(&t, 7u, 6u);
	char s[250];
	char col;
	unsigned int ligne;
	
	//char pseudo_joueur1[TAILLE_ID] = "";
	//char pseudo_joueur2[TAILLE_ID] = "";
	//scanf_s("quel le nom du premier joueur ? %s", &pseudo_joueur1);
	//scanf_s("quel le nom du deuxieme joueur ? %s", &pseudo_joueur2);

	for (int i = 0; i < 46; ++i) {	//version tirage aléatoire pour tester de nombreuses parties
		do
			col = tirage('a', 'g');
		while(estRemplie(&t,col));// col = choixJoueur(&t);
		ligne = placerJeton(&t, col, getSymbole((i + 1) % 2 + 1));
		toString(&t, s);
		printf("%s", s);
		//printf("%s  %c  %s", pseudo_joueur1, getSymbole((i + 1) % 2 + 1)), pseudo_joueur2);
		if (estVictoire(&t, col, ligne) == true) {
			printf("gg\n");
			break;
		}
	}
	viderGrille(&t);
	assertFalse(estRemplie(&t, 'd'), "Non estRemplie(&t,'d')");
	set(&t, 'd', 1, 'X');
	set(&t, 'd', 2, 'X');
	set(&t, 'd', 3, 'X');
	set(&t, 'd', 4, 'X');
	set(&t, 'd', 5, 'X');
	set(&t, 'd', 6, 'X');
	char* liste;
	liste = coupsLegaux(&t);
	assertEquals(0, strcmp("abcefg", liste), "coup legaux d pleine");
	assertTrue(estRemplie(&t, 'd'), "estRemplie(&t,'d')");
	// vérifier que la largeur de t est 7
	assertEquals(7u, getLargeur(&t), "largeur de t");
	// vérifier que la hauteur de t est 6
	assertEquals(6u, getHauteur(&t), "hauteur de t");
	// apres l'initialisation
	// toutes les cases contiennent le symbole de la case vide
	//for (unsigned int lig = 1; lig <= 6; ++lig) {
	//	for (char col = 'a'; col <= 'g'; ++col)
	//		assertEquals('.', get(&t, col, lig), "tout vide");
	//}
	// mettre 'X' dans la case ('d', 3) de t
	set(&t, 'd', 3, 'X');
	// verifier que 'X' est bien dans la case ('d', 3)
	assertEquals('X', get(&t, 'd', 3u), "get('d',3)");
	set(&t, 'd', 4, 'X');
	set(&t, 'd', 2, 'X');
	set(&t, 'd', 1, 'X');
	assertTrue(estVictoire(&t, 'd', 4u), "estVictoire(&t, 'd', 4u)");
	set(&t, 'a', 1, 'O');
	assertFalse(estVictoire(&t, 'a', 1u), "Non estVictoire(&t, 'a', 1u)");
	toString(&t, s);
	printf("%s", s);
	viderGrille(&t);
	set(&t, 'd', 1, 'X');
	assertEquals('X', get(&t, 'd', 1), "d1 X");
	annulerCoup(&t, 'd');
	assertEquals(getSymbole(0), get(&t, 'd', 1), "d1 vide");
	viderGrille(&t);
	set(&t, 'a', 1, 'X');
	set(&t, 'b', 1, 'X');
	set(&t, 'c', 1, 'X');
	set(&t, 'd', 1, 'X');
	assertTrue(estVictoire(&t, 'd', 1u), "estVictoire(&t, 'd', 1u)");
	assertTrue(estVictoire(&t, 'a', 1u), "estVictoire(&t, 'a', 1u)");
	set(&t, 'd', 2, 'O');
	assertFalse(estVictoire(&t, 'd', 2u), "Non estVictoire(&t, 'd', 2u)");
	toString(&t, s);
	printf("%s", s);
	viderGrille(&t);
	set(&t, 'a', 1, 'X');
	set(&t, 'b', 2, 'X');
	set(&t, 'c', 3, 'X');
	set(&t, 'd', 4, 'X');
	toString(&t, s);
	assertTrue(estVictoire(&t, 'a', 1), "estVictoire(&t, 'a', 1), victoire / montante ");
	assertTrue(estVictoire(&t, 'd', 4), "estVictoire(&t, 'd', 4), victoire / descendante ");
	set(&t, 'g', 4, 'O');
	assertFalse(estVictoire(&t, 'g', 4), "Non estVictoire(&t, 'g', 4) ");
	printf("%s", s);
	viderGrille(&t);
	set(&t, 'a', 4, 'X');
	set(&t, 'b', 3, 'X');
	set(&t, 'c', 2, 'X');
	set(&t, 'd', 1, 'X');
	toString(&t, s);
	assertTrue(estVictoire(&t, 'a', 4), "estVictoire(&t, 'a', 4)");
	assertTrue(estVictoire(&t, 'd', 1), "estVictoire(&t, 'd', 1)");
	set(&t, 'g', 4, 'O');
	assertFalse(estVictoire(&t, 'g', 4), "Non estVictoire(&t, 'g', 4)");
	printf("%s", s);

	liberer(&t);
}

void  initSeed() {
	static bool initialized = false;
	if (!initialized) {
		srand((unsigned)time(NULL));
		initialized = true;
	}
}

int tirage(int min, int max) {
	initSeed();
	return (rand() % (max - min + 1)) + min;
}
