#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

struct Joueur {
	char pseudo;
	char nom;
	char prenom;
	int partiesJouees; //nbr partie joué
	int partiesGagnees; //nbr parties gagnées
	int partiesPerdues; //nbr parties perdues
	float partiesRatio; //ratio partie gagnées/jouées
}
#endif // JOUEUR_H_INCLUDED