#include "../prototypes.h"
#include "../structures.h"

void reperage_chemin(BITMAP * buffer, int x_joueur, int y_joueur, int x_souris, int y_souris, t_bloc matrice[23][23], t_joueur* j, int i, int *autorisation_dep)
{
    int x_augmente;
    int y_augmente;
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
    while((x_joueur != x_souris || y_joueur != y_souris) && (abs(x_joueur - x_souris) + abs(y_joueur - y_souris)) <= j[i].pm && !matrice[x_souris][y_souris].occuper)
    {
        if (x_joueur != x_souris) // le x du joueur différent de la souris, alors
        {
            // on dessine un bloc puis on augmente de 1 la valeur du x_joueur
            if (x_augmente && !matrice[x_joueur + 1][y_joueur].occuper)
            {
                dessin_bloc_unique(buffer, x_joueur + 1, y_joueur, matrice, j[i].red, j[i].green, j[i].blue);
                x_joueur = x_joueur + 1;
            }
            else if (!x_augmente && !matrice[x_joueur - 1][y_joueur].occuper)
            {
                dessin_bloc_unique(buffer, x_joueur - 1, y_joueur, matrice, j[i].red, j[i].green, j[i].blue);
                x_joueur = x_joueur - 1;
            }
        }
        if (y_joueur != y_souris)
        {
            if (y_augmente && !matrice[x_joueur][y_joueur + 1].occuper)
            {
                dessin_bloc_unique(buffer, x_joueur, y_joueur + 1, matrice, j[i].red, j[i].green, j[i].blue);
                y_joueur = y_joueur + 1;
            }
            else if (!y_augmente && !matrice[x_joueur][y_joueur - 1].occuper)
            {
                dessin_bloc_unique(buffer, x_joueur, y_joueur - 1, matrice, j[i].red, j[i].green, j[i].blue);
                y_joueur = y_joueur - 1;
            }
        }
        dessin_bloc_unique(buffer, x_souris, y_souris, matrice, j[i].red, j[i].green, j[i].blue);
        dessin_bloc_unique(buffer, x_souris, y_souris, matrice, j[i].red, j[i].green, j[i].blue);
    }
    if (mouse_b&1)
    {
        *autorisation_dep = 1;
    }
}

void deplacement_personnage(BITMAP * buffer,BITMAP * fond, t_joueur* joueur, int i, int ligne_souris, int colonne_souris, t_bloc matrice[23][23], int *deplacement_effectuer, int nb_joueurs/*, int chrono1, int *erreur1*/)
{

    /// affichage du message d'erreur apres changement de prog et avec chrono :::::: A REGLER
    /*while(1)
    {
        if ((int) time(NULL) - chrono1 < 2 && *erreur1 == 1)
        {
            blit(fond, buffer, 0, 0, 0, 0, fond->w, fond->h);
            textout_ex(buffer, font,"Vous ne pouvez pas vous deplacer en dehors de la carte !! ",15, 30, makecol(255,0,0), -1);
            circlefill(buffer, matrice[ligne_joueur][colonne_joueur].x_bloc, matrice[ligne_joueur][colonne_joueur].y_bloc, 9, makecol(0,0,0));
            textprintf_ex(buffer, font, 415, 710, makecol(0,255,0), -1, "position de la souris : x = %d et y = %d", mouse_x, mouse_y);
            quadrillage_test(buffer);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        }
        else
        {
            blit(fond, buffer, 0, 0, 0, 0, fond->w, fond->h);
            circlefill(buffer, matrice[ligne_joueur][colonne_joueur].x_bloc, matrice[ligne_joueur][colonne_joueur].y_bloc, 9, makecol(0,0,0));
            textprintf_ex(buffer, font, 415, 710, makecol(0,255,0), -1, "position de la souris : x = %d et y = %d", mouse_x, mouse_y);
            quadrillage_test(buffer);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            *erreur1 = 0;
        }
    }*/

    int x_augmente;
    int y_augmente;

    if (joueur[i].x <= ligne_souris)
        x_augmente = 1;
    else
        x_augmente = 0;
    if (joueur[i].y <= colonne_souris)
        y_augmente = 1;
    else
        y_augmente = 0;

    while ((joueur[i].x != ligne_souris || joueur[i].y != colonne_souris) && (abs(joueur[i].x - ligne_souris) + abs(joueur[i].y - colonne_souris)) <= joueur[i].pm && !matrice[ligne_souris][colonne_souris].occuper)
    {
        clear_bitmap(buffer);
        /// condition -> le joueur doit descendre
        while(x_augmente && joueur[i].x != ligne_souris && !matrice[joueur[i].x + 1][joueur[i].y].occuper)
        {
            joueur[i].x = joueur[i].x +1;
            joueur[i].pm--;
            blit(fond, buffer, 0, 0, 0, 0, fond->w, fond->h);
            for (int j = 0;j< nb_joueurs; j++)
            {
                if (joueur[i].vivant)
                {
                    couleur_sous_joueur(buffer, joueur[j].x , joueur[j].y, matrice);
                    circlefill(buffer, matrice[joueur[j].x][joueur[j].y].x_bloc, matrice[joueur[j].x][joueur[j].y].y_bloc, 9, makecol(joueur[j].red,joueur[j].green,joueur[j].blue));
                }
            }
            //circlefill(buffer, matrice[joueur[i].x][joueur[i].y].x_bloc, matrice[joueur[i].x][joueur[i].y].y_bloc, 9, makecol(0,0,0));
            textprintf_ex(buffer, font, 415, 710, makecol(0,255,0), -1, "position de la souris : x = %d et y = %d", mouse_x, mouse_y);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            usleep(200000);
        }
        /// condition -> le joueur doit monter
        while(!x_augmente && joueur[i].x != ligne_souris && !matrice[joueur[i].x - 1][joueur[i].y].occuper)
        {
            joueur[i].x = joueur[i].x -1;
            joueur[i].pm--;
            blit(fond, buffer, 0, 0, 0, 0, fond->w, fond->h);
            for (int j = 0;j< nb_joueurs; j++)
            {
                if (joueur[i].vivant)
                {
                    couleur_sous_joueur(buffer, joueur[j].x , joueur[j].y, matrice);
                    circlefill(buffer, matrice[joueur[j].x][joueur[j].y].x_bloc, matrice[joueur[j].x][joueur[j].y].y_bloc, 9, makecol(joueur[j].red,joueur[j].green,joueur[j].blue));
                }
            }
            //circlefill(buffer, matrice[joueur[i].x][joueur[i].y].x_bloc, matrice[joueur[i].x][joueur[i].y].y_bloc, 9, makecol(0,0,0));
            textprintf_ex(buffer, font, 415, 710, makecol(0,255,0), -1, "position de la souris : x = %d et y = %d", mouse_x, mouse_y);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            usleep(200000);
        }
        /// condition -> le joueur doit aller a droite
        while(y_augmente && joueur[i].y != colonne_souris && !matrice[joueur[i].x][joueur[i].y + 1].occuper)
        {
            joueur[i].y = joueur[i].y +1;
            joueur[i].pm--;
            blit(fond, buffer, 0, 0, 0, 0, fond->w, fond->h);
            for (int j = 0;j< nb_joueurs; j++)
            {
                if (joueur[i].vivant)
                {
                    couleur_sous_joueur(buffer, joueur[j].x , joueur[j].y, matrice);
                    circlefill(buffer, matrice[joueur[j].x][joueur[j].y].x_bloc, matrice[joueur[j].x][joueur[j].y].y_bloc, 9, makecol(joueur[j].red,joueur[j].green,joueur[j].blue));
                }
            }
            //circlefill(buffer, matrice[joueur[i].x][joueur[i].y].x_bloc, matrice[joueur[i].x][joueur[i].y].y_bloc, 9, makecol(0,0,0));
            textprintf_ex(buffer, font, 415, 710, makecol(0,255,0), -1, "position de la souris : x = %d et y = %d", mouse_x, mouse_y);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            usleep(200000);
        }
        /// condition -> le joueur doit aller a gauche
        while(!y_augmente && joueur[i].y != colonne_souris && !matrice[joueur[i].x][joueur[i].y - 1].occuper)
        {
            joueur[i].y = joueur[i].y -1;
            joueur[i].pm--;
            blit(fond, buffer, 0, 0, 0, 0, fond->w, fond->h);
            for (int j = 0;j< nb_joueurs; j++)
            {
                if (joueur[i].vivant)
                {
                    couleur_sous_joueur(buffer, joueur[j].x , joueur[j].y, matrice);
                    circlefill(buffer, matrice[joueur[j].x][joueur[j].y].x_bloc, matrice[joueur[j].x][joueur[j].y].y_bloc, 9, makecol(joueur[j].red,joueur[j].green,joueur[j].blue));
                }
            }
            //circlefill(buffer, matrice[joueur[i].x][joueur[i].y].x_bloc, matrice[joueur[i].x][joueur[i].y].y_bloc, 9, makecol(0,0,0));
            textprintf_ex(buffer, font, 415, 710, makecol(0,255,0), -1, "position de la souris : x = %d et y = %d", mouse_x, mouse_y);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            usleep(200000);
        }
        *deplacement_effectuer = *deplacement_effectuer +1;
    }
}

void dessin_bloc_unique(BITMAP *buffer, int param1, int param2, t_bloc matrice[23][23], int r, int g, int b)
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
