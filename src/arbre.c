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
        perror("parametre error");
        break;
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
        perror("parametre error");
        break;
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
   

    char* cheminAncienSlash=strcat(cheminA,"/");
    
    int tailleA2=strlen(cheminAncienSlash);
    char cheminCat[tailleA2+tailleC];
    strcpy(cheminCat,cheminAncienSlash);
    strcat(cheminCat,objCourant);
    strcpy(enregistre,cheminCat);

}

void parcourirDossier(char* chemin){ //faudrait donner les fichiers aussi
    //initialisation, on ouvre le dossier en fonction du chemin donné
    DIR* entree = opendir(chemin);
    struct dirent* courant = NULL;//structure après readdir

    char cheminP[200];//seule façon à enregistrer le prochain chemin
    //printf("chemin courant : %s\n",chemin);
    
    while ((courant = readdir(entree))!= NULL)
    {    
        char* nom = courant->d_name; //nom du fichier ou dossier

        //printf("name is : %s, coutinue ? : %d\n",courant->d_name,etatContinue(courant));
        if( (strcmp(nom,".")!=0) & (strcmp(nom,"..")!=0) & (nom[0]!='.') ){//on prend pas en compte le dossier courant, le dossier précédent ou les fichiers cachés

            getChemin(chemin,nom,cheminP);
            printf("%s\n",cheminP); //on print le chemin du dossier ou fichier

            if (etatContinue(courant)){ //si c'est un dossier
                parcourirDossier(cheminP);
            }    
        } 
    }
    closedir(entree);
}


Liste* parcourir_choisir(char* chemin, char** options_demandees, char** parametres, Liste* liste){
    //////////////////PARCOURS DE L'ARBORESCENCE
    printf("\n\nEntrée dans parcourir_choisir, chemin = %s\n",chemin);

    char* options[100*sizeof(char*)]={"-test","-name","-size","-date","-mime","-ctc","-dir"};

    //la taille du tableau
    //long int taille = sizeof(options)/sizeof(options[0]);

    int taille = 7;

    //initialisation, on ouvre le dossier en fonction du chemin donné
    DIR* entree = opendir(chemin);
    struct dirent* courant = NULL;//structure après readdir

    char cheminP[200];//place pour enregistrer le prochain chemin
    
    while ((courant = readdir(entree))!= NULL){    
        char* nom = courant->d_name; //nom du fichier ou dossier

        if( (strcmp(nom,".")!=0) & (strcmp(nom,"..")!=0) & (nom[0]!='.') ){//on prend pas en compte le dossier courant, le dossier précédent ou les dossiers/fichiers cachés

            getChemin(chemin,nom,cheminP); //chemin de ce que j'analyse (je ne suis pas encore "dessus", je l'analyse depuis "chemin" = dossier)
            printf("\nFichier/dossier analysé : %s\n",cheminP);

            bool status = true;
            int j = 0;
            
            while (options_demandees[j] != NULL){ //pour chaque option demandée
                printf("Option demandée %d : %s\n",j,options_demandees[j]);

                if (strcmp(options_demandees[j],"-dir") != 0){ //si ce n'est pas une option sur les dossiers

                    if (estFichier(courant)){ //si c'est un fichier
                        
                        for (int i = 0 ; i < taille ; i++){ //parcours tableau des options connues/demandables
                            
                            if (strcmp(options_demandees[j],options[i]) == 0){ //on trouve l'indice de la fonction demandée
                                printf("Option reconnue %d : %s\n",i,options[i]);
                                if (!commande_a_exec(i,parametres[j],courant)){    //on l'exécute avec son paramètre et on voit si le fichier correspond
                                    printf("Condition non respectée\n");
                                    status = false; //il ne correspond pas à au moins une condition imposée par le paramètre d'une fonction
                                }
                                break; //pas besoin de regarder les autres options connues, on a déjà trouvé la bonne  
                            }
                        }

                        if (!status){ //au moins une condition non rencontrée
                            break;  //pas besoin de regarder les autres options demandées
                        }
                    }

                    else{ //option != -dir (forcément option sur fichiers) et c'est pas un fichier
                        status = false; //ne peut pas être valable
                        break;
                    }
                }
                
                else{ //option -dir aka sur les dossiers
                printf("Option dir\n");
                    if (etatContinue(courant)){ //si c'est un dossier
                        printf("Option dir et c'est un dossier\n");
                        if (!commande_a_exec(6,parametres[j],courant)){    //on exécute dir avec son paramètre et on voit si le fichier correspond
                            status = false; //il ne correspond pas à au moins une condition imposée par le paramètre d'une fonction
                        }  
                    }
                    else{ //option -dir et c'est pas un dossier
                        status = false; //ne peut pas être valable
                    }
                //!!!!!!!!!!!!!!!!!! si on met pas de break ça va normalement car si on a -dir, l'option sera seule, SINON le rajouter ici
                }
            j++;
            }
            //fin de l'analyse par rapport aux options demandées 
            
            if (status){
                ajouter(liste,cheminP); //le fichier/dossier valide toutes les conditions
                printf("A tout validé : %s\n",cheminP); //on print le chemin du fichier/dossier
                afficherListe(liste);
            }
            
            if (etatContinue(courant)){ //si dossier
                printf("Liste avant parcours dossier : ");
                afficherListe(liste);
                liste = parcourir_choisir(cheminP,options_demandees,parametres,liste);  //j'analyse les fichiers/dossiers de ce dossier
                printf("Liste après parcours dossier : ");
                afficherListe(liste);
            }
            
        }
    }
    closedir(entree);
    return liste;
}
/* Avant changement
        if(etatContinue(courant) ){//on prend pas en compte le dossier courant, le dossier précédent ou les fichiers cachés

            getChemin(chemin,nom,cheminP);

            if (estFichier(courant)){ //si c'est un fichier

                bool status = true;
                
                for (int j = 0 ; j < taille ; j++){ //pour chaque option demandée
                    printf("Option demandée %d : %s\n",j,options_demandees[j]);
                   
                    if (options_demandees[j] == "-dir"){ //si c'est une option sur les dossiers
                        break;
                    }

                    for (int i = 0 ; i < taille ; i++){ //parcours tableau des options connues/demandables
                        printf("Option connue %d : %s\n",i,options[i]);
                        
                        if (strcmp(options_demandees[j],options[i]) == 0){ //on trouve l'indice de la fonction demandée
                            
                            printf("Booléen : %d\n",commande_a_exec(i,parametres[j],courant));

                            if (!commande_a_exec(i,parametres[j],courant)){    //on l'exécute avec son paramètre et on voit si le fichier correspond
                                status = false; //il ne correspond pas à au moins une condition imposée par le paramètre d'une fonction
                                break;
                            }  
                        }
                    }
                    if (!status){
                        break;
                    }
                    
                }
                if (status){
                    ajouter(liste,cheminP); //le fichier valide toutes les conditions
                    printf("%s\n",cheminP); //on print le chemin du fichier
                }
            }
            //fichier ou dossier
            liste = parcourir_choisir(cheminP,options_demandees,parametres,liste);    
        } 
    }
*/


//fonctions qui correspondent aux commandes (bien si c'est du même nom)



void test(){
    printf("Fonction test\n");
    return;
}

bool name(char* parametre, struct dirent* fichier){

    char* nom = fichier->d_name; //nom du fichier

    if (strcmp(nom,parametre) == 0){ //si le nom est correct
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
        perror("stat ERREUR");
        exit(EXIT_FAILURE);
    } 

    if(parametre[0]=='+'){
        if ((long long)sb.st_size > sizeToNumber(parametre))
        {
            printf("chemin : %s taille de fichier : %lu octets\n",chemin,sb.st_size);
            return true;
        }    
    }
    else if(parametre[0]=='-')
    {
        if ((long long)sb.st_size < sizeToNumber(parametre))
        {
            //printf("chemin : %s taille de fichier : %lu octets\n",chemin,sb.st_size);
            return true;
        }    
    }
    else
    {
        perror("paramètre erreur, caractère dehors '+''-'\n");
        exit(EXIT_FAILURE);
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
        perror("stat ERREUR");
        exit(EXIT_FAILURE);
    } 
    
    if (parametre[0]=='+') // + 3h ==>plus que trois heures
    {
        //printf("Current Date/Time = %s", ctime(&now));
        time_t temps=sb.st_atime;//je comprends pas pk il marche comme ça
        
        if ( (int) difftime(now,temps)>diff_time_obj)
        {
            printf("%d",(int) difftime(now,temps));
            printf("chemin : %s dernier accès : %s s \n",chemin,ctime(&sb.st_atime));
            return true;
        }
        
    }
    else if (parametre[0]=='-') //-3h ==>moins que trois heures
    {
        time_t temps=sb.st_atime;
        if ( (int) difftime(now,temps)<diff_time_obj)
        {
            printf("%d",(int) difftime(now,temps));

            printf("chemin : %s dernier accès : %s s \n",chemin,ctime(&sb.st_atime));
            return true;
        }
        
    }
    else
    {
        perror("paramètre erreur, caractère dehors '+''-'\n");
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
    printf("Nom dossier : %s\n",nom);
    printf("Nom dossier recherché : %s\n",parametre);

    if (strcmp(nom,parametre) == 0){ //si le nom est correct
        return true;
    }
    return false;
}

bool commande_a_exec(int indice_commande,char* parametre,struct dirent* fichier){

    switch (indice_commande)
    {
    case 0:
        test();
        return false;
    
    case 1:
        return name(parametre,fichier);

    case 2:
        return stateSize(parametre,"");// à modifier

    case 3:
        return stateDate(parametre,"");// à modifier

    case 4:
        return mime(parametre,fichier);

    case 5:
        return ctc(parametre,fichier);

    case 6:
        return dir(parametre,fichier);

    default:
        printf("Erreur : option non reconnue.\n");
        return false;
    }
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
            printf ("%s est un fichier valide\n", nom);
            return true;
        }
        else if (match == REG_NOMATCH)
        {
            printf ("%s n\'est pas un fichier valide\n", nom);
            return false;
        }
    }
    else
    {
        perror("erreur de compilation de regex\n");
        exit(EXIT_FAILURE);
    }
    
}
