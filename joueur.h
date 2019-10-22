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

void creationJoueur(Joueur * j, char pseudo, char nom, char prenom){

void matchJoueur(Joueur* j, char pseudo, bool victoire);
int nombreLignesTable(char filepath);
void ecritureJoueurs(Joueur* j);
void affichageTableJoueurs(char filepath);
char afficherInfo(char * string, unsigned int ranginitial, char separateur);


#endif // JOUEUR_H_INCLUDED
