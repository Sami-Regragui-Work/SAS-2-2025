#ifndef BRIDGE_H
#define BRIDGE_H

#define CLIENT_PaN_MAX 20
#define PRODUIT_N_MAX 30
#define CAT_MAX 30
#define EMAIL_MAX 60
#define DESC 250

#define N_PROD 6
#define N_CLI 1

typedef struct {
    int idClient;
    char nom[CLIENT_PaN_MAX];
    char prenom[CLIENT_PaN_MAX];
    char email[EMAIL_MAX];
    float solde;
} Client;

typedef struct {
    int idProduit;
    char nom[PRODUIT_N_MAX];
    char categorie[CAT_MAX];
    float prix;
    int stock;
    char description[DESC];
} Produit;

typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

extern Produit LProd[N_PROD];

extern Client LClient[N_CLI];

void _fillProd(void);

void _generateIdCli(void);

void showProd(Produit prod, int index);

void showAllProd(void);

void showDetailProd(Produit prod);

void addClient(Client cli);

void modifyClient(char nom[], char prenom[]);

void _generateEmail(Client cli);

void _setSold(Client cli);

int *findProdByName(char *name);

int *findProdByCat(char *cat);

int *findProdByPrice(int min, int max);

void swap(Produit *fr, Produit *sc);

void sortByPrice(int order); 

void sortByName();

void sortByCat();
// void addAllClient(void);

#endif