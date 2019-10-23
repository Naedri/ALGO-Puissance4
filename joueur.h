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

Joueur creationJoueur(char pseudo, char nom, char prenom, const char filepath_joueurs);
int nombreLignesTable(const char filepath_table, char nomTable);
void sauvegarderJoueur(Joueur j, const char filepath_joueurs);
Joueur chargementJoueur(char pseudo,const char filepath_joueurs);
void affichageJoueur(char pseudo, const char filepath_joueurs);
void matchJoueur(Joueur* j, char pseudo, bool victoire);

#endif // JOUEUR_H_INCLUDED
