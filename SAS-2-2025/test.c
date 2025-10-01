#include<stdio.h>
#include"bridge.h"
#include<string.h>
#include<stdlib.h>

void showProdIds(){
    for (int prd=0; prd<N_PROD; prd++)
        printf("ID: %d\n", LProd[prd].idProduit);
}

int main(){

    char string1[]="HeLlo";
    char lowered[sizeof(string1)];
    lowerString(lowered, string1);
    printf("Original: %s\n", string1);
    printf("Lowered: %s\n", lowered);


    // _fillProd();
    // showAllProd();
    // showDetailProd(LProd[2]);
    // char string1[10], string2[10];
    // int integer;
    // printf("Entez un nombre");
    // scanf("%d",&integer);
    // printf("Entrez le premier string: ");
    // scanf("%s", string1);
    // printf("Entrez le deuxieme string: ");
    // scanf("%s", string2);
    // showProdIds();
    // sortByCat();
    // showAllProd();
    // char cat[CAT_MAX];
    // int *ids=NULL;
    // int found=0;
    // printf("Entrer une categorie: ");
    // scanf("%s", cat);
    // ids=findProdByCat(cat, ids, 0, N_PROD-1, found);

    // if (ids){
    //     printf("Produits dans la categorie %s:\n", cat);
    //     for (int i=0; i<sizeof(ids)/sizeof(ids[0]); i++)
    //         printf("ID: %d\n", ids[i]);
    // }
    // else
    //     printf("Aucun produit dans cette categorie\n");

    
    // for (int prd=0; prd<N_PROD; prd++){
    //     printf("ID: %d\nNom: %s\nCategorie: %s\nPrix: %.2f\nStock: %d\nDescription: %s\n\n", LProd[prd].idProduit, LProd[prd].nom, LProd[prd].categorie, LProd[prd].prix, LProd[prd].stock, LProd[prd].description);
    // }
    // for (int prd=0; prd<N_PROD; prd++){
    //     showProd(LProd[prd], prd);
    // }


    return 0;
}