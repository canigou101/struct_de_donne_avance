#include <stdlib.h>
#include <stdio.h>
#include "joueur.h"
#include <time.h>
#include <string.h>

time_t get_time(){
    return time(NULL);
}


t_personne nouveau_joueur(char* id,int elo,int canal){
    t_joueur* res=malloc(sizeof(t_joueur));
    res->identificateur=id;
    res->l_elo=elo;
    res->le_canal=canal;
    res->registerDate=0;
    return (t_personne)res;
    
}
void afficher_joueur(t_personne lui){
    printf("nom: %s  - elo: %d  - canal: %d  - reg date: %ld",lui->identificateur,lui->l_elo,lui->le_canal,lui->registerDate);

}
void supprimer_joueur(t_personne* lui){
    if (*lui==NULL)
    {
        fprintf(stderr,"personne non initialisé");
    }else{
        free(*lui);
    }
}
