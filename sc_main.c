#include <stdio.h>
#include <stdlib.h>
#include "joueur.h"

int main(){
    
    t_personne test1=nouveau_joueur("bobby",10,1);
    afficher_joueur(test1);
    supprimer_joueur(&test1);
    
    return 0;

}