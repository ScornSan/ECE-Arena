#include "../prototypes.h"
#include "../structures.h"

void animation_sort_mage(BITMAP *buffer, BITMAP *bg, t_joueur* j, int i, t_bloc matrice[23][23], int nb_joueurs, int direction, int respiration_joueur[], int ligne_souris, int colonne_souris, int num_spell)
{
    j[i].direction = direction;
    int k = 0;
    int x_depart = 0;
    int y_depart = 0;
    int x_arrive = 20 * abs(j[i].x - ligne_souris);
    int y_arrive = 10 * abs(j[i].y - colonne_souris);

    animation_attaque_de_base(buffer, bg, j, i, matrice, nb_joueurs, direction, respiration_joueur);
    while (x_depart <= x_arrive || y_depart <= y_arrive)
    {
        switch(direction)
        {
        case 0: /// SUD OUEST
            blit(bg,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
            // 2) DETERMINER NOUVELLEs POSITIONs
            // 3) AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
            draw_sprite(buffer, j[i].classe.spell[num_spell].anim_attaque_cible[direction][k], matrice[j[i].x][j[i].y].x_bloc - 22 - x_depart, matrice[j[i].x][j[i].y].y_bloc - 52 + y_depart);
            affichage_joueurs_respiration(buffer, j, i, nb_joueurs, matrice, respiration_joueur, 5);
            x_depart = x_depart + 4;
            y_depart = y_depart + 2;
            k = (k+1) % 2;
            break;
        case 2: /// NORD EST
            blit(bg,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
            // 2) DETERMINER NOUVELLEs POSITIONs

            // 3) AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
            affichage_joueurs_respiration(buffer, j, i, nb_joueurs, matrice, respiration_joueur, 5);
            draw_sprite(buffer, j[i].classe.spell[num_spell].anim_attaque_cible[direction][k], matrice[j[i].x][j[i].y].x_bloc - 22 + x_depart, matrice[j[i].x][j[i].y].y_bloc - 52 - y_depart);
            x_depart = x_depart + 4;
            y_depart = y_depart + 2;
            k = (k+1) % 2;
            break;
        case 3: /// SUD EST
            blit(bg,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
            // 2) DETERMINER NOUVELLEs POSITIONs

            // 3) AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
            draw_sprite(buffer, j[i].classe.spell[num_spell].anim_attaque_cible[direction][k], matrice[j[i].x][j[i].y].x_bloc - 22 + x_depart, matrice[j[i].x][j[i].y].y_bloc - 52 + y_depart);
            affichage_joueurs_respiration(buffer, j, i, nb_joueurs, matrice, respiration_joueur, 5);
            x_depart = x_depart + 4;
            y_depart = y_depart + 2;
            k = (k+1) % 2;
            break;
        case 1: /// NORD OUEST
            blit(bg,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
            // 2) DETERMINER NOUVELLEs POSITIONs

            // 3) AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
            affichage_joueurs_respiration(buffer, j, i, nb_joueurs, matrice, respiration_joueur, 5);
            draw_sprite(buffer, j[i].classe.spell[num_spell].anim_attaque_cible[direction][k], matrice[j[i].x][j[i].y].x_bloc - 22 - x_depart, matrice[j[i].x][j[i].y].y_bloc - 52 - y_depart);
            x_depart = x_depart + 4;
            y_depart = y_depart + 2;
            k = (k+1) % 2;
            break;
        }
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(60);
    }
    //textprintf_ex(buffer, font, 0, 5, makecol(0, 0, 0), -1, "  : %d", matrice[x_souris][y_souris].occuper);
    //textprintf_ex(buffer, font, 0, 15, makecol(0, 0, 0), -1, " : %d", matrice[joueur[(i + 1) % nb_joueurs].x][joueur[(i + 1) % nb_joueurs].y].occuper);
}
