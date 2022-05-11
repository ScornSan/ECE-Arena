#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>

void initialisationAllegro()
{
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT,1280,720,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}

typedef struct bloc
{
    int red;
    int green;
    int blue;
    int x_bloc;
    int y_bloc;
    int accessible;
    int occuper;
} t_bloc;

void display_cursor(BITMAP* cursor, BITMAP* buffer, int mouse_x, int mouse_y)
{
    masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, cursor->w, cursor->h);
}

int chrono()
{
    time_t start = time (NULL);
    while ((float) (time (NULL) - start)<= 2.1)
    {
        printf ("Duree = %fs\n", (float) (time (NULL) - start));
    }

}

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

void definition_accessible(t_bloc tab_bloc[23][23])
{
    for (int i = 0; i<23; i++)
    {
        for (int j = 0; j<23; j++)
        {
            /// partie supérieur droite et gauche en double rectancgle

            if (i <= 4 && (j <= 8 || j >= 16))
            {
                tab_bloc[i][j].accessible = 0;
            }
            if (((i >= 5 && i<= 7) && j <= 5) || (i == 5 && j >= 18) || (i == 6 && j >= 18))
            {
                tab_bloc[i][j].accessible = 0;
            }

            /// partie inférieur droite et gauche en double rectangle

            if (i >= 17 && (j <= 7 || j >= 15))
            {
                tab_bloc[i][j].accessible = 0;
            }
            if (((i >= 14 && i<= 16) && j >= 18) || (i == 15 && j <= 5) || (i == 16 && j <= 5))
            {
                tab_bloc[i][j].accessible = 0;
            }
        }
    }

    /// partie supérieur droite et gauche, exceptions

    tab_bloc[0][9].accessible = 0;
    tab_bloc[5][6].accessible = 0;
    tab_bloc[5][7].accessible = 0;
    tab_bloc[6][6].accessible = 0;
    tab_bloc[8][0].accessible = 0;
    tab_bloc[0][15].accessible = 0;
    tab_bloc[5][17].accessible = 0;
    tab_bloc[7][22].accessible = 0;

    ///partie inférieur droite et gauche, exceptions

    tab_bloc[16][6].accessible = 0;
    tab_bloc[14][0].accessible = 0;
    tab_bloc[22][8].accessible = 0;
    tab_bloc[22][14].accessible = 0;
    tab_bloc[16][16].accessible = 0;
    tab_bloc[16][17].accessible = 0;
    tab_bloc[15][17].accessible = 0;
    tab_bloc[13][22].accessible = 0;
}

void definition_occuper(t_bloc tab_bloc[23][23])
{
    tab_bloc[0][13].occuper = 1;
    tab_bloc[7][6].occuper = 1;
    tab_bloc[8][4].occuper = 1;
    tab_bloc[12][22].occuper = 1;

    tab_bloc[15][16].occuper = 1;
    tab_bloc[21][13].occuper = 1;
    tab_bloc[17][14].occuper = 1;
    tab_bloc[18][14].occuper = 1;

    tab_bloc[7][15].occuper = 1;
    tab_bloc[8][14].occuper = 1;
    tab_bloc[5][16].occuper = 1;
    tab_bloc[6][16].occuper = 1;

    tab_bloc[7][16].occuper = 1;
    tab_bloc[9][12].occuper = 1;
    tab_bloc[9][13].occuper = 1;
    tab_bloc[9][14].occuper = 1;

    tab_bloc[11][11].occuper = 1;
    tab_bloc[11][12].occuper = 1;
    tab_bloc[12][10].occuper = 1;
    tab_bloc[12][11].occuper = 1;

    tab_bloc[13][9].occuper = 1;
    tab_bloc[13][10].occuper = 1;
    tab_bloc[13][11].occuper = 1;
    tab_bloc[15][7].occuper = 1;

    tab_bloc[12][2].occuper = 1;
    tab_bloc[12][3].occuper = 1;
    tab_bloc[13][2].occuper = 1;
    tab_bloc[13][3].occuper = 1;

    tab_bloc[20][9].occuper = 1;
    tab_bloc[20][10].occuper = 1;
    tab_bloc[21][9].occuper = 1;
    tab_bloc[21][10].occuper = 1;
    tab_bloc[19][9].occuper = 1;
    tab_bloc[19][10].occuper = 1;

    tab_bloc[5][10].occuper = 1;
    tab_bloc[5][11].occuper = 1;
    tab_bloc[6][10].occuper = 1;
    tab_bloc[6][11].occuper = 1;

    tab_bloc[6][11].occuper = 1;
    tab_bloc[6][11].occuper = 1;
    tab_bloc[6][11].occuper = 1;
    tab_bloc[6][11].occuper = 1;

    tab_bloc[15][8].occuper = 1;
    tab_bloc[15][9].occuper = 1;
    tab_bloc[16][7].occuper = 1;

    for (int i = 0; i<23; i++)
    {
        for (int j = 0; j<23; j++)
        {
            if ((i >= 1 && i<= 3) &&(j >= 9 && j <= 11))
            {
                tab_bloc[i][j].occuper = 1;
            }
            if ((i == 7 && j >= 19 && j<= 21) || (i == 8 && j >= 19 && j<= 21))
            {
                tab_bloc[i][j].occuper = 1;
            }
        }
    }
}



void quadrillage_test(BITMAP *buffer)
{
    for( int i = 0; i<24; i++)
    {
        line(buffer, 114 +i*23, 399 +i*13, 642 +i*23, 100 +i*13, makecol(255,0,0));
        line(buffer, 115 +i*23, 399 -i*13, 643 +i*23, 697 -i*13, makecol(255,0,0));
    }
}

void reperage_bloc_souris(int *ligne_souris, int *colonne_souris,int red_mouse, int green_mouse, int blue_mouse, t_bloc tab_bloc[23][23], int *autorisation_dep)
{
    for (int i = 0; i<23; i++)
    {
        for (int j = 0; j<23; j++)
        {
            if (tab_bloc[i][j].red == red_mouse && tab_bloc[i][j].green == green_mouse && tab_bloc[i][j].blue == blue_mouse)
            {
                *ligne_souris = i;
                *colonne_souris = j;
            }
        }
    }
    /// blindage souris pour clic en dehros de la zone verte
    if(getr(getpixel(screen, mouse_x, mouse_y)) == 0 && getg(getpixel(screen, mouse_x, mouse_y)) == 255 && getb(getpixel(screen, mouse_x, mouse_y)) == 0)
    {
        *autorisation_dep = 1;
    }
    else
    {
        *autorisation_dep = 0;
    }
}

void deplacement_joueur(BITMAP * buffer,BITMAP * fond, int *ligne_joueur, int *colonne_joueur, int ligne_souris, int colonne_souris, t_bloc tab_bloc[23][23], int *deplacement_effectuer/*, int chrono1, int *erreur1*/)
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

void zone_max_deplacement_2pm(BITMAP * buffer, int ligne_joueur, int colonne_joueur, t_bloc tab_bloc[23][23])
{
    for(int j = ligne_joueur-1; j<= ligne_joueur +1; j++)
    {
        for (int k = colonne_joueur -1; k <= colonne_joueur +1; k++)
        {
            if (k >= 23 || k<=0 || j >= 23 || j<=0) {}
            else
            {
                ///condition affichage en vert cases disponibles
                if (tab_bloc[j][k].accessible == 1 && tab_bloc[j][k].occuper == 0)
                {
                    dessin_bloc_unique(buffer, j, k, tab_bloc, 0, 255, 0);
                }
            }
        }
    }
    if (tab_bloc[ligne_joueur-2][colonne_joueur].accessible == 1 && tab_bloc[ligne_joueur-2][colonne_joueur].occuper == 0 && (ligne_joueur-2 >=0 && ligne_joueur-2 <= 22) && (colonne_joueur >= 0 && colonne_joueur <= 22))
    {
        dessin_bloc_unique(buffer, ligne_joueur-2, colonne_joueur, tab_bloc, 0, 255, 0);
    }
    if (tab_bloc[ligne_joueur+2][colonne_joueur].accessible == 1 && tab_bloc[ligne_joueur+2][colonne_joueur].occuper == 0 && (ligne_joueur+2 >=0 && ligne_joueur+2 <= 22) && (colonne_joueur >= 0 && colonne_joueur <= 22))
    {
        dessin_bloc_unique(buffer, ligne_joueur+2, colonne_joueur, tab_bloc, 0, 255, 0);
    }
    if (tab_bloc[ligne_joueur][colonne_joueur-2].accessible == 1 && tab_bloc[ligne_joueur][colonne_joueur-2].occuper == 0&& (ligne_joueur >=0 && ligne_joueur <= 22) && (colonne_joueur -2 >= 0 && colonne_joueur -2 <= 22))
    {
        dessin_bloc_unique(buffer, ligne_joueur, colonne_joueur-2, tab_bloc, 0, 255, 0);
    }
    if (tab_bloc[ligne_joueur][colonne_joueur+2].accessible == 1 && tab_bloc[ligne_joueur][colonne_joueur+2].occuper == 0 && (ligne_joueur >=0 && ligne_joueur <= 22) && (colonne_joueur +2 >= 0 && colonne_joueur +2 <= 22))
    {
        dessin_bloc_unique(buffer, ligne_joueur, colonne_joueur +2, tab_bloc, 0, 255, 0);
    }
}

void zone_max_deplacement_3pm(BITMAP * buffer, int ligne_joueur, int colonne_joueur, t_bloc tab_bloc[23][23])
{
    /// dessin gros retangle central
    for(int j = ligne_joueur-1; j<= ligne_joueur +1; j++)
    {
        for (int k = colonne_joueur -2; k <= colonne_joueur +2; k++)
        {
            ///condition affichage en vert cases disponibles
            if (tab_bloc[j][k].accessible == 1 && tab_bloc[j][k].occuper == 0)
            {
                dessin_bloc_unique(buffer, j, k, tab_bloc, 0, 255,0);
            }
        }
    }
    /// dessin ligne de 3 blocs en haut et en bas
    for (int k = colonne_joueur -1; k <= colonne_joueur +1; k++)
    {
        ///condition affichage en vert cases disponibles
        if (tab_bloc[ligne_joueur+2][k].accessible == 1 && tab_bloc[ligne_joueur+2][k].occuper == 0)
        {
            dessin_bloc_unique(buffer, ligne_joueur +2, k, tab_bloc, 0, 255, 0);
        }
        if (tab_bloc[ligne_joueur-2][k].accessible == 1 && tab_bloc[ligne_joueur-2][k].occuper == 0)
        {
            dessin_bloc_unique(buffer, ligne_joueur -2, k, tab_bloc, 0, 255, 0);
        }

    }
    /// dessin 4 blocs aux extremités
    if (tab_bloc[ligne_joueur-3][colonne_joueur].accessible == 1 && tab_bloc[ligne_joueur-3][colonne_joueur].occuper == 0 && (ligne_joueur-3 >=0 && ligne_joueur-3 <= 22) && (colonne_joueur >= 0 && colonne_joueur <= 22))
    {
        dessin_bloc_unique(buffer, ligne_joueur-3, colonne_joueur, tab_bloc, 0, 255, 0);
    }
    if (tab_bloc[ligne_joueur+3][colonne_joueur].accessible == 1 && tab_bloc[ligne_joueur+3][colonne_joueur].occuper == 0 && (ligne_joueur+3 >=0 && ligne_joueur+3 <= 22) && (colonne_joueur >= 0 && colonne_joueur <= 22))
    {
        dessin_bloc_unique(buffer, ligne_joueur+3, colonne_joueur, tab_bloc, 0, 255, 0);
    }
    if (tab_bloc[ligne_joueur][colonne_joueur-3].accessible == 1 && tab_bloc[ligne_joueur][colonne_joueur-3].occuper == 0&& (ligne_joueur >=0 && ligne_joueur <= 22) && (colonne_joueur -3 >= 0 && colonne_joueur -3 <= 22))
    {
        dessin_bloc_unique(buffer, ligne_joueur, colonne_joueur-3, tab_bloc, 0, 255, 0);
    }
    if (tab_bloc[ligne_joueur][colonne_joueur+3].accessible == 1 && tab_bloc[ligne_joueur][colonne_joueur+3].occuper == 0 && (ligne_joueur >=0 && ligne_joueur <= 22) && (colonne_joueur +3 >= 0 && colonne_joueur +3 <= 22))
    {
        dessin_bloc_unique(buffer, ligne_joueur, colonne_joueur +3, tab_bloc, 0, 255, 0);
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

void lecture_pixels_buffer_map(BITMAP * buffer_map, int *red_mouse, int *green_mouse, int *blue_mouse)
{
    *green_mouse = getg(getpixel(buffer_map, mouse_x, mouse_y));
    *red_mouse = getr(getpixel(buffer_map, mouse_x, mouse_y));
    *blue_mouse = getb(getpixel(buffer_map, mouse_x, mouse_y));
}


void anomalie_case_deplacement(BITMAP * buffer_pixels, BITMAP * buffer, int ligne_joueur, int colonne_joueur, t_bloc tab_bloc[23][23])
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
            if(getg(getpixel(buffer, tab_bloc[i][j].x_bloc, tab_bloc[i][j].y_bloc)) == 255)
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
                        if (tab_bloc[ligne_temp][colonne_temp].occuper == 1)
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
                        if (tab_bloc[ligne_temp][colonne_temp].occuper == 1)
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
                            if (tab_bloc[ligne_temp][colonne_temp].occuper == 1)
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
                            if (tab_bloc[ligne_temp][colonne_temp].occuper == 1)
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
                            if (tab_bloc[ligne_temp][colonne_temp].occuper == 1)
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
                            if (tab_bloc[ligne_temp][colonne_temp].occuper == 1)
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
                                if (tab_bloc[ligne_temp][colonne_temp].occuper == 1)
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
                                if (tab_bloc[ligne_temp][colonne_temp].occuper == 1)
                                {
                                    affiche = 0;
                                    break;
                                }
                            }
                        }
                    }
                    if (affiche == 0)
                    {
                        dessin_bloc_unique(buffer, i,j,tab_bloc, 255,255,255);
                    }
                }
            }
        }
    }
}

/// Conditions affichage de la zone de pm pour la rivière
/*
    /// bloc supérieur gauche
    if (tab_bloc[ligne_joueur-1][colonne_joueur].occuper == 1 && tab_bloc[ligne_joueur][colonne_joueur-1].occuper == 1)
    {
        int k = 0;
        for (int j = 3; j>=0;j--)
        {
            for (int i = 0; i<=j;i++)
            {
                effacement_bloc_unique(buffer_pixels, buffer,ligne_joueur-k,colonne_joueur-i, tab_bloc);
            }
            k++;
        }
    }
    /// bloc supérieur droit
    if (tab_bloc[ligne_joueur-1][colonne_joueur].occuper == 1 && tab_bloc[ligne_joueur][colonne_joueur-1].occuper == 1)
    {
        int k = 0;
        for (int j = 3; j>=0;j--)
        {
            for (int i = 0; i<=j;i++)
            {
                effacement_bloc_unique(buffer_pixels, buffer,ligne_joueur-k,colonne_joueur-i, tab_bloc);
            }
            k++;
        }
    }
    /// bloc inferieur gauche
    if (tab_bloc[ligne_joueur-1][colonne_joueur].occuper == 1 && tab_bloc[ligne_joueur][colonne_joueur-1].occuper == 1)
    {
        int k = 0;
        for (int j = 3; j>=0;j--)
        {
            for (int i = 0; i<=j;i++)
            {
                effacement_bloc_unique(buffer_pixels, buffer,ligne_joueur-k,colonne_joueur-i, tab_bloc);
            }
            k++;
        }
    }
    /// bloc inferieur droit
    if (tab_bloc[ligne_joueur-1][colonne_joueur].occuper == 1 && tab_bloc[ligne_joueur][colonne_joueur-1].occuper == 1)
    {
        int k = 0;
        for (int j = 3; j>=0;j--)
        {
            for (int i = 0; i<=j;i++)
            {
                effacement_bloc_unique(buffer_pixels, buffer,ligne_joueur-k,colonne_joueur-i, tab_bloc);
            }
            k++;
        }
    }*/



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

void deplacement_nombre_pm(BITMAP* buffer_pixels, BITMAP * buffer, int ligne_joueur, int colonne_joueur, t_bloc tab_bloc[23][23], int *nombre_pm, int *clic, BITMAP *cursor)
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
            zone_max_deplacement_1pm(buffer, ligne_joueur, colonne_joueur, tab_bloc);
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
            zone_max_deplacement_2pm(buffer, ligne_joueur, colonne_joueur, tab_bloc);
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
            zone_max_deplacement_3pm(buffer, ligne_joueur, colonne_joueur, tab_bloc);
            anomalie_case_deplacement(buffer_pixels,buffer, ligne_joueur, colonne_joueur, tab_bloc);
        }
        break;
    }
}

typedef struct joueur
{
    int x;
    int y;
    int ligne_joueur;
    int colonne_joueur;
    int nb_pm;
} t_j;

int main()
{
    srand(time(NULL));
    initialisationAllegro();
    install_timer();
    BITMAP * fond;
    BITMAP * buffer;
    BITMAP * cursor;
    BITMAP * buffer_pixels;
    BITMAP * buffer_map;
    BITMAP * croix_rouge;
    BITMAP * croix_bleue;
    fond =load_bitmap("map.bmp",NULL);
    buffer =create_bitmap(SCREEN_W,SCREEN_H);
    buffer_map =create_bitmap(SCREEN_W,SCREEN_H);
    buffer_pixels =create_bitmap(SCREEN_W,SCREEN_H);
    croix_rouge = load_bitmap("croix_rouge.bmp", NULL);
    croix_bleue = load_bitmap("croix_bleue.bmp", NULL);
    cursor = load_bitmap("cursor.bmp", NULL);
    int x_souris;
    time_t chrono1 = time (NULL);
    time_t chrono2 = time (NULL);
    int erreur1 = 0;
    int erreur2 = 0;
    int clic = 0;
    int deplacement_effectuer = 0;
    int autorisation_dep = 0;
    int nombre_pm = 3;
    t_bloc tab_bloc[23][23];
    //int x = 114, y = 399;
    quadrillage_test(screen);
    distribution_couleur_blocs(buffer_map, tab_bloc);
    definition_accessible(tab_bloc);
    definition_occuper(tab_bloc);
    /// VERIFICATION ACCESSIBLE ET OCCUPER
    /*for (int i = 0; i <23; i++)
    {
        for (int j = 0; j< 23 ; j++)
        {
            if (tab_bloc[i][j].accessible == 0)
            {
                circlefill(screen, tab_bloc[i][j].x_bloc , tab_bloc[i][j].y_bloc, 9, makecol(255,255,255));
            }
            usleep(3000);
        }
    }*/
    /*for (int i = 0; i <23; i++)
    {
        for (int j = 0; j< 23 ; j++)
        {
            if (tab_bloc[i][j].occuper == 1)
            {
                circlefill(screen, tab_bloc[i][j].x_bloc , tab_bloc[i][j].y_bloc, 9, makecol(255,255,0));
            }
            usleep(3000);
        }
    }
    while(1)
    {

    }*/
    ///int x_joueur = tab_bloc[12][15].x_bloc , y_joueur = tab_bloc[12][15].y_bloc;
    int ligne_souris, colonne_souris;
    int green_mouse, red_mouse, blue_mouse;

    blit(fond, buffer_pixels, 0, 0, 0, 0, fond->w, fond->h);
    int ligne_joueur = 10, colonne_joueur = 10;
    while (deplacement_effectuer != 50)
    {
        lecture_pixels_buffer_map(buffer_map, &red_mouse, &green_mouse, &blue_mouse);
        blit(fond, buffer, 0, 0, 0, 0, fond->w, fond->h);
        //effacement_bloc_unique(buffer_pixels,buffer, ligne_joueur, colonne_joueur+2, tab_bloc, 255,100,255);
        reperage_bloc_souris(&ligne_souris, &colonne_souris, red_mouse, green_mouse, blue_mouse, tab_bloc, &autorisation_dep);
        if(mouse_b && autorisation_dep == 1)
        {
            /// variables contenant les parametres de la souris au moment du clic
            lecture_pixels_buffer_map(buffer_map, &red_mouse, &green_mouse, &blue_mouse);
            /// recherche du bloc correspondant sous la souris au moment du clic
            reperage_bloc_souris(&ligne_souris, &colonne_souris, red_mouse, green_mouse, blue_mouse, tab_bloc, &autorisation_dep);

            /// condition si la souris clic sur un bloc valable
            if (tab_bloc[ligne_souris][colonne_souris].accessible == 0)
            {
                textout_ex(screen, font,"Vous ne pouvez pas vous deplacer en dehors de la carte !! ",15, 30, makecol(255,0,0), -1); /////// A CHANGER PLUS TARD
                sleep(3); ///////// A CHANGER PLUS TARD
                chrono1 = time(NULL);
                erreur1 =1;
            }
            else if (tab_bloc[ligne_souris][colonne_souris].occuper == 1)
            {
                textout_ex(screen, font,"Cette case est deja occupee par un joueur ou un obstacle !! ", 800, 30, makecol(255,255,0), -1); /////// A CHANGER PLUS TARD
                sleep(3); ///////// A CHANGER PLUS TARD
                chrono2 = time(NULL);
                erreur2 =1;
            }
            else
            {
                clic = 1;
                deplacement_joueur(buffer,fond, &ligne_joueur,&colonne_joueur, ligne_souris, colonne_souris,tab_bloc, &deplacement_effectuer/*, chrono1, &erreur1*/);
                autorisation_dep = 0;
            }
        }
        /// Chrono a finir d'integrer plus tard
        /*if ((int) (time (NULL) - chrono1) < 2 && erreur1 == 1)
        {
            textout_ex(buffer, font,"Vous ne pouvez pas vous deplacer en dehors de la carte !! ",15, 30, makecol(255,0,0), -1);
        }
        else
        {
            erreur1 = 0;
        }*/
        //couleur_sous_joueur(buffer, ligne_joueur, colonne_joueur, tab_bloc);
        textprintf_ex(buffer, font, 415, 710, makecol(0,255,0), -1, "position de la souris : x = %d et y = %d", mouse_x, mouse_y);
        quadrillage_test(buffer);
        affichage_croix_bleue(buffer, croix_bleue, ligne_souris, colonne_souris, tab_bloc);
        affichage_croix_rouge(buffer, croix_rouge, ligne_souris, colonne_souris, tab_bloc);
        //encadrement_souris(buffer, red_mouse, green_mouse, blue_mouse);
        deplacement_nombre_pm(buffer_pixels, buffer, ligne_joueur, colonne_joueur, tab_bloc, &nombre_pm, &clic, cursor);
        reperage_chemin(buffer, &ligne_joueur, &colonne_joueur, ligne_souris, colonne_souris, tab_bloc);
        circlefill(buffer, tab_bloc[ligne_joueur][colonne_joueur].x_bloc, tab_bloc[ligne_joueur][colonne_joueur].y_bloc, 9, makecol(0,0,0));
        blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
    }
    textout_ex(screen, font,"Au tour du joueur suivant ",15, 100, makecol(255,255,255), -1);
    sleep(2);
    destroy_bitmap(fond);
    destroy_bitmap(buffer);
    return 0;
}
END_OF_MAIN() ;
