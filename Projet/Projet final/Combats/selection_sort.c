#include "../prototypes.h"
#include "../structures.h"

void attaque_de_base(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, t_bloc matrice[23][23], int x_souris, int y_souris, BITMAP *cursor, BITMAP *map, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP *desc_sorts)
{
    int attaque = 0;
    int ennemi1 = i + 1;
    int ennemi2;
    int ennemi3;
    if (nb_joueurs == 3)
        ennemi2 = i + 2;
    if (nb_joueurs == 4)
        ennemi3 = i + 3;
    //time_t start = time(NULL);
    /// tant qu'on ne clique pas sur l'icone de l'attaque de base, ou qu'on a lancé l'attaque
    while (!attaque)
    {
        clear_bitmap(buffer);
        affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
        dessin_bloc_unique(buffer, joueur[i].x + 1, joueur[i].y, matrice, 250, 140, 0);
        dessin_bloc_unique(buffer, joueur[i].x, joueur[i].y - 1, matrice, 250, 140, 0);
        dessin_bloc_unique(buffer, joueur[i].x - 1, joueur[i].y, matrice, 250, 140, 0);
        dessin_bloc_unique(buffer, joueur[i].x, joueur[i].y + 1, matrice, 250, 140, 0);
        affichage_joueurs(buffer, joueur, i, nb_joueurs, matrice);
        display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        // on attaque le joueur ennemi1 sur on clique et que la souris est sur lui
        if (matrice[x_souris][y_souris].x_bloc == matrice[joueur[ennemi1 % nb_joueurs].x][joueur[ennemi1 % nb_joueurs].y].x_bloc && matrice[x_souris][y_souris].y_bloc == matrice[joueur[ennemi1 % nb_joueurs].x][joueur[ennemi1 % nb_joueurs].y].y_bloc && mouse_b&1)
        {
            circlefill(buffer, 400, 500, 9, makecol(0, 0, 0));
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest(1000);
            attaque = 1; // on a attaqué, on peut sortir de la boucle en infligeant les dégâts, avec le % de chance
        }
        if (matrice[x_souris][y_souris].x_bloc == matrice[joueur[ennemi2 % nb_joueurs].x][joueur[ennemi2 % nb_joueurs].y].x_bloc && matrice[x_souris][y_souris].y_bloc == matrice[joueur[ennemi1 % nb_joueurs].x][joueur[ennemi1 % nb_joueurs].y].y_bloc && mouse_b&1)
        {
            circlefill(buffer, 400, 500, 9, makecol(0, 0, 0));
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest(1000);
            attaque = 1; // on a attaqué, on peut sortir de la boucle en infligeant les dégâts, avec le % de chance
        }
        if (matrice[x_souris][y_souris].x_bloc == matrice[joueur[ennemi3 % nb_joueurs].x][joueur[ennemi1 % nb_joueurs].y].x_bloc && matrice[x_souris][y_souris].y_bloc == matrice[joueur[ennemi3 % nb_joueurs].x][joueur[ennemi3 % nb_joueurs].y].y_bloc && mouse_b&1)
        {
            circlefill(buffer, 400, 500, 9, makecol(0, 0, 0));
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest(1000);
            attaque = 1; // on a attaqué, on peut sortir de la boucle en infligeant les dégâts, avec le % de chance
        }
        if (mouse_x >= 300 && mouse_x <= 330 && mouse_y >= 670 && mouse_y <= 700 && mouse_b&1)
        {
            animation_attaque_de_base(buffer, map, joueur, i, matrice, nb_joueurs);
            attaque = 1; // le joueur a annulé son attaque, l'attaque est considéré comme faite mais sans dégâts
        }
    }
}


void sort1(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, t_bloc matrice [23][23], BITMAP *desc_sorts, int x_souris, int y_souris, BITMAP *cursor, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP* map)
{
    switch(joueur[i].id_classe)
    {
    case 1: // GUERRIER
        sort1_guerrier(joueur, i, nb_joueurs, buffer, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts);
        break;
    case 2: // MAGE
        break;
    case 3: // VAMPIRE
        break;
    case 4: // ASSASSIN
        break;
    }
}

void sort2(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, t_bloc matrice [23][23], BITMAP *desc_sorts, int x_souris, int y_souris, BITMAP *cursor, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP* map)
{
    switch(joueur[i].id_classe)
    {
    case 1: // GUERRIER
        sort2_guerrier(joueur, i, nb_joueurs, buffer, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts);
        break;
    case 2: // MAGE
        break;
    case 3: // VAMPIRE
        break;
    case 4: // ASSASSIN
        break;
    }
}

void sort3(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, t_bloc matrice [23][23], BITMAP *desc_sorts, int x_souris, int y_souris, BITMAP *cursor, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP* map)
{
    switch(joueur[i].id_classe)
    {
    case 1: // GUERRIER
        sort3_guerrier(joueur, i, nb_joueurs, buffer, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts);
        break;
    case 2: // MAGE
        break;
    case 3: // VAMPIRE
        break;
    case 4: // ASSASSIN
        break;
    }
}

void sort4(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, t_bloc matrice [23][23], BITMAP *desc_sorts, int x_souris, int y_souris, BITMAP *cursor, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP* map){
    switch(joueur[i].id_classe)
    {
    case 1: // GUERRIER
        sort4_guerrier(joueur, i, nb_joueurs, buffer, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts);
        break;
    case 2: // MAGE
        break;
    case 3: // VAMPIRE
        break;
    case 4: // ASSASSIN
        break;
    }
}

void selection_sort(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, t_bloc matrice [23][23], BITMAP *desc_sorts, int x_souris, int y_souris, BITMAP *cursor, BITMAP *map, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone)
{
    /// On met des rest avant et après l'appel du programme pour bien qu'il y ait un clique : la pause est suffisante pour stopper un moment sans repasser dans la boucle
    if (mouse_x >= 300 && mouse_x <= 330 && mouse_y >= 670 && mouse_y <= 700 && mouse_b&1) // attaque de base
    {
        rest(80);
        attaque_de_base(joueur, i, nb_joueurs, buffer, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts);
        rest(80);
    }
    if (mouse_x >= 335 && mouse_x <= 365 && mouse_y >= 670 && mouse_y <= 700 && mouse_b&1) // sort 1
    {
        rest(80);
        sort1(joueur, i, nb_joueurs, buffer, matrice, desc_sorts, x_souris, y_souris, cursor, hud_joueur, icone_classes, hud_icone, map);
        rest(80);
    }
    if (mouse_x >= 370 && mouse_x <= 400 && mouse_y >= 670 && mouse_y <= 700 && mouse_b&1) // sort 2
    {
        rest(80);
        sort2(joueur, i, nb_joueurs, buffer, matrice, desc_sorts, x_souris, y_souris, cursor, hud_joueur, icone_classes, hud_icone, map);
        rest(80);
    }
    if (mouse_x >= 405 && mouse_x <= 435 && mouse_y >= 670 && mouse_y <= 700 && mouse_b&1) // sort 3
    {
        rest(80);
        sort3(joueur, i, nb_joueurs, buffer, matrice, desc_sorts, x_souris, y_souris, cursor, hud_joueur, icone_classes, hud_icone, map);
        rest(80);
    }
    if (mouse_x >= 440 && mouse_x <= 470 && mouse_y >= 670 && mouse_y <= 700 && mouse_b&1) // sort 4
    {
        rest(80);
        sort4(joueur, i, nb_joueurs, buffer, matrice, desc_sorts, x_souris, y_souris, cursor, hud_joueur, icone_classes, hud_icone, map);
        rest(80);
    }
}
