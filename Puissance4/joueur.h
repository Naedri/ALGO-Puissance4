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
	float partiesRatio ;// = partiesGagnees/ partiesPerdues avec cast
};

typedef struct Joueur Joueur;


void creationJoueur(Joueur* j, char *pseudo, char *nom, char *prenom, const char *filepath_joueurs, bool* redondance);
int nombreLignesTable(char *filePathName);
void sauvegarderJoueur(Joueur j, const char* filepath_joueurs);
Joueur chargementJoueur(char *pseudo,const char *filepath_joueurs);
void affichageJoueur(char *pseudo, const char *filepath_joueurs);
void matchJoueur(Joueur* j, bool partieNulle, bool victoire);
char* getPseudo(Joueur* j);

bool affichageJoueursDispo(const char *filepath_joueurs);
int nombreProfils(const char* filepath_joueurs);
int choixProfil(int maxProfil);
void getPseudoSelonID(char* chainePourPseudo, int id, const char* filepath_joueurs);

void menuProfil(); //affiche profilDispo
void menuCreationProfil(); //creer un profil
#endif // JOUEUR_H_INCLUDED
