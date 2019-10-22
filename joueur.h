/// @file joueur.h
#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

struct Joueur {
	char pseudo;
	char nom;
	char prenom;
	int partiesJouees; //nbr partie joué
	int partiesGagnees; //nbr parties gagnées
	int partiesPerdues; //nbr parties perdues
	float partiesRatio = partiesGagnees/ partiesPerdues; //ratio partie gagnées/jouées
};
typedef struct Joueur Joueur;

void matchJoueur(Joueur* j, char pseudo, bool victoire);



#endif // JOUEUR_H_INCLUDED
