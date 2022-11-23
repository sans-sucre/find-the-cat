#include <stdio.h>
#include <string.h>
#include "arbre.h"
#include "liste.h"
#include "MegaMimes.h"
#include "check.h"


int main(int argc, char const *argv[]){
    
   // statePerm("000","/arbre/different/tell/owner/my.flac");
    char* starting_point=argv[1];
    if (strcmp(argv[0],"./ftc")!=0)
    {
        printf("La ligne de commande doit être écrit sous forme :\n \t\t./ftc starting-point [-option [paramètre]]\n ");
        return(EXIT_FAILURE);
    }
    option_liste* options_demandees = createOptionListe();
    int i = 2; //commence à 2 car 0 = ./ftc et 1 = starting_point

    while (argv[i]!=NULL) // pour détecter la fin de la ligne de commande
    {   
        int indice = give_id(argv[i]);

        if (indice==0) //si -test
        {
            ajouteOption(options_demandees,argv[i],indice,NULL);
            
        }
        else
        {
            if (argv[i+1] != NULL){
                if (give_id(argv[i+1])>=0)//si le prochain élément est une option
                {
                    ajouteOption(options_demandees,argv[i],indice,NULL);
                }
                else// sinon, c'est pas une option
                {
                    ajouteOption(options_demandees,argv[i],indice,argv[i+1]);
                    i++;
                }
            }
            else{ //on ajoute l'option sans paramètre
                ajouteOption(options_demandees,argv[i],indice,NULL);
            }
        }
        i++;
    }

    Liste* liste_finale=initialisationListe();
    
    if (options_demandees->premier == NULL){
        //printf("Aucune option donnée. La ligne de commande doit être écrite sous la forme :\n \t\t./ftc starting-point -option paramètre\n ");
        ajouter(liste_finale,starting_point);
    }
    
    if (test_option(options_demandees))//s'il y a option -test 
    {
        supprime(options_demandees);
        return 0;
    }
    //size("27c",starting_point);
    //test_option(options_demandees);
    
    //show_option_list(options_demandees);
    
    parcourir_choisir(starting_point,options_demandees,liste_finale);
    afficher_chemins_liste(liste_finale);
    
    supprimerListe(liste_finale);
    supprime(options_demandees);

   return 0;
}
