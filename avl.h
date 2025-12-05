#ifndef P_CONTENEUR_H
#define P_CONTENEUR_H
#include <stdlib.h>
#include "joueur.h"

/**
    Interface des conteneurs manipulant dans nos elements. 
    Un conteneur pourra être :
       - Créer (allocation de mémoire et configuration initiale)
       - Supprimer (libération mémoire)
       - Afficher son contenu
       - Ajouter un élément.
       - restituer un élément précédemment stocké.
 */

typedef struct sNoeud{
    t_personne joueur;
    struct sNoeud* gauche;
    struct sNoeud* droite;
    //struct sNoeud* precedent;
    int hauteur;
}tNoeud;
typedef tNoeud* tAvl;

typedef void* t_conteneur;

#define CONTENEUR_NON_INITIALISE NULL

t_conteneur nouveau_conteneur();

void finaliser_conteneur(t_conteneur* ceci);

void afficher_conteneur(t_conteneur ceci);

int ajouter_conteneur(t_conteneur* ceci, t_personne cela, time_t timeZero);

int retirer_conteneur(t_conteneur* ceci, t_personne* cela);



#endif // P_CONTENEUR_H