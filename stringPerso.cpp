/// @file stringPerso.cpp
#include <stdlib.h> //initialisation à NULL
#include <stdio.h> //FILE structure est definie dans stdio.h
#include "stringPerso.h"

char strcatPerso(char destination, char source){
	int i=0;
	char *pdestination = NULL;
	char *psource = NULL;
	char *resultat[]=NULL;
	char *p[]=NULL;
	resultat = (char*)malloc((strlenPerso(pdestination) + strlenPerso(psource)+1) * sizeof(char));
	p = resultat;
	for (i = 0; i < strlenPerso(pdestination); i++)
		*p++ = destination[i];
	for (i = 0; i < strlenPerso(psource); i++)
		*p++ = source[i];
	return *resultat;
}
/*
int strlenPerso2(char chaine){
	char *pchaine = chaine;
	for (int i = 0; *pchaine != ’\0’; ++i)
		++pchaine;
	return i;
}
*/

int strlenPerso(char *chaine){
	for (int i = 0; *chaine != ’\0’; ++i)
		++chaine;
	return i;
}
