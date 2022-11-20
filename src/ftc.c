#include <stdio.h>
#include <string.h>
#include "arbre.h"
#include "liste.h"
#include "check.h"


int main(int argc, char const *argv[]){
    char* starting_point=argv[1];
    
    if (strcmp(argv[0],"./ftc")!=0)
    {
        printf("La ligne de commande doit être écrit sous forme :\n \t\t./ftc starting-point [-option [paramètre]]\n ");
        return(EXIT_FAILURE);
    }
    option_liste* options_demandees = createOptionListe();
    int i = 2; //commence à 2 car 0 = ./ftc et 1 = starting_point
    //char* options[12]={"-test","-name","-size","-date","-mime","-ctc","-dir","-color","-perm","-link","-threads","-ou"};

    while (argv[i]!=NULL) // pour détecter la fin de la ligne de commande
    {   
        int indice = give_id(argv[i]);

        if (indice==0)
        {
            ajouteOption(options_demandees,argv[i],indice,NULL);
            
        }
        else
        {
            if (argv[i+1] != NULL){
                if (give_id(argv[i+1])>=0)//si le preochaine élément est une option
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
    
    if (options_demandees->premier == NULL){
        printf("Aucune option donnée. La ligne de commande doit être écrite sous la forme :\n \t\t./ftc starting-point -option paramètre\n ");
    }
    if (test_option(options_demandees))//s'il y a option -test 
    {
        supprime(options_demandees);
        return 0;
    }
    
    //test_option(options_demandees);
    Liste* Liste_finale=initialisationListe();
    //show_option_list(options_demandees);
    Liste* liste_finale = parcourir_choisir(starting_point,options_demandees,initialisationListe());
    afficher_chemins_liste(liste_finale);
    
    //supprimerListe(liste_finale);
    supprime(options_demandees);
    //check_regex("a*","arbr.h");

    /*
    int départ = 0;
    int fin = 0;
    for (int i = 1; i < fin; i++)
    {   
        int indice = give_value(argv[i]);
        if (indice >= 0)
        {
            //int indice=give_value(argv[i]);
           // printf("indice %d\n",indice);
            if (give_value(argv[i+1])==-1)
            {
                ajouteOption(optionListe,give_value(argv[i]),argv[i+1]);
            }
            else{
                ajouteOption(optionListe,give_value(argv[i]),NULL);
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
    */
    
    /*
    char* options[100*sizeof(char*)];
    char* parametres[100*sizeof(char*)];
    int i = 1;

    while (argv[i] != NULL){ 

    for(int i = 1 ; i < argc ; i++){ //est-ce que y'a un caractère \n à la fin ? pk parfois je vois une autre option demandée avec des caractères chelous alors que je n'en ai pas mise ?
        //changer, marche pas bien (trous, pas d'option 1 mais 0 et 2 quand on met deux options et deux paramtres...)
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
                    options[i-2] = argv[i];
                    break;
                }
                
                else{
                    parametres[i-3] = argv[i];
                    parametres[i-3][strcspn(parametres[i-3], "\n")] = 0;
                    break;
                }
        }
    }

    Liste* liste_finale = parcourir_choisir(starting_point,options,parametres,initialisationListe());
    afficher_chemins_liste(liste_finale);
    supprimerListe(liste_finale);
    //bonne_sortie(starting_point,options,parametres,initialisationListe()); //une seule fonction qui gère la sortie, comme ça plus simple de modifier
    /*

    //date("-1h",chemin);
    check_regex("a*","arbr.h");
    */
   return 0;
}
