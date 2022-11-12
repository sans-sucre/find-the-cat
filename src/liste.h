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

typedef struct cellule
{
    int option;
    char* param;
    char* nom_option;
    struct cellule* next;
}cellule;

typedef struct option_liste
{
    cellule* premier;
}option_liste;

Liste* initialisationListe();

void ajouter(Liste* liste, char* chemin_fichier);

void afficherListe(Liste *liste);

void afficher_chemins_liste(Liste *liste);

void supprimerListe(Liste* liste);

//option liste :
option_liste* createOptionListe();

void ajouteOption(option_liste* liste,char* nom_option,int option,char* param);

void show_option_list(option_liste* liste);

void supprime(option_liste* liste);



#endif //__LISTE__