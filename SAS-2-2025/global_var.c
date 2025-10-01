#include"bridge.h"

Produit LProd[N_PROD];

Client LClient[N_CLI];

int gClientId=0;

int hist[N_PROD][2]; // idProduit, quantity

int histIndex=0;