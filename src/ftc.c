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
                else{// sinon, c'est pas une option
                    
                    int j = i+1;
                    char* param = malloc(sizeof(char) * strlen(argv[j]) +1); //on initialise le paramètre
                    strcpy(param,"");
                    
                    while (j < argc && give_id(argv[j]) < 0){ //tant qu'on a des paramètres
                       
                        char* temp = malloc(sizeof(char) * (strlen(param)+1 + strlen(argv[j])+1 +2)); //+2 pour l'espace
                        strcpy(temp,param); //on copie ce qu'il y avait avant
                        
                        free(param); //on free le paramètre pour lui allouer la bonne taille
                        param = malloc(sizeof(char) * (strlen(temp)+1 + strlen(argv[j]) +1));

                        if(strcmp(temp,"") != 0){ //s'il y avait un autre mot avant, on met un espace
                            strcat(temp," ");
                        }

                        strcat(temp,argv[j]); //on ajoute le nv mot
                        strcpy(param,temp); //on copie dans le paramètre
                        j++;
                        
                        //printf("j : %d\nargc : %d\nparam : %s\n",j,argc,param);
                        
                        free(temp);
                    }
                    
                    ajouteOption(options_demandees,argv[i],indice,param); //param contient au moins un mot
                    free(param);
                    i = j-1;
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
