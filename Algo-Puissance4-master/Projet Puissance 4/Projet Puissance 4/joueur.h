#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

struct Joueur {
	char pseudo;
	char nom;
	char prenom;
	int partiesJouees; //nbr partie jou�
	int partiesGagnees; //nbr parties gagn�es
	int partiesPerdues; //nbr parties perdues
	float partiesRatio; //ratio partie gagn�es/jou�es
}
#endif // JOUEUR_H_INCLUDED