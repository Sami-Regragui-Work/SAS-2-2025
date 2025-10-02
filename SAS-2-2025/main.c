#include<stdio.h>
#include"bridge.h"
#include<string.h>



int main(){
    int *ids=NULL;
    char choice1, choice2, choice3;
    int tempInt;
    Produit tempProd;
    char name[PRODUIT_N_MAX], cat[CAT_MAX]; // 30 30
    float min, max;
    _fillProd();
    initHist();
    do{
        printf("\n=== SYSTEME D'ACHAT CLIENT ===\n");
        printf("1. Gestion du profil client\n");
        printf("2. Gestion du solde virtuel\n");
        printf("3. Consultation des produits\n");
        printf("4. Effectuer un achat\n");
        printf("5. Mes statistiques\n");
        printf("0. Quitter l'application\n\n");

        scanf("%c", &choice1);
        getchar();
        switch(choice1){
            case '1': do{
                    printf("\n=== GESTION DU PROFIL CLIENT ===\n");
                    if (gClientId==0) printf("1. Creation de profil\n");
                    else {printf("1. Modification de profil\n");
                    printf("2. Consultation de profil\n");}
                    printf("0. Retour au menu principal\n\n");

                    scanf("%c", &choice2);
                    getchar();
                    // printf("%c %d\n", choice2, gClientId);
                    if (gClientId==0 && choice2=='1')
                        addClient(&LClient[0]);
                    else if (gClientId){
                        if (choice2=='1')
                            modifyClient(&LClient[0]);
                        else if (choice2=='2')
                            showClient(LClient[0]);
                        else if (choice2!='0')
                            printf("Choix invalide! reessayer\n");
                    }
                    else if (choice2!='0')
                        printf("Choix invalide! reessayer\n");
                } while (choice2!='0');
                break;
            case '2': if (gClientId==0){
                        printf("Creer un profil client d\'abord\n");
                        break;
                    }
                do{
                    printf("\n=== GESTION DU SOLDE VIRTUEL ===\n");
                    printf("1. Affichage du montant disponible\n");
                    printf("2. Ajouter du montant\n");
                    printf("0. Retour au menu principal\n\n");

                    scanf("%c", &choice2);
                    getchar();
                    if (choice2=='1')
                        showSolde(LClient[0]);
                    else if (choice2=='2')
                        addSolde(&LClient[0]);
                    else if (choice2!='0')
                        printf("Choix invalide! reessayer\n");
                    } while (choice2!='0');
                break;
            case '3': do{
                    printf("\n=== CONSULTATION DES PRODUITS ===\n");
                    printf("1. Afficher tous les produits\n");
                    printf("2. Rechercher un produit par nom\n");
                    printf("3. Rechercher un produit par categorie\n");
                    printf("4. Rechercher un produit par intervalle de prix\n");
                    printf("5. Trier les produits par prix\n");
                    printf("6. Trier les produits par nom\n");
                    printf("7. Trier les produits par categorie\n");
                    printf("0. Retour au menu principal\n\n");

                    scanf("%c", &choice2);
                    getchar();
                    switch(choice2){
                        case '1': showAllProd();
                            break;
                        case '2': printf("Entrez le nom du produit: ");
                            scanf("%29[^\n]", name); // 29 is PRODUIT_N_MAX-1 for \n
                            getchar();
                            ids=findProdByName(name);
                            if (ids){
                                printf("Produits avec le nom %s sont:\n", name);
                                for (int i=0; i<sizeof(ids)/sizeof(ids[0]); i++){
                                    tempProd=getProdById(ids[i]);
                                    if (tempProd.idProduit)
                                        showDetailProd(tempProd);
                                }
                            }
                            else
                                printf("Aucun produit avec ce nom\n");
                            break;
                        case '3': printf("Entrez la categorie du produit: ");
                            scanf("%29[^\n]", cat); // 29 is CAT_MAX-1 for \n
                            getchar();
                            ids=findProdByCat(cat);
                            if (ids){
                                printf("Produits dans la categorie %s:\n", cat);
                                for (int i=0; i<sizeof(ids)/sizeof(ids[0]); i++){
                                    tempProd=getProdById(ids[i]);
                                    if (tempProd.idProduit)
                                        showDetailProd(tempProd);
                                }
                            }
                            else
                                printf("Aucun produit dans cette categorie\n");
                            break;
                        case '4': printf("Entrez l\'intervalle de prix min et max separe par un espace: ");
                            scanf("%f %f", &min, &max);
                            if (min>max){
                                tempInt=min;
                                min=max;
                                max=tempInt;
                            }
                            getchar();
                            ids=findProdByPrice(min, max);
                            if (ids){
                                printf("Produits entre les prix %.2f et %.2f:\n", min, max);
                                for (int i=0; i<sizeof(ids)/sizeof(ids[0]); i++){
                                    tempProd=getProdById(ids[i]);
                                    if (tempProd.idProduit)
                                        showDetailProd(tempProd);
                                }
                            }
                            else
                                printf("Aucun produit entre cet intervalle\n");
                            break;
                        case '5': do{
                                printf("\n=== TRI PAR PRIX ===\n");
                                printf("1. Ordre decroissant\n");
                                printf("2. Ordre croissant\n\n");
                                scanf("%c", &choice3);
                                getchar();
                                // sortByPrice(((int)(choice3-'0')/2)*2-1); 
                                if (choice3=='1')
                                    sortByPrice(-1);
                                else if (choice3=='2')
                                    sortByPrice(1);
                                else {
                                    printf("Choix invalide! reessayer\n");
                                    break;
                                }
                                showAllProd();
                            } while (choice3!='1' && choice3!='2');
                            break;
                        case '6': printf("\n=== TRI PAR NOM ===\n");
                            sortByName();
                            showAllProd();
                            break;
                        case '7': printf("\n=== TRI PAR CATEGORIE ===\n");
                            sortByCat();
                            showAllProd();
                            break;
                    }
                } while (choice2!='0');
            case '4': printf("\n=== EFFECTUER UN ACHAT ===\n");
                if (gClientId==0){
                    printf("Creer un profil client d\'abord\n");
                    break;
                }
                printf("Entrez le nom de produit: ");
                scanf("%29[^\n]", name); // 29 is PRODUIT_N_MAX-1 for \n
                getchar();
                ids=findProdByName(name);
                if (ids){
                    printf("Produits avec le nom %s sont:\n", name);
                    for (int i=0; i<sizeof(ids)/sizeof(ids[0]); i++){
                        tempProd=getProdById(ids[i]);
                        if (tempProd.idProduit)
                            showDetailProd(tempProd);
                    }
                    printf("Entrez l\'ID du produit a acheter: ");
                    
                    scanf("%d", &tempInt);
                    tempProd=getProdById(tempInt);
                    if (tempProd.idProduit){
                        tempInt=buyProd(&LClient[0], &tempProd);
                        if (tempInt)
                            updateHist(&tempProd, tempInt);
                    }
                }
                else
                    printf("le produit n\'existe pas\n");
                    break;
            case '5': if (gClientId==0){
                    printf("Creer un profil client d\'abord\n");
                    break;
                }
                printf("\n=== STATISTIQUES ===\n");
                printf("1. Historique des achats:\n");
                printf("2. Statistiques personnelles de %s %s:\n", LClient[0].prenom, LClient[0].nom);
                scanf("%c", &choice2);
                getchar();
                if (choice2=='1')
                    showHist();
                else if (choice2=='2')
                    printf("Statistiques personnelles de %s %s sont %.2fMAD\n", LClient[0].prenom, LClient[0].nom, persStats());
                break;
            case '0': printf("Merci d\'avoir utilise notre application!\n");
                break;
            default: printf("Choix invalide! reessayer\n");
                break;
        }
    } while (choice1!='0');
    return 0;
}