#include "../prototypes.h"
#include "../structures.h"

void reperage_chemin(BITMAP * buffer, int *ligne_joueur, int *colonne_joueur, int x_souris, int y_souris, t_bloc tab_bloc[23][23])
{
    int x_augmente;
    int y_augmente;
    int x_joueur = *ligne_joueur;
    int y_joueur = *colonne_joueur;

    if (*ligne_joueur <= x_souris)
        x_augmente = 1;
    else
        x_augmente = 0;
    if (*colonne_joueur <= y_souris)
        y_augmente = 1;
    else
        y_augmente = 0;

/// tant que le x et le y du joueur sont différents de celui de la souris ET seulement si la case est accessible la ou pointe la souris
    while( (x_joueur != x_souris || y_joueur != y_souris) && (abs(x_joueur - x_souris) + abs(y_joueur - y_souris)) <= 3 && !tab_bloc[x_souris][y_souris].occuper)
    {
        if (x_joueur != x_souris) // le x du joueur différent de la souris, alors
        {                             // on dessine un bloc puis on augmente de 1 la valeur du x_joueur
            if (x_augmente && !tab_bloc[x_joueur + 1][y_joueur].occuper)
            {
                dessin_bloc_unique(buffer, x_joueur + 1, y_joueur, tab_bloc, 0, 180, 0);
                x_joueur = x_joueur + 1;
            }
            else if (!x_augmente && !tab_bloc[x_joueur - 1][y_joueur].occuper)
            {
                dessin_bloc_unique(buffer, x_joueur - 1, y_joueur, tab_bloc, 0, 180, 0);
                x_joueur = x_joueur - 1;
            }
        }
        if (y_joueur != y_souris)
        {
            if (y_augmente && !tab_bloc[x_joueur][y_joueur + 1].occuper)
            {
                dessin_bloc_unique(buffer, x_joueur, y_joueur + 1, tab_bloc, 0, 180, 0);
                y_joueur = y_joueur + 1;
            }
            else if (!y_augmente && !tab_bloc[x_joueur][y_joueur - 1].occuper)
            {
                dessin_bloc_unique(buffer, x_joueur, y_joueur - 1, tab_bloc, 0, 180, 0);
                y_joueur = y_joueur - 1;
            }
        }
        dessin_bloc_unique(buffer, x_souris, y_souris, tab_bloc, 0, 180, 0);
        dessin_bloc_unique(buffer, x_souris, y_souris, tab_bloc, 0, 180, 0);
    }
}

void deplacement_personnage(BITMAP * buffer,BITMAP * fond, int *ligne_joueur, int *colonne_joueur, int ligne_souris, int colonne_souris, t_bloc tab_bloc[23][23], int *deplacement_effectuer/*, int chrono1, int *erreur1*/)
{

    /// affichage du message d'erreur apres changement de prog et avec chrono :::::: A REGLER
    /*while(1)
    {
        if ((int) time(NULL) - chrono1 < 2 && *erreur1 == 1)
        {
            blit(fond, buffer, 0, 0, 0, 0, fond->w, fond->h);
            textout_ex(buffer, font,"Vous ne pouvez pas vous deplacer en dehors de la carte !! ",15, 30, makecol(255,0,0), -1);
            circlefill(buffer, tab_bloc[ligne_joueur][colonne_joueur].x_bloc, tab_bloc[ligne_joueur][colonne_joueur].y_bloc, 9, makecol(0,0,0));
            textprintf_ex(buffer, font, 415, 710, makecol(0,255,0), -1, "position de la souris : x = %d et y = %d", mouse_x, mouse_y);
            quadrillage_test(buffer);
            blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
        }
        else
        {
            blit(fond, buffer, 0, 0, 0, 0, fond->w, fond->h);
            circlefill(buffer, tab_bloc[ligne_joueur][colonne_joueur].x_bloc, tab_bloc[ligne_joueur][colonne_joueur].y_bloc, 9, makecol(0,0,0));
            textprintf_ex(buffer, font, 415, 710, makecol(0,255,0), -1, "position de la souris : x = %d et y = %d", mouse_x, mouse_y);
            quadrillage_test(buffer);
            blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
            *erreur1 = 0;
        }
    }*/

    /// condition -> le joueur doit aller a gauche
    if (*colonne_joueur >= colonne_souris)
    {
        while(*colonne_joueur != colonne_souris)
        {
            *colonne_joueur = *colonne_joueur -1;
            blit(fond, buffer, 0, 0, 0, 0, fond->w, fond->h);
            circlefill(buffer, tab_bloc[*ligne_joueur][*colonne_joueur].x_bloc, tab_bloc[*ligne_joueur][*colonne_joueur].y_bloc, 9, makecol(0,0,0));
            textprintf_ex(buffer, font, 415, 710, makecol(0,255,0), -1, "position de la souris : x = %d et y = %d", mouse_x, mouse_y);
            quadrillage_test(buffer);
            blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
            usleep(200000);
        }
    }
    /// condition -> le joueur doit aller a droite
    else
    {
        while(*colonne_joueur != colonne_souris)
        {
            *colonne_joueur = *colonne_joueur +1;
            blit(fond, buffer, 0, 0, 0, 0, fond->w, fond->h);
            circlefill(buffer, tab_bloc[*ligne_joueur][*colonne_joueur].x_bloc, tab_bloc[*ligne_joueur][*colonne_joueur].y_bloc, 9, makecol(0,0,0));
            textprintf_ex(buffer, font, 415, 710, makecol(0,255,0), -1, "position de la souris : x = %d et y = %d", mouse_x, mouse_y);
            quadrillage_test(buffer);
            blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
            usleep(200000);
        }
    }
    /// condition -> le joueur doit monter
    if (*ligne_joueur >= ligne_souris)
    {
        while(*ligne_joueur != ligne_souris)
        {
            *ligne_joueur = *ligne_joueur -1;
            blit(fond, buffer, 0, 0, 0, 0, fond->w, fond->h);
            circlefill(buffer, tab_bloc[*ligne_joueur][*colonne_joueur].x_bloc, tab_bloc[*ligne_joueur][*colonne_joueur].y_bloc, 9, makecol(0,0,0));
            textprintf_ex(buffer, font, 415, 710, makecol(0,255,0), -1, "position de la souris : x = %d et y = %d", mouse_x, mouse_y);
            quadrillage_test(buffer);
            blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
            usleep(200000);
        }
    }
    /// condition -> le joueur doit descendre
    else
    {
        while(*ligne_joueur != ligne_souris)
        {
            *ligne_joueur = *ligne_joueur +1;
            blit(fond, buffer, 0, 0, 0, 0, fond->w, fond->h);
            circlefill(buffer, tab_bloc[*ligne_joueur][*colonne_joueur].x_bloc, tab_bloc[*ligne_joueur][*colonne_joueur].y_bloc, 9, makecol(0,0,0));
            textprintf_ex(buffer, font, 415, 710, makecol(0,255,0), -1, "position de la souris : x = %d et y = %d", mouse_x, mouse_y);
            quadrillage_test(buffer);
            blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
            usleep(200000);
        }
    }
    *deplacement_effectuer = *deplacement_effectuer +1;
}

void dessin_bloc_unique(BITMAP *buffer, int param1, int param2, t_bloc tab_bloc[23][23], int r, int g, int b)
{
    for(int i = 0; i< 12; i++)
    {
        line(buffer, tab_bloc[param1][param2].x_bloc +2*i, tab_bloc[param1][param2].y_bloc -12 +i, tab_bloc[param1][param2].x_bloc+1 -2*i,tab_bloc[param1][param2].y_bloc -12 +i, makecol(r,g,b));
    }
    for(int i = 0; i< 12; i++)
    {
        line(buffer, tab_bloc[param1][param2].x_bloc -22 +2*i, tab_bloc[param1][param2].y_bloc +i, tab_bloc[param1][param2].x_bloc +23 -2*i, tab_bloc[param1][param2].y_bloc +i, makecol(r,g,b));
    }
}

void effacement_bloc_unique(BITMAP *buffer_pixels, BITMAP * buffer, int param1, int param2, t_bloc tab_bloc[23][23])
{
    int r,g,b;
    for(int i = 0; i< 12; i++)
    {
        for (int j= 0; j<=((tab_bloc[param1][param2].x_bloc +2*i)-(tab_bloc[param1][param2].x_bloc -2*i))/2 +1; j++)
        {
            r = getr(getpixel(buffer_pixels, tab_bloc[param1][param2].x_bloc-j, tab_bloc[param1][param2].y_bloc-12 +i));
            g = getg(getpixel(buffer_pixels, tab_bloc[param1][param2].x_bloc-j, tab_bloc[param1][param2].y_bloc-12 +i));
            b = getb(getpixel(buffer_pixels, tab_bloc[param1][param2].x_bloc-j, tab_bloc[param1][param2].y_bloc-12 +i));

            putpixel(buffer, tab_bloc[param1][param2].x_bloc-j, tab_bloc[param1][param2].y_bloc-12 +i, makecol(r,g,b));

            r = getr(getpixel(buffer_pixels, tab_bloc[param1][param2].x_bloc+j, tab_bloc[param1][param2].y_bloc-12 +i));
            g = getg(getpixel(buffer_pixels, tab_bloc[param1][param2].x_bloc+j, tab_bloc[param1][param2].y_bloc-12 +i));
            b = getb(getpixel(buffer_pixels, tab_bloc[param1][param2].x_bloc+j, tab_bloc[param1][param2].y_bloc-12 +i));

            putpixel(buffer, tab_bloc[param1][param2].x_bloc+j, tab_bloc[param1][param2].y_bloc-12 +i, makecol(r,g,b));
        }
    }
    for(int i = 0; i< 12; i++)
    {
        for (int j= ((tab_bloc[param1][param2].x_bloc+22 -2*i)-(tab_bloc[param1][param2].x_bloc -22+2*i))/2 +1; j>=0; j--)
        {
            r = getr(getpixel(buffer_pixels, tab_bloc[param1][param2].x_bloc-j, tab_bloc[param1][param2].y_bloc +i));
            g = getg(getpixel(buffer_pixels, tab_bloc[param1][param2].x_bloc-j, tab_bloc[param1][param2].y_bloc +i));
            b = getb(getpixel(buffer_pixels, tab_bloc[param1][param2].x_bloc-j, tab_bloc[param1][param2].y_bloc +i));

            putpixel(buffer, tab_bloc[param1][param2].x_bloc-j, tab_bloc[param1][param2].y_bloc +i, makecol(r,g,b));

            r = getr(getpixel(buffer_pixels, tab_bloc[param1][param2].x_bloc+j, tab_bloc[param1][param2].y_bloc +i));
            g = getg(getpixel(buffer_pixels, tab_bloc[param1][param2].x_bloc+j, tab_bloc[param1][param2].y_bloc +i));
            b = getb(getpixel(buffer_pixels, tab_bloc[param1][param2].x_bloc+j, tab_bloc[param1][param2].y_bloc +i));

            putpixel(buffer, tab_bloc[param1][param2].x_bloc+j, tab_bloc[param1][param2].y_bloc +i, makecol(r,g,b));
        }
    }
}

void zone_max_deplacement_0pm(BITMAP * buffer)
{
    textout_ex(buffer, font,"0 PM!! Vous ne pouvez pas vous deplacer ",15, 120, makecol(255,0,0), -1);
}

void zone_max_deplacement_1pm(BITMAP * buffer, int ligne_joueur, int colonne_joueur, t_bloc tab_bloc[23][23])
{
    for (int k = colonne_joueur -1; k <= colonne_joueur +1; k++)
    {
        if (k >= 23 || k<=0) {}
        else
        {
            ///condition affichage en vert cases disponibles
            if (tab_bloc[ligne_joueur][k].accessible == 1 && tab_bloc[ligne_joueur][k].occuper == 0 )
            {
                dessin_bloc_unique(buffer, ligne_joueur, k, tab_bloc, 0, 255, 0);
            }
        }
    }
    for (int k = ligne_joueur -1; k <= ligne_joueur +1; k++)
    {
        if (k >= 23 || k<=0) {}
        else
        {
            ///condition affichage en vert cases disponibles
            if (tab_bloc[k][colonne_joueur].accessible == 1 && tab_bloc[k][colonne_joueur].occuper == 0)
            {
                dessin_bloc_unique(buffer, k, colonne_joueur, tab_bloc, 0, 255, 0);
            }
        }
    }
}
