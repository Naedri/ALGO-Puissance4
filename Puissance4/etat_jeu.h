/// @file etat_jeu.h
#ifndef ETAT_JEU_H_INCLUDED
#define ETAT_JEU_H_INCLUDED

struct EtatJeu {
    char joueur1 ;
    char joueur2 ;
    char symbole1 ; //symbole du joueur1
    char symbole2 ; //symbole du joueur2
    char joueurinitial ;  // qui a été le premier joueur a mettre un jeton
    char * grille;
    char tour ; //qui doit insérer le prochain jeton
}
#endif // ETAT_JEU_H_INCLUDED
