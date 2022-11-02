#ifndef __ARBRE__
#define __ARBRE__   //sert à quoi ?

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <string.h>


bool etatContinue(struct dirent* entree);//1 signifie que l'object est un dossier et on peut y aller

void parcourirDossier( char* chemin);

void getChemin(char* cheminAvant, char* objCourant,char* enregistre);//chemin sera enregistré dans le paramettre enregistre
























#endif //__ARBRE__
