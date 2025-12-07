#include <stdio.h>
#include <stdlib.h>
#include "joueur.h"
#include "avl.h"
#include "matchmaking.h"
#include <unistd.h>


int main(){
    time_t timeZero = time(NULL);
    //printf("\n*%d*\n", timeZero);
    t_conteneur testavl = nouveau_conteneur();
    t_personne test1=nouveau_joueur("bobby",10,1);
    t_personne test2=nouveau_joueur("bobbby",15,1);
    t_personne test3=nouveau_joueur("baubby",9,1);
    t_personne test4=nouveau_joueur("bobbi",8,1);
    t_personne test5=nouveau_joueur("boby",2,1);
    ajouter_conteneur(&testavl, test1,timeZero);
    sleep(5);
    ajouter_conteneur(&testavl, test3,timeZero);
    sleep(10);
    ajouter_conteneur(&testavl, test4,timeZero);
    ajouter_conteneur(&testavl, test5,timeZero);
    ajouter_conteneur(&testavl, test2,timeZero);
    afficher_conteneur(testavl);
    printf("\n\n\n");
    chercherMatch(&testavl, timeZero);
    printf("\n\n\n");
    afficher_conteneur(testavl);
    finaliser_conteneur(&testavl);
    return 0;

}