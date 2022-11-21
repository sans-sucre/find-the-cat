#ifndef __ARBRE__
#define __ARBRE__   
#include "liste.h"
#include "check.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <regex.h>
#include <ctype.h> //pour isdigit()


bool etatContinue(struct dirent* entree);//1 signifie que l'object est un dossier et on peut y aller

bool estFichier(struct dirent* entree);

int sizeToNumber(char* parametre);//transformer un paramètre en un nombre

int timeToNumber(char* parametre);//transformer un paramètre de temps en un nombre

void parcourir_choisir(char* chemin, option_liste* options_demandees, Liste* liste);

void getChemin(char* cheminAvant, char* objCourant,char* enregistre);//chemin sera enregistré dans le paramettre enregistre

bool commande_a_exec(int indice_commande, char* parametre, struct dirent* fichier,char* cheminP);

void bonne_sortie(char* chemin, option_liste* options_demandees, Liste* liste);

int give_id(char* option);//donner la valeur d'un flag, si c'est pas une option, alors -1

#endif //__ARBRE__
