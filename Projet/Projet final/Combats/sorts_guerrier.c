#include "../prototypes.h"
#include "../structures.h"

void sort1_guerrier(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, BITMAP *buffer_map, t_bloc matrice[23][23], int x_souris, int y_souris, BITMAP *cursor, BITMAP *map, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP *desc_sorts, int respiration_joueur[])
{
    BITMAP *buffer_pixels;
    buffer_pixels = create_bitmap(SCREEN_W,SCREEN_H);
    int attaque = 0;
    int num_bitmap = 0;
    time_t start = (int)(time(NULL));
    //time_t start = time(NULL);
    /// tant qu'on ne clique pas sur l'icone de l'attaque de base, ou qu'on a lanc� l'attaque
    //L'attaque se une fois le while franchi
    if (pourcentage_de_chance() < 9 && joueur[i].pa >= 2)
    {
        joueur[i].pa = joueur[i].pa - 2;
        if (joueur[i].pv >= 70)
        {
            textprintf_ex(buffer, font, mouse_x - 10, mouse_y - 70, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "PV MAX atteints !");
        }
        else
        {
            joueur[i].pv += 15;
            while ((int)(time(NULL) - start < 1))
            {
                clear_bitmap(buffer);
                joueur[i].bouclier = 1;
                affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
                //dessin_bloc_unique(buffer, joueur[i].x, joueur[i].y, matrice, 0, 220, 0);
                affichage_joueurs_respiration(buffer, joueur, i, nb_joueurs, matrice, respiration_joueur, 5);
                display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                rest(80);
                // on attaque le joueur ennemi1 sur on clique et que la souris est sur lui
            }
        }

    }
}

void sort2_guerrier(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, BITMAP *buffer_map, t_bloc matrice[23][23], int x_souris, int y_souris, BITMAP *cursor, BITMAP *map, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP *desc_sorts)
{
    BITMAP *buffer_pixels;
    buffer_pixels = create_bitmap(SCREEN_W,SCREEN_H);
    int red_temp, green_temp,blue_temp;
    int attaque = 0;
    int ennemi1 = i + 1;
    int ennemi2;
    int ennemi3;
    if (nb_joueurs == 3)
        ennemi2 = i + 2;
    if (nb_joueurs == 4)
        ennemi3 = i + 3;
    //time_t start = time(NULL);
    /// tant qu'on ne clique pas sur l'icone de l'attaque de base, ou qu'on a lanc� l'attaque
    while (!attaque)
    {
        clear_bitmap(buffer);
        affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
        dessin_ligne(joueur, i, nb_joueurs, buffer, buffer_pixels, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts, 2);
        dessin_diagonales(joueur, i, nb_joueurs, buffer, buffer_pixels, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts, 1);
        affichage_joueurs(buffer, joueur, i, nb_joueurs, matrice);

        display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        lecture_pixels_buffer_map(buffer_map, &red_temp, &green_temp,&blue_temp);
        reperage_bloc_souris(&x_souris, &y_souris, red_temp, green_temp, blue_temp, matrice, joueur, i);
        // on attaque le joueur ennemi1 sur on clique et que la souris est sur lui
        if (matrice[x_souris][y_souris].occuper != matrice[joueur[i].x][joueur[i].y].occuper && matrice[x_souris][y_souris].occuper != 0 && mouse_b&1)
        {
            int id_ennemi = matrice[x_souris][y_souris].occuper - 1;
            if (pourcentage_de_chance() < 9)
            {
                textprintf_ex(buffer, font, mouse_x - 10, mouse_y - 70, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "- %d", joueur[i].classe.spell[1].degats_max);
            }
            else
            {
                textprintf_ex(buffer, font, mouse_x - 10, mouse_y - 70, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "Attaque manqu�");
            }
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest(300);
            attaque = 1;
        }
        if (mouse_x >= 370 && mouse_x <= 400 && mouse_y >= 670 && mouse_y <= 700 && mouse_b&1)
        {
            attaque = 1; // le joueur a annul� son attaque, l'attaque est consid�r� comme faite mais sans d�g�ts
        }
    }
}

void sort3_guerrier(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, BITMAP *buffer_map, t_bloc matrice[23][23], int x_souris, int y_souris, BITMAP *cursor, BITMAP *map, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP *desc_sorts)
{
    BITMAP *buffer_pixels = create_bitmap(SCREEN_W, SCREEN_H);
    int attaque = 0;
    int red_temp, green_temp,blue_temp;
    int ennemi1 = i + 1;
    int ennemi2;
    int ennemi3;
    if (nb_joueurs == 3)
        ennemi2 = i + 2;
    if (nb_joueurs == 4)
        ennemi3 = i + 3;
    //time_t start = time(NULL);
    /// tant qu'on ne clique pas sur l'icone de l'attaque de base, ou qu'on a lanc� l'attaque
    while (!attaque)
    {
        clear_bitmap(buffer);
        affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
        dessin_ligne(joueur, i, nb_joueurs, buffer, buffer_pixels, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts, 2);
        affichage_joueurs(buffer, joueur, i, nb_joueurs, matrice);

        display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        lecture_pixels_buffer_map(buffer_map, &red_temp, &green_temp,&blue_temp);
        reperage_bloc_souris(&x_souris, &y_souris, red_temp, green_temp, blue_temp, matrice, joueur, i);
        // on attaque le joueur ennemi1 sur on clique et que la souris est sur lui
        if (matrice[x_souris][y_souris].occuper != matrice[joueur[i].x][joueur[i].y].occuper && matrice[x_souris][y_souris].occuper != 0 && mouse_b&1)
        {
            if (pourcentage_de_chance() < 8)
            {
                textprintf_ex(buffer, font, mouse_x - 5, mouse_y - 50, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "Inflige hemorragie");
            }
            else
            {
                textprintf_ex(buffer, font, mouse_x - 5, mouse_y - 50, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "Attaque manque");
            }
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest(300);
        }
        if (mouse_x >= 405 && mouse_x <= 435 && mouse_y >= 670 && mouse_y <= 700 && mouse_b&1)
        {
            attaque = 1; // le joueur a annul� son attaque, l'attaque est consid�r� comme faite mais sans d�g�ts
        }
    }
}

void sort4_guerrier(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, BITMAP *buffer_map, t_bloc matrice[23][23], int x_souris, int y_souris, BITMAP *cursor, BITMAP *map, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP *desc_sorts, int respiration_joueur[])
{
    int attaque = 0;
    int red_temp, green_temp,blue_temp;
    //time_t start = time(NULL);
    clear_bitmap(buffer);
    affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
    /// ANIMATION A FAIRE
    //dessin_bloc_unique(buffer, joueur[i].x, joueur[i].y, matrice, 0, 220, 0);
    affichage_joueurs_respiration(buffer, joueur, i, nb_joueurs, matrice, respiration_joueur, i);
    if (!joueur[i].rage)
    {
        joueur[i].rage = 1;
        joueur[i].compteur_rage = 1;
        textprintf_ex(buffer, font, matrice[joueur[i].x][joueur[i].y].x_bloc - 5, matrice[joueur[i].x][joueur[i].y].y_bloc - 50, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "Effet de rage!");
        display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(300);
        lecture_pixels_buffer_map(buffer_map, &red_temp, &green_temp,&blue_temp); /// recupere position de la souris par rapport aux couleurs sur le buffer
        reperage_bloc_souris(&x_souris, &y_souris, red_temp, green_temp, blue_temp, matrice, joueur, i); /// repere la couleur du bloc sous la souris grace a la ligne d avant
    }
    else
    {
        textprintf_ex(buffer, font, matrice[joueur[i].x][joueur[i].y].x_bloc - 5, matrice[joueur[i].x][joueur[i].y].y_bloc - 50, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "Effet de rage!");
        display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(300);
        lecture_pixels_buffer_map(buffer_map, &red_temp, &green_temp,&blue_temp); /// recupere position de la souris par rapport aux couleurs sur le buffer
        reperage_bloc_souris(&x_souris, &y_souris, red_temp, green_temp, blue_temp, matrice, joueur, i); /// repere la couleur du bloc sous la souris grace a la ligne d avant
    }

    // on attaque le joueur ennemi1 sur on clique et que la souris est sur lui

}
