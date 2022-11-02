#include "arbre.h"


bool etatContinue(struct dirent* entree){
    //printf("type: %d\n",entree->d_type);
    if(entree->d_type==DT_DIR){
        if(strchr(entree->d_name,'.')==NULL){//on prend pas en compte les dossiers cachés, le dossier courant ou le dossier précedédent
            return true;
        }
        return false;
        
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
            parcourirDossier(cheminP);
        }    
    } 
    closedir(entree);
}
