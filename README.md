# Algo-Puissance4
IUT Paris Descartes - 2019 - Enseignant : ZIANE Mikal.

## Algorithme et Programmation en C.

Dans le cadre du cours de Algorithme et Programmation en C, Mikal Ziane a proposé de développer un jeu : Le puissance4.

## Auteurs

BERTHIER Nicolas : <nicolas-berthier@orange.fr>  
ESCOFFIER Vincent : <alainvincentesc@gmail.com>  
JALLAIS Adrien : <adrien.jallais@protonmail.com>  

## Description
Le Puissance4 est un jeux à géometrie variable.  
Une présentation du jeu est consultable au lien suivant : <https://fr.wikipedia.org/wiki/Puissance_4> .

### Portabilité
Nécesitte un compilateur C, ou joueur seulement le fichier x64/Debug/Puissance4.exe
Deux dossiers 'joueurs' et 'parties' doivent être créés au préalable dans le même dossier que l'executable afin de permettre leur sauvegarde respective.

### Interface graphique
+ Mode console
+ Présence d'un Menu 
+ Grille de Jeu épurée

### Conception de la grille
+ 7 colonnes de A à G (verticales)
+ 6 rangées de 1 à 6 (horizontales)

### Joueurs
+ Jeu à deux joueurs physiques
+ Jeu contre l'ordinateur (IA)
  
### Options possibles
+ Partie
  + Sauvegarde et Chargement (format binaire)
+ Profil de joueur
  + Sauvegarde et Chargement (format binaire)
  + Création et Actualisation des statistiques de jeu

## Programmation

### Grille
La grille est stockée sous la forme d'une chaine de caractères. 
Cependant pour faciliter le choix de jeu de l'utilisateur, un traitement est réalisé au préalable pour l'afficher en colonnes. 

### Test de Production
Le jeu devra être testé tout au long de sa production, par l'utilisation de tests (assert).

### Tour de jeu
+ Afficher clairement le nom du joueur et son jeton associé qui devra jouer au prochain tour.
+ Evaluer la validité des coups proposés par l'utilisateur.
+ Evaluer une victoire ou un match-nul.

### Jeu contre l'ordinateur
L'IA utilisée lors d'une partie contre l'ordinateur est selon Minmax - alpha beta.

#### MinMax
A partir d’une grille de jeu donnee, on génère l’ensemble des positions que l’ordinateur peut atteindre.
Pour chacunes de ces positions, on génère l’ensemble des posistions que l’adversaire pourrait à son tour atteindre.
On recommence l’operation aussi lontemps que le permet la puissance de calcul de l’ordinateur. 
On construit ainsi un arbre representant l’ensemble des configurations de la grille du jeu pour un certain nombre de coups à l’avance. 
Il est clair que par cette technique, on ne peut pas construire l’arbre complet de la partie, c’est à dire un arbre dont toutes les feuilles seraient des coups terminaux (gagnant ou match nul). 
Puisqu’on est obligé de limiter la profondeur de l’arbre, il est nécessaire d’evaluer une position non terminale pour un joueur donné.

#### Algorithme α−β
Tel que présenté ci-dessus, MinMax calcule sans distonctions toutes les positions jouables de chaque grille. 
Afin de limiter le nombre de noeuds de l’arbre, l’algorithme α−β empêche le calcul des positions jugées inintéressantes.
