#include "../prototypes.h"
#include "../structures.h"

void encadrement_souris(BITMAP * buffer, int rouge, int vert, int bleu)
{
    for(int i = 0; i< 12; i++)
    {
        line(buffer, mouse_x +2*i, mouse_y -13 +i, mouse_x -2*i, mouse_y -13 +i, makecol(rouge, vert, bleu));
    }
    for(int i = 0; i< 13; i++)
    {
        line(buffer, mouse_x -23 +2*i, mouse_y-1 +i, mouse_x +23 -2*i, mouse_y- 1 +i, makecol(rouge, vert, bleu));
    }
}

void affichage_croix_rouge(BITMAP * buffer, BITMAP * croix_rouge, int ligne_souris, int colonne_souris, t_bloc tab_bloc[23][23])
{
    if (tab_bloc[ligne_souris][colonne_souris].occuper == 1)
    {
        masked_blit(croix_rouge, buffer, 0,0, tab_bloc[ligne_souris][colonne_souris].x_bloc -11, tab_bloc[ligne_souris][colonne_souris].y_bloc -11, croix_rouge->w, croix_rouge->h);
    }
}

void affichage_croix_bleue(BITMAP * buffer, BITMAP * croix_bleue, int ligne_souris, int colonne_souris, t_bloc tab_bloc[23][23])
{
    if (tab_bloc[ligne_souris][colonne_souris].accessible == 0)
    {
        masked_blit(croix_bleue, buffer, 0,0, tab_bloc[ligne_souris][colonne_souris].x_bloc -11, tab_bloc[ligne_souris][colonne_souris].y_bloc -11, croix_bleue->w, croix_bleue->h);
    }
}