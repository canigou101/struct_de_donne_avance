#include <stdlib.h>
#include "matchmaking.h"

tAvl* plusPetitNoeud(tAvl *ceci){
    if(ceci !=NULL){
        plusPetitNoeud(&((*ceci)->gauche));
        return ceci;
    }
}

void retirer(tAvl *ceci){
    tAvl* temp = plusPetitNoeud(ceci);
    *ceci = *temp;
    free(temp);
}

tAvl* chercherAdversaire(tAvl *racine, tAvl *ceci, int centre, int rayon){
    if(racine !=NULL){
        chercherAdversaire(&((*racine)->gauche), ceci, centre,rayon);
        if((*racine)->joueur->l_elo > centre-rayon && (*racine)->joueur->l_elo < centre+rayon && (*racine)!=(*ceci)){
            return racine;
        }
        chercherAdversaire(&((*racine)->droite), ceci,centre,rayon);
    }
}

void chercherMatchRec(tAvl *racine, tAvl *ceci){
    tAvl nouCont = nouveau_conteneur();
    tAvl* cela = &nouCont;
    if(ceci != NULL){
        chercherMatchRec(racine, &((*ceci)->gauche));
        cela = chercherAdversaire(racine, ceci, (*ceci)->joueur->l_elo, (*ceci)->joueur->registerDate);
        if (cela != CONTENEUR_NON_INITIALISE){
            retirer(ceci);
            retirer(cela);
        }
        chercherMatchRec(racine, &((*ceci)->droite));
    }
}

void chercherMatch(tAvl *ceci){
    chercherMatchRec(ceci, ceci);
}
