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
    DIR* entree=opendir(chemin);
    struct dirent* courant=NULL;//structure après readdir

    char cheminP[200];//seule façon à enregistrer le prochain chemin
    //printf("chemin courant : %s\n",chemin);
    
    while ((courant=readdir(entree))!= NULL)
    {
        
        //printf("name is : %s, coutinue ? : %d\n",courant->d_name,etatContinue(courant));
        if (etatContinue(courant))
        {
            char* nom=courant->d_name;
            getChemin(chemin,nom,cheminP);
            printf("chemin : %s\n",cheminP);
            if (courant->d_name[0]=='.'){
                printf("occurence 0 : %c\n",courant->d_name[0]);
            }
            
            parcourirDossier(cheminP);
        }    
    } 
    closedir(entree);
}


//fonctions qui correspondent aux commandes (bien si c'est du même nom)

void test(){
    printf("Fonction test\n");
    return;
}
void name(char* parametre){
    printf("Fonction name\n");
    //faut modifier parcoursdossier pour qu'il fasse une comparaison à chaque dossier ou on prend les lignes qu'il nous donne à la fin et on cherche dans la string ??
    //analyser la string à la fin sera plus simple jpense et c'est mieux par rapport à ce qui est demandé
    
    return;
}
void size(char* parametre){
    printf("Fonction size\n");
    return;
}
void date(char* parametre){
    printf("Fonction date\n");
    return;
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
    char* commandes[]={'-test','-name','-size','-date','-mime','-ctc','-dir'};

    //la taille du tableau peut changer donc on la met dans une variable plutôt qu'en dur 
    long int taille = sizeof(commandes)/sizeof(commandes[0]);

    int commande_exec;

    printf("Size tableau : %ld\n", taille);

    for (int i = 0 ; i < taille ; i++){
        if (strcmp(commande,commandes[i])){ //on trouve l'indice de la commande qui correspond à la commande demandée
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
        size(parametre);
        break;

    case 3:
        date(parametre);
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
