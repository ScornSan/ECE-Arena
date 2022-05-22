#include "../prototypes.h"
#include "../structures.h"

void sort1_assassin(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, BITMAP *buffer_map, t_bloc matrice[23][23], int x_souris, int y_souris, BITMAP *cursor, BITMAP *map, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP *desc_sorts, int respiration_joueur[])
{
    time_t start = (int)(time(NULL));
    int num_bitmap = 0;
    /// tant qu'on ne clique pas sur l'icone de l'attaque de base, ou qu'on a lancé l'attaque
    if (joueur[i].pa >= 2 && joueur[i].classe.spell[0].dispo && !joueur[i].lucide)
    {
        joueur[i].classe.spell[0].dispo = 0;
        if (pourcentage_de_chance() < 8)
        {
            while ((int)(time(NULL)) - start < 2)
            {
                clear_bitmap(buffer);
                affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
                affichage_joueurs_respiration_ralenti(buffer, joueur, i, nb_joueurs, matrice, respiration_joueur, 5);
                draw_sprite(buffer, joueur[i].classe.spell[0].animation_sort[num_bitmap], matrice[joueur[i].x][joueur[i].y].x_bloc - 20,  matrice[joueur[i].x][joueur[i].y].y_bloc - 60);
                num_bitmap = (num_bitmap + 1) % 4;
                if (joueur[i].pm == 3 && joueur[i].pa == 6)
                {
                    textprintf_ex(buffer, font, matrice[joueur[i].x][joueur[i].y].x_bloc - 10, matrice[joueur[i].x][joueur[i].y].y_bloc - 80, makecol(0,0,0), -1, "PM et PA max atteints !");
                }
                else
                {
                    textprintf_ex(buffer, font, matrice[joueur[i].x][joueur[i].y].x_bloc - 10, matrice[joueur[i].x][joueur[i].y].y_bloc - 65, makecol(0,0,0), -1, " PM + 3!");
                    textprintf_ex(buffer, font, matrice[joueur[i].x][joueur[i].y].x_bloc - 10, matrice[joueur[i].x][joueur[i].y].y_bloc - 80, makecol(0,0,0), -1, " PA + 3!");
                }
                display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            }
            if (joueur[i].pa +2 > 6)
            {
                joueur[i].pa = 6;
            }
            else
            {
                joueur[i].pa += 2;
            }
            if (joueur[i].pm +2 > 3)
            {
                joueur[i].pm = 3;
            }
            else
            {
                joueur[i].pm += 2;
            }

        }
        else
        {
            while ((int)(time(NULL)) - start < 2)
            {
                clear_bitmap(buffer);
                affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
                affichage_joueurs_respiration_ralenti(buffer, joueur, i, nb_joueurs, matrice, respiration_joueur, 5);
                textout_ex(buffer, font,"SORT MANQUE !", matrice[joueur[i].x][joueur[i].y].x_bloc - 15, matrice[joueur[i].x][joueur[i].y].y_bloc - 80, makecol(0,0,0), -1);
                display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                // on attaque le joueur ennemi1 sur on clique et que la souris est sur lui
            }
        }
    }
    else
    {
        start = time(NULL);
        while ((int)time(NULL) - start < 2)
        {
            clear_bitmap(buffer);
            affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
            affichage_joueurs_respiration(buffer, joueur, i, nb_joueurs, matrice, respiration_joueur, 5);
            textprintf_ex(buffer, font, matrice[joueur[i].x][joueur[i].y].x_bloc - strlen("Attaque indisponible") - 30, matrice[joueur[i].x][joueur[i].y].y_bloc  - 70, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "Attaque indisponible");
            display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        }
    }
}

void sort2_assassin(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, BITMAP* buffer_map, t_bloc matrice[23][23], int x_souris, int y_souris, BITMAP *cursor, BITMAP *map, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP *desc_sorts, int respiration[])
{
    int attaque = 0;
    BITMAP *buffer_pixels;
    buffer_pixels = create_bitmap(SCREEN_W,SCREEN_H);
    int red_temp, green_temp, blue_temp;
    int red_temp1, green_temp1, blue_temp1;
    int longueur_ligne = 4;
    int id_ennemi;
    time_t start = time(NULL);

    while(!attaque)
    {
        if (joueur[i].pa >= 4 && joueur[i].classe.spell[1].dispo)
        {
            clear_bitmap(buffer);
            blit(map, buffer, 0,0,0,0, SCREEN_W,SCREEN_H);
            affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
            ///dessin limite zone d'attaque autour du perso
            dessin_ligne(joueur, i, nb_joueurs, buffer, buffer_pixels, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts, longueur_ligne);
            affichage_joueurs_respiration(buffer, joueur, i, nb_joueurs, matrice, respiration, 5);
            display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);

            lecture_pixels_buffer_map(buffer_map, &red_temp, &green_temp,&blue_temp); /// recupere position de la souris par rapport aux couleurs sur le buffer
            reperage_bloc_souris(&x_souris, &y_souris, red_temp, green_temp, blue_temp, matrice, joueur, i); /// repere la couleur du bloc sous la souris grace a la ligne d avant
            lecture_pixels_buffer_map(buffer_pixels, &red_temp1, &green_temp1,&blue_temp1); /// recupere position de la souris par rapport aux couleurs sur le buffer
            if (matrice[x_souris][y_souris].occuper != matrice[joueur[i].x][joueur[i].y].occuper && matrice[x_souris][y_souris].occuper != 0 && mouse_b&1 && green_temp1 == 140)
            {
                id_ennemi = matrice[x_souris][y_souris].id_case - 1;
                //printf("Ennemi : %d\n", id_ennemi);
                /// NORD OUEST
                if (x_souris < joueur[i].x && y_souris == joueur[i].y)
                {
                    animation_sort2_assassin(buffer, map, joueur, i, matrice, nb_joueurs, 1, respiration, x_souris, y_souris, 1);
                }
                /// SUD EST
                if (x_souris > joueur[i].x && y_souris == joueur[i].y)
                {
                    animation_sort2_assassin(buffer, map, joueur, i, matrice, nb_joueurs, 3, respiration, x_souris, y_souris, 1);
                }
                /// SUD OUEST
                if (x_souris == joueur[i].x && y_souris < joueur[i].y)
                {
                    animation_sort2_assassin(buffer, map, joueur, i, matrice, nb_joueurs, 0, respiration, x_souris, y_souris, 1);
                }
                /// NORD EST
                if (x_souris == joueur[i].x && y_souris > joueur[i].y)
                {
                    animation_sort2_assassin(buffer, map, joueur, i, matrice, nb_joueurs, 2, respiration, x_souris, y_souris, 1);
                }
                /// ATTAQUE
                start = time(NULL);
                joueur[i].pa = joueur[i].pa - 4;
                if (pourcentage_de_chance() < 7)
                {
                    int degats = random(4, 8);
                    joueur[id_ennemi].pv  = joueur[id_ennemi].pv - degats;
                    joueur[i].degatstotal = joueur[i].degatstotal + degats;
                    while ((int)time(NULL) - start < 2)
                    {
                        clear_bitmap(buffer);
                        blit(map, buffer, 0,0,0,0, SCREEN_W,SCREEN_H);
                        affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
                        affichage_joueurs_respiration(buffer, joueur, i, nb_joueurs, matrice, respiration, 5);
                        textprintf_ex(buffer, font, matrice[joueur[id_ennemi].x][joueur[id_ennemi].y].x_bloc - 10, matrice[joueur[id_ennemi].x][joueur[id_ennemi].y].y_bloc - 70, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "- %d", degats);
                        display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
                        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                    }
                }
                else
                {
                    while ((int)time(NULL) - start < 2)
                    {
                        clear_bitmap(buffer);
                        blit(map, buffer, 0,0,0,0, SCREEN_W,SCREEN_H);
                        affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
                        affichage_joueurs_respiration(buffer, joueur, i, nb_joueurs, matrice, respiration, 5);
                        textprintf_ex(buffer, font, matrice[joueur[id_ennemi].x][joueur[id_ennemi].y].x_bloc - 10, matrice[joueur[id_ennemi].x][joueur[id_ennemi].y].y_bloc - 70, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "Attaque manque !");
                        display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
                        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                    }
                }
                attaque = 1; // on a attaqué, on peut sortir de la boucle en infligeant les dégâts, avec le % de chance
            }
            if (mouse_x >= 370 && mouse_x <= 400 && mouse_y >= 670 && mouse_y <= 700 && mouse_b&1)
            {
                attaque = 1; // le joueur a annulé son attaque, l'attaque est considéré comme faite mais sans dégâts
            }
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        }
        else
        {
            start = time(NULL);
            while ((int)time(NULL) - start < 2)
            {
                clear_bitmap(buffer);
                affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
                affichage_joueurs_respiration(buffer, joueur, i, nb_joueurs, matrice, respiration, 5);
                textprintf_ex(buffer, font, matrice[joueur[i].x][joueur[i].y].x_bloc - strlen("Attaque indisponible") - 30, matrice[joueur[i].x][joueur[i].y].y_bloc  - 70, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "Attaque indisponible");
                display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            }
            attaque = 1;
        }
    }
}

void sort3_assassin(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, BITMAP *buffer_map, t_bloc matrice[23][23], int x_souris, int y_souris, BITMAP *cursor, BITMAP *map, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP *desc_sorts, int respiration_joueur[])
{
    time_t start = (int)(time(NULL));
    int num_bitmap = 0;
    /// tant qu'on ne clique pas sur l'icone de l'attaque de base, ou qu'on a lancé l'attaque
    if (joueur[i].classe.spell[2].dispo && !joueur[i].invincible && joueur[i].pa >= 4)
    {
        joueur[i].pa = joueur[i].pa - 4;
        if (pourcentage_de_chance() < 6)
        {
            joueur[i].invincible = 1;
            joueur[i].compteur_invincible = 1;
            while ((int)(time(NULL)) - start < 2)
            {
                clear_bitmap(buffer);
                affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
                affichage_joueurs_respiration_ralenti(buffer, joueur, i, nb_joueurs, matrice, respiration_joueur, 5);
                textout_ex(buffer, font,"Applique invincibilite !", matrice[joueur[i].x][joueur[i].y].x_bloc - 15, matrice[joueur[i].x][joueur[i].y].y_bloc - 80, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1);
                draw_sprite(buffer, joueur[i].classe.spell[0].animation_sort[num_bitmap], matrice[joueur[i].x][joueur[i].y].x_bloc - 20,  matrice[joueur[i].x][joueur[i].y].y_bloc - 60);
                num_bitmap = (num_bitmap + 1) % 4;
                display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            }
        }
        else
        {
            while ((int)(time(NULL)) - start < 2)
            {
                clear_bitmap(buffer);
                affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
                affichage_joueurs_respiration_ralenti(buffer, joueur, i, nb_joueurs, matrice, respiration_joueur, 5);
                textout_ex(buffer, font,"SORT MANQUE !", matrice[joueur[i].x][joueur[i].y].x_bloc - 15, matrice[joueur[i].x][joueur[i].y].y_bloc - 80, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1);
                display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                // on attaque le joueur ennemi1 sur on clique et que la souris est sur lui
            }
        }
    }
    else
    {
        while ((int)(time(NULL)) - start < 2)
        {
            clear_bitmap(buffer);
            affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
            affichage_joueurs_respiration_ralenti(buffer, joueur, i, nb_joueurs, matrice, respiration_joueur, 5);
            textout_ex(buffer, font,"Attaque indisponible !", matrice[joueur[i].x][joueur[i].y].x_bloc - 15, matrice[joueur[i].x][joueur[i].y].y_bloc - 80, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1);
            display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        }
    }

}


void sort4_assassin(BITMAP *buffer_map, BITMAP * map,BITMAP * cursor, BITMAP *buffer, t_joueur* joueur, int i, t_bloc matrice[23][23], int *red_mouse, int * green_mouse, int *blue_mouse, int *ligne_souris,
                    int *colonne_souris, int nb_joueurs, BITMAP * hud_icone, BITMAP * desc_sorts, BITMAP **hud_joueur, BITMAP **icone_classes, int respiration[])
{
    int sort_lance = 0;
    int annulation = 0;
    int tab[3] = {0,0,0};
    time_t start = time(NULL);
    if( !joueur[i].classe.spell[3].dispo)
    {
        while ((int)time(NULL) - start < 2)
        {
            clear_bitmap(buffer);
            affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
            affichage_joueurs_respiration_ralenti(buffer, joueur, i, nb_joueurs, matrice, respiration, 5);
            textprintf_ex(buffer, font, matrice[joueur[i].x][joueur[i].y].x_bloc - strlen("Attaque indisponible") - 30, matrice[joueur[i].x][joueur[i].y].y_bloc  - 70, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "Attaque indisponible");
            display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        }
    }
    else
    {
        while(sort_lance == 0 && annulation == 0)
        {
            if(mouse_b &1 && (abs(joueur[i].x - *ligne_souris) + abs(joueur[i].y - *colonne_souris)) <= 3 && matrice[*ligne_souris][*colonne_souris].accessible)
            {
                joueur[i].classe.spell[3].chance = random(joueur[i].classe.spell[3].degats_min,joueur[i].classe.spell[3].degats_max);
                if (pourcentage_de_chance() < 6 && joueur[i].pa >= 5)
                {
                    sort_lance = 1;
                    /// NORD OUEST
                    if (*ligne_souris < joueur[i].x)
                    {
                        joueur[i].direction = 1;
                    }
                    /// SUD OUEST
                    else if (*colonne_souris < joueur[i].y)
                    {
                        joueur[i].direction = 0;
                    }
                    /// SUD EST
                    if (*ligne_souris >= joueur[i].x)
                    {
                        joueur[i].direction = 3;
                    }
                    /// NORD EST
                    if (*colonne_souris >= joueur[i].y)
                    {
                        joueur[i].direction = 2;
                    }
                }
                else
                {
                    start = time(NULL);
                    while ((int)time(NULL) - start < 2)
                    {
                        clear_bitmap(buffer);
                        blit(map, buffer, 0,0,0,0, SCREEN_W,SCREEN_H);
                        affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
                        affichage_joueurs_respiration_ralenti(buffer, joueur, i, nb_joueurs, matrice, respiration, 5);
                        textprintf_ex(buffer, font, matrice[joueur[i].x][joueur[i].y].x_bloc - 10, matrice[joueur[i].x][joueur[i].y].y_bloc - 70, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "Attaque manque !");
                        display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
                        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                    }
                    joueur[i].pa = joueur[i].pa - 5;
                    joueur[i].classe.spell[3].dispo = 0;
                    annulation = 1;
                }
            }
            else if((mouse_b &1 && mouse_x >= 280 && mouse_x<= 490 && mouse_y >= 650 && mouse_y <= 720) )
            {
                annulation = 1;
            }
            else
            {
                blit(map, buffer, 0,0,0,0, SCREEN_W, SCREEN_H);
                textprintf_ex(buffer, font, 0, 0, makecol(0, 0, 0), -1, "Mouse X : %d", mouse_x);
                textprintf_ex(buffer, font, 0, 10, makecol(0, 0, 0), -1, "Mouse Y : %d", mouse_y);
                lecture_pixels_buffer_map(buffer_map, red_mouse, green_mouse, blue_mouse);
                reperage_bloc_souris(ligne_souris, colonne_souris, *red_mouse, *green_mouse, *blue_mouse, matrice);
                int n = 0;
                if((abs(joueur[i].x - *ligne_souris) + abs(joueur[i].y - *colonne_souris)) <= 3 && matrice[*ligne_souris][*colonne_souris].accessible)
                {
                    for(int k = *ligne_souris-3; k < *ligne_souris+4; k++)
                    {
                        for (int l = *colonne_souris-3; l< *colonne_souris+4; l++)
                        {
                            if(matrice[k][l].accessible == 1 && (k >=0 && k <= 22) && (l >= 0 && l <= 22))
                            {
                                dessin_bloc_unique(buffer, k, l, matrice, 213,210,117);
                                if(matrice[k][l].id_case)
                                {
                                    tab[n] = matrice[k][l].id_case;
                                    n++;
                                }
                            }
                        }
                    }
                }
                affichage_hud_sorts(joueur, i, nb_joueurs, buffer, hud_icone, desc_sorts); // Blit de 5 logos (les mêmes pour la barre d'action, à changer après...)
                affichage_hud_joueur(buffer, hud_joueur, joueur, i,icone_classes);
                affichage_joueurs_respiration(buffer, joueur, i, nb_joueurs, matrice, respiration, 5);
                rest(5);
                display_cursor(cursor, buffer, mouse_x-5, mouse_y-5);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            }
        }
        if (sort_lance == 1)
        {
            for (int l = 0; l<3; l++)
            {
                if (tab[l] != 0 && tab[l]-1 != i)
                {
                    joueur[tab[l]-1].pv = joueur[tab[l]-1].pv - joueur[i].classe.spell[3].chance;
                    joueur[i].degatstotal = joueur[i].degatstotal + joueur[i].classe.spell[3].chance;
                }
            }
            printf("degat %d \n", joueur[i].classe.spell[3].chance);
            joueur[i].pa = joueur[i].pa - 5;
            joueur[i].classe.spell[3].dispo = 0;
            int num_sprites = 0;
            int compteur = 0;
            time_t start = time(NULL);
            while((int)(time(NULL) - start < 4))
            {
                blit(map, buffer, 0,0,0,0, SCREEN_W, SCREEN_H);
                affichage_hud_sorts(joueur, i, nb_joueurs, buffer, hud_icone, desc_sorts); // Blit de 5 logos (les mêmes pour la barre d'action, à changer après...)
                affichage_hud_joueur(buffer, hud_joueur, joueur, i,icone_classes);
                affichage_joueurs_respiration(buffer, joueur, i, nb_joueurs, matrice, respiration, 5);
                draw_sprite(buffer, joueur[i].classe.spell[3].animation_sort[num_sprites], matrice[*ligne_souris][*colonne_souris].x_bloc - 161, matrice[*ligne_souris][*colonne_souris].y_bloc - 100);
                if (compteur == 40)
                {
                    num_sprites = (num_sprites +1) % 4;
                    compteur = 0;
                }
                /*if (joueur[i].classe.spell[3].chance == 8)
                {
                    textout_ex(buffer, font,"COUP CRITIQUE !!", 100, 630, makecol(255,255,255), -1);
                    textout_ex(buffer, font,"-8 ", 30 + rand2, 630 - rand1, makecol(255,255,255), -1);
                }*/
                compteur++;
                display_cursor(cursor, buffer, mouse_x-5, mouse_y-5);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            }
        }
    }
}
