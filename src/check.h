#ifndef __CHECK__
#define __CHECK__

#include "liste.h"
#include "MegaMimes.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <unistd.h>
#include <regex.h>
#include <ctype.h> //pour isdigit()


bool check_regex(char* parametre, char* nom);

void bonne_sortie(char* chemin, option_liste* options_demandees, Liste* liste);

bool check_param(int indiceOption, char* param);

bool test_option(option_liste* options_demandees);// pour option -test 

bool name(char* parametre, struct dirent* fichier);

bool stateSize(char* parametre, char* chemin);

bool stateDate(char* parametre,char* chemin);

bool statePerm(char* parametre, char* chemin);

bool mime(char* parametre, char* chemin);

bool ctc(char* parametre, struct dirent* fichier);

bool dir(char* parametre, struct dirent* dossier);

bool color(char* parametre,char* cheminP);

int octToDec(int octal);



#endif // __CHECK__
