#include<stdio.h>
#include"arbre.h"

int main(int argc, char const *argv[])
{
    printf("hello world\n");
    char* chemin=".";//la racine de dossier, donné par question1
    
    parcourirDossier(chemin);

    return 0;
}
