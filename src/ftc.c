#include <stdio.h>
#include "arbre.h"
#include "liste.h"


int main(int argc, char const *argv[]){
    
    printf("Hello world!\n");
    char* chemin = ".";//la racine de dossier, donné par question1

    //char* parametres[7]; //mettre les options de chaque commande à l'indice i qui correspond bien à la commande i dans la liste commandes
    //plutôt faire une dictionnaire => pas de structure dictionnaire mais table de hashage... avec à chaque alvéole la liste simplement chaînée des options
    //on utilise commande pour trouver les options dans le dico, si la commande != clé du dico, commande pas reconnue
    //=> pas besoin car options possibles trop grandes pour dates et tailles => analyser le paramètre dans la fonction, si c'est sous une forme qui marche, ok
    //ou sinon on met dans paramètres que les options qui sont uniques ou dénombrables, genre d m y pour dates mais pas chaque nb et + ou -

    /*
    ////////////////AJOUT DANS LISTE DES COMMANDES DEMANDEES SI ELLES SONT VALIDES (et ajout du paramètre dans la liste des paramètres)
    char* commandes[]={"-test","-name","-size","-date","-mime","-ctc","-dir"};

    //la taille du tableau peut changer donc on la met dans une variable plutôt qu'en dur 
    long int taille = sizeof(commandes)/sizeof(commandes[0]);

    char* options[taille];
    char* parametres[taille];
    int i = 1;
    while (argv[i] != NULL){
        switch (i){
            case 1:
                char* starting_point = argv[1]; // d'où on commence la recherche
                printf("Départ : %s\n",starting_point);
                break;

            case 2:
                bool trouvee = false;

                for (int j = 0 ; j < taille ; j++){
                    if (strcmp(argv[i],commandes[j]) == 0){ //l'option demandée est valide
                        trouvee = true;
                        options[i-2] = argv[i];
                        printf("Option %d : %s\n",i-2,argv[i]);
                        break;
                    }
                }

                if (!trouvee){
                    printf("Option %s non reconnue.\n",argv[i]);
                }
                break;

            case 3:
                parametres[i-3] = argv[i];   
                printf("Paramètre %d : %s\n",i-3,argv[i]);
                break;

            default:
                if (argv[i][0] == '-' & !isdigit(argv[i][1])){ //si c'est bien une option et pas un paramètre comme -9k
                    
                    bool trouvee = false;

                    for (int j = 0 ; j < taille ; j++){
                        if (strcmp(argv[i],commandes[j]) == 0){ //l'option demandée est valide
                            trouvee = true;
                            options[i-3] = argv[i];   
                            printf("Option %d : %s\n",i-3,argv[i]);
                            break;
                        }
                    }

                    if (!trouvee){
                    printf("Option non reconnue.\n",argv[i]);
                    }
                    break;
                }
                
                else{
                    parametres[i-3] = argv[i];   
                    printf("Paramètre %d : %s\n",i-3,argv[i]);
                    break;
                }
        }
    }
    */

   ////////////////AJOUT DANS LISTE DES COMMANDES DEMANDEES (et ajout du paramètre dans la liste des paramètres)
    char* starting_point;
    char* options[12];//nuffer problème
    char* parametres[12];// buffer problème
    int i = 1;

    while (argv[i] != NULL){

        switch (i){
            case 1:
                starting_point = argv[1]; // d'où on commence la recherche
                printf("Départ : %s\n",starting_point);
                break;

            case 2:
                options[i-2] = argv[i];
                printf("Option %d : %s\n",i-2,argv[i]);
                break;

            case 3:
                parametres[i-3] = argv[i];   
                printf("Paramètre %d : %s\n",i-3,argv[i]);
                break;

            default:
                if ( (argv[i][0] == '-') & (!isdigit(argv[i][1])) ){ //si c'est bien une option et pas un paramètre comme -9k
                    options[i-3] = argv[i];   
                    printf("Option %d : %s\n",i-3,argv[i]);
                    break;
                }
                
                else{
                    parametres[i-3] = argv[i];   
                    printf("Paramètre %d : %s\n",i-3,argv[i]);
                    break;
                }
        }
    i++;
    }

    parcourirDossier(chemin);

    //Liste* liste_finale = parcourir_choisir(chemin,options,parametres,initialisationListe());
    
    /*
    //parcourirDossier(chemin);

    commande_a_exec(commande,parametre);    //on exécute la command demandée avec le parametre donné
    //si le paramètre n'est pas correct, ce sera dans la fonction qu'il sera analysé et jugé mauvais

    //date("-1h",chemin);
    //check_regex("a*","arbr.h");
    */
   return 0;
}
