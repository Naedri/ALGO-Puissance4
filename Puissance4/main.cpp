// main.cpp
#include "unittest.h"
#include "T2d.h"

int main() {
	assertEquals('.', getSymbole(0), "case vide");
	assertEquals('X', getSymbole(1), "symbole joueur 1");
	assertEquals('O', getSymbole(2), "symbole joueur 2");
	T2d t;
	init(&t, 7u, 6u);
	char s[250];
	char col;
	unsigned int ligne;
	
	for (int i = 0; i < 1000; ++i) {	// ATTENTION VERSION GROS SCHLAG POUR TEST <-- PAS BIEN
		col = choixJoueur(&t);
		ligne = placerJeton(&t, col, getSymbole((i+1)%2 +1));
		toString(&t, s);
		printf("%s", s);
		if (estVictoire(&t, col, ligne) == true){
			printf("gg");
			break;
		}
	}
	viderGrille(&t);
	set(&t, 'd', 1, 'X');
	set(&t, 'd', 2, 'X');
	set(&t, 'd', 3, 'X');
	set(&t, 'd', 4, 'X');
	set(&t, 'd', 5, 'X');
	set(&t, 'd', 6, 'X');
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
	return 0;
}