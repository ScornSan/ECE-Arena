#include "../prototypes.h"
#include "../structures.h"

void reperage_chemin(BITMAP * buffer, int x_joueur, int y_joueur, int x_souris, int y_souris, t_bloc matrice[23][23], t_joueur* j, int i, int *autorisation_dep)
{
    int x_augmente;
    int y_augmente;
    int autorisation;
    int compteur = 0;
    x_joueur = j[i].x;
    y_joueur = j[i].y;

    if (x_joueur <= x_souris)
        x_augmente = 1;
    else
        x_augmente = 0;
    if (y_joueur <= y_souris)
        y_augmente = 1;
    else
        y_augmente = 0;

/// tant que le x et le y du joueur sont différents de celui de la souris ET seulement si la case est accessible la ou pointe la souris
    while(!j[i].gel && (x_joueur != x_souris || y_joueur != y_souris) && (abs(x_joueur - x_souris) + abs(y_joueur - y_souris)) <= j[i].pm && matrice[x_souris][y_souris].accessible)
    {
        compteur++;
        while (x_joueur != x_souris) // le x du joueur différent de la souris, alors
        {

            // on dessine un bloc puis on augmente de 1 la valeur du x_joueur
            if (x_augmente && matrice[x_joueur + 1][y_joueur].accessible)
            {
                autorisation = 1;
                dessin_bloc_unique(buffer, x_joueur + 1, y_joueur, matrice, j[i].red, j[i].green, j[i].blue);
                x_joueur = x_joueur + 1;
            }
            else if (!x_augmente && matrice[x_joueur - 1][y_joueur].accessible)
            {
                autorisation = 1;
                dessin_bloc_unique(buffer, x_joueur - 1, y_joueur, matrice, j[i].red, j[i].green, j[i].blue);
                x_joueur = x_joueur - 1;
            }
            else
            {
                autorisation = 0;
                break;
            }
        }
        while (y_joueur != y_souris)
        {
            if (y_augmente && matrice[x_joueur][y_joueur + 1].accessible)
            {
                autorisation = 1;
                dessin_bloc_unique(buffer, x_joueur, y_joueur + 1, matrice, j[i].red, j[i].green, j[i].blue);
                y_joueur = y_joueur + 1;
            }
            else if (!y_augmente && matrice[x_joueur][y_joueur - 1].accessible)
            {
                autorisation = 1;
                dessin_bloc_unique(buffer, x_joueur, y_joueur - 1, matrice, j[i].red, j[i].green, j[i].blue);
                y_joueur = y_joueur - 1;
            }
            else
            {
                autorisation = 0;
                break;
            }
        }
        if (matrice[x_souris][y_souris].accessible == 0)
        {
            //masked_blit(croix_bleue, buffer, 0,0, matrice[x_souris][y_souris].x_bloc -11, matrice[x_souris][y_souris].y_bloc -11, croix_bleue->w, croix_bleue->h);
        }
        if (matrice[x_souris][y_souris].occuper == 1)
        {
            //masked_blit(croix_rouge, buffer, 0,0, matrice[x_souris][y_souris].x_bloc -11, matrice[x_souris][y_souris].y_bloc -11, croix_rouge->w, croix_rouge->h);
        }
        //dessin_bloc_unique(buffer, x_souris, y_souris, matrice, j[i].red, j[i].green, j[i].blue);
        //dessin_bloc_unique(buffer, x_souris, y_souris, matrice, j[i].red, j[i].green, j[i].blue);
        if (compteur == 3)
        {
            break;
        }
    }
    if (mouse_b&1 && autorisation)
    {
        *autorisation_dep = 1;
    }
}

int random(int min, int max)
{
    srand(time(NULL));
    int resultat;
    resultat = min + rand()%(min - max +1);
    return resultat;
}

void dessin_bloc_unique(BITMAP *buffer, int param1, int param2, t_bloc matrice[23][23], int r, int g, int b)
{
    if (matrice[param1][param2].accessible)
    {
        for(int i = 0; i< 12; i++)
        {
            line(buffer, matrice[param1][param2].x_bloc +2*i, matrice[param1][param2].y_bloc -12 +i, matrice[param1][param2].x_bloc+1 -2*i,matrice[param1][param2].y_bloc -12 +i, makecol(r,g,b));
        }
        for(int i = 0; i< 12; i++)
        {
            line(buffer, matrice[param1][param2].x_bloc -22 +2*i, matrice[param1][param2].y_bloc +i, matrice[param1][param2].x_bloc +23 -2*i, matrice[param1][param2].y_bloc +i, makecol(r,g,b));
        }
    }

}

void effacement_bloc_unique(BITMAP *buffer_pixels, BITMAP * buffer, int param1, int param2, t_bloc matrice[23][23])
{
    int r,g,b;
    for(int i = 0; i< 12; i++)
    {
        for (int j= 0; j<=((matrice[param1][param2].x_bloc +2*i)-(matrice[param1][param2].x_bloc -2*i))/2 +1; j++)
        {
            r = getr(getpixel(buffer_pixels, matrice[param1][param2].x_bloc-j, matrice[param1][param2].y_bloc-12 +i));
            g = getg(getpixel(buffer_pixels, matrice[param1][param2].x_bloc-j, matrice[param1][param2].y_bloc-12 +i));
            b = getb(getpixel(buffer_pixels, matrice[param1][param2].x_bloc-j, matrice[param1][param2].y_bloc-12 +i));

            putpixel(buffer, matrice[param1][param2].x_bloc-j, matrice[param1][param2].y_bloc-12 +i, makecol(r,g,b));

            r = getr(getpixel(buffer_pixels, matrice[param1][param2].x_bloc+j, matrice[param1][param2].y_bloc-12 +i));
            g = getg(getpixel(buffer_pixels, matrice[param1][param2].x_bloc+j, matrice[param1][param2].y_bloc-12 +i));
            b = getb(getpixel(buffer_pixels, matrice[param1][param2].x_bloc+j, matrice[param1][param2].y_bloc-12 +i));

            putpixel(buffer, matrice[param1][param2].x_bloc+j, matrice[param1][param2].y_bloc-12 +i, makecol(r,g,b));
        }
    }
    for(int i = 0; i< 12; i++)
    {
        for (int j= ((matrice[param1][param2].x_bloc+22 -2*i)-(matrice[param1][param2].x_bloc -22+2*i))/2 +1; j>=0; j--)
        {
            r = getr(getpixel(buffer_pixels, matrice[param1][param2].x_bloc-j, matrice[param1][param2].y_bloc +i));
            g = getg(getpixel(buffer_pixels, matrice[param1][param2].x_bloc-j, matrice[param1][param2].y_bloc +i));
            b = getb(getpixel(buffer_pixels, matrice[param1][param2].x_bloc-j, matrice[param1][param2].y_bloc +i));

            putpixel(buffer, matrice[param1][param2].x_bloc-j, matrice[param1][param2].y_bloc +i, makecol(r,g,b));

            r = getr(getpixel(buffer_pixels, matrice[param1][param2].x_bloc+j, matrice[param1][param2].y_bloc +i));
            g = getg(getpixel(buffer_pixels, matrice[param1][param2].x_bloc+j, matrice[param1][param2].y_bloc +i));
            b = getb(getpixel(buffer_pixels, matrice[param1][param2].x_bloc+j, matrice[param1][param2].y_bloc +i));

            putpixel(buffer, matrice[param1][param2].x_bloc+j, matrice[param1][param2].y_bloc +i, makecol(r,g,b));
        }
    }
}

void zone_max_deplacement_0pm(BITMAP * buffer)
{
    textout_ex(buffer, font,"0 PM!! Vous ne pouvez pas vous deplacer ",15, 120, makecol(255,0,0), -1);
}

void zone_max_deplacement_1pm(BITMAP * buffer, int ligne_joueur, int colonne_joueur, t_bloc matrice[23][23])
{
    for (int k = colonne_joueur -1; k <= colonne_joueur +1; k++)
    {
        if (k >= 23 || k<=0) {}
        else
        {
            ///condition affichage en vert cases disponibles
            if (matrice[ligne_joueur][k].accessible == 1 && matrice[ligne_joueur][k].occuper == 0 )
            {
                dessin_bloc_unique(buffer, ligne_joueur, k, matrice, 0, 255, 0);
            }
        }
    }
    for (int k = ligne_joueur -1; k <= ligne_joueur +1; k++)
    {
        if (k >= 23 || k<=0) {}
        else
        {
            ///condition affichage en vert cases disponibles
            if (matrice[k][colonne_joueur].accessible == 1 && matrice[k][colonne_joueur].occuper == 0)
            {
                dessin_bloc_unique(buffer, k, colonne_joueur, matrice, 0, 255, 0);
            }
        }
    }
}
