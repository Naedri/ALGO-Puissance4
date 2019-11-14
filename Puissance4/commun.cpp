/// @file commun.cpp
#include <stdlib.h>
#include <stdio.h> 
#include <malloc.h>
#include <cassert>

//ubuntu
/*
#include <dirent.h>
*/
//windows
/**/
#include "dirent.h" //windows opendir() renvoie un pointeur de type DIR https://codeyarns.com/2014/06/06/how-to-use-dirent-h-with-visual-studio/
#pragma warning(disable : 4996) //ouverture de fichier et manipulation de chaine et d heure
#pragma warning(suppress : 4996) //ouverture de fichier et manipulation de chaine et d heure


//viderBuffer
int viderBuffer(){
	int caraActuel = 0;
	while (caraActuel != '\n') //fin de saisie
	{
		caraActuel = getchar();
	}
	return 1;
}

/*
int viderBuffer() {
	while (getchar() != '\n');
	return 1;
}
*/

bool fichierExiste(char* nomDuFichierAvecExtension, const char* filepath) {
	assert(nomDuFichierAvecExtension != NULL);
	assert(filepath != NULL);

	bool existe = true;
	unsigned int nbrFichier = 0u;

	//dirent.h
	DIR* dossier = opendir(filepath); // DIR *opendir(const char *dirname);
	struct dirent* fichier = NULL; //struct dirent *readdir(DIR *dir);

	// opendir()
	// renvoie un pointeur NULL si le dossier n a pas ete trouve
	if (dossier == NULL) {
		printf("\nIL y a eu une erreur dans l'ouverture du dossier /joueurs.\n");
		exit(1);
	}

	else {
		// readdir()
		while ((fichier = readdir(dossier)) != NULL) {
			if ((strcmp(nomDuFichierAvecExtension, fichier->d_name) == 0)) {
				++nbrFichier;
			}
		}
		
		if (nbrFichier == 0u)
		{
			closedir(dossier);
			existe = false;
		}
		else {
			closedir(dossier);
			existe = true;
		}
	}
	return existe;
}