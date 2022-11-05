#ifndef __ARBRE__
#define __ARBRE__   //sert à quoi ?

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include<time.h>
#include <unistd.h>

bool etatContinue(struct dirent* entree);//1 signifie que l'object est un dossier et on peut y aller

bool estFichier(struct dirent* entree);

int sizeToNumber(char* parametre);//transformer un paramètre en un nombre

int timeToNumber(char* parametre);//transformer un paramètre de temps en un nombre

int parcourirDossier(char* chemin);

void getChemin(char* cheminAvant, char* objCourant,char* enregistre);//chemin sera enregistré dans le paramettre enregistre

void commande_a_exec(char * commande, char* parametre);

void test();

void name(char* parametre);

char** parser(int nb_files_dir);

void size(char* parametre,char* chemin);

bool stateSize(char* parametre, char* chemin);

void date(char* parametre,char* chemin);

bool stateDate(char* parametre,char* chemin);

void mime(char* parametre);

void ctc(char* parametre);

void dir(char* parametre);





















#endif //__ARBRE__
