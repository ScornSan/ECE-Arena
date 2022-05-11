#include "../prototypes.h"
#include "../structures.h"

void deplacement_nombre_pm(BITMAP* buffer_pixels, BITMAP * buffer, int ligne_joueur, int colonne_joueur, t_bloc matrice[23][23], int *nombre_pm, int *clic, BITMAP *cursor)
{
    switch(*nombre_pm)
    {
    case 0:
        zone_max_deplacement_0pm(buffer);
        break;
    case 1:
        if (*clic == 1)
        {
            //*nombre_pm = *nombre_pm -1;
            *clic = 0;
        }
        else
        {
            zone_max_deplacement_1pm(buffer, ligne_joueur, colonne_joueur, matrice);
        }
        break;
    case 2:
        if (*clic == 1)
        {
            //*nombre_pm = *nombre_pm -2;
            *clic = 0;
        }
        else
        {
            zone_max_deplacement_2pm(buffer, ligne_joueur, colonne_joueur, matrice);
        }
        break;
    case 3:
        if (*clic == 1)
        {
            //*nombre_pm = *nombre_pm -3;
            *clic = 0;
        }
        else
        {
            //zone_max_deplacement_3pm(buffer, ligne_joueur, colonne_joueur, matrice);
            anomalie_case_deplacement(buffer_pixels,buffer, ligne_joueur, colonne_joueur, matrice);
        }
        break;
    }
}

void zone_max_deplacement_2pm(BITMAP * buffer, int ligne_joueur, int colonne_joueur, t_bloc matrice[23][23])
{
    for(int j = ligne_joueur-1; j<= ligne_joueur +1; j++)
    {
        for (int k = colonne_joueur -1; k <= colonne_joueur +1; k++)
        {
            if (k >= 23 || k<=0 || j >= 23 || j<=0) {}
            else
            {
                ///condition affichage en vert cases disponibles
                if (matrice[j][k].accessible == 1 && matrice[j][k].occuper == 0)
                {
                    dessin_bloc_unique(buffer, j, k, matrice, 0, 255, 0);
                }
            }
        }
    }
    if (matrice[ligne_joueur-2][colonne_joueur].accessible == 1 && matrice[ligne_joueur-2][colonne_joueur].occuper == 0 && (ligne_joueur-2 >=0 && ligne_joueur-2 <= 22) && (colonne_joueur >= 0 && colonne_joueur <= 22))
    {
        dessin_bloc_unique(buffer, ligne_joueur-2, colonne_joueur, matrice, 0, 255, 0);
    }
    if (matrice[ligne_joueur+2][colonne_joueur].accessible == 1 && matrice[ligne_joueur+2][colonne_joueur].occuper == 0 && (ligne_joueur+2 >=0 && ligne_joueur+2 <= 22) && (colonne_joueur >= 0 && colonne_joueur <= 22))
    {
        dessin_bloc_unique(buffer, ligne_joueur+2, colonne_joueur, matrice, 0, 255, 0);
    }
    if (matrice[ligne_joueur][colonne_joueur-2].accessible == 1 && matrice[ligne_joueur][colonne_joueur-2].occuper == 0&& (ligne_joueur >=0 && ligne_joueur <= 22) && (colonne_joueur -2 >= 0 && colonne_joueur -2 <= 22))
    {
        dessin_bloc_unique(buffer, ligne_joueur, colonne_joueur-2, matrice, 0, 255, 0);
    }
    if (matrice[ligne_joueur][colonne_joueur+2].accessible == 1 && matrice[ligne_joueur][colonne_joueur+2].occuper == 0 && (ligne_joueur >=0 && ligne_joueur <= 22) && (colonne_joueur +2 >= 0 && colonne_joueur +2 <= 22))
    {
        dessin_bloc_unique(buffer, ligne_joueur, colonne_joueur +2, matrice, 0, 255, 0);
    }
}

void zone_max_deplacement_3pm(BITMAP * buffer, int ligne_joueur, int colonne_joueur, t_bloc matrice[23][23])
{
    /// dessin gros retangle central
    for(int j = ligne_joueur-1; j<= ligne_joueur +1; j++)
    {
        for (int k = colonne_joueur -2; k <= colonne_joueur +2; k++)
        {
            ///condition affichage en vert cases disponibles
            if (matrice[j][k].accessible == 1 && matrice[j][k].occuper == 0)
            {
                dessin_bloc_unique(buffer, j, k, matrice, 0, 255,0);
            }
        }
    }
    /// dessin ligne de 3 blocs en haut et en bas
    for (int k = colonne_joueur -1; k <= colonne_joueur +1; k++)
    {
        ///condition affichage en vert cases disponibles
        if (matrice[ligne_joueur+2][k].accessible == 1 && matrice[ligne_joueur+2][k].occuper == 0)
        {
            dessin_bloc_unique(buffer, ligne_joueur +2, k, matrice, 0, 255, 0);
        }
        if (matrice[ligne_joueur-2][k].accessible == 1 && matrice[ligne_joueur-2][k].occuper == 0)
        {
            dessin_bloc_unique(buffer, ligne_joueur -2, k, matrice, 0, 255, 0);
        }

    }
    /// dessin 4 blocs aux extremités
    if (matrice[ligne_joueur-3][colonne_joueur].accessible == 1 && matrice[ligne_joueur-3][colonne_joueur].occuper == 0 && (ligne_joueur-3 >=0 && ligne_joueur-3 <= 22) && (colonne_joueur >= 0 && colonne_joueur <= 22))
    {
        dessin_bloc_unique(buffer, ligne_joueur-3, colonne_joueur, matrice, 0, 255, 0);
    }
    if (matrice[ligne_joueur+3][colonne_joueur].accessible == 1 && matrice[ligne_joueur+3][colonne_joueur].occuper == 0 && (ligne_joueur+3 >=0 && ligne_joueur+3 <= 22) && (colonne_joueur >= 0 && colonne_joueur <= 22))
    {
        dessin_bloc_unique(buffer, ligne_joueur+3, colonne_joueur, matrice, 0, 255, 0);
    }
    if (matrice[ligne_joueur][colonne_joueur-3].accessible == 1 && matrice[ligne_joueur][colonne_joueur-3].occuper == 0&& (ligne_joueur >=0 && ligne_joueur <= 22) && (colonne_joueur -3 >= 0 && colonne_joueur -3 <= 22))
    {
        dessin_bloc_unique(buffer, ligne_joueur, colonne_joueur-3, matrice, 0, 255, 0);
    }
    if (matrice[ligne_joueur][colonne_joueur+3].accessible == 1 && matrice[ligne_joueur][colonne_joueur+3].occuper == 0 && (ligne_joueur >=0 && ligne_joueur <= 22) && (colonne_joueur +3 >= 0 && colonne_joueur +3 <= 22))
    {
        dessin_bloc_unique(buffer, ligne_joueur, colonne_joueur +3, matrice, 0, 255, 0);
    }
}

void anomalie_case_deplacement(BITMAP * buffer_pixels, BITMAP * buffer, int ligne_joueur, int colonne_joueur, t_bloc matrice[23][23])
{
    int affiche = 1 ;
    int ligne_final = ligne_joueur;
    int colonne_final = colonne_joueur;
    /// for un carre de taille 3x3 autour de la case du joueur
    for (int i = ligne_joueur -3; i < ligne_joueur+3; i++)
    {
        for (int j = colonne_joueur-3; j< colonne_joueur+3; j++)
        {
            printf("i = %d  ", i);
            printf("j = %d\n", j);
            /// si le pixel du centre de la case i, j, est vert, je regarde si il y a bien un chemin pour y parvenir
            if(getg(getpixel(buffer, matrice[i][j].x_bloc, matrice[i][j].y_bloc)) == 255)
            {
                int colonne_temp = colonne_joueur;
                int ligne_temp = ligne_joueur;
                affiche = 1;
                /// test chemin 1
                if (colonne_temp >= j)
                {
                    while(colonne_temp != j)
                    {
                        colonne_temp--;
                        if (matrice[ligne_temp][colonne_temp].occuper == 1)
                        {
                            affiche = 0;
                            break;
                        }
                    }
                }
                else
                {
                    while(colonne_temp != j)
                    {
                        colonne_temp++;
                        if (matrice[ligne_temp][colonne_temp].occuper == 1)
                        {
                            affiche = 0;
                            break;
                        }
                    }
                }
                if (affiche == 1)
                {
                    if (ligne_temp >= i)
                    {
                        while(ligne_temp != i)
                        {
                            ligne_temp--;
                            if (matrice[ligne_temp][colonne_temp].occuper == 1)
                            {
                                affiche = 0;
                                break;
                            }
                        }
                    }
                    else
                    {
                        while(ligne_temp != i)
                        {
                            ligne_temp++;
                            if (matrice[ligne_temp][colonne_temp].occuper == 1)
                            {
                                affiche = 0;
                                break;
                            }
                        }
                    }
                }
                /// test chemin 2
                if (affiche == 0)
                {
                    affiche = 1;
                    ligne_temp = colonne_joueur;
                    colonne_temp = colonne_joueur;
                    if (ligne_temp >= i)
                    {
                        while(ligne_temp != i)
                        {
                            ligne_temp--;
                            if (matrice[ligne_temp][colonne_temp].occuper == 1)
                            {
                                affiche = 0;
                                break;
                            }
                        }
                    }
                    else
                    {
                        while(ligne_temp != i)
                        {
                            ligne_temp++;
                            if (matrice[ligne_temp][colonne_temp].occuper == 1)
                            {
                                affiche = 0;
                                break;
                            }
                        }
                    }
                    if (affiche == 1)
                    {
                        if (colonne_temp >= j)
                        {
                            while(colonne_temp != j)
                            {
                                colonne_temp--;
                                if (matrice[ligne_temp][colonne_temp].occuper == 1)
                                {
                                    affiche = 0;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            while(colonne_temp != j)
                            {
                                colonne_temp++;
                                if (matrice[ligne_temp][colonne_temp].occuper == 1)
                                {
                                    affiche = 0;
                                    break;
                                }
                            }
                        }
                    }
                    if (affiche == 0)
                    {
                        dessin_bloc_unique(buffer, i,j,matrice, 255,255,255);
                    }
                }
            }
        }
    }
}
