#include <stdio.h>
#include "arbre.h"

//fonctions qui correspondent aux commandes (bien si c'est du même nom)






int main(int argc, char const *argv[]){
    printf("Hello world!\n");
    char* chemin=".";//la racine de dossier, donné par question1

    char* commandes[7]={'-test','-name','-size','-date','-mime','-ctc','-dir'};

    char* options[7]; //mettre les options de chaque commande à l'indice i qui correspond bien à la commande i dans la liste commandes
    //plutôt faire une dictionnaire => pas de structure dictionnaire mais table de hashage... avec à chaque alvéole la liste simplement chaînée des options

    char* starting_point = argv[1]; // d'où on commence la recherche
    
    char* commande = argv[2];
    //printf("Commande : %s\n",commande);

    for (int i = 0 ; i < 7 ; i++){
        if (strcmp(commande,commandes[i])){
            for (int j = 0 ; j < options[i].length ; j++){ //nb d'options de la commande
                if (strcmp())
            }//pour chaque option donnée dans la ligne de commande faut qu'il fasse ça...
        }
    }


    //on utilise commande pour trouver les options dans le dico, si la commande != clé du dico, commande pas reconnue

    parcourirDossier(chemin);

    return 0;
}
