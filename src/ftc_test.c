#include <stdio.h>
#include "arbre.h"

//fonctions qui correspondent aux commandes (bien si c'est du même nom)

void test(){
    printf("Fonction test\n");
    return;
}
void name(char* parametre){
    printf("Fonction name\n");
    return;
}
void size(char* parametre){
    printf("Fonction size\n");
    return;
}
void date(char* parametre){
    printf("Fonction date\n");
    return;
}
void mime(char* parametre){
    printf("Fonction mime\n");
    return;
}
void ctc(char* parametre){
    printf("Fonction ctc\n");
    return;
}
void dir(char* parametre){
    printf("Fonction dir\n");
    return;
}

void commande_a_exec(char* commande,char* parametre){
    char* commandes[]={'-test','-name','-size','-date','-mime','-ctc','-dir'};

    //la taille du tableau peut changer donc on la met dans une variable plutôt qu'en dur 
    long int taille = sizeof(commandes)/sizeof(commandes[0]);

    int commande_exec;

    printf("Size tableau : %ld\n", taille);

    for (int i = 0 ; i < taille ; i++){
        if (strcmp(commande,commandes[i])){ //on trouve l'indice de la commande qui correspond à la commande demandée
            commande_exec = i;  //on le sauvegarde pour le switch
        }
    }

    switch (commande_exec)
    {
    case 0:
        test();
        break;
    
    case 1:
        name(parametre);
        break;

    case 2:
        size(parametre);
        break;

    case 3:
        date(parametre);
        break;

    case 4:
        mime(parametre);
        break;

    case 5:
        ctc(parametre);
        break;

    case 6:
        dir(parametre);
        break;

    default:
        printf("Erreur, commande non reconnue.\n");
        break;
    }
}



int main(int argc, char const *argv[]){
    printf("Hello world!\n");
    char* chemin=".";//la racine de dossier, donné par question1

    char* parametres[7]; //mettre les options de chaque commande à l'indice i qui correspond bien à la commande i dans la liste commandes
    //plutôt faire une dictionnaire => pas de structure dictionnaire mais table de hashage... avec à chaque alvéole la liste simplement chaînée des options
    //on utilise commande pour trouver les options dans le dico, si la commande != clé du dico, commande pas reconnue
    //=> pas besoin car options possibles trop grandes pour dates et tailles => analyser le paramètre dans la fonction, si c'est sous une forme qui marche, ok
    //ou sinon on met dans paramètres que les options qui sont uniques ou dénombrables, genre d m y pour dates mais pas chaque nb et + ou -

    char* starting_point = argv[1]; // d'où on commence la recherche
    //printf("Départ : %s\n",starting_point);

    char* commande = argv[2];   
    //printf("Commande : %s\n",commande);

    char* parametre = argv[3]; //paramètre de la commande
    //printf("Paramètre : %s\n",parametre);
    
    commande_a_exec(commande,parametre);    //on exécute la command demandée avec le parametre donné
    //si le paramètre n'est pas correct, ce sera dans la fonction qu'il sera analysé et jugé mauvais

    parcourirDossier(chemin);

    return 0;
}