#include <stdio.h>
#include "arbre.h"


int main(int argc, char const *argv[]){
    printf("Hello world!\n");
    char* chemin=".";//la racine de dossier, donné par question1

    char* parametres[7]; //mettre les options de chaque commande à l'indice i qui correspond bien à la commande i dans la liste commandes
    //plutôt faire une dictionnaire => pas de structure dictionnaire mais table de hashage... avec à chaque alvéole la liste simplement chaînée des options
    //on utilise commande pour trouver les options dans le dico, si la commande != clé du dico, commande pas reconnue
    //=> pas besoin car options possibles trop grandes pour dates et tailles => analyser le paramètre dans la fonction, si c'est sous une forme qui marche, ok
    //ou sinon on met dans paramètres que les options qui sont uniques ou dénombrables, genre d m y pour dates mais pas chaque nb et + ou -

    char* starting_point = argv[1]; // d'où on commence la recherche
    printf("Départ : %s\n",starting_point);

    char* commande = argv[2];   
    printf("Commande : %s\n",commande);

    char* parametre = argv[3]; //paramètre de la commande
    printf("Paramètre : %s\n",parametre);
    
    //commande_a_exec(commande,parametre);    //on exécute la command demandée avec le parametre donné
    //si le paramètre n'est pas correct, ce sera dans la fonction qu'il sera analysé et jugé mauvais

    parcourirDossier(chemin);

    commande_a_exec(commande,parametre);

    return 0;
}
