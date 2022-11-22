#include "arbre.h"


bool etatContinue(struct dirent* entree){
    //printf("type: %d\n",entree->d_type);
    if(entree->d_type==DT_DIR){
        //printf("occurence 0 : %c\n",entree->d_name[0]);
        if(strcmp(entree->d_name,".")==0 || strcmp(entree->d_name,"..")==0||(entree->d_name)[0]=='.'){//on prend pas en compte le dossier courant, précédent ou caché
            return false;
        }
        return true;
        
    }
    else{
        return false;
    }
}

bool estFichier(struct dirent* entree){
    if(entree->d_type==DT_REG){
        
        if((entree->d_name)[0]=='.'){//on prend pas en compte les fichiers cachés
            return false;
        }
        return true;
        
    }
    return false;
}

int sizeToNumber(char* parametre){
    int number=abs(atoi(parametre));

    switch (parametre[strlen(parametre)-1])
    {
    case 'c':
        break;
    case 'k':
        number=number*1024;
        break;
    case 'm':
        number=number*1024*1024;
        break;
    case 'G':
        number=number*1024*1024*1024;
        break;
    default:
        //perror("parametre error");
        return -1;
    }
    return number;
}

int timeToNumber(char* parametre){
    int number=abs(atoi(parametre));

    switch (parametre[strlen(parametre)-1])
    {
    case 'm':
        number=number*60;
        break;
    case 'h':
        number=number*60*60;
        break;
    case 'j':
        number=number*60*60*24;//transformer en unité seconde
        break;
    default:
        //perror("parametre error");
        return -1;
    }
    return number;
}


void getChemin(char* cheminAncien, char* objCourant,char* enregistre){// cette fonction sert à concaténer les chemins
    
    int tailleA=strlen(cheminAncien)+4;
    int tailleC=strlen(objCourant)+4;
    
    char cheminA[tailleA];//chemin ancien
    strcpy(cheminA,cheminAncien);
    
    char cheminC[tailleC];
    strcpy(cheminC,objCourant);
    char* cheminAncienSlash;
    if (cheminAncien[strlen(cheminAncien)-1]== '/')
    {
        //printf("ok\n");
        //exit(EXIT_SUCCESS);
        cheminAncienSlash=strcat(cheminA,"");
    }
    else{
        cheminAncienSlash=strcat(cheminA,"/");
    }
    
    
    int tailleA2=strlen(cheminAncienSlash);
    char cheminCat[tailleA2+tailleC];
    strcpy(cheminCat,cheminAncienSlash);
    strcat(cheminCat,objCourant);
    strcpy(enregistre,cheminCat);

}



void parcourir_choisir(char* chemin, option_liste* options_demandees, Liste* liste){
    //initialisation, on ouvre le dossier en fonction du chemin donné
    DIR* entree =NULL;
    if ((entree = opendir (chemin)) == NULL) {
        exit (1);
    }
    struct dirent* courant = NULL;//structure après readdir
    char cheminP[200];//place pour enregistrer le prochain chemin
    
    while ((courant = readdir(entree))!= NULL){    
        char* nom = courant->d_name; //nom du fichier ou dossier
        //printf("nom : %s\n",nom);
        if( (strcmp(nom,".")!=0) & (strcmp(nom,"..")!=0) & (nom[0]!='.')  ){

            getChemin(chemin,nom,cheminP); //chemin de ce que j'analyse (je ne suis pas encore "dessus", je l'analyse depuis "chemin" = dossier)
            //printf("\nFichier/dossier analysé : %s\n",cheminP);
            bool status = true;
            int j = 0;
            cellule* current_option = options_demandees->premier;
            
            while (current_option != NULL){ //pour chaque option demandée
                //printf("Option demandée %d : %s\n",j,current_option->nom_option);

                if (current_option->option != 6){ //si ce n'est pas -dir, une option sur les dossiers
                    if (estFichier(courant)){ //si c'est un fichier   
                        if (!commande_a_exec(current_option->option,current_option->param,courant,cheminP)){  //on exécute l'option avec son paramètre et on voit si le fichier correspond
                            status = false; //il ne correspond pas à au moins une condition imposée par le paramètre d'une fonction
                            break;  //pas besoin de regarder les autres options demandées
                        }
                    }
                    else{ //option != -dir (forcément option sur fichiers) et c'est pas un fichier
                        status = false; //ne peut pas être valable
                        break; //pas besoin de regarder les autres options demandées
                    }
                }
                
                else{ //option -dir aka sur les dossiers
                    if (etatContinue(courant)){ //si c'est un dossier
                        if (!commande_a_exec(6,current_option->param,courant,cheminP)){    //on exécute dir avec son paramètre et on voit si le fichier correspond
                            status = false; //il ne correspond pas à au moins une condition imposée par le paramètre d'une fonction
                            //!!!!!!!!!!!!!!!!!! si on met pas de break ça va normalement car si on a -dir, l'option sera seule, SINON le rajouter ici
                        }  
                    }
                    else{ //option -dir et c'est pas un dossier
                        status = false; //ne peut pas être valable
                        //!!!!!!!!!!!!!!!!!! si on met pas de break ça va normalement car si on a -dir, l'option sera seule, SINON le rajouter ici
                    }
                }
            
            current_option = current_option->next;
            ++j;
            }
            //fin de l'analyse par rapport aux options demandées 
            
            if (status){
                ajouter(liste,cheminP); //le fichier/dossier valide toutes les conditions
                //printf("A tout validé : %s\n",cheminP); //on print le chemin du fichier/dossier
            }
            
            if (etatContinue(courant)){ //si dossier
                parcourir_choisir(cheminP,options_demandees,liste);  //j'analyse les fichiers/dossiers de ce dossier
            }    
        }
    }
    //fin du parcours de l'arborescence
    closedir(entree);
    
}

//fonctions qui correspondent aux commandes (bien si c'est du même nom)


bool commande_a_exec(int indice_commande,char* parametre,struct dirent* fichier,char* cheminP){
    //printf("chemin %s0\n",cheminP);
    switch (indice_commande)
    {
    case 1:
        return name(parametre,fichier);

    case 2:
        return stateSize(parametre,cheminP);

    case 3:
        return stateDate(parametre,cheminP);

    case 4:
        return mime(parametre,cheminP);

    case 5:
        return ctc(parametre,fichier);

    case 6:
        return dir(parametre,fichier);
    case 7 :
        return color(parametre,cheminP);
    case 8 :
        return statePerm(parametre,cheminP);
    default:
        printf("Erreur : option non reconnue.\n");
        return false;
    }
}

int give_id(char* option){
    char* options[12]={"-test","-name","-size","-date","-mime","-ctc","-dir","-color","-perm","-link","-threads","-ou"};
    for (int i = 0; i < 12; i++)
    {
        if (strcmp(options[i],option)==0)
        {
            return i;
        }
        
    }
    
    if (option[0] == '-'){ //une option inconnue ou un paramètre avec moins
        return -1;
    }
    
    return -2; //forcément un paramètre ou input erreur
}


