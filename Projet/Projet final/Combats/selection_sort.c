#include "../prototypes.h"
#include "../structures.h"

void attaque_de_base(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, BITMAP* buffer_map, t_bloc matrice[23][23], int x_souris, int y_souris, BITMAP *cursor, BITMAP *map, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP *desc_sorts, int respiration[])
{
    BITMAP *buffer_pixels;
    buffer_pixels = create_bitmap(SCREEN_W,SCREEN_H);
    int red_temp, green_temp,blue_temp;
    int red_temp1, green_temp1,blue_temp1;
    int attaque = 0;
    int id_ennemi;
    int degats;
    time_t start;
    //time_t start = time(NULL);
    /// tant qu'on ne clique pas sur l'icone de l'attaque de base, ou qu'on a lancé l'attaque
    while (!attaque)
    {
        if (joueur[i].attaque_dispo && joueur[i].pa >= 1)
        {
            clear_bitmap(buffer);
            affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
            dessin_ligne(joueur, i, nb_joueurs, buffer, buffer_pixels, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts, 1);
            affichage_joueurs_respiration_ralenti(buffer, joueur, i, nb_joueurs, matrice, respiration, 5);
            display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            lecture_pixels_buffer_map(buffer_map, &red_temp, &green_temp,&blue_temp);
            reperage_bloc_souris(&x_souris, &y_souris, red_temp, green_temp, blue_temp, matrice, joueur, i);
            lecture_pixels_buffer_map(buffer_pixels, &red_temp1, &green_temp1,&blue_temp1);
            // on attaque le joueur ennemi1 sur on clique et que la souris est sur lui
            if (matrice[x_souris][y_souris].occuper != matrice[joueur[i].x][joueur[i].y].occuper && matrice[x_souris][y_souris].occuper != 0 && mouse_b&1 && green_temp1 == 140)
            {
                start = time(NULL);
                id_ennemi = matrice[x_souris][y_souris].id_case - 1;
                joueur[i].pa = joueur[i].pa - 2;
                /// NORD OUEST
                if (x_souris < joueur[i].x && y_souris == joueur[i].y)
                {
                    animation_attaque_de_base(buffer, map, joueur, i, matrice, nb_joueurs, 1, respiration);
                    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                }
                /// SUD EST
                if (x_souris > joueur[i].x && y_souris == joueur[i].y)
                {
                    animation_attaque_de_base(buffer, map, joueur, i, matrice, nb_joueurs, 3, respiration);
                    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                }
                /// SUD OUEST
                if (x_souris == joueur[i].x && y_souris < joueur[i].y)
                {
                    animation_attaque_de_base(buffer, map, joueur, i, matrice, nb_joueurs, 0, respiration);
                    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                }
                /// NORD EST
                if (x_souris == joueur[i].x && y_souris > joueur[i].y)
                {
                    animation_attaque_de_base(buffer, map, joueur, i, matrice, nb_joueurs, 2, respiration);
                    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                }
                if (pourcentage_de_chance() < 9)
                {
                    degats = random(1, 5);
                    joueur[id_ennemi].pv = joueur[id_ennemi].pv - degats;
                    joueur[i].degatstotal = joueur[i].degatstotal + degats;
                    attaque = 1; // on a attaqué, on peut sortir de la boucle en infligeant les dégâts, avec le % de chance
                }
                else
                {
                    attaque = 2;
                }
                joueur[i].pa = joueur[i].pa - 1;
                joueur[i].attaque_dispo = 0;
                while ((int)time(NULL) - start < 3)
                {
                    clear_bitmap(buffer);
                    affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
                    affichage_joueurs_respiration_ralenti(buffer, joueur, i, nb_joueurs, matrice, respiration, 5);
                    if (attaque == 1)
                        textprintf_ex(buffer, font, matrice[joueur[id_ennemi].x][joueur[id_ennemi].y].x_bloc - 10, matrice[joueur[id_ennemi].x][joueur[id_ennemi].y].y_bloc  - 70, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "- %d", degats);
                    else if (attaque == 2)
                        textprintf_ex(buffer, font, matrice[joueur[id_ennemi].x][joueur[id_ennemi].y].x_bloc - 10, matrice[joueur[id_ennemi].x][joueur[id_ennemi].y].y_bloc  - 70, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "Attaque manque");
                    display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
                    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                }
            }
            if (mouse_x >= 300 && mouse_x <= 330 && mouse_y >= 670 && mouse_y <= 700 && mouse_b&1)
            {
                attaque = 1; // le joueur a annulé son attaque, l'attaque est considéré comme faite mais sans dégâts
            }
        }
        else
        {
            start = time(NULL);
            while ((int)time(NULL) - start < 2)
            {
                clear_bitmap(buffer);
                affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
                affichage_joueurs_respiration_ralenti(buffer, joueur, i, nb_joueurs, matrice, respiration, 5);
                textprintf_ex(buffer, font, matrice[joueur[i].x][joueur[i].y].x_bloc - strlen("Attaque indisponible") - 30, matrice[joueur[i].x][joueur[i].y].y_bloc  - 70, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "Attaque indisponible");
                display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            }
            attaque = 1;
        }
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(20);
    }
}

/// CRASH POUR LASSASSIN ATTAQUE DE BASE


void sort1(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, BITMAP *buffer_map, t_bloc matrice [23][23], BITMAP *desc_sorts, int x_souris, int y_souris, BITMAP *cursor, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP* map, int respiration[])
{
    switch(joueur[i].id_classe)
    {
    case 1: // GUERRIER
        sort1_guerrier(joueur, i, nb_joueurs, buffer, buffer_map, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts);
        break;
    case 2: // MAGE
        sort1_mage(joueur, i, nb_joueurs, buffer, buffer_map, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts, respiration);
        break;
    case 3: // VAMPIRE
        sort1_vampire(joueur, i, nb_joueurs, buffer, buffer_map, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts, respiration);
        break;
    case 4: // ASSASSIN
        sort1_assassin(joueur, i, nb_joueurs, buffer, buffer_map, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts, respiration);
        break;
    }
}

void sort2(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, BITMAP *buffer_map, t_bloc matrice [23][23], BITMAP *desc_sorts, int x_souris, int y_souris, BITMAP *cursor, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP* map, int respiration[])
{
    switch(joueur[i].id_classe)
    {
    case 1: // GUERRIER
        sort2_guerrier(joueur, i, nb_joueurs, buffer, buffer_map, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts, respiration);
        break;
    case 2: // MAGE
        sort2_mage(joueur, i, nb_joueurs, buffer, buffer_map, matrice, x_souris, y_souris, cursor, map,hud_joueur, icone_classes, hud_icone,desc_sorts, respiration);
        break;
    case 3: // VAMPIRE
        sort2_vampire(joueur, i, nb_joueurs, buffer, buffer_map, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts);
        break;
    case 4: // ASSASSIN
        sort2_assassin(joueur, i, nb_joueurs, buffer, buffer_map, matrice, x_souris, y_souris, cursor, map,hud_joueur, icone_classes, hud_icone,desc_sorts, respiration);
        break;
    }
}

void sort3(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, BITMAP *buffer_map, t_bloc matrice [23][23], BITMAP *desc_sorts, int x_souris, int y_souris, BITMAP *cursor, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP* map, int respiration[])
{
    switch(joueur[i].id_classe)
    {
    case 1: // GUERRIER
        sort3_guerrier(joueur, i, nb_joueurs, buffer, buffer_map, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts);
        break;
    case 2: // MAGE
        sort3_mage(joueur, i, nb_joueurs, buffer, buffer_map, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts, respiration);
        break;
    case 3: // VAMPIRE
        sort3_vampire(joueur, i, nb_joueurs, buffer, buffer_map, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts, respiration);
        break;
    case 4: // ASSASSIN
        sort3_assassin(joueur, i, nb_joueurs, buffer, buffer_map, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts, respiration);
        break;
    }
}

void sort4(BITMAP * buffer_map, BITMAP *map,int *ligne_souris, int *colonne_souris, int *red_mouse, int * green_mouse, int *blue_mouse, t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, t_bloc matrice [23][23], BITMAP *desc_sorts, int x_souris, int y_souris, BITMAP *cursor, BITMAP **hud_joueur, BITMAP *hud_icone, BITMAP **icone_classes, int respiration[])
{
    switch(joueur[i].id_classe)
    {
    case 1: // GUERRIER
        sort4_guerrier(joueur, i, nb_joueurs, buffer, buffer_map, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts, respiration);
        break;
    case 2: // MAGE
        sort4_mage(buffer_map, map, cursor, buffer, joueur, i, matrice, red_mouse, green_mouse, blue_mouse, ligne_souris, colonne_souris,nb_joueurs, hud_icone, desc_sorts, hud_joueur, icone_classes);
        break;
    case 3: // VAMPIRE
        sort4_vampire(buffer_map, map, cursor, buffer, joueur, i, matrice, red_mouse, green_mouse, blue_mouse, ligne_souris,colonne_souris, nb_joueurs, hud_icone, desc_sorts, hud_joueur, icone_classes);
        break;
    case 4: // ASSASSIN
        sort4_assassin(buffer_map, map, cursor, buffer, joueur, i, matrice, red_mouse, green_mouse, blue_mouse, ligne_souris, colonne_souris, nb_joueurs, hud_icone, desc_sorts, hud_joueur, icone_classes);
        break;
    }
}

void selection_sort(BITMAP * buffer_map,int *ligne_souris, int *colonne_souris,int *red_mouse, int *green_mouse, int *blue_mouse, t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, t_bloc matrice [23][23], BITMAP *desc_sorts, int x_souris, int y_souris, BITMAP *cursor, BITMAP *map, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, int respiration_joueur[])
{
    /// On met des rest avant et après l'appel du programme pour bien qu'il y ait un clique : la pause est suffisante pour stopper un moment sans repasser dans la boucle
    if (mouse_x >= 300 && mouse_x <= 330 && mouse_y >= 670 && mouse_y <= 700 && mouse_b&1) // attaque de base
    {
        rest(80);
        attaque_de_base(joueur, i, nb_joueurs, buffer, buffer_map, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts, respiration_joueur);
        rest(80);
    }
    if (mouse_x >= 335 && mouse_x <= 365 && mouse_y >= 670 && mouse_y <= 700 && mouse_b&1) // sort 1
    {
        rest(80);
        sort1(joueur, i, nb_joueurs, buffer, buffer_map, matrice, desc_sorts, x_souris, y_souris, cursor, hud_joueur, icone_classes, hud_icone, map, respiration_joueur);
        rest(80);
    }
    if (mouse_x >= 370 && mouse_x <= 400 && mouse_y >= 670 && mouse_y <= 700 && mouse_b&1) // sort 2
    {
        rest(80);
        sort2(joueur, i, nb_joueurs, buffer, buffer_map, matrice, desc_sorts, x_souris, y_souris, cursor, hud_joueur, icone_classes, hud_icone, map, respiration_joueur);
        rest(80);
    }
    if (mouse_x >= 405 && mouse_x <= 435 && mouse_y >= 670 && mouse_y <= 700 && mouse_b&1) // sort 3
    {
        rest(80);
        sort3(joueur, i, nb_joueurs, buffer, buffer_map, matrice, desc_sorts, x_souris, y_souris, cursor, hud_joueur, icone_classes, hud_icone, map, respiration_joueur);
        rest(80);
    }
    if (mouse_x >= 440 && mouse_x <= 470 && mouse_y >= 670 && mouse_y <= 700 && mouse_b&1) // sort 4
    {
        rest(80);
        sort4(buffer_map, map,ligne_souris,colonne_souris, red_mouse, green_mouse, blue_mouse,joueur, i, nb_joueurs, buffer, matrice, desc_sorts, x_souris, y_souris, cursor, hud_joueur, hud_icone, icone_classes, respiration_joueur);
        rest(80);
    }
}
