#include"bridge.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

void _fillProd(){
    char names[N_PROD][PRODUIT_N_MAX]={"Laptop","Pc bureau","Smartphone","Montre","Refrigirateur","Controleur PS3"};
    char categories[N_PROD][CAT_MAX]={"Electroniques","Electroniques","Telephones et tablettes","Montres","Apparails","Jeu"};
    float prices[N_PROD]={2750.99, 3000., 1499., 150., 9500., 120.};
    int stock[N_PROD]={5,10,10,15,20,12};
    char desc[N_PROD][DESC]={
        "Intel i5, 8GB RAM, 256GB SSD, 15.6in FHD, 8h battery.",
        "AMD Ryzen 5, 16GB RAM, 512GB SSD, GTX 1660, Win10 Pro.",
        "6.5in AMOLED, 128GB, 48MP camera, 4500mAh, 5G, fast charge.",
        "Steel case 42mm, leather strap, quartz, water resistant 50m.",
        "350L, A++ class, No Frost, 100L freezer compartment.",
        "Bluetooth, rechargeable battery, DualShock, USB charging."
    };
    
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

void initHist(void){
    for (int prd=0; prd<N_PROD; prd++){
        hist[prd][0]=-1;
        hist[prd][1]=0;
    }
}

void _generateIdCli(void){
    gClientId++;
    LClient[gClientId-1].idClient=gClientId;
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

void showCats(void){
    printf("Categories disponibles:\n");
    printf("-------------------------------------------------\n");
    printf("| %-30s |\n", "Categorie");
    printf("-------------------------------------------------\n");
    printf("| %-30s |\n", "Electroniques");
    printf("-------------------------------------------------\n");
    printf("| %-30s |\n", "Telephones et tablettes");
    printf("-------------------------------------------------\n");
    printf("| %-30s |\n", "Montres");
    printf("-------------------------------------------------\n");
    printf("| %-30s |\n", "Apparails");
    printf("-------------------------------------------------\n");
    printf("| %-30s |\n", "Jeu");
    printf("-------------------------------------------------\n");
}

void showAllProd(void){
    for (int prd=0; prd<N_PROD; prd++)
        showProd(LProd[prd], prd);
}

Produit getProdById(int id){
    for (int prd=0; prd<N_PROD; prd++){
        if (LProd[prd].idProduit==id)
            return LProd[prd];
    }
    return (Produit){0, "", "", 0.0, 0, ""};
}

void _generateEmail(Client* cli){
    sprintf(cli->email, "%s.%s@client.com", cli->nom, cli->prenom);
}

void addClient(Client* cli){
    _generateIdCli();
    printf("Entrez votre nom: ");
    scanf("%19s", cli->nom); // 19 is CLIENT_PaN_MAX-1 for \n
    getchar();
    printf("Entrez votre prenom: ");
    scanf("%19s", cli->prenom); // 19 is CLIENT_PaN_MAX-1 for \n
    getchar();
    _generateEmail(cli);
    printf("Votre email est: %s\n", cli->email);
    cli->solde=0.0;
    printf("Votre solde est: %.2fMAD\n", cli->solde);
}

void modifyClient(Client* cli){
    printf("Entrez votre nouveau nom: ");
    scanf("%19s", cli->nom); // 19 is CLIENT_PaN_MAX-1 for \n
    getchar();
    printf("Entrez votre nouveau prenom: ");
    scanf("%19s", cli->prenom); // 19 is CLIENT_PaN_MAX-1 for \n
    getchar();
    _generateEmail(cli);
    printf("Votre nouveau email est: %s\n", cli->email);
}

void showClient(Client cli){
    printf("Votre ID: %d\n", cli.idClient);
    printf("Votre nom: %s\n", cli.nom);
    printf("Votre Prenom: %s\n", cli.prenom);
    printf("Votre Email: %s\n", cli.email);
    printf("Votre Solde: %.2fMAD\n", cli.solde);
}

void addSolde(Client *cli){
    float addedSolde;
    int verify;
    do {
        printf("Combien voulez-vous disposer: ");
        verify=scanf("%f", &addedSolde);
        getchar();
    } while(verify!=1 || addedSolde<0);
    
    cli->solde+=addedSolde;
}

float getSolde(Client cli){
    return cli.solde;
}

void showSolde(Client cli){
    printf("solde de %s %s actuel est: %.2fMAD\n", cli.prenom, cli.nom, cli.solde);
}

int buyProd(Client *cli, Produit *prod){
    int quantity, verify;
    do {
        printf("Combien de %s voulez-vous acheter: ", prod->nom);
        verify=scanf("%d", &quantity);
        getchar();
    } while(verify!=1 || quantity<0);
    
    if (quantity>prod->stock){
        printf("Stock insuffisant! Stock actuel: %d\n", prod->stock);
        return 0;
    }
    if (quantity * prod->prix > getSolde(*cli)){
        printf("Solde insuffisant! Votre solde est: %.2fMAD\n", getSolde(*cli));
        return 0;
    }
    prod->stock-=quantity;
    cli->solde-=quantity*prod->prix;
    printf("Achat de %d %ss avec succes!\n", quantity, prod->nom);
    return quantity;
}

void updateHist(Produit *prod, int quantity){
    if (hist[prod->idProduit-1][1])
        hist[prod->idProduit-1][1]+=quantity;
    else{
        hist[prod->idProduit-1][0]=prod->idProduit;
        hist[prod->idProduit-1][1]=quantity;
    }
}

void showHist(void){
    printf("----------------------------------------------\n");
    printf("| %-30s | %-9s |\n", "Nom", "Quantite");
    printf("----------------------------------------------\n");
    for (int prd=0; prd<N_PROD; prd++){
        if (hist[prd][1]){
            printf("| %-30s | %-9d |\n", LProd[prd].nom, hist[prd][1]);
            printf("----------------------------------------------\n");
            break;
        }
    }
}

float persStats(void){
    float total=0.0;
    for (int prd=0; prd<N_PROD; prd++){
        if (hist[prd][1]){
            total+=hist[prd][1]*LProd[getProdById(prd+1).idProduit-1].prix;
        }
    }
    return total;
}

void lowerString( char *lowered, char *str){
    int size= strlen(str);
    for (int ch=0; ch<size; ch++)
        lowered[ch]=tolower(str[ch]);
    lowered[size]='\0';
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
    char lowered[PRODUIT_N_MAX], nextLowered[PRODUIT_N_MAX];
    for (int prd=0; prd<N_PROD-1; prd++){
        lowerString(lowered, LProd[prd].nom);
        for (int nextPrd=prd+1; nextPrd<N_PROD; nextPrd++){
            lowerString(nextLowered, LProd[nextPrd].nom);
            if (strcmp(lowered, nextLowered)>0)
                swap(&LProd[prd], &LProd[nextPrd]);
        }
    }
        
}

void sortByCat(){
    // Bubble sort "tri à bulles"
    bool change;
    char lowered[CAT_MAX], nextLowered[CAT_MAX];

    for (int iter=0; iter<N_PROD-1; iter++){
        lowerString(lowered, LProd[iter].categorie);
        change=0;
        for (int prd=0; prd< N_PROD-1-iter; prd++){
            lowerString(nextLowered, LProd[prd+1].categorie);
            if (strcmp(lowered, nextLowered)>0){
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
    ids=NULL;
    int found=0, start=0, end=N_PROD-1, mid, firstMid;
    char lowered[CAT_MAX], catLowered[CAT_MAX];
    lowerString(catLowered, cat);
    sortByCat();
    while (start<=end){
        mid=(start+end)/2;
        lowerString(lowered, LProd[mid].categorie);
        if (strcmp(lowered, catLowered)>0)
            end=mid-1;
        else if (strcmp(lowered, catLowered)<0)
            start=mid+1;
        else {
            found++;
            ids=(int *)realloc(ids, found*sizeof(int));
            ids[found-1]=LProd[mid].idProduit;
            // dichotomie ends here, rest is 2 sides linear search since the array is sorted
            firstMid=mid;
            mid--;
            lowerString(lowered, LProd[mid].categorie);
            while(mid>0 && !strcmp(lowered, catLowered)){
                found++;
                ids=(int *)realloc(ids, found*sizeof(int));
                ids[found-1]=LProd[mid].idProduit;
                mid--;
                lowerString(lowered, LProd[mid].categorie);
            }
            mid=firstMid+1;
            lowerString(lowered, LProd[mid].categorie);
            while(mid<N_PROD && !strcmp(lowered, catLowered)){
                found++;
                ids=(int *)realloc(ids, found*sizeof(int));
                ids[found-1]=LProd[mid].idProduit;
                mid++;
                lowerString(lowered, LProd[mid].categorie);
            }
            break;
        }
    }
    return ids;
}

int *findProdByName(char *name){
    ids=NULL;
    int found=0;
    char lowered[PRODUIT_N_MAX], nameLowered[PRODUIT_N_MAX];
    lowerString(nameLowered, name);
    for (int prd=0; prd<N_PROD; prd++){
        lowerString(lowered, LProd[prd].nom);
        if (!strcmp(lowered, nameLowered)){
            found++;
            ids=(int *)realloc(ids, found*sizeof(int));
            ids[found-1]=LProd[prd].idProduit;
        }
    }
    return ids;
}

int *findProdByPrice(float min, float max){
    ids=NULL;
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





