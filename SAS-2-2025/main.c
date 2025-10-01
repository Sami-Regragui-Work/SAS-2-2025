#include<stdio.h>
#include"bridge.h"
#include<string.h>



int main(){
    int choice1, choice2;
    // int tempInt;
    char name[CLIENT_PaN_MAX], prenom[CLIENT_PaN_MAX];
    _fillProd();
    do{
        printf("=== SYSTEME D'ACHAT CLIENT ===\n");
        printf("1. Gestion du profil client\n");
        printf("2. Gestion du solde virtuel\n");
        printf("3. Consultation des produits\n");
        printf("4. Effectuer un achat\n");
        printf("5. Mes statistiques\n");
        printf("0. Quitter l'application\n");

        scanf("%d", &choice1);
        switch(choice1){
            case 1: do{
                    printf("=== GESTION DU PROFIL CLIENT ===\n");
                    if (gClientId==0) printf("1. Creation de profil\n");
                    else {printf("1. Modification de profil\n");
                    printf("2. Consultation de profil\n");}
                    printf("0. Retour au menu principal\n");

                    scanf("%d", &choice2);
                    if (gClientId==0 && choice2==1)
                        addClient(&LClient[0]);
                    else if (gClientId)
                        if (choice2==1)
                            modifyClient(&LClient[0]);
                        else if (choice2==2)
                            showClient(LClient[0]);
                    } while (choice2);
                break;
            case 2: do{
                    printf("=== GESTION DU SOLDE VIRTUEL ===\n");
                    if (gClientId==0) printf("1. Creation de profil\n");
                    else {printf("1. Modification de profil\n");
                    printf("2. Consultation de profil\n");}
                    printf("0. Retour au menu principal\n");

                    scanf("%d", &choice2);
                    if (gClientId==0 && choice2==1)
                        addClient(&LClient[0]);
                    else if (gClientId)
                        if (choice2==1)
                            modifyClient(&LClient[0]);
                        else if (choice2==2)
                            showClient(LClient[0]);
                    } while (choice2);
            break;
        }
    } while (choice1);



    return 0;
}