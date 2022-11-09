#include <stdio.h>
#include <string.h>
#include "arbre.h"
#include "liste.h"


int main(int argc, char const *argv[]){
    if (strcmp(argv[1],"ftc")!=0)
    {
        printf("La ligne de commande doit être écrit sous forme :\n \t\tftc starting-point [-option [paramètre]]\n ");
        return(EXIT_FAILURE);
    }
    
    int fin=0;//indice du dernier élément est fin-1
    int depart=0;//indice de "ftc"
    while (argv[fin]!=NULL) // pour détercter la fin de la ligne de commande
    {
        fin++;
    }
    option_liste* optionListe=createOptionListe();
    for (int i = 1; i < fin; i++)
    {
        if (give_value(argv[i])>=0)
        {
            int indice=give_value(argv[i]);
            printf("indice %d\n",indice);
            if (give_value(argv[i+1])==-1)
            {
                ajouteOption(optionListe,indice,argv[i+1]);
            }
            else{
                ajouteOption(optionListe,indice,NULL);
            }

        }
        else if ( (argv[i][0] == '-') & (!isdigit(argv[i][1])) &(give_value(argv[i])<0)) 
        {
            printf("Option %s inconnue\n",argv[i]);
            printf("La ligne de commande doit être écrit sous forme :\n \t\tftc starting-point [-option [paramètre]]\n ");
            supprime(optionListe);
            return(EXIT_FAILURE);
        }    
         
    }
    show_option_list(optionListe);
    supprime(optionListe);
    /*
    char* starting_point=argv[2];
    char* options[100*sizeof(char*)];
    char* parametres[100*sizeof(char*)];
    int i = 1;

    while (argv[i] != NULL){ 

        switch (i){
            case 1:
                starting_point = argv[2]; // d'où on commence la recherche
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
                    parametres[i-3][strcspn(parametres[i-3], "\n")] = 0;   
                    printf("Paramètre %d : %s\n",i-3,argv[i]);
                    break;
                }
        }
    i++;
    }*/

    //Liste* liste_finale = parcourir_choisir(starting_point,options,parametres,initialisationListe());
    //Liste* liste_finale=initialisationListe();
    //ajouter(liste_finale,"00.txt");
    //afficherListe(liste_finale);
    //supprimerListe(liste_finale);
    
    //parcourirDossier(starting_point);
/*
    commande_a_exec(commande,parametre);    //on exécute la command demandée avec le parametre donné
    //si le paramètre n'est pas correct, ce sera dans la fonction qu'il sera analysé et jugé mauvais

    //date("-1h",chemin);
    //check_regex("a*","arbr.h");
    */
   return 0;
}
