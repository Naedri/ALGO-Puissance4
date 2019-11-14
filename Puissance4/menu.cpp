#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "T2d.h"
#include <string.h>
#include "partie.h"
#include "joueur.h"

//ubuntu
/*
#include <dirent.h>
*/
//windows
/**/
#include "dirent.h" //windows opendir() renvoie un pointeur de type DIR https://codeyarns.com/2014/06/06/how-to-use-dirent-h-with-visual-studio/
#pragma warning(disable : 4996) //ouverture de fichier et manipulation de chaine et d heure
#pragma warning(suppress : 4996) //ouverture de fichier et manipulation de chaine et d heure


void reglesJeu() {
	printf("\n\n***** Les regles de Puissance 4 *****\n\n");
	printf("**Deux joueurs s'affrontent en posant successivement un pion dans la colonne de son choix.\n");
	printf("**Les pions inseres tombent tout en bas de la colonne ou jusqu'aux pions qui y sont deja poses.\n");
	printf("**Le premier joueur alignant 4 pions (horizontalement, verticalement, ou en diagonale) gagne la partie.\n");
	printf("**Si aucun des joueurs n'arrivent a aligner 4 pions, la partie est declaree nulle.\n");
	printf("\n\n*************************************\n\n");
	//peut-être afficher le plan de jeu ?
}

void retourAccueil() {
	accueilJeu();
}

void accueilJeu() {
	unsigned int choixJeuouStat = 0;//variable qui demande à l'utilisateur de jouer (2) ou de regarder les stats(1)
	unsigned int ChoixretourMenu = 0; //retourner au menu (1) sortir du jeu (2)
	unsigned int choixJouerIA = 0; //retourner au menu (1) sortir du jeu (2)
	unsigned int choixListeJoueurs = 0;// //
	unsigned int choixCreationJoueurs = 0; //demande si un joueur a déjà un pseudonyme d'enregistré
	unsigned int numeroPseudoJ1 = 0;//numero de pseudo déjà existant sélectionné par l'utilisateur
	unsigned int numeroPseudoJ2 = 0;//idem pour joueur 2
	char pseudoStat[10] = ""; //pseudo demandé pour avoir les statistiques d'un joueur

	printf("\n\n\n ####### PUISSANCE 4 ####### \n\n");
	printf("\n\n\n******** Menu principal ********\n\n");
	printf("Le jeu Puissance 4 est un jeu qui se joue a deux.\nDe nombreux joueurs l ont deja essaye !\n");
	printf("Tapez < 1 > : Pour connaitre les statisques des joueurs disponibles.\n");
	printf("Tapez < 2 > : Si vous souhaitez creer un nouveau profil de joueur.\n");
	printf("Tapez < 3 > : Pour debuter une partie. Les nouveaux joueurs doivent au prealable creer un profil.\n");
	printf("Tapez < 4 > : Pour reprendre une partie en cours.\n");
	printf("Tapez < 5 > : Pour vous entrainez.\n");
	printf("Tapez < 6 > : Pour voir les regles du jeu.\n");
	printf("Tapez < 7 > : Pour afficher les auteurs.\n\n");
	do {
		scanf_s("%d", &choixJeuouStat); //je n'ai rien securise

		if (choixJeuouStat == 1) {//IL CHOISIT DE REGARDER LES STATISTIQUES
			printf("\n\n******** Statistiques ********\n\n");
			menuProfil();
			accueilJeu();
		}

		if (choixJeuouStat == 2) {//IL CHOISIT DE CREER UN NOUVEAU PROFIL DE JOUEUR
			printf("\n\n******** Creation de Profil ********\n\n");
			menuCreationProfil();
			accueilJeu();
		}

		if (choixJeuouStat == 3) {//IL CHOISIT DE JOUER
			printf("\n\n******** Jouons ! ********\n\n");
			printf("\nQui etes vous parmi les joueurs suivants ?\n");
			
			//initialisation
			bool joueursDispo = false;
			joueursDispo = affichageJoueursDispo(FILEPATH_JOUEURS);

			if (joueursDispo == false) { //il n y a pas de profils de dispo donc retour a l accueil
				accueilJeu();
			}
			if (joueursDispo == true) { //des profils sont dispo pour leur chargement
				
				//initialisation
				Joueur joueur1 = NOUVEAU_JOUEUR;
				Joueur joueur2 = NOUVEAU_JOUEUR;
				Partie partie = NOUVELLE_PARTIE;

				//chargement des joueurs
				printf("Verifier que vos pseudos sont présents dans la liste des joueurs ci dessus.\n");
				printf("Souhaitez vous revenir au menu principal. Tapez < 0 >.\n");

				//initialisation1
				int choixChargementJ1 = 0;
				//char c; //verif du dernier caractere est un retour chariot.
				int nbrCaraEntres = 0;
				
				//nombre de profil max
				int nbrProfilMAX = 0;
				nbrProfilMAX = nombreProfils(FILEPATH_JOUEURS); //scan des profil pour avoir nbr profil max

				//entree utilisateur pour choix joueur1
				printf("Sinon veuillez indiquer le numero d'un des deux joueurs qui sera implique dans cette partie.\n");
				//nbrCaraEntres = scanf("%c%c", &choixChargementJ1, &c);
				//nbrCaraEntres = scanf_s("%2s", choixChargementJ1, (unsigned)_countof(choixChargementJ1));
				nbrCaraEntres = scanf_s("%d", &choixChargementJ1);
				//while (nbrCaraEntres != 2 && c != '\n' && choixChargementJ1 < 0 && choixChargementJ1 > nbrProfilMAX) {
				while (nbrCaraEntres >= 3 || choixChargementJ1 < 0 || choixChargementJ1 > nbrProfilMAX) {
					printf("Veuillez choisir un numero valide.\n");
					//nbrCaraEntres = scanf("%d%c", &choixChargementJ1, &c);
					nbrCaraEntres = scanf_s("%d", &choixChargementJ1);
				}

				if (choixChargementJ1 == 0) {
					printf("Retour au Menu Principal.\n");
					accueilJeu();
				}

				if (choixChargementJ1 != 0) {
					//joueur1
					char profilPseudo[TAILLE_ID] = "";
					getPseudoSelonID(profilPseudo, choixChargementJ1, FILEPATH_JOUEURS);//ecrit dans ProfilPseudo le pseudo associé à profilXID

					joueur1 = chargementJoueur(profilPseudo, FILEPATH_JOUEURS); //chargement du profil x
					printf("Ce joueur a les details suivants.\n");
					affichageJoueur(profilPseudo, FILEPATH_JOUEURS);

					//choix joueur2
					printf("Veuillez indiquer le numero de l'autre joueur qui sera implique dans cette partie.\n");
					//initialisation1
					unsigned int choixChargementJ2 = 0;
					//char c2; //verif du dernier caractere est un retour chariot.
					int nbrCaraEntres2 = 0;

					nbrCaraEntres2 = scanf("%d", &choixChargementJ2);
					while (nbrCaraEntres2 >=3 ||choixChargementJ2 < 0 || choixChargementJ2 > nbrProfilMAX || choixChargementJ2 == choixChargementJ1)
					{
						printf("Veuillez un numero valide ou un numero different du pseudo precedement choisi.\n");
						nbrCaraEntres2 = scanf_s("%d", &choixChargementJ2);
					}

					if (choixChargementJ2 == 0u) {
						printf("Retour au Menu Principal.\n");
					}

					if (choixChargementJ2 != 0u) {
						//joueur2
						char profilPseudo2[TAILLE_ID] = "";
						getPseudoSelonID(profilPseudo2, choixChargementJ2, FILEPATH_JOUEURS);//ecrit dans ProfilPseudo le pseudo associé à profilXID

						joueur2 = chargementJoueur(profilPseudo2, FILEPATH_JOUEURS); //chargement du profil x
						printf("Ce joueur a les details suivants.\n");
						affichageJoueur(profilPseudo2, FILEPATH_JOUEURS);
					}
				}
				
				//definition de la partie
				Partie p = NOUVELLE_PARTIE;
				printf("\nLes joueurs seront : \n");
				printf("(1)%s vs (2)%s.\n", joueur1.pseudo, joueur2.pseudo);
				//definition la table
				T2d t = NOUVELLE_TABLE;
				init(&t, 7u, 6u);
				unsigned int largeur = 0;
				unsigned int hauteur = 0;
				largeur = getLargeur(&t);
				hauteur = getHauteur(&t);
				//integration de la grille dans partie
				p.grilleHauteur = hauteur;
				p.grilleLargeur = largeur;
				p.grilleChar = t.grille ;

				//premier joueur
				printf("\nSaisissez le numero d'identifiant [(1) ou (2)] du joueur qui debutera la partie : \n");
				int choixPremierJoueur = 0;
				//char c3; //verif du dernier caractere est un retour chariot.
				int nbrCaraEntres3 = 0;
				nbrCaraEntres3 = scanf_s("%d", &choixPremierJoueur);

				while (nbrCaraEntres3 >=2 || choixPremierJoueur <= 0 || choixPremierJoueur > 2) {
					printf("Veuillez choisir un numero valide.\n");
					nbrCaraEntres3 = scanf_s("%d", &choixPremierJoueur);
				}

				if (choixPremierJoueur == 1) {
					strcpy(p.joueurInitial, joueur1.pseudo);
					printf("\nLe joueur %s debute la partie. ", p.joueurInitial);
				}
				if (choixPremierJoueur == 2) {
					strcpy(p.joueurInitial, joueur2.pseudo);
					printf("\nLe joueur %s debute la partie. ", p.joueurInitial);
				}

				//detail de jeu
				unsigned int symbole1 = 1u;
				//symbolePremier = getSymbole(2);
				printf("Il jouera avec le jeton (%c). ", symbole1);
				//second joueur
				if (strcmp(p.joueurInitial, joueur1.pseudo) == 0) {
					printf("\nLe second joueur sera %s. ", joueur2.pseudo);
				}
				if (strcmp(p.joueurInitial, joueur1.pseudo) != 0) {
					printf("\nLe second joueur sera %s. ", joueur1.pseudo);
				}

				unsigned int symbole2 = 2u;
				printf("Il jouera avec le jeton (%c).\n\n\n", symbole2);
				viderBuffer();
				if (strcmp(p.joueurInitial, joueur1.pseudo) == 0) {
					creationPartie(&p, joueur1.pseudo, 1u, joueur2.pseudo, symbole2,
						p.joueurInitial, 1,
						p.joueurInitial, 0u,
						largeur, hauteur, t.grille);
				}
				if (strcmp(p.joueurInitial, joueur1.pseudo) != 0) {
					creationPartie(&p, joueur1.pseudo, 2u, joueur2.pseudo, symbole1,
						p.joueurInitial, 1,
						p.joueurInitial, 0u,
						largeur, hauteur, t.grille);
				}
				
				sauvegarderPartie(p, FILEPATH_PARTIES);
				lancerPartie(p, joueur1, joueur2);
				accueilJeu();
			}
		}

		if (choixJeuouStat == 4) {//IL CHOISIT DE REGARDER LES PARTIES DISPO
			printf("\n\n******** Parties ********\n\n");
			Partie p = NOUVELLE_PARTIE;
			p = menuPartie(p);
			if (p.symboleActif == 0u) { //il n y a pas de parties dispo
				accueilJeu();
			}
			else { //il y a des parties dispos
				char pseudo1[TAILLE_ID] = "";
				char pseudo2[TAILLE_ID] = "";
				strcpy(pseudo1, p.joueur1);
				strcpy(pseudo2, p.joueur2);
				Joueur joueur1 = NOUVEAU_JOUEUR;
				Joueur joueur2 = NOUVEAU_JOUEUR;
				joueur1 = chargementJoueur(pseudo1, FILEPATH_JOUEURS);
				joueur2 = chargementJoueur(pseudo2, FILEPATH_JOUEURS);
				Joueur* pjoueur1 = &joueur1;
				Joueur* pjoueur2 = &joueur2;
				Partie* ppartie = &p;

				lancerPartie(p, joueur1, joueur2);
				accueilJeu();
			}
		}

		if (choixJeuouStat == 5) {//IL CHOISIT DE JOUER CONTRE L IA
			printf("\n\n******** Entrainez vous ********\n\n");

			printf("Tapez < 1 > : Pour jouer contre l'IA.\nTapez < 2 > : Pour retourner au menu principal.\n");
			scanf_s("%d", &choixJouerIA);            
			
			while (choixJouerIA != 1 && choixJouerIA != 2) {
				viderBuffer();
				printf("\nVeuillez entrer un numero valide.\n\a");
				scanf_s("%d", &choixJouerIA);
			}
			if (choixJouerIA == 1) {
				initSeed();
				playIA();
			}
			if (choixJouerIA == 2) {
				accueilJeu();
			}
		}

		if (choixJeuouStat == 6) {//IL CHOISIT DE REGARDER LES REGLES DU JEU
			printf("\n\n******** Regles ********\n\n");
			reglesJeu();
			printf("\nTapez < 1 > : Pour retourner au menu principal.\n");
			do {
				scanf_s("%d", &ChoixretourMenu);
				if (ChoixretourMenu == 1) {
					accueilJeu();
				}
				if (ChoixretourMenu != 1) {
					printf("\nVeuillez rentrer une commande valide.\nTapez < 1 > : Pour retourner au menu principal.\n\a");
				}
			} while (ChoixretourMenu != 1);
		}

		if (choixJeuouStat == 7) {//IL CHOISIT DE REGARDER LES REGLES DU JEU
			printf("\n\n******** Auteurs ********\n\n");
			printf("\npar ordre alphabetique :\n\n");
			printf("BERTHIER Nicolas nicolas-berthier@orange.fr\n");
			printf("ESCOFFIER Vincent alain.vincent@gmail.com\n");
			printf("JALLAIS Adrien adrien.jallais@protonmail.com\n\n");
			printf("\nTapez < 1 > : Pour retourner au menu principal.\n");
			do {
				scanf_s("%d", &ChoixretourMenu);
				if (ChoixretourMenu == 1) {
					accueilJeu();
				}
				if (ChoixretourMenu != 1) {
					printf("\nVeuillez rentrer une commande valide.\nTapez < 1 > : Pour retourner au menu principal.\n\a");
				}
			} while (ChoixretourMenu != 1);
		}

		if (choixJeuouStat != 1 && choixJeuouStat != 2 && choixJeuouStat != 3 && choixJeuouStat != 4 && choixJeuouStat != 5 && choixJeuouStat != 6 && choixJeuouStat != 7) {
			printf("\nVeuillez rentrer une commande valide,\a\n ");
		}
	} while ((choixJeuouStat != 1 && choixJeuouStat != 2 && choixJeuouStat != 3));
}

void lancerPartie(Partie p, Joueur j1, Joueur j2) {
	
	//chargement de T2d*t à partir de Partie p
	T2d tt = NOUVELLE_TABLE;
	tt.hauteur = p.grilleHauteur;
	tt.largeur = p.grilleLargeur;
	tt.grille = p.grilleChar;

	T2d* t = NULL;
	t = &tt;
	
	//initialisation
	char s[250];
	char choix;
	char col;
	unsigned int ligne;
	
	//table des noms de joueurs
	char listeJoueur[2][TAILLE_ID] = { "", "" } ;
	if (strcmp(p.joueurInitial, p.joueur1) == 0) {
		strcpy(listeJoueur[0], p.joueur1);
		strcpy(listeJoueur[1], p.joueur2);
	}	if (strcmp(p.joueurInitial, p.joueur2) == 0) {
		strcpy(listeJoueur[0], p.joueur2);
		strcpy(listeJoueur[1], p.joueur1);
	}

	//affichage de la table
	printf("\nVous etes pret ? \n");
	printf("\n***** Let's go ! *****\n");
	toString(t, s);
	printf("%s", s);
	//affichage du premier joueur
	char pseudoAffiche0[TAILLE_ID];
	if (p.nbrTour % 2 == 1) {
		strcpy(pseudoAffiche0, listeJoueur[1]);
		printf("\nC'est au joueur '%s' de commencer avec le jeton (X).\n", pseudoAffiche0);
	}
	if (p.nbrTour % 2 == 0) {
		strcpy(pseudoAffiche0, listeJoueur[0]);
		printf("\nC'est au joueur '%s' de commencer avec le jeton (X).\n", pseudoAffiche0);
	}

	//dereoulement du jeu
	for (unsigned int i = p.nbrTour; i < (getLargeur(t) * getHauteur(t) +1); ++i) {
		char pseudoAffiche[TAILLE_ID];
		char pseudoVictoire[TAILLE_ID];
		char pseudoPerdant[TAILLE_ID];
		choix = choixJoueur(t);
		if (choix == '#') {
			printf("Vous avez sauvegarde la partie.\n");
			printf("Vous allez etre redirige vers le menu principal.\n");
			sauvegarderPartie(p, FILEPATH_PARTIES);
			break; //on sort de la boucle for
		}
		else {
			col = choix;
			ligne = placerJeton(t, col, getSymbole((i) % 2 + 1));
			toString(t, s);
			printf("%s", s);

			if (estVictoire(t, col, ligne) == true && (i % 2 == 0)) {
				strcpy(pseudoAffiche, listeJoueur[0]);
				printf("Le joueur '%s' a gagne la partie !\n", pseudoAffiche);
				printf("Vous allez etre redirige vers le menu principal.\n");

				strcpy(pseudoVictoire, listeJoueur[0]);
				strcpy(pseudoPerdant, listeJoueur[1]);
				
				if (strcmp(pseudoVictoire, j1.pseudo)==0) {
					matchJoueur(&j1, false, true);
					matchJoueur(&j2, false, false);
				}
				if (strcmp(pseudoVictoire, j1.pseudo)!=0) {
					matchJoueur(&j2, false, true);
					matchJoueur(&j1, false, false);
				}
				sauvegarderJoueur(j1,FILEPATH_JOUEURS);
				sauvegarderJoueur(j2,FILEPATH_JOUEURS);
				break;
			}
			if (estVictoire(t, col, ligne) == true && (i % 2 == 1)) {
				strcpy(pseudoAffiche, listeJoueur[1]);
				printf("Le joueur '%s' a gagne la partie !\n", pseudoAffiche);
				printf("Vous allez etre redirige vers le menu principal.\n");

				strcpy(pseudoVictoire, listeJoueur[1]);
				strcpy(pseudoPerdant, listeJoueur[0]);

				if (strcmp(pseudoVictoire, j1.pseudo) == 0) {
					matchJoueur(&j1, false, true);
					matchJoueur(&j2, false, false);
				}
				if (strcmp(pseudoVictoire, j1.pseudo) != 0) {
					matchJoueur(&j2, false, true);
					matchJoueur(&j1, false, false);
				}
				sauvegarderJoueur(j1, FILEPATH_JOUEURS);
				sauvegarderJoueur(j2, FILEPATH_JOUEURS);

				break;
			}

			if (i % 2 == 0) {
				strcpy(pseudoAffiche, listeJoueur[1]);
				printf("\nC'est au joueur '%s' de jouer avec le jeton (O).\n", pseudoAffiche);
			}
			if (i % 2 == 1) {
				strcpy(pseudoAffiche, listeJoueur[0]);
				printf("\nC'est au joueur '%s' de jouer avec le jeton (X).\n", pseudoAffiche);
			}

			//if (i == getLargeur(t) * getHauteur(t)) {
			if (grillePleine(t)) {
				printf("Match nul.\n");
				printf("Vous allez etre redirige vers le menu principal.\n");
				matchJoueur(&j1, true, false);
				matchJoueur(&j2, true, false);
				sauvegarderJoueur(j1, FILEPATH_JOUEURS);
				sauvegarderJoueur(j2, FILEPATH_JOUEURS);
				break;
			}
		}
	}
	accueilJeu();
}