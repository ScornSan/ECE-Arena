#include "../prototypes.h"
#include "../structures.h"

void distribution_couleur_blocs(BITMAP * buffer_map, t_bloc matrice[23][23])
{
    int red = 5;
    int green = 10;
    int blue = 10;
    for (int j = 0; j<23; j++)
    {
        int x1 = 137 +23*j;
        int x2 = 114 +23*j;
        int y1 = 387 +13*j;
        int y2 = 399 +13*j;
        for (int k = 0; k<23; k++)
        {
            matrice[j][k].blue = blue;
            matrice[j][k].red = k*red;
            matrice[j][k].green = j*green;
            matrice[j][k].accessible = 1;
            matrice[j][k].occuper = 0;
            matrice[j][k].x_bloc = 137 + j*23 +k*23;
            matrice[j][k].y_bloc = 399  - k*13 +j*13;
            for(int i = 0; i< 12; i++)
            {
                line(buffer_map, x1 -2*i +k*23, y1 +i - k*13, (x1 + 1) +2*i +k*23, y1 +i - k*13, makecol(k*red,j*green,blue));
            }
            for(int i = 0; i< 12; i++)
            {
                line(buffer_map, x2 +2*i +k*23, y2 +i - k*13, (x2 + 46) -2*i +k*23, y2 +i - k*13, makecol(k*red,j*green,blue));
            }
            if (red *k > 200) {}
            else
            {
                red = 5;
            }
        }
        if (green *j > 110)
        {
            blue = blue +20;
        }
        else
        {
            green= 10;
        }
    }
}


void couleur_sous_joueur(BITMAP * buffer, int ligne_joueur, int colonne_joueur, t_bloc matrice[23][23], t_joueur* j, int k)
{
    for(int i = 0; i< 12; i++)
    {
        line(buffer, matrice[ligne_joueur][colonne_joueur].x_bloc +2*i, matrice[ligne_joueur][colonne_joueur].y_bloc-12 +i, matrice[ligne_joueur][colonne_joueur].x_bloc+1 -2*i,matrice[ligne_joueur][colonne_joueur].y_bloc -12 +i, makecol(j[k].red,j[k].green, j[k].blue));
    }
    for(int i = 0; i< 12; i++)
    {
        line(buffer, matrice[ligne_joueur][colonne_joueur].x_bloc -22 +2*i, matrice[ligne_joueur][colonne_joueur].y_bloc +i, matrice[ligne_joueur][colonne_joueur].x_bloc +23 -2*i, matrice[ligne_joueur][colonne_joueur].y_bloc +i, makecol(j[k].red, j[k].green,j[k].blue));
    }
}
