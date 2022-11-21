#include <string.h>
#include"liste.h"


Liste* initialisationListe(){

    Liste* liste = calloc(1,sizeof(Liste));

    if (liste == NULL)
    {
        perror("Problème mémoire\n");
        exit(EXIT_FAILURE);
    }
    return liste;
}

void ajouter(Liste* liste, char* chemin_fichier){
    assert(liste!=NULL);
    Element* nouveau = calloc(1,sizeof(Element));
    
    //faut malloc et faire strcpy sinon quand le pointeur chemin_fichier pointera sur autre chose, la valeur changera aussi
    nouveau->chemin_fichier = malloc(sizeof(char) * (strlen(chemin_fichier)+1) );
    strcpy(nouveau->chemin_fichier,chemin_fichier); 
    
    nouveau->next=NULL;

    if (nouveau==NULL){
        perror("Erreur d'allocation mémoire !");
    }

    Element* current = liste->premier;
    if (current==NULL){
        liste->premier = nouveau;
        //printf("ok ici2\n");
    }

    else{
        while (current->next != NULL){
            //printf("ok ici2\n");
            current = current->next;
        } 
        //printf("ok ici2\n");
        current->next = nouveau;
    }
}

void afficherListe(Liste *liste){
    assert(liste!=NULL);
    Element* current = liste->premier;

    printf("[");
    while (current!= NULL){
        printf( "%s ", current->chemin_fichier);
        current = current->next;
    }
    printf("]\n");
}

void afficher_chemins_liste(Liste* liste){
    assert(liste!=NULL);
    Element* current = liste->premier;

    while (current!= NULL){
        printf( "%s\n", current->chemin_fichier);
        current = current->next;
    }
}

void supprimerListe(Liste* liste){
    assert(liste!=NULL);

    if (liste->premier != NULL){
        while (liste->premier->next != NULL){ //tant que le suivant n'est pas nul
            Element* aSupprimer = liste->premier;
            liste->premier = aSupprimer->next;
            aSupprimer->next=NULL;
            free(aSupprimer->chemin_fichier);
            free(aSupprimer);
        }
        free(liste->premier->chemin_fichier);
        free(liste->premier);
    }
    free(liste);
}

option_liste* createOptionListe(){
    option_liste* liste = calloc(1,sizeof(option_liste));

    if (liste == NULL)
    {
        perror("Problème mémoire\n");
        exit(EXIT_FAILURE);
    }
    return liste;
}

void ajouteOption(option_liste* liste,char* nom_option,int option,char* param){
    //printf("ok ici91\n");

    assert(liste!=NULL);
    cellule* nouveau = calloc(1,sizeof(cellule));
    if (nouveau==NULL){
        perror("Erreur d'allocation mémoire !");
    }

    nouveau->option = option;
    nouveau->nom_option = nom_option;
    nouveau->param=param;

    nouveau->next=NULL;

    cellule* current = liste->premier;
    if (current==NULL){
        liste->premier = nouveau;
        //printf("ok ici2\n");
    }

    else{
        while (current->next != NULL){
            //printf("ok ici2\n");
            current = current->next;
        } 
        //printf("ok ici2\n");
        current->next = nouveau;
    }
}

void show_option_list(option_liste* liste){
    assert(liste!=NULL);
    cellule* current = liste->premier;
    
    printf("[");
    while (current!= NULL){
        printf( "option : %s ", current->nom_option);
        printf( "param : %s ", current->param);
        current = current->next;
    }
    printf("]\n");
}

void supprime(option_liste* liste){
    assert(liste!=NULL);

    if (liste->premier != NULL){
        while (liste->premier->next != NULL){ //tant que le suivant n'est pas nul
            cellule* aSupprimer = liste->premier;
            liste->premier = aSupprimer->next;
            //free(aSupprimer->param);
            //free(aSupprimer->nom_option);
            free(aSupprimer);
        }
        //free(liste->premier->param);
        //free(liste->premier->nom_option);
        free(liste->premier);
    }
    free(liste);
}
