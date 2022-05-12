#include "../prototypes.h"
#include "../structures.h"


void sort4_assassin(BITMAP *buffer_map, BITMAP * map,BITMAP * cursor, BITMAP *buffer, t_joueur* joueur, int i, t_bloc matrice[23][23], int *red_mouse, int * green_mouse, int *blue_mouse, int *ligne_souris,
                             int *colonne_souris, int nb_joueurs, BITMAP * hud_icone, BITMAP * desc_sorts, BITMAP **hud_joueur, BITMAP **icone_classes)
{
    int sort_lance = 0;
    int annulation = 0;
    BITMAP* buffer_pixels;
    buffer_pixels = create_bitmap(1280,720);
    int red_temp, green_temp, blue_temp;
    int red_mouse2, green_mouse2, blue_mouse2;
    ///dessin limite zone d'attaque autour du perso
    /// dessin gros retangle central
    for(int j = joueur[i].x-1; j<= joueur[i].x +1; j++)
    {
        for (int k = joueur[i].y -2; k <= joueur[i].y +2; k++)
        {
            ///condition affichage en vert cases disponibles
            if (matrice[j][k].accessible == 1)
            {
                dessin_bloc_unique(buffer_pixels, j, k, matrice, 0, 255,0);
            }
        }
    }
    /// dessin ligne de 3 blocs en haut et en bas
    for (int k = joueur[i].y -1; k <= joueur[i].y +1; k++)
    {
        ///condition affichage en vert cases disponibles
        if (matrice[joueur[i].x+2][k].accessible == 1)
        {
            dessin_bloc_unique(buffer_pixels, joueur[i].x +2, k, matrice, 0, 255, 0);
        }
        if (matrice[joueur[i].x-2][k].accessible == 1)
        {
            dessin_bloc_unique(buffer_pixels, joueur[i].x -2, k, matrice, 0, 255, 0);
        }

    }
    /// dessin 4 blocs aux extremit�s
    if (matrice[joueur[i].x-3][joueur[i].y].accessible == 1 && (joueur[i].x-3 >=0 && joueur[i].x-3 <= 22) && (joueur[i].y >= 0 && joueur[i].y <= 22))
    {
        dessin_bloc_unique(buffer_pixels, joueur[i].x-3, joueur[i].y, matrice, 0, 255, 0);
    }
    if (matrice[joueur[i].x+3][joueur[i].y].accessible == 1 && (joueur[i].x+3 >=0 && joueur[i].x+3 <= 22) && (joueur[i].y >= 0 && joueur[i].y <= 22))
    {
        dessin_bloc_unique(buffer_pixels, joueur[i].x+3, joueur[i].y, matrice, 0, 255, 0);
    }
    if (matrice[joueur[i].x][joueur[i].y-3].accessible == 1 && (joueur[i].x >=0 && joueur[i].x <= 22) && (joueur[i].y -3 >= 0 && joueur[i].y -3 <= 22))
    {
        dessin_bloc_unique(buffer_pixels, joueur[i].x, joueur[i].y-3, matrice, 0, 255, 0);
    }
    if (matrice[joueur[i].x][joueur[i].y+3].accessible == 1 && (joueur[i].x >=0 && joueur[i].x <= 22) && (joueur[i].y +3 >= 0 && joueur[i].y +3 <= 22))
    {
        dessin_bloc_unique(buffer_pixels, joueur[i].x, joueur[i].y +3, matrice, 0, 255, 0);
    }

    int num_bitmap = 0;
    while(sort_lance == 0 && annulation == 0)
    {
        lecture_pixels_buffer_map(buffer_pixels, &red_mouse2, &green_mouse2, &blue_mouse2);
        if(mouse_b &1 && green_mouse2 == 255)
        {
            rest(80);
            sort_lance = 1;
            reperage_bloc_souris(ligne_souris, colonne_souris, red_mouse2, green_mouse2, blue_mouse2, matrice);
        }
        else if((mouse_b &1 && mouse_x >= 280 && mouse_x<= 490 && mouse_y >= 650 && mouse_y <= 720) )
        {
            annulation = 1;
        }
        else
        {
            blit(map, buffer, 0,0,0,0, SCREEN_W, SCREEN_H);
            textprintf_ex(buffer, font, 0, 0, makecol(0, 0, 0), -1, "Mouse X : %d", mouse_x);
            textprintf_ex(buffer, font, 0, 10, makecol(0, 0, 0), -1, "Mouse Y : %d", mouse_y);
            lecture_pixels_buffer_map(buffer_map, red_mouse, green_mouse, blue_mouse);
            reperage_bloc_souris(ligne_souris, colonne_souris, *red_mouse, *green_mouse, *blue_mouse, matrice);
            lecture_pixels_buffer_map(buffer_pixels, &red_temp, &green_temp, &blue_temp);
            if(green_temp == 255)
            {
               for(int k = *ligne_souris-3; k < *ligne_souris+4;k++)
                {
                    for (int l = *colonne_souris-3; l< *colonne_souris+4; l++)
                    {
                        if(matrice[k][l].accessible == 1 && (k >=0 && k <= 22) && (l >= 0 && l <= 22))
                        {
                            dessin_bloc_unique(buffer, k , l, matrice, 213,210,117);
                        }
                    }
                }
            }
            affichage_hud_sorts(joueur, i, nb_joueurs, buffer, hud_icone, desc_sorts); // Blit de 5 logos (les m�mes pour la barre d'action, � changer apr�s...)
            affichage_hud_joueur(buffer, hud_joueur, joueur, i,icone_classes);
            for (int j = 0; j< nb_joueurs; j++)
            {
                if (joueur[j].vivant)
                {
                    //couleur_sous_joueur(buffer, joueur[j].x, joueur[j].y, matrice);
                    masked_blit(joueur[j].classe.deplacement[0][0], buffer, 0, 0, matrice[joueur[j].x][joueur[j].y].x_bloc - 22, matrice[joueur[j].x][joueur[j].y].y_bloc - 52, 49, 64);
                }
            } // affiche du hud joueur, avec pv, pa, pm
            display_cursor(cursor, buffer, mouse_x-5, mouse_y-5);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        }
    }
    if (sort_lance == 1)
    {
        for(int l = 0; l< 5 ; l++)
        {
            for (int k = 0; k < 2;k++)
            {
                blit(map, buffer, 0,0,0,0, SCREEN_W, SCREEN_H);
                affichage_hud_sorts(joueur, i, nb_joueurs, buffer, hud_icone, desc_sorts); // Blit de 5 logos (les m�mes pour la barre d'action, � changer apr�s...)
                affichage_hud_joueur(buffer, hud_joueur, joueur, i,icone_classes);
                for (int j = 0; j< nb_joueurs; j++)
                {
                    if (joueur[j].vivant)
                    {
                        //couleur_sous_joueur(buffer, joueur[j].x, joueur[j].y, matrice);
                        masked_blit(joueur[j].classe.deplacement[0][0], buffer, 0, 0, matrice[joueur[j].x][joueur[j].y].x_bloc - 22, matrice[joueur[j].x][joueur[j].y].y_bloc - 52, 49, 64);
                    }
                } // affiche du hud joueur, avec pv, pa, pm
                draw_sprite(buffer, joueur[i].classe.spell[3].animation_sort[k], matrice[*ligne_souris][*colonne_souris].x_bloc - 161, matrice[*ligne_souris][*colonne_souris].y_bloc - 100);
                affichage_autres_joueurs(joueur, buffer, i,nb_joueurs, matrice);
                display_cursor(cursor, buffer, mouse_x-5, mouse_y-5);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                rest(400);
            }
        }
    }
    clear_bitmap(buffer_pixels);
}
