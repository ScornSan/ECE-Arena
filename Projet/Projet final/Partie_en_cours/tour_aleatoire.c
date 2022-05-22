#include "../prototypes.h"
#include "../structures.h"

void tour_joueur_alea( t_joueur* joueur, int nb_joueurs)
{
    int x = rand()% nb_joueurs;    //[0,nb_joueurs]
    t_joueur temp[4];
    temp[0] = joueur[0];
    temp[1] = joueur[1];
    temp[2] = joueur[2];
    temp[3] = joueur[3];
    int nb = 0;

    for (int i = 0; i < nb_joueurs; i++)
    {
        if(x < nb_joueurs)
        {
            joueur[i] = joueur[x];
            x = x+1;
        }
        else
        {
            joueur[i] = temp[nb];
            nb = nb+1;
        }
    }
}
