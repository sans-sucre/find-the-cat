#include"liste.h"


Liste* initialisationListe(){

    Liste* liste = calloc(1,sizeof(*liste));

    if (liste == NULL)
    {
        perror("problème mémoire\n");
        exit(EXIT_FAILURE);
    }
    return liste;
}

void ajouter(Liste* liste, char* chemin_fichier){
    assert(liste!=NULL);
    Element* nouveau = calloc(1,sizeof(Element));
    nouveau->chemin_fichier = chemin_fichier;
    nouveau->next=NULL;
    if (nouveau==NULL)
    {
        perror("allouer mémoire erreur!");
    }

    Element* current = liste->premier;
    if (current==NULL)
    {
        liste->premier= nouveau;
        //printf("ok ici2\n");
    }
    else
    {
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
    printf("ok ici4\n");

    while (current!= NULL){
        printf("ok ici5\n");

        printf("%s, ", current->chemin_fichier);
        current = current->next;
    }
    //printf("%s\n", current->chemin_fichier);

}

void supprimerListe(Liste* liste){
    
    if (liste == NULL){
        printf("Suppression impossible : la liste est NULL.\n");
        exit(EXIT_FAILURE);
    }

    while (liste->premier->next != NULL){ //tant que le suivant n'est pas nul
        Element* aSupprimer = liste->premier;
        liste->premier = aSupprimer->next;
        free(aSupprimer);
    }
    free(liste->premier);
    
    free(liste);
}