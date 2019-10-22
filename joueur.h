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

void creationJoueur(Joueur* j, char pseudo, char nom, char prenom, const char* filepath_joueurs);
int nombreLignesTable(const char* filepath);
void sauvegarderJoueur(Joueur* j);
Joueur chargementJoueur(const char pseudo, const char filepath);
void affichageJoueur(const char pseudo, const char filepath);
char *afficherInfo(const char * string, unsigned int ranginitial, char separateur);
void matchJoueur(Joueur* j, char pseudo, bool victoire);

#endif // JOUEUR_H_INCLUDED
