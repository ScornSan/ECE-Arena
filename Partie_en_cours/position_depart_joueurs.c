#include "../prototypes.h"
#include "../structures.h"

void affichage_emplacement_depart(BITMAP * buffer, int nb_joueurs, t_bloc matrice[23][23], t_joueur *joueur)
{
    for (int j = 0; j < nb_joueurs;j++)
    {
        if(j == 0)
        {
            for (int k = 1; k < 5;k++)
            {
                for (int l = 12;l <15; l++)
                {
                    dessin_bloc_unique(buffer, k, l, matrice, joueur[j].red, joueur[j].green, joueur[j].blue);
                }
            }
            dessin_bloc_unique(buffer, 4, 9, matrice, joueur[j].red, joueur[j].green, joueur[j].blue);
            dessin_bloc_unique(buffer, 4, 10, matrice, joueur[j].red, joueur[j].green, joueur[j].blue);
            dessin_bloc_unique(buffer, 4, 11, matrice, joueur[j].red, joueur[j].green, joueur[j].blue);
            dessin_bloc_unique(buffer, 0, 12, matrice, joueur[j].red, joueur[j].green, joueur[j].blue);
        }
        else if(j == 1)
        {
            for (int k = 9; k < 14;k++)
            {
                for (int l = 19;l <22; l++)
                {
                    dessin_bloc_unique(buffer, k, l, matrice, joueur[j].red, joueur[j].green, joueur[j].blue);
                }
            }
            dessin_bloc_unique(buffer, 10, 22, matrice, joueur[j].red, joueur[j].green, joueur[j].blue);
        }
        else if(j == 2)
        {
            for (int k = 21; k < 23;k++)
            {
                for (int l = 10;l <13; l++)
                {
                    dessin_bloc_unique(buffer, k, l, matrice, joueur[j].red, joueur[j].green, joueur[j].blue);
                }
            }
            for (int k = 19; k < 21;k++)
            {
                for (int l = 11;l <14; l++)
                {
                    dessin_bloc_unique(buffer, k, l, matrice, joueur[j].red, joueur[j].green, joueur[j].blue);
                }
            }
            for (int l = 10;l <14; l++)
            {
                dessin_bloc_unique(buffer, 18, l, matrice, joueur[j].red, joueur[j].green, joueur[j].blue);
            }
        }
        else if(j == 3)
        {
            for (int k = 8; k < 12;k++)
            {
                for (int l = 1;l <4; l++)
                {
                    dessin_bloc_unique(buffer, k, l, matrice, joueur[j].red, joueur[j].green, joueur[j].blue);
                }
            }
            for (int k = 9; k < 13;k++)
            {
                dessin_bloc_unique(buffer, k, 4, matrice, joueur[j].red, joueur[j].green, joueur[j].blue);
            }
        }
    }
}

void condition_positionnement_depart(int *fini, int ligne_souris, int colonne_souris, t_bloc matrice[23][23], t_joueur* joueur, int *choix1, int *choix2, int *choix3, int *choix4, int red_mouse2, int green_mouse2, int blue_mouse2)
{
    if (mouse_b&1 && matrice[ligne_souris][colonne_souris].accessible == 1 && matrice[ligne_souris][colonne_souris].occuper == 0 && red_mouse2 == 170 && *choix1 == 0)
    {
        *fini = *fini +1;
        *choix1 = 1;
        joueur[0].x = ligne_souris;
        joueur[0].y = colonne_souris;
        joueur[0].place_manuellement = 1;
        matrice[joueur[0].x][joueur[0].y].occuper = 1;
        rest(200);
    }
    else if (mouse_b&1 && matrice[ligne_souris][colonne_souris].accessible == 1 && matrice[ligne_souris][colonne_souris].occuper == 0 && blue_mouse2 == 170 && *choix2 == 0)
    {
        *fini = *fini +1;
        *choix2 = 1;
        joueur[1].x = ligne_souris;
        joueur[1].y = colonne_souris;
        joueur[1].place_manuellement = 1;
        matrice[joueur[1].x][joueur[1].y].occuper = 2;
        rest(200);
    }
    else if (mouse_b&1 && matrice[ligne_souris][colonne_souris].accessible == 1 && matrice[ligne_souris][colonne_souris].occuper == 0 && green_mouse2 == 170 && *choix3 == 0)
    {
        *fini = *fini +1;
        *choix3 = 1;
        joueur[2].x = ligne_souris;
        joueur[2].y = colonne_souris;
        joueur[2].place_manuellement = 1;
        matrice[joueur[2].x][joueur[2].y].occuper = 3;
        rest(200);
    }
    else if (mouse_b&1 && matrice[ligne_souris][colonne_souris].accessible == 1 && matrice[ligne_souris][colonne_souris].occuper == 0 && green_mouse2 == 230 && *choix4 == 0)
    {
        *fini = *fini +1;
        *choix4 = 1;
        joueur[3].x = ligne_souris;
        joueur[3].y = colonne_souris;
        joueur[3].place_manuellement = 1;
        matrice[joueur[3].x][joueur[3].y].occuper = 4;
        rest(200);
    }
}

void placement_aleatoire(int *fini, t_bloc matrice[23][23], t_joueur* joueur, int nb_joueur)
{
    if(joueur[0].place_manuellement != 1)
    {
        joueur[0].x = 2 ;
        joueur[0].y = 12 ;
        matrice[joueur[0].x][joueur[0].y].occuper = 1;
    }
    if(joueur[1].place_manuellement !=1)
    {
        joueur[1].x = 10;
        joueur[1].y = 20;
        matrice[joueur[1].x][joueur[1].y].occuper = 1;
    }

    if(joueur[2].place_manuellement !=1)
    {
        joueur[2].x = 20;
        joueur[2].y = 11;
        matrice[joueur[2].x][joueur[2].y].occuper = 1;
    }

    if(joueur[3].place_manuellement !=1)
    {
        joueur[3].x = 11;
        joueur[3].y = 2;
        matrice[joueur[3].x][joueur[3].y].occuper = 1;
    }
   *fini = nb_joueur;
}
