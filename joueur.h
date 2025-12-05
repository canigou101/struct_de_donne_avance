#include <time.h>
#ifndef JOUEUR_H
#define JOUEUR_H


typedef struct s_joueur
{
    char* identificateur;
    int l_elo;
    time_t registerDate;
    int le_canal;
    
}t_joueur;

typedef t_joueur* t_personne;

t_personne nouveau_joueur(char* id,int elo,int canal);
void afficher_joueur(t_personne lui);
void supprimer_joueur(t_personne* lui);



#endif