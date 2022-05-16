#include "../prototypes.h"
#include "../structures.h"

void affichage_autres_joueurs(t_joueur* j, BITMAP *buffer, int i, int nb_joueurs, t_bloc matrice[23][23])
{
    int joueur_suivant1 = (i + 1) % nb_joueurs;
    int joueur_suivant2 = (i + 2) % nb_joueurs;
    int joueur_suivant3 = (i + 3) % nb_joueurs;
    /// animation de respiration plus tard
    switch (nb_joueurs)
    {
    case 2:
        if (j[joueur_suivant1].vivant){
            draw_sprite(buffer, j[joueur_suivant1].classe.deplacement[j[joueur_suivant1].direction][0], matrice[j[joueur_suivant1].x][j[joueur_suivant1].y].x_bloc - 22, matrice[j[joueur_suivant1].x][j[joueur_suivant1].y].y_bloc - 52);
        }
        break;
    case 3:
        if (j[joueur_suivant1].vivant){
            draw_sprite(buffer, j[joueur_suivant1].classe.deplacement[j[joueur_suivant1].direction][0], matrice[j[joueur_suivant1].x][j[joueur_suivant1].y].x_bloc - 22, matrice[j[joueur_suivant1].x][j[joueur_suivant1].y].y_bloc - 52);
        }
        if (j[joueur_suivant2].vivant){
            draw_sprite(buffer, j[joueur_suivant2].classe.deplacement[j[joueur_suivant2].direction][0], matrice[j[joueur_suivant2].x][j[joueur_suivant2].y].x_bloc - 22, matrice[j[joueur_suivant2].x][j[joueur_suivant2].y].y_bloc - 52 );
        }
        break;
    case 4:
        if (j[joueur_suivant1].vivant){
            draw_sprite(buffer, j[joueur_suivant1].classe.deplacement[j[joueur_suivant1].direction][0], matrice[j[joueur_suivant1].x][j[joueur_suivant1].y].x_bloc - 22, matrice[j[joueur_suivant1].x][j[joueur_suivant1].y].y_bloc - 52);
        }
        if (j[joueur_suivant2].vivant){
            draw_sprite(buffer, j[joueur_suivant2].classe.deplacement[j[joueur_suivant2].direction][0], matrice[j[joueur_suivant2].x][j[joueur_suivant2].y].x_bloc - 22, matrice[j[joueur_suivant2].x][j[joueur_suivant2].y].y_bloc - 52 );
        }
        if (j[joueur_suivant3].vivant){
            draw_sprite(buffer, j[joueur_suivant3].classe.deplacement[j[joueur_suivant3].direction][0], matrice[j[joueur_suivant3].x][j[joueur_suivant3].y].x_bloc - 22, matrice[j[joueur_suivant3].x][j[joueur_suivant3].y].y_bloc - 52);
        }
        break;
    }
}

void animation_deplacement(BITMAP *buffer, BITMAP *bg, t_joueur* j, int i, t_bloc matrice[23][23], int nb_joueurs, int respiration_joueur[])
{
    int x_depart = 0;
    int y_depart = 0;
    int x_arrive = 22;
    int y_arrive = 13;
    int num_bitmap = 0;
    while (x_depart <= x_arrive && y_depart <= y_arrive)
    {
        switch (j[i].direction)
        {
        case 0: /// sud ouest
            // matrice de matrice[j[i].x][j[i].y].x_bloc
            // matrice de matrice[j[i].x][j[i].y].y_bloc
            // milieu du matrice : 23 pixel en x jusqu'au milieu, 13 en y
            // augmente de 2 en x, 1 en y
            // 1)  EFFACER BUFFER, en appliquant décor  (pas de clear_bitmap)
            blit(bg,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
            // 2) DETERMINER NOUVELLEs POSITIONs

            // 3) AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
            draw_sprite(buffer, j[i].classe.deplacement[j[i].direction][num_bitmap], matrice[j[i].x][j[i].y].x_bloc - 22 - x_depart, matrice[j[i].x][j[i].y].y_bloc - 52 + y_depart);
            affichage_joueurs_respiration(buffer, j, i, nb_joueurs, matrice, respiration_joueur, i);
            num_bitmap = (num_bitmap + 1) % NB_BITMAPS_D;
            x_depart = x_depart + 4;
            y_depart = y_depart + 2;

            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest(80);
            break;
        case 1: /// nord ouest
            // matrice de matrice[j[i].x][j[i].y].x_bloc
            // matrice de matrice[j[i].x][j[i].y].y_bloc
            // milieu du matrice : 23 pixel en x jusqu'au milieu, 13 en y
            // augmente de 2 en x, 1 en y
            // 1)  EFFACER BUFFER, en appliquant décor  (pas de clear_bitmap)
            blit(bg,buffer,0,0,0,0,SCREEN_W,SCREEN_H);

            // 2) DETERMINER NOUVELLEs POSITIONs

            // 3) AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
            draw_sprite(buffer, j[i].classe.deplacement[j[i].direction][num_bitmap], matrice[j[i].x][j[i].y].x_bloc - 22 - x_depart, matrice[j[i].x][j[i].y].y_bloc - 52 - y_depart);
            affichage_joueurs_respiration(buffer, j, i, nb_joueurs, matrice, respiration_joueur, i);
            num_bitmap = (num_bitmap + 1) % NB_BITMAPS_D;
            x_depart = x_depart + 4;
            y_depart = y_depart + 2;

            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest(80);
            break;
        case 2: /// nord est
            // matrice de matrice[j[i].x][j[i].y].x_bloc
            // matrice de matrice[j[i].x][j[i].y].y_bloc
            // milieu du matrice : 23 pixel en x jusqu'au milieu, 13 en y
            // augmente de 2 en x, 1 en y
            // 1)  EFFACER BUFFER, en appliquant décor  (pas de clear_bitmap)
            blit(bg,buffer,0,0,0,0,SCREEN_W,SCREEN_H);

            // 2) DETERMINER NOUVELLEs POSITIONs

            // 3) AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
            draw_sprite(buffer, j[i].classe.deplacement[j[i].direction][num_bitmap], matrice[j[i].x][j[i].y].x_bloc - 22 + x_depart, matrice[j[i].x][j[i].y].y_bloc - 52 - y_depart);
            affichage_joueurs_respiration(buffer, j, i, nb_joueurs, matrice, respiration_joueur, i);
            num_bitmap = (num_bitmap + 1) % NB_BITMAPS_D;
            x_depart = x_depart + 4;
            y_depart = y_depart + 2;

            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest(80);
            break;
        case 3: /// sud est
            // matrice de matrice[j[i].x][j[i].y].x_bloc
            // matrice de matrice[j[i].x][j[i].y].y_bloc
            // milieu du matrice : 23 pixel en x jusqu'au milieu, 13 en y
            // augmente de 2 en x, 1 en y
            // 1)  EFFACER BUFFER, en appliquant décor  (pas de clear_bitmap)
            blit(bg,buffer,0,0,0,0,SCREEN_W,SCREEN_H);

            // 2) DETERMINER NOUVELLEs POSITIONs

            // 3) AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
            draw_sprite(buffer, j[i].classe.deplacement[j[i].direction][num_bitmap], matrice[j[i].x][j[i].y].x_bloc - 22 + x_depart, matrice[j[i].x][j[i].y].y_bloc - 52 + y_depart);
            affichage_joueurs_respiration(buffer, j, i, nb_joueurs, matrice, respiration_joueur, i);
            num_bitmap = (num_bitmap + 1) % NB_BITMAPS_D;
            x_depart = x_depart + 4;
            y_depart = y_depart + 2;

            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest(80);
            break;
        }
        for (int j = 0; j < nb_joueurs; j++)
        {
            respiration_joueur[j] = (respiration_joueur[j] + 1) % 30;
        }
    }
}
