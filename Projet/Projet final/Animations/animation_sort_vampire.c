#include "../prototypes.h"
#include "../structures.h"

void animation_sort3_vampire(BITMAP *buffer, BITMAP *bg, t_joueur* j, int i, t_bloc matrice[23][23], int nb_joueurs, int direction, int respiration_joueur[])
{
    j[i].direction = direction;
    int num_bitmap = 0;
    for (int k = 0; k < 10; k++)
    {
        switch(direction)
        {
        case 0:
            blit(bg,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
            // 2) DETERMINER NOUVELLEs POSITIONs

            // 3) AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
            draw_sprite(buffer, j[i].classe.spell[2].animation_sort_perso[j[i].direction][num_bitmap], matrice[j[i].x][j[i].y].x_bloc - 22, matrice[j[i].x][j[i].y].y_bloc - 52);
            affichage_joueurs_respiration(buffer, j, i, nb_joueurs, matrice, respiration_joueur, i);

            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest(80);
            break;
        case 2:
            blit(bg,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
            // 2) DETERMINER NOUVELLEs POSITIONs

            // 3) AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
            draw_sprite(buffer, j[i].classe.spell[2].animation_sort_perso[j[i].direction][num_bitmap], matrice[j[i].x][j[i].y].x_bloc - 22, matrice[j[i].x][j[i].y].y_bloc - 52);
            affichage_joueurs_respiration(buffer, j, i, nb_joueurs, matrice, respiration_joueur, i);

            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest(80);
            break;
        case 3:
            blit(bg,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
            // 2) DETERMINER NOUVELLEs POSITIONs

            // 3) AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
            draw_sprite(buffer, j[i].classe.spell[2].animation_sort_perso[j[i].direction][num_bitmap], matrice[j[i].x][j[i].y].x_bloc - 22, matrice[j[i].x][j[i].y].y_bloc - 52);
            affichage_joueurs_respiration(buffer, j, i, nb_joueurs, matrice, respiration_joueur, i);

            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest(80);
            break;
        case 1:
            blit(bg,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
            // 2) DETERMINER NOUVELLEs POSITIONs

            // 3) AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
            draw_sprite(buffer, j[i].classe.spell[2].animation_sort_perso[j[i].direction][num_bitmap], matrice[j[i].x][j[i].y].x_bloc - 22, matrice[j[i].x][j[i].y].y_bloc - 52);
            affichage_joueurs_respiration(buffer, j, i, nb_joueurs, matrice, respiration_joueur, i);

            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest(80);
            break;
        }
    }
}
