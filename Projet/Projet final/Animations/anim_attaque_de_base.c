#include "../prototypes.h"
#include "../structures.h"

void animation_attaque_de_base(BITMAP *buffer, BITMAP *bg, t_joueur* j, int i, t_bloc matrice[23][23], int nb_joueurs)
{
    int num;
    for (num = 0; num < NB_CLASSES; num++)
    {
        blit(bg,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
    // 2) DETERMINER NOUVELLEs POSITIONs

    // 3) AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
    draw_sprite(buffer, j[i].classe.anim_attaques[j[i].id_classe][j[i].direction][0], matrice[j[i].x][j[i].y].x_bloc - 22, matrice[j[i].x][j[i].y].y_bloc - 52);
    affichage_autres_joueurs(j, buffer, i, nb_joueurs, matrice);

    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    rest(80);
    affichage_autres_joueurs(j, buffer, i,nb_joueurs, matrice);
    }
}
