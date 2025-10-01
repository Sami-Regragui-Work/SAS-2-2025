#include"bridge.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void _fillProd(){
    char names[N_PROD][PRODUIT_N_MAX]={"Laptop","Pc bureau","Smartphone","Montre","Refrigirateur","Controleur PS3"};
    char categories[N_PROD][CAT_MAX]={"Electroniques","Electroniques","Telephones et tablettes","Montres","Apparails","Jeu"};
    float prices[N_PROD]={2750.99, 3000., 1499., 150., 9500., 120.};
    int stock[N_PROD]={5,10,10,15,20,12};
    char desc[N_PROD][DESC]={"Processeur Intel Core i5, 8GB RAM, 256GB SSD. Ecran 15.6 pouces Full HD, batterie autonomie 8 heures.",
        "Processeur AMD Ryzen 5, 16GB RAM, 512GB SSD. Carte graphique NVIDIA GTX 1660, Windows 10 Pro.",
        "Ecran 6.5 pouces AMOLED, 128GB stockage, camera 48MP. Batterie 4500mAh, charge rapide, 5G compatible.",
        "Boîtier acier inoxydable 42mm, bracelet cuir veritable. Mouvement quartz, resistance à l\'eau 50m.",
        "Capacite 350 litres, classe energetique A++. Technologie No Frost, compartiment congelateur 100 litres.",
        "Connexion sans fil Bluetooth, batterie rechargeable lithium-ion. Fonction vibration DualShock, port USB pour charge."};
    
    for (int prd=0; prd<N_PROD; prd++){
        LProd[prd].idProduit=prd+1;
        strcpy(LProd[prd].nom, names[prd]);
        strcpy(LProd[prd].categorie, categories[prd]);
        LProd[prd].prix=prices[prd];
        LProd[prd].stock=stock[prd];
        strcpy(LProd[prd].description, desc[prd]);
    }
    // strcpy(LProd[0].nom, "Laptop");
}

void _generateIdCli(void){
    static int id=0;
    LClient[id].idClient=id;
    id++;
}

void showProd(Produit prod, int index){
    if (!index){
        printf("---------------------------------------------------------\n");
        printf("| %-30s | %-9s    | %-5s |\n", "Nom", "Prix", "Stock");
        printf("---------------------------------------------------------\n");
    }
    printf("| %-30s | %-9.2fMAD | %-5d |\n", prod.nom, prod.prix, prod.stock);
    printf("---------------------------------------------------------\n");
}

void showDetailProd(Produit prod){
    printf("-----------------------------------------------------------------------------------------------\n");
    printf("| %-2s | %-30s | %-30s | %-9s    | %-5s |\n", "ID", "Nom", "Categorie", "Prix", "Stock");
    printf("-----------------------------------------------------------------------------------------------\n");
    printf("| %-2d | %-30s | %-30s | %-9.2fMAD | %-5d |\n", prod.idProduit, prod.nom, prod.categorie, prod.prix, prod.stock);
    printf("-----------------------------------------------------------------------------------------------\n");
}

void showAllProd(void){
    for (int prd=0; prd<N_PROD; prd++)
        showProd(LProd[prd], prd);
}

void _generateEmail(Client cli){
    snprintf(cli.email, EMAIL_MAX, "%s.%s@client.com", cli.nom, cli.prenom);
}
void _setSold(Client cli){
    cli.solde=500.0;
}
void addClient(Client cli){
    _generateIdCli();
    printf("Entrez votre nom: ");
    scanf("%s", cli.nom);
    getchar();
    printf("Entrez votre prenom: ");
    scanf("%s", cli.prenom);
    _generateEmail(cli);
    printf("Votre email est: %s\n", cli.email);
    _setSold(cli);
    printf("Votre solde est: %.2fMAD\n", cli.solde);
}

void swap(Produit *fr, Produit *sc){
    Produit temp=*fr;
    *fr=*sc;
    *sc=temp;
}

void sortByPrice(int order){
    if (order==1){//asc
        for (int prd=0; prd<N_PROD-1; prd++)
            for (int nextPrd=prd+1; nextPrd<N_PROD; nextPrd++)
                if (LProd[prd].prix > LProd[nextPrd].prix)
                    swap(&LProd[prd], &LProd[nextPrd]);
    } else if (order==-1) {//desc
        for (int prd=0; prd<N_PROD-1; prd++)
            for (int nextPrd=prd+1; nextPrd<N_PROD; nextPrd++)
                if (LProd[prd].prix < LProd[nextPrd].prix)
                    swap(&LProd[prd], &LProd[nextPrd]);
    }
}

void sortByName(){
    for (int prd=0; prd<N_PROD-1; prd++)
        for (int nextPrd=prd+1; nextPrd<N_PROD; nextPrd++)
            if (strcmp(LProd[prd].nom, LProd[nextPrd].nom)>0)
                swap(&LProd[prd], &LProd[nextPrd]);
}

void sortByCat(){
    // Bubble sort "tri à bulles"
    bool change;

    for (int iter=0; iter<N_PROD-1; iter++){
        change=0;
        for (int prd=0; prd< N_PROD-1-iter; prd++){
            if (strcmp(LProd[prd].categorie, LProd[prd+1].categorie)>0){
                swap(&LProd[prd],&LProd[prd+1]);
                change=1;
            }
        }
        if (!change)
            break;
    }
}
    

int *findProdByCat(char *cat){
    // dichotomique search
    int *ids=NULL;
    int found=0;
    sortByCat();
    int start=0, end=N_PROD-1, mid;
    int firstMid;
    while (start<=end){
        mid=(start+end)/2;
        if (strcmp(LProd[mid].categorie, cat)>0)
            end=mid-1;
        else if (strcmp(LProd[mid].categorie, cat)<0)
            start=mid+1;
        else {
            found++;
            ids=(int *)realloc(ids, found*sizeof(int));
            ids[found-1]=LProd[mid].idProduit;
            // dichotomie ends here, rest is 2 sides linear search since the array is sorted
            firstMid=mid;
            mid--;
            while(mid>0 && !strcmp(LProd[mid].categorie, cat)){
                found++;
                ids=(int *)realloc(ids, found*sizeof(int));
                ids[found-1]=LProd[mid].idProduit;
                mid--;
            }
            mid=firstMid+1;
            while(mid<N_PROD && !strcmp(LProd[mid].categorie, cat)){
                found++;
                ids=(int *)realloc(ids, found*sizeof(int));
                ids[found-1]=LProd[mid].idProduit;
                mid++;
            }
            break;
        }
    }
    return ids;
}

int *findProdByName(char *name){
    int *ids=NULL;
    int found=0;

    for (int prd=0; prd<N_PROD; prd++)
        if (!strcmp(LProd[prd].nom, name)){
            found++;
            ids=(int *)realloc(ids, found*sizeof(int));
            ids[found-1]=LProd[prd].idProduit;
        }
    return ids;
}

int *findProdByPrice(int min, int max){
    int *ids=NULL;
    int found=0;
    sortByPrice(1);

    for (int prd=0; prd<N_PROD; prd++){
        if (LProd[prd].prix>max)
            break;
        if (LProd[prd].prix>=min){
            found++;
            ids=(int *)realloc(ids, found*sizeof(int));
            ids[found-1]=LProd[prd].idProduit;
        }
    }
    return ids;
}




