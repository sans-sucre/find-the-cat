#include "check.h"
bool name(char* parametre, struct dirent* fichier){
    int tailleP=strlen(parametre)+4;
    char param[tailleP];
    strcpy(param,parametre);

    char* nom = fichier->d_name; //nom du fichier
    int tailleN=strlen(nom)+4;
    char name[tailleN];
    strcpy(name,nom);

    if (strcmp(nom,parametre) == 0){ //si le nom est correct
        return true;
    }
    if (check_regex(param,name))
    {
        return true;
    }
    
    return false;
}

void size(char* parametre,char* chemin){

    DIR* entree = opendir(chemin);
    struct dirent* courant = NULL;
    char cheminP[200];
    
    while ((courant = readdir(entree))!= NULL)
    {    
        char* nom = courant->d_name; 
        getChemin(chemin,nom,cheminP);

        if (estFichier(courant)) // est un fichier
        {
            if(stateSize(parametre,cheminP)){
                //printf("chemin : %s \n",cheminP);
            }
        }
        if (etatContinue(courant)){ 
            
            size(parametre,cheminP);
        }    
    }
    closedir(entree);
    
}

bool stateSize(char* parametre, char* chemin){
    struct stat sb;
    if (stat(chemin,&sb)==-1){
        //perror("stat ERREUR");
        exit(EXIT_FAILURE);
    } 
    switch (parametre[0])
    {
    case '+' :
        if ((long long)sb.st_size > sizeToNumber(parametre))
        {
            //printf("chemin : %s taille de fichier : %lu octets\n",chemin,sb.st_size);
            return true;
        }  
        break;  
    case '-' : 
        if ((long long)sb.st_size < sizeToNumber(parametre))
        {
            //printf("chemin : %s taille de fichier : %lu octets\n",chemin,sb.st_size);
            return true;
        } 
        break; 
    default:
         //perror("paramètre erreur, caractère dehors '+''-'\n");
        exit(EXIT_FAILURE);
        break;
    }
    return false;
}

bool stateDate(char* parametre,char* chemin){
    struct stat sb;
    time_t now=time(NULL);
    int diff_time_obj=timeToNumber(parametre);
    //time_t temps=sb.st_atime;
    //int diff_time=(int)difftime(now,temps);
    //printf("diff%d\n",diff_time);

    if (stat(chemin,&sb)==-1){
        //perror("stat ERREUR");
        exit(EXIT_FAILURE);
    } 
    
    if (parametre[0]=='+') // + 3h ==>plus que trois heures
    {
        //printf("Current Date/Time = %s", ctime(&now));
        time_t temps=sb.st_atime;//je comprends pas pk il marche comme ça
        
        if ( (int) difftime(now,temps)>diff_time_obj)
        {
            //printf("%d",(int) difftime(now,temps));
            //printf("chemin : %s dernier accès : %s s \n",chemin,ctime(&sb.st_atime));
            return true;
        }
        
    }
    else if (isdigit(parametre[0])) //-3h ==>moins que trois heures
    {
        time_t temps=sb.st_atime;
        if ( (int) difftime(now,temps)<diff_time_obj)
        {
            //printf("%d",(int) difftime(now,temps));

            //printf("chemin : %s dernier accès : %s s \n",chemin,ctime(&sb.st_atime));
            return true;
        }
        
    }
    else
    {
        //perror("paramètre erreur, caractère dehors '+''-'\n");
        exit(EXIT_FAILURE);
    }
    return false;
}


void date(char* parametre,char* chemin){
    
    DIR* entree = opendir(chemin);
    struct dirent* courant = NULL;
    char cheminP[200];
    
    while ((courant = readdir(entree))!= NULL)
    {    
        char* nom = courant->d_name; 
        getChemin(chemin,nom,cheminP);
        //printf("chemin : %s \n",cheminP);

        if (estFichier(courant)) // est un fichier
        {

            if(stateDate(parametre,cheminP)){
                
            }
            
        }
        if (etatContinue(courant)){ 
            
            date(parametre,cheminP);
        }    
    }
    closedir(entree);
    
}
bool mime(char* parametre, struct dirent* fichier){
    printf("Fonction mime\n");
    return;
}
bool ctc(char* parametre, struct dirent* fichier){
    printf("Fonction ctc\n");
    return;
}
bool dir(char* parametre, struct dirent* dossier){

    char* nom = dossier->d_name; //nom du dossier

    if (parametre == NULL){ //si -dir sans option, on affiche tous les dossiers
        return true;
    }

    if (strcmp(nom,parametre) == 0){ //si le nom est correct
        return true;
    }
    return false;
}


bool check_regex(char* parametre, char* nom){// les paramètres ici doit lui passer un const char
    regex_t preg;
    
    int err = regcomp (&preg, parametre, REG_NOSUB | REG_EXTENDED);//on compile la chaîne de caractères 
    if (err == 0)//pas d'erreur
    {
        int match = regexec (&preg,nom, 0, NULL, 0);
        regfree (&preg);

        if (match == 0)
        {
            //printf ("%s est un fichier valide\n", nom);
            return true;
        }
        else if (match == REG_NOMATCH)
        {
            //printf ("%s n\'est pas un fichier valide\n", nom);
            return false;
        }
    }
    else
    {
        //perror("erreur de compilation de regex\n");
        exit(EXIT_FAILURE);
    }
    
}

void bonne_sortie(char* chemin, option_liste* options_demandees, Liste* liste){
    Liste* liste_finale = parcourir_choisir(chemin,options_demandees,liste);
    afficher_chemins_liste(liste_finale);
    supprimerListe(liste_finale);

}

bool check_param(int indiceOption, char* param){
    switch (indiceOption)
    {
    case 2 :
        if (param[0]=='+'||param[0]=='-')
        {
            if (sizeToNumber(param)==-1)
            {
                return false;
            }
            return true;
        }
        return false;
    case 3 :
        if (param[0]=='+'||isdigit(param[0]))
        {
            if (timeToNumber(param)==-1)
            {
                return false;
            }
            return true;
        }
        return false;
    
    default:
        break;
    }
    return true;
}

bool test_option(option_liste* options_demandees){
    cellule* current_option = options_demandees->premier;

    if (current_option==NULL)
    {
        return false;
    }
    

    if (current_option->option == 0){ //si c'est le test
        cellule* suivant = current_option->next;
        //   printf("option  %s, param :%s\n",suivant->nom_option,suivant->param);
        if (give_id(suivant->nom_option)>0)
        {
            printf("La valeur du flag %s est %s",suivant->nom_option,suivant->param);
        }
        else
        {
            printf("Le flag %s n'est pas correct",suivant->nom_option);
        }
        return true;
    }
    return false;

}