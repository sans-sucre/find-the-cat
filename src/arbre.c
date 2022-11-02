#include "arbre.h"


bool etatContinue(struct dirent* entree){
    //printf("type: %d\n",entree->d_type);
    if(entree->d_type==DT_DIR){
        //printf("occurence 0 : %c\n",entree->d_name[0]);
        if(strcmp(entree->d_name,".")==0 || strcmp(entree->d_name,"..")==0||(entree->d_name)[0]=='.'){//on prend pas en compte le dossier courant ou le dossier précedédent
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

void parcourirDossier(char* chemin){
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
