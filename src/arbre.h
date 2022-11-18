#ifndef __ARBRE__
#define __ARBRE__   
#include "liste.h"
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

void parcourirDossier(char* chemin);

Liste* parcourir_choisir(char* chemin, option_liste* options_demandees, Liste* liste);

void getChemin(char* cheminAvant, char* objCourant,char* enregistre);//chemin sera enregistré dans le paramettre enregistre

bool commande_a_exec(int indice_commande, char* parametre, struct dirent* fichier);

bool name(char* parametre, struct dirent* fichier);

void size(char* parametre,char* chemin);

bool stateSize(char* parametre, char* chemin);

void date(char* parametre,char* chemin);

bool stateDate(char* parametre,char* chemin);

bool mime(char* parametre, struct dirent* fichier);

bool ctc(char* parametre, struct dirent* fichier);

bool dir(char* parametre, struct dirent* dossier);

bool check_regex(char* parametre, char* nom);

void bonne_sortie(char* chemin, option_liste* options_demandees, Liste* liste);

int give_id(char* option);//donner la valeur d'un flag, si c'est pas une option, alors -1




#endif //__ARBRE__
