/// @file joueur.h
#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

struct Joueur {
	char pseudo;
	char nom;
	char prenom;
	int partiesJouees; //nbr partie jou�
	int partiesGagnees; //nbr parties gagn�es
	int partiesPerdues; //nbr parties perdues
	float partiesRatio = partiesGagnees/ partiesPerdues; //ratio partie gagn�es/jou�es
};
typedef struct Joueur Joueur;

void creationJoueur(Joueur * j, char pseudo, char nom, char prenom){

void matchJoueur(Joueur* j, char pseudo, bool victoire);
int nombreLignesTable(char filepath);
void ecritureJoueurs(Joueur* j);
void affichageTableJoueurs(char filepath);
char afficherInfo(char * string, unsigned int ranginitial, char separateur);


#endif // JOUEUR_H_INCLUDED
