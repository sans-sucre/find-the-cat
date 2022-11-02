#ifndef __ARBRE__
#define __ARBRE__

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <string.h>


bool etatContinue(struct dirent* entree);

void parcourirDossier( char* chemin);

void getChemin(char* cheminAvant, char* objCourant,char* enregistre);
























#endif //__ARBRE__
