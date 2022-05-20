#include "../prototypes.h"
#include "../structures.h"

void sort1_guerrier(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, BITMAP *buffer_map, t_bloc matrice[23][23], int x_souris, int y_souris, BITMAP *cursor, BITMAP *map, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP *desc_sorts, int respiration_joueur[])
{
    time_t start = (int)(time(NULL));
    //time_t start = time(NULL);
    /// tant qu'on ne clique pas sur l'icone de l'attaque de base, ou qu'on a lancé l'attaque
    //L'attaque se une fois le while franchi
    if (pourcentage_de_chance() < 9 && joueur[i].pa >= 2 && !joueur[i].compteur_bouclier)
    {
        joueur[i].pa = joueur[i].pa - 2;
        joueur[i].bouclier = 1;
        joueur[i].compteur_bouclier = 1;
        joueur[i].pv += 15;
        if (joueur[i].pv >= 70)
        {
            textprintf_ex(buffer, font, mouse_x - 10, mouse_y - 70, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "PV MAX atteints !");
        }
        else
        {
            while ((int)(time(NULL) - start < 1))
            {
                clear_bitmap(buffer);
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

void sort2_guerrier(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, BITMAP *buffer_map, t_bloc matrice[23][23], int x_souris, int y_souris, BITMAP *cursor, BITMAP *map, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP *desc_sorts, int respiration_joueur[])
{
    BITMAP *buffer_pixels;
    buffer_pixels = create_bitmap(SCREEN_W,SCREEN_H);
    int red_temp, green_temp,blue_temp;
    int red_temp1, green_temp1,blue_temp1;
    int attaque = 0;
    int attaque_reussie;
    time_t start = time(NULL);
    /// tant qu'on ne clique pas sur l'icone de l'attaque de base, ou qu'on a lancé l'attaque
    while (!attaque)
    {
        clear_bitmap(buffer);
        affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
        dessin_ligne(joueur, i, nb_joueurs, buffer, buffer_pixels, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts, 2);
        dessin_diagonales(joueur, i, nb_joueurs, buffer, buffer_pixels, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts, 1);
        affichage_joueurs(buffer, joueur, i, nb_joueurs, matrice);

        display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        /// recupere la place de la souris sur la map (le bloc)
        lecture_pixels_buffer_map(buffer_map, &red_temp, &green_temp,&blue_temp);
        reperage_bloc_souris(&x_souris, &y_souris, red_temp, green_temp, blue_temp, matrice, joueur, i);
        lecture_pixels_buffer_map(buffer_pixels, &red_temp1, &green_temp1,&blue_temp1);
        // on attaque le joueur ennemi1 sur on clique et que la souris est sur lui
        if (matrice[x_souris][y_souris].occuper != matrice[joueur[i].x][joueur[i].y].occuper && matrice[x_souris][y_souris].occuper != 0 && mouse_b&1 && green_temp1 == 140)
        {
            int id_ennemi = matrice[x_souris][y_souris].id_case - 1;
            int degats = random(joueur[i].classe.spell[1].degats_min, joueur[i].classe.spell[1].degats_max);
            /// NORD OUEST
            if (x_souris < joueur[i].x && y_souris == joueur[i].y)
            {
                joueur[i].direction = 1;
                animation_attaque_de_base(buffer, map, joueur, i, matrice, nb_joueurs, 1, respiration_joueur);
            }
            /// SUD EST
            if (x_souris > joueur[i].x && y_souris == joueur[i].y)
            {
                joueur[i].direction = 3;
                animation_attaque_de_base(buffer, map, joueur, i, matrice, nb_joueurs, 3, respiration_joueur);
            }
            /// SUD OUEST
            if (x_souris == joueur[i].x && y_souris < joueur[i].y)
            {
                joueur[i].direction = 0;
                animation_attaque_de_base(buffer, map, joueur, i, matrice, nb_joueurs, 0, respiration_joueur);
            }
            /// NORD EST
            if (x_souris == joueur[i].x && y_souris > joueur[i].y)
            {
                joueur[i].direction = 2;
                animation_attaque_de_base(buffer, map, joueur, i, matrice, nb_joueurs, 2, respiration_joueur);
            }
            if (pourcentage_de_chance() < 8 && joueur[i].pa >= 4)
            {
                joueur[id_ennemi].pv = joueur[id_ennemi].pv - degats;
                joueur[i].pa = joueur[i].pa - 4;
                attaque_reussie = 1;
            }
            else
            {
                joueur[i].pa = joueur[i].pa - 4;
                attaque_reussie = 0;
            }

            while ((int)time(NULL) - start < 3)
            {
                clear_bitmap(buffer);
                affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
                affichage_joueurs_respiration(buffer, joueur, i, nb_joueurs, matrice, respiration_joueur, 5);
                if (attaque_reussie)
                    textprintf_ex(buffer, font, matrice[joueur[id_ennemi].x][joueur[id_ennemi].y].x_bloc - 10, matrice[joueur[id_ennemi].x][joueur[id_ennemi].y].y_bloc  - 70, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "- %d", degats);
                else
                    textprintf_ex(buffer, font, matrice[joueur[id_ennemi].x][joueur[id_ennemi].y].x_bloc - 10, matrice[joueur[id_ennemi].x][joueur[id_ennemi].y].y_bloc  - 70, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "Attaque manque");
                display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            }
            attaque = 1;
        }
        if (mouse_x >= 370 && mouse_x <= 400 && mouse_y >= 670 && mouse_y <= 700 && mouse_b&1)
        {
            attaque = 1; // le joueur a annulé son attaque, l'attaque est considéré comme faite mais sans dégâts
        }
    }
}

void sort3_guerrier(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, BITMAP *buffer_map, t_bloc matrice[23][23], int x_souris, int y_souris, BITMAP *cursor, BITMAP *map, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP *desc_sorts, int respiration_joueur[])
{
    BITMAP *buffer_pixels = create_bitmap(SCREEN_W, SCREEN_H);
    int attaque = 0;
    int red_temp, green_temp,blue_temp;
    int red_temp1, green_temp1,blue_temp1;
    int attaque_reussie;
    time_t start = time(NULL);
    /// tant qu'on ne clique pas sur l'icone de l'attaque de base, ou qu'on a lancé l'attaque
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
        lecture_pixels_buffer_map(buffer_pixels, &red_temp1, &green_temp1,&blue_temp1);
        // on attaque le joueur ennemi1 sur on clique et que la souris est sur lui
        if (matrice[x_souris][y_souris].occuper != matrice[joueur[i].x][joueur[i].y].occuper && matrice[x_souris][y_souris].occuper != 0 && mouse_b&1 && green_temp1 == 140)
        {
            int id_ennemi = matrice[x_souris][y_souris].id_case - 1;
            /// NORD OUEST
            if (x_souris < joueur[i].x && y_souris == joueur[i].y)
            {
                joueur[i].direction = 1;
                animation_attaque_de_base(buffer, map, joueur, i, matrice, nb_joueurs, 1, respiration_joueur);
            }
            /// SUD EST
            if (x_souris > joueur[i].x && y_souris == joueur[i].y)
            {
                joueur[i].direction = 3;
                animation_attaque_de_base(buffer, map, joueur, i, matrice, nb_joueurs, 3, respiration_joueur);
            }
            /// SUD OUEST
            if (x_souris == joueur[i].x && y_souris < joueur[i].y)
            {
                joueur[i].direction = 0;
                animation_attaque_de_base(buffer, map, joueur, i, matrice, nb_joueurs, 0, respiration_joueur);
            }
            /// NORD EST
            if (x_souris == joueur[i].x && y_souris > joueur[i].y)
            {
                joueur[i].direction = 2;
                animation_attaque_de_base(buffer, map, joueur, i, matrice, nb_joueurs, 2, respiration_joueur);
            }
            if (pourcentage_de_chance() < 7 && joueur[i].pa >= 4)
            {
                joueur[id_ennemi].pv = joueur[id_ennemi].pv - random(4, 8);
                joueur[id_ennemi].rage = 1;
                joueur[id_ennemi].compteur_rage = 1;
                joueur[i].pa = joueur[i].pa - 4;
                attaque_reussie = 1;
            }
            else
            {
                joueur[i].pa = joueur[i].pa - 4;
                attaque_reussie = 0;
            }

            while ((int)time(NULL) - start < 3)
            {
                clear_bitmap(buffer);
                affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
                affichage_joueurs_respiration(buffer, joueur, i, nb_joueurs, matrice, respiration_joueur, 5);
                if (attaque_reussie)
                    textprintf_ex(buffer, font, matrice[joueur[id_ennemi].x][joueur[id_ennemi].y].x_bloc - 10, matrice[joueur[id_ennemi].x][joueur[id_ennemi].y].y_bloc  - 70, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "Inflige Hemorragie");
                else
                    textprintf_ex(buffer, font, matrice[joueur[id_ennemi].x][joueur[id_ennemi].y].x_bloc - 10, matrice[joueur[id_ennemi].x][joueur[id_ennemi].y].y_bloc  - 70, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "Attaque manque");
                display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            }
            attaque = 1;
        }
        if (mouse_x >= 405 && mouse_x <= 435 && mouse_y >= 670 && mouse_y <= 700 && mouse_b&1)
        {
            attaque = 1; // le joueur a annulé son attaque, l'attaque est considéré comme faite mais sans dégâts
        }
    }
}

void sort4_guerrier(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, BITMAP *buffer_map, t_bloc matrice[23][23], int x_souris, int y_souris, BITMAP *cursor, BITMAP *map, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP *desc_sorts, int respiration_joueur[])
{
    time_t start = (int)(time(NULL));
    //time_t start = time(NULL);
    /// tant qu'on ne clique pas sur l'icone de l'attaque de base, ou qu'on a lancé l'attaque
    //L'attaque se une fois le while franchi
    if (pourcentage_de_chance() < 6 && joueur[i].pa >= 5)
    {
        joueur[i].pa = joueur[i].pa - 5;
        joueur[i].rage = 1;
        joueur[i].compteur_rage = 1;
            while ((int)(time(NULL) - start < 1))
            {
                clear_bitmap(buffer);
                affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
                //dessin_bloc_unique(buffer, joueur[i].x, joueur[i].y, matrice, 0, 220, 0);
                affichage_joueurs_respiration(buffer, joueur, i, nb_joueurs, matrice, respiration_joueur, 5);
                textout_ex(buffer, font,"Rage !", matrice[joueur[i].x][joueur[i].y].x_bloc - 15, matrice[joueur[i].x][joueur[i].y].y_bloc - 80, makecol(0,0,0), -1);
                display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                rest(80);
                // on attaque le joueur ennemi1 sur on clique et que la souris est sur lui
            }

    }
    else
    {
        while ((int)(time(NULL) - start < 2))
        {
            clear_bitmap(buffer);
            affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
            //dessin_bloc_unique(buffer, joueur[i].x, joueur[i].y, matrice, 0, 220, 0);
            affichage_joueurs_respiration(buffer, joueur, i, nb_joueurs, matrice, respiration_joueur, 5);
            textout_ex(buffer, font,"SORT MANQUE !", matrice[joueur[i].x][joueur[i].y].x_bloc - 15, matrice[joueur[i].x][joueur[i].y].y_bloc - 80, makecol(0,0,0), -1);
            display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            // on attaque le joueur ennemi1 sur on clique et que la souris est sur lui
        }
    }
}
