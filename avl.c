#include <stdio.h>
#include "avl.h"

typedef struct sNoeud{
    struct sNoeud* gauche;
    struct sNoeud* droite;
    //struct sNoeud* precedent;
    int hauteur;
    t_personne joueur;
}tNoeud;
typedef tNoeud* tAvl;

t_conteneur nouveau_conteneur(){
    return CONTENEUR_NON_INITIALISE;
}

void detruire(tAvl ceci){
    if(ceci != NULL){
        detruire(ceci->gauche);
        detruire(ceci->droite);
        free(ceci);
    }
}

void finaliser_conteneur(t_conteneur* ceci){
    detruire(*((tAvl*)ceci));
    *ceci = CONTENEUR_NON_INITIALISE;
}

int hauteur_avl(tAvl ceci){
    if(ceci == NULL){
        return -1;
    }
    return ceci->hauteur;
}

int max2(int x, int y){
    return (x>y)?x:y;
}

void mettreAJour(tAvl ceci){
    if(ceci != NULL){
        ceci->hauteur = max2(hauteur_avl(ceci->gauche),hauteur_avl(ceci->droite)) + 1;
    }
}

int desequilibre(tAvl ceci){
    if(ceci == NULL){
        return 0;
    }
    int hauteurGauche = hauteur_avl(ceci->gauche);
    int hauteurDroite = hauteur_avl(ceci->droite);
    return hauteurDroite - hauteurGauche;
}

void afficher_conteneur_rec(tAvl ceci, int decalage){
    if(ceci != NULL){
        afficher_conteneur_rec((ceci)->gauche,decalage+1);
        for (int i = 0; i < decalage; i++){
            printf("   ");
        }
        afficher_joueur(ceci->joueur);
        printf(" - h=%d ; deseq=%d\n", ceci->hauteur, desequilibre(ceci));
        afficher_conteneur_rec(((tAvl)ceci)->droite, decalage+1);
    }
}


void afficher_conteneur(t_conteneur ceci){
    if (ceci==CONTENEUR_NON_INITIALISE){
        return ;
    }else{
        afficher_conteneur_rec((tAvl)ceci, 0);
    }
}

tAvl nouvelle_feuille(t_personne joueur){
    tAvl res = (tAvl)malloc(sizeof(tNoeud));
    res->droite = NULL;
    res->gauche = NULL;
    res->joueur = joueur;
    //res->precedent = NULL;
    res->hauteur = 0;
    return res;
}



void rotationGauche(tAvl* ceci){
    tAvl s = (*ceci)->droite;
    (*ceci)->droite = s->gauche;
    s->gauche = (*ceci);
    mettreAJour(*ceci);
    mettreAJour(s);
    *ceci = s;
}

void rotationDroite(tAvl* ceci){
    tAvl s = (*ceci)->gauche;
    (*ceci)->gauche = s->droite;
    s->droite = (*ceci);
    mettreAJour(*ceci);
    mettreAJour(s);
    *ceci = s;
}

void rotationDG(tAvl* ceci){
    rotationGauche(&((*ceci)->gauche));
    rotationDroite(ceci);
}

void rotationGD(tAvl* ceci){
    //rotationDroite(&((*ceci)->droite));
    rotationGauche(ceci);
}

void ramener_a_gauche(tAvl* ceci){
    if(desequilibre((*ceci)->droite) == -1){ // il faut encore vérifier le test. Est ce == -1 ou <=0 ?
        rotationGauche(ceci);
    }else{
        rotationGD(ceci);
    }
}

void ramener_a_droite(tAvl* ceci){
    if(desequilibre((*ceci)->gauche) == 1){ // idem
        rotationDroite(ceci);
    }else{
        rotationDG(ceci);
    }
}

void inserer_avl(tAvl* ceci, t_personne cela){
    if(*ceci == NULL){
        *ceci = nouvelle_feuille(cela);
    }else{
        if((*ceci)->joueur->l_elo > (cela->l_elo)){
            inserer_avl(&((*ceci)->droite), cela);
        }else{
            inserer_avl(&((*ceci)->gauche), cela);
        }
        mettreAJour(*ceci);
        if(desequilibre(*ceci) < -1){
            ramener_a_droite(ceci);
        }else if (desequilibre(*ceci) > 1){
            ramener_a_gauche(ceci);
        }
    }
}




int ajouter_conteneur(t_conteneur* ceci, t_personne cela, time_t timeZero){
    //printf("\n*%d*\n",time(NULL) - timeZero);
    cela->registerDate = time(NULL) - timeZero;
    printf("\n*%d*\n",cela->registerDate);
    inserer_avl((tAvl*)ceci,cela);
    return 1;
}
    
void extraire_plus_petit_avl(tAvl* ceci, t_personne* cela){
    if((*ceci)->gauche == NULL){
        tAvl tmp = *ceci;
        (*ceci) = (*ceci)->droite;
        *cela = tmp->joueur;
        free(tmp);
    }else{
        extraire_plus_petit_avl(&((*ceci)->gauche), cela);
        mettreAJour(*ceci);
        if(desequilibre(*ceci) < -1){
            rotationGauche(ceci);
        }
    }
}

int retirer_conteneur(t_conteneur* ceci, t_personne* cela){
    if(*ceci == NULL){
        return 0;
    }
    extraire_plus_petit_avl((tAvl*) ceci, cela);
    return 1;
}