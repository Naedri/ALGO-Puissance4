/// @file commun.cpp
#include <stdlib.h>
#include <stdio.h> 
#include <malloc.h>
#include <cassert>

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