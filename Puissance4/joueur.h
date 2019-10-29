/// @file joueur.h
#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

#define		FILEPATH_JOUEURS	"./joueurs/"
#define		NOUVEAU_JOUEUR		{ "", "", "", 0, 0, 0, 0.0f }
#define		TAILLE_ID			10 //le pseudo, le nom, le prenom sont des chaines au max de 9caractères de long


struct Joueur{
	char pseudo[TAILLE_ID];
	char nom[TAILLE_ID];
	char prenom[TAILLE_ID];
	int partiesJouees; //nbr partie joué
	int partiesGagnees; //nbr parties gagnées
	int partiesPerdues; //nbr parties perdues
	float partiesRatio ;// = partiesGagnees/ partiesPerdues
};

typedef struct Joueur Joueur;

Joueur creationJoueur(char *pseudo, char *nom, char *prenom, const char *filepath_joueurs);
int nombreLignesTable(char *filePathName);
void sauvegarderJoueur(Joueur j, const char *filepath_joueurs);
Joueur chargementJoueur(char *pseudo,const char *filepath_joueurs);
void affichageJoueur(char *pseudo, const char *filepath_joueurs);
void matchJoueur(Joueur* j, bool partieNulle, bool victoire);
char* getPseudo(Joueur* j);

void affichageJoueursDispo(const char *filepath_joueurs);

int choixProfil(unsigned int maxProfil);
void viderBufferAdrien();

#endif // JOUEUR_H_INCLUDED
