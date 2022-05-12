#include "../prototypes.h"
#include "../structures.h"

void dessin_ligne(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, BITMAP* buffer_pixels, t_bloc matrice[23][23], int x_souris, int y_souris, BITMAP *cursor, BITMAP *map, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP *desc_sorts, int longueur_ligne)
{
    for(int j = 1; j <= longueur_ligne; j++)
    {
        dessin_bloc_unique(buffer, joueur[i].x + j, joueur[i].y, matrice, 250, 140, 0);
        dessin_bloc_unique(buffer, joueur[i].x, joueur[i].y - j, matrice, 250, 140, 0);
        dessin_bloc_unique(buffer, joueur[i].x - j, joueur[i].y, matrice, 250, 140, 0);
        dessin_bloc_unique(buffer, joueur[i].x, joueur[i].y + j, matrice, 250, 140, 0);
        dessin_bloc_unique(buffer_pixels, joueur[i].x + j, joueur[i].y, matrice, 250, 140, 0);
        dessin_bloc_unique(buffer_pixels, joueur[i].x, joueur[i].y - j, matrice, 250, 140, 0);
        dessin_bloc_unique(buffer_pixels, joueur[i].x - j, joueur[i].y, matrice, 250, 140, 0);
        dessin_bloc_unique(buffer_pixels, joueur[i].x, joueur[i].y + j, matrice, 250, 140, 0);
    }
}

void dessin_diagonales(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, BITMAP* buffer_pixels, t_bloc matrice[23][23], int x_souris, int y_souris, BITMAP *cursor, BITMAP *map, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP *desc_sorts, int longueur_ligne)
{
    for(int j = 1; j <= longueur_ligne; j++)
    {
        dessin_bloc_unique(buffer, joueur[i].x + j, joueur[i].y + j, matrice, 250, 140, 0);
        dessin_bloc_unique(buffer, joueur[i].x + j, joueur[i].y - j, matrice, 250, 140, 0);
        dessin_bloc_unique(buffer, joueur[i].x - j, joueur[i].y - j, matrice, 250, 140, 0);
        dessin_bloc_unique(buffer, joueur[i].x - j, joueur[i].y + j, matrice, 250, 140, 0);
        dessin_bloc_unique(buffer_pixels, joueur[i].x + j, joueur[i].y + j, matrice, 250, 140, 0);
        dessin_bloc_unique(buffer_pixels, joueur[i].x + j, joueur[i].y - j, matrice, 250, 140, 0);
        dessin_bloc_unique(buffer_pixels, joueur[i].x - j, joueur[i].y + j, matrice, 250, 140, 0);
        dessin_bloc_unique(buffer_pixels, joueur[i].x - j, joueur[i].y - j, matrice, 250, 140, 0);
    }
}


void animation_attaque_de_base(BITMAP *buffer, BITMAP *bg, t_joueur* j, int i, t_bloc matrice[23][23], int nb_joueurs, int direction)
{
    printf("%d ptn\n", direction);
    j[i].direction = direction;
    switch(direction)
    {
    case 0:
        blit(bg,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
        // 2) DETERMINER NOUVELLEs POSITIONs

        // 3) AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
        draw_sprite(buffer, j[i].classe.anim_attaques[j[i].id_classe][j[i].direction][0], matrice[j[i].x][j[i].y].x_bloc - 22, matrice[j[i].x][j[i].y].y_bloc - 52);
        affichage_autres_joueurs(j, buffer, i, nb_joueurs, matrice);

        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(80);
        affichage_autres_joueurs(j, buffer, i,nb_joueurs, matrice);
        break;
    case 2:
        blit(bg,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
        // 2) DETERMINER NOUVELLEs POSITIONs

        // 3) AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
        draw_sprite(buffer, j[i].classe.anim_attaques[j[i].id_classe][j[i].direction][0], matrice[j[i].x][j[i].y].x_bloc - 22, matrice[j[i].x][j[i].y].y_bloc - 52);
        affichage_autres_joueurs(j, buffer, i, nb_joueurs, matrice);

        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(80);
        affichage_autres_joueurs(j, buffer, i,nb_joueurs, matrice);
        break;
    case 3:
        blit(bg,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
        // 2) DETERMINER NOUVELLEs POSITIONs

        // 3) AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
        draw_sprite(buffer, j[i].classe.anim_attaques[j[i].id_classe][j[i].direction][0], matrice[j[i].x][j[i].y].x_bloc - 22, matrice[j[i].x][j[i].y].y_bloc - 52);
        affichage_autres_joueurs(j, buffer, i, nb_joueurs, matrice);

        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(80);
        affichage_autres_joueurs(j, buffer, i,nb_joueurs, matrice);
        break;
    case 1:
        blit(bg,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
        // 2) DETERMINER NOUVELLEs POSITIONs

        // 3) AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
        draw_sprite(buffer, j[i].classe.anim_attaques[j[i].id_classe][j[i].direction][0], matrice[j[i].x][j[i].y].x_bloc - 22, matrice[j[i].x][j[i].y].y_bloc - 52);
        affichage_autres_joueurs(j, buffer, i, nb_joueurs, matrice);

        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(80);
        affichage_autres_joueurs(j, buffer, i,nb_joueurs, matrice);
        break;
    }
}
