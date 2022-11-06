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
    //initialisation, on ouvre le dossier en fonction de chemin donné
    DIR* entree = opendir(chemin);
    struct dirent* courant = NULL;//structure après readdir

    char cheminP[200];//seule façon à enregistrer le prochain chemin
    //printf("chemin courant : %s\n",chemin);
    
    while ((courant = readdir(entree))!= NULL)
    {    
        char* nom = courant->d_name; //nom du fichier ou dossier

        //printf("name is : %s, coutinue ? : %d\n",courant->d_name,etatContinue(courant));
        if(strcmp(nom,".")!=0 & strcmp(nom,"..")!=0 & nom[0]!='.'){//on prend pas en compte le dossier courant, le dossier précédent ou les fichiers cachés

            getChemin(chemin,nom,cheminP);
            printf("%s\n",cheminP); //on print le chemin du dossier ou fichier
            
            if (nom[0]=='.'){   //ici pas possible comme j'ai fait, ça sert à quoi ?
                printf("occurence 0 : %c\n",courant->d_name[0]);
            }

            if (etatContinue(courant)){ //si c'est un dossier
                parcourirDossier(cheminP);
            }    
        } 
    }
    closedir(entree);
}


//fonctions qui correspondent aux commandes (bien si c'est du même nom)

void test(){
    printf("Fonction test\n");
    return;
}

char** name(char* parametre, char* chemin){
    printf("Fonction name\n");

    char** res = malloc (sizeof(char*)*100);
    
    //initialisation, on ouvre le dossier en fonction du chemin donné
    DIR* entree = opendir(chemin);
    struct dirent* courant = NULL;//structure après readdir

    char cheminP[200];//place pour enregistrer le prochain chemin
    
    while ((courant = readdir(entree))!= NULL){    
        char* nom = courant->d_name; //nom du fichier ou dossier

        
            if(strcmp(nom,".")!=0 & strcmp(nom,"..")!=0 & nom[0]!='.'){ //on prend pas en compte le dossier courant, le dossier précédent ou les fichiers cachés
                if (!etatContinue(courant)){ //si ce n'est pas un dossier
                
                    if (strcmp(nom,parametre) == 0){
                        getChemin(chemin,nom,cheminP);
                        printf("%s\n",cheminP); //on print le chemin du dossier ou fichier demandé

                    }
                }
            }
            else{
                parcourirDossier(cheminP);
            }    
        } 
    closedir(entree);
    return res;
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
void mime(char* parametre){
    printf("Fonction mime\n");
    return;
}
void ctc(char* parametre){
    printf("Fonction ctc\n");
    return;
}
void dir(char* parametre){
    printf("Fonction dir\n");
    return;
}

void commande_a_exec(char* commande,char* parametre){
    char* commandes[]={"-test","-name","-size","-date","-mime","-ctc","-dir"};

    //la taille du tableau peut changer donc on la met dans une variable plutôt qu'en dur 
    long int taille = sizeof(commandes)/sizeof(commandes[0]);
    //printf("Size tableau : %ld\n", taille);

    int commande_exec;

    for (int i = 0 ; i < taille ; i++){
        if (strcmp(commande,commandes[i]) == 0){ //on trouve l'indice de la commande qui correspond à la commande demandée
            commande_exec = i;  //on le sauvegarde pour le switch
        }
    }

    switch (commande_exec)
    {
    case 0:
        test();
        break;
    
    case 1:
        name(parametre);
        break;

    case 2:
        size(parametre,"");// à modifier
        break;

    case 3:
        date(parametre,"");// à modifier
        break;

    case 4:
        mime(parametre);
        break;

    case 5:
        ctc(parametre);
        break;

    case 6:
        dir(parametre);
        break;

    default:
        printf("Erreur, commande non reconnue.\n");
        break;
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
