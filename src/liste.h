#ifndef __LISTE__
#define __LISTE__ 
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <regex.h>
#include <ctype.h> 
#include <assert.h>

typedef struct Element{
    char* chemin_fichier;
    struct Element* next;
}Element;

typedef struct Liste{
    Element* premier;
}Liste;

Liste* initialisationListe();

void ajouter(Liste* liste, char* chemin_fichier);

void afficherListe(Liste *liste);

void afficher_chemins_liste(Liste *liste);

void supprimerListe(Liste* liste);
#endif //__LISTE__