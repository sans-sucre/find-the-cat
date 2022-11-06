#ifndef __ARBRE__
#define __ARBRE__   //sert à quoi ?

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <string.h>


bool etatContinue(struct dirent* entree);//1 signifie que l'object est un dossier et on peut y aller

void parcourirDossier(char* chemin);

void getChemin(char* cheminAvant, char* objCourant,char* enregistre);//chemin sera enregistré dans le paramettre enregistre

void commande_a_exec(char * commande, char* parametre);

void test();

void name(char* parametre);

void size(char* parametre);

void date(char* parametre);

void mime(char* parametre);

void ctc(char* parametre);

void dir(char* parametre);





















#endif //__ARBRE__
