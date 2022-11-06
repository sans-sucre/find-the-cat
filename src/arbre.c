#include "arbre.h"


bool etatContinue(struct dirent* entree){
    //printf("type: %d\n",entree->d_type);
    if(entree->d_type==DT_DIR){
        //printf("occurence 0 : %c\n",entree->d_name[0]);
        if(strcmp(entree->d_name,".")==0 || strcmp(entree->d_name,"..")==0||(entree->d_name)[0]=='.'){//on prend pas en compte le dossier courant ou le dossier précédent
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
        
        if((entree->d_name)[0]=='.'){//on prend pas en compte le dossier courant ou le dossier précédent
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
    
    int tailleA=strlen(cheminAncien);
    int tailleC=strlen(objCourant);
    
    char cheminA[tailleA];//chemin ancien
    strcpy(cheminA,cheminAncien);
    
    char cheminC[tailleC];
    strcpy(cheminC,objCourant);
   

    char* cheminAncienSlash=strcat(cheminA,"/");
    
    int tailleA2=strlen(cheminAncienSlash);
    char cheminCat[tailleA2];
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

Liste* initialisationListe(){

    Liste* liste = malloc(sizeof(*liste));

    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    liste->premier = NULL;

    return liste;
}

void ajouter(Liste* liste, char* chemin_fichier){
    
    Element* current = liste->premier;

    Element* nouveau = malloc(sizeof(*nouveau));
    
    if (current != NULL){
        while (current->next != NULL){
            current = current->next;
        }

        nouveau->chemin_fichier = chemin_fichier;
        current->next = nouveau;
    }
    
    else{
        nouveau->chemin_fichier = chemin_fichier;
        current = nouveau;
    }
}

void afficherListe(Liste *liste){
    if (liste == NULL){
        printf("La liste est NULL.\n");
        exit(EXIT_FAILURE);
    }

    Element* current = liste->premier;

    while (current != NULL){
        printf("%s", current->chemin_fichier);
        current = current->next;
    }
}

void supprimerListe(Liste* liste){
    
    if (liste == NULL){
        printf("Suppression impossible : la liste est NULL.\n");
        exit(EXIT_FAILURE);
    }

    if (liste->premier != NULL){

        while (liste->premier->next != NULL){ //tant que le suivant n'est pas nul
            Element* aSupprimer = liste->premier;
            liste->premier = aSupprimer->next;
            free(aSupprimer);
        }
        free(liste->premier);
    }
    free(liste);
}

Liste* parcourir_choisir(char* chemin, char** options_demandees, char** parametres, Liste* liste){
    //////////////////PARCOURS DE L'ARBORESCENCE
    printf("\n\nEntrée dans parcourir_choisir, chemin = %s\n",chemin);

    char* options[]={"-test","-name","-size","-date","-mime","-ctc","-dir"};

    //la taille du tableau
    long int taille = sizeof(options)/sizeof(options[0]);

    //initialisation, on ouvre le dossier en fonction du chemin donné
    DIR* entree = opendir(chemin);
    struct dirent* courant = NULL;//structure après readdir

    char cheminP[200];//place pour enregistrer le prochain chemin
    
    while ((courant = readdir(entree))!= NULL)
    {    
        char* nom = courant->d_name; //nom du fichier ou dossier

        if( (strcmp(nom,".")!=0) & (strcmp(nom,"..")!=0) & (nom[0]!='.') ){//on prend pas en compte le dossier courant, le dossier précédent ou les fichiers cachés

            getChemin(chemin,nom,cheminP);

            if (!etatContinue(courant)){ //si c'est un fichier

                bool status = true;
                
                for (int j = 0 ; j < taille ; j++){ //pour chaque option demandée
                    printf("j : %d\n",j);
                    printf("Option demandée %d : %s\n",j,options_demandees[j]);

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

            else{ //si c'est un dossier
                liste = parcourir_choisir(cheminP,options_demandees,parametres,liste);
            }    
        } 
    }
    return liste;
    closedir(entree);

}

//fonctions qui correspondent aux commandes (bien si c'est du même nom)



void test(){
    printf("Fonction test\n");
    return;
}

bool name(char* parametre, struct dirent* fichier){
    printf("Fonction name\n");  

    char* nom = fichier->d_name; //nom du fichier ou dossier

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
bool dir(char* parametre, struct dirent* fichier){
    printf("Fonction dir\n");
    return;
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
