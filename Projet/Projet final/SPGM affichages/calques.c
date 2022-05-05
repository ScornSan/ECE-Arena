#include "../prototypes.h"
#include "../structures.h"

void distribution_couleur_blocs(BITMAP * buffer_map, t_bloc tab_bloc[23][23])
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
            tab_bloc[j][k].blue = blue;
            tab_bloc[j][k].red = k*red;
            tab_bloc[j][k].green = j*green;
            tab_bloc[j][k].accessible = 1;
            tab_bloc[j][k].occuper = 0;
            tab_bloc[j][k].x_bloc = 137 + j*23 +k*23;
            tab_bloc[j][k].y_bloc = 399  - k*13 +j*13;
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


void couleur_sous_joueur(BITMAP * buffer, int ligne_joueur, int colonne_joueur, t_bloc tab_bloc[23][23])
{
    for(int i = 0; i< 12; i++)
    {
        line(buffer, tab_bloc[ligne_joueur][colonne_joueur].x_bloc +2*i, tab_bloc[ligne_joueur][colonne_joueur].y_bloc-12 +i, tab_bloc[ligne_joueur][colonne_joueur].x_bloc+1 -2*i,tab_bloc[ligne_joueur][colonne_joueur].y_bloc -12 +i, makecol(0,255, 255));
    }
    for(int i = 0; i< 12; i++)
    {
        line(buffer, tab_bloc[ligne_joueur][colonne_joueur].x_bloc -22 +2*i, tab_bloc[ligne_joueur][colonne_joueur].y_bloc +i, tab_bloc[ligne_joueur][colonne_joueur].x_bloc +23 -2*i, tab_bloc[ligne_joueur][colonne_joueur].y_bloc +i, makecol(0, 255,255));
    }
}
