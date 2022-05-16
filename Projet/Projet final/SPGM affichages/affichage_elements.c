#include "../prototypes.h"
#include "../structures.h"

void affichage_joueurs(BITMAP *buffer, t_joueur* joueur, int i, int nb_joueurs, t_bloc matrice[23][23])
{
    for (int j = 0; j< nb_joueurs; j++)
    {
        if (joueur[j].vivant)
        {
            //couleur_sous_joueur(buffer, joueur[j].x, joueur[j].y, matrice);
            draw_sprite(buffer, joueur[j].classe.deplacement[joueur[j].direction][0],  matrice[joueur[j].x][joueur[j].y].x_bloc - 22, matrice[joueur[j].x][joueur[j].y].y_bloc - 52);
            //masked_blit(joueur[j].classe.deplacement[joueur[j].direction][1], buffer, 0, 0, matrice[joueur[j].x][joueur[j].y].x_bloc - 22, matrice[joueur[j].x][joueur[j].y].y_bloc - 52, 49, 64);
        }
    }
}

void affichage_joueurs_respiration(BITMAP *buffer, t_joueur* joueur, int i, int nb_joueurs, t_bloc matrice[23][23], int respiration_joueur[], int joueur_deplace, int aff_shield)
{
    BITMAP * shield;
    shield = load_bitmap("SPRITES/CHEVALIER/BOUCLIER/shield_0.bmp", NULL);
    if (shield == NULL)
    {
        allegro_message("erreur shield");
    }

    for (int j = 0; j < nb_joueurs; j++)
    {
        if (joueur_deplace != j)
        {
            if (respiration_joueur[j] < 15)
            {
                draw_sprite(buffer, joueur[j].classe.respiration[joueur[j].direction][0],  matrice[joueur[j].x][joueur[j].y].x_bloc - 22, matrice[joueur[j].x][joueur[j].y].y_bloc - 52);
            }
            else
            {
                draw_sprite(buffer, joueur[j].classe.respiration[joueur[j].direction][1],  matrice[joueur[j].x][joueur[j].y].x_bloc - 22, matrice[joueur[j].x][joueur[j].y].y_bloc - 52);
            }
        }
        respiration_joueur[j] = (respiration_joueur[j] + 1) % 30;
        if (joueur[j].bouclier == 1 && aff_shield == 1)
        {
            masked_blit(shield, buffer,0,0,matrice[joueur[j].x][joueur[j].y].x_bloc - 21,matrice[joueur[j].x][joueur[j].y].y_bloc - 93, SCREEN_W, SCREEN_H);
            aff_shield == 0;
        }
    }
}


/*void respiration(t_joueur* joueur, int id_joueur, BITMAP *buffer, t_bloc matrice[23][23])
{
    switch(id_joueur)
    {
    case 0:
        if (id_joueur < 15)
        {
            draw_sprite(buffer, joueur[id_joueur].classe.respiration[joueur[id_joueur].direction][0],  matrice[joueur[id_joueur].x][joueur[id_joueur].y].x_bloc - 22, matrice[joueur[id_joueur].x][joueur[id_joueur].y].y_bloc - 52);
        }
        else
        {
            draw_sprite(buffer, joueur[id_joueur].classe.respiration[joueur[id_joueur].direction][1],  matrice[joueur[id_joueur].x][joueur[id_joueur].y].x_bloc - 22, matrice[joueur[id_joueur].x][joueur[id_joueur].y].y_bloc - 52);
        }
        break;
    case 1:
        if (id_joueur < 15)
        {
            draw_sprite(buffer, joueur[id_joueur].classe.respiration[joueur[id_joueur].direction][0],  matrice[joueur[id_joueur].x][joueur[id_joueur].y].x_bloc - 22, matrice[joueur[id_joueur].x][joueur[id_joueur].y].y_bloc - 52);
        }
        else
        {
            draw_sprite(buffer, joueur[id_joueur].classe.respiration[joueur[id_joueur].direction][1],  matrice[joueur[id_joueur].x][joueur[id_joueur].y].x_bloc - 22, matrice[joueur[id_joueur].x][joueur[id_joueur].y].y_bloc - 52);
        }
        break;
    case 2:
        if (id_joueur < 15)
        {
            draw_sprite(buffer, joueur[id_joueur].classe.respiration[joueur[id_joueur].direction][0],  matrice[joueur[id_joueur].x][joueur[id_joueur].y].x_bloc - 22, matrice[joueur[id_joueur].x][joueur[id_joueur].y].y_bloc - 52);
        }
        else
        {
            draw_sprite(buffer, joueur[id_joueur].classe.respiration[joueur[id_joueur].direction][1],  matrice[joueur[id_joueur].x][joueur[id_joueur].y].x_bloc - 22, matrice[joueur[id_joueur].x][joueur[id_joueur].y].y_bloc - 52);
        }
        break;
    case 3:
        if (id_joueur < 15)
        {
            draw_sprite(buffer, joueur[id_joueur].classe.respiration[joueur[id_joueur].direction][0],  matrice[joueur[id_joueur].x][joueur[id_joueur].y].x_bloc - 22, matrice[joueur[id_joueur].x][joueur[id_joueur].y].y_bloc - 52);
        }
        else
        {
            draw_sprite(buffer, joueur[id_joueur].classe.respiration[joueur[id_joueur].direction][1],  matrice[joueur[id_joueur].x][joueur[id_joueur].y].x_bloc - 22, matrice[joueur[id_joueur].x][joueur[id_joueur].y].y_bloc - 52);
        }
        break;
    }

}*/

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

void affichage_croix_rouge(BITMAP * buffer, BITMAP * croix_rouge, int *ligne_souris, int *colonne_souris, t_bloc matrice[23][23])
{
    if (matrice[*ligne_souris][*colonne_souris].occuper == 1)
    {
        masked_blit(croix_rouge, buffer, 0,0, matrice[*ligne_souris][*colonne_souris].x_bloc -11, matrice[*ligne_souris][*colonne_souris].y_bloc -11, croix_rouge->w, croix_rouge->h);
    }
}

void affichage_croix_bleue(BITMAP *buffer, BITMAP *croix_bleue, int *ligne_souris, int *colonne_souris, t_bloc matrice[23][23])
{
    if (matrice[*ligne_souris][*colonne_souris].accessible == 0)
    {
        masked_blit(croix_bleue, buffer, 0,0, matrice[*ligne_souris][*colonne_souris].x_bloc -11, matrice[*ligne_souris][*colonne_souris].y_bloc -11, croix_bleue->w, croix_bleue->h);
    }
}
