/// @file joueur.h
#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED
#define TAILLE_ID 10

struct Joueur {
	char pseudo[TAILLE_ID];
	char nom[TAILLE_ID];
	char prenom[TAILLE_ID];
	int partiesJouees; //nbr partie joué
	int partiesGagnees; //nbr parties gagnées
	int partiesPerdues; //nbr parties perdues
	float partiesRatio ;// = partiesGagnees/ partiesPerdues;
};
typedef struct Joueur Joueur;

Joueur creationJoueur(char *pseudo, char *nom, char *prenom, const char *filepath_joueurs);
int nombreLignesTable(char *filePathName);
void sauvegarderJoueur(Joueur j, const char *filepath_joueurs);
Joueur chargementJoueur(char *pseudo,const char *filepath_joueurs);
void affichageJoueur(char *pseudo, const char *filepath_joueurs);
void matchJoueur(Joueur* j, bool victoire);

#endif // JOUEUR_H_INCLUDED
