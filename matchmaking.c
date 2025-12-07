#include <stdlib.h>
#include <stdio.h>
#include "matchmaking.h"

typedef struct sNoeud{
    struct sNoeud* gauche;
    struct sNoeud* droite;
    //struct sNoeud* precedent;
    int hauteur;
    t_personne joueur;
}tNoeud;
typedef tNoeud* tAvl;

tAvl plusPetitNoeud(tAvl *ceci){
    if(ceci !=NULL){
        plusPetitNoeud(&((*ceci)->gauche));
        return *ceci;
    }
}

tAvl plusGrandNoeud(tAvl *ceci){
    if(ceci !=NULL){
        plusGrandNoeud(&((*ceci)->droite));
        return *ceci;
    }
}

int hauteur_avlM(tAvl ceci){
    if(ceci == NULL){
        return -1;
    }
    return ceci->hauteur;
}

int max2M(int x, int y){
    return (x>y)?x:y;
}

void MettreAJourAvl(tAvl* ceci){
    if(*ceci!=NULL){
        MettreAJourAvl(&((*ceci)->gauche));
        (*ceci)->hauteur = max2M(hauteur_avlM((*ceci)->gauche),hauteur_avlM((*ceci)->droite)) + 1;
        MettreAJourAvl(&((*ceci)->droite));
    }
}

void retirerNoeudFin(tAvl* ceci){
    *ceci = NULL;
    free(*ceci);
}

tAvl supprimer(tAvl ceci){
    if( (ceci->gauche == NULL) || (ceci->droite == NULL) ){
        tAvl temp = ceci->gauche ? ceci->gauche : ceci->droite;
            if (temp == NULL)
            {
                retirerNoeudFin(&ceci);
            }
            else{
                printf("test2 ");
                *ceci = *temp;
                free(temp);
            }
    }else{
        printf("test3");
        tAvl temp = plusPetitNoeud(&(ceci->droite));
        ceci->joueur = temp->joueur;
        ceci->droite = supprimer(ceci->droite);
    }
    if (ceci == NULL)
        printf("test4");
        return ceci;
}

void chercherAdversaire(tAvl *racine, tAvl *ceci, time_t timeZero, int* i){
    int centre = (*ceci)->joueur->l_elo;
    int rayon = time(NULL)-timeZero-(*ceci)->joueur->registerDate;
    if(*racine !=NULL && i[0] == 0){
        chercherAdversaire(&((*racine)->gauche), ceci, timeZero, i);
        //printf("/i: %d/", i);
        if((*racine)->joueur->l_elo > centre-rayon && (*racine)->joueur->l_elo < centre+rayon && (*racine)!=(*ceci) && i[0] == 0){
            printf("\n%d   -   %d\n",(*racine)->joueur->l_elo, ((*ceci)->joueur->l_elo));
            supprimer(*racine);
            supprimer(*ceci);
            i[0]++;
        }
        if(i[0]==0){
            chercherAdversaire(&((*racine)->droite), ceci, timeZero, i);
        }
    }
}

void chercherMatchRec(tAvl *racine, tAvl *ceci, time_t timeZero){
    int i[1];
    i[0] = 0;
    if(*ceci != NULL){
        chercherMatchRec(racine, &((*ceci)->gauche), timeZero);
        chercherAdversaire(racine, ceci, timeZero,i);
        //printf("*%d*\n", (*ceci)->joueur->l_elo);
        chercherMatchRec(racine, &((*ceci)->droite), timeZero);
    }
}

void chercherMatch(t_conteneur *ceci, time_t timeZero){
    chercherMatchRec((tAvl*)ceci, (tAvl*)ceci, timeZero);
}
