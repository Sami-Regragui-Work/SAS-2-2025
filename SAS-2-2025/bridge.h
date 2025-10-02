#ifndef BRIDGE_H
#define BRIDGE_H
#include<stdbool.h>
#include<ctype.h>
// #include<time.h>

#define CLIENT_PaN_MAX 20
#define PRODUIT_N_MAX 30
#define CAT_MAX 30
#define EMAIL_MAX 60
#define DESC 100

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

extern int hist[N_PROD][2]; // idProduit, quantity

extern Produit LProd[N_PROD];

extern Client LClient[N_CLI];

extern int gClientId;

extern int *ids;

// extern int histIndex;

void _fillProd(void);

void initHist(void);

void _generateIdCli(void);

void showProd(Produit prod, int index);

void showAllProd(void);

void showDetailProd(Produit prod);

void showCats(void);

Produit getProdById(int id);

void addClient(Client *cli);

void modifyClient(Client *cli);

void showClient(Client cli);

void _generateEmail(Client *cli);

void addSolde(Client *cli);

float getSolde(Client cli);

void showSolde(Client cli);

int buyProd(Client *cli, Produit *prod);

void updateHist(Produit *prod, int quantity);

void showHist(void);

float persStats(void);

void lowerString(char *lowered, char *str);

int *findProdByName(char *name);

int *findProdByCat(char *cat);

int *findProdByPrice(float min, float max);

void swap(Produit *fr, Produit *sc);

void sortByPrice(int order); 

void sortByName();

void sortByCat();
// void addAllClient(void);
void statClient(Client cli);

#endif