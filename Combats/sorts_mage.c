#include "../prototypes.h"
#include "../structures.h"

void sort1_mage(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, BITMAP *buffer_map, t_bloc matrice[23][23], int x_souris, int y_souris, BITMAP *cursor, BITMAP *map, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP *desc_sorts, int respiration_joueur[])
{
    int num_bitmap = 0;
    time_t start = (int)(time(NULL));
    int attaque = 0;
    //time_t start = time(NULL);
    if (pourcentage_de_chance() < 9 && joueur[i].pa >= 2)
    {
        joueur[i].pv = joueur[i].pv + random(4, 8);
        joueur[i].pa = joueur[i].pa - 2;
        if (joueur[i].pv > 55)
        {
            joueur[i].pv = 55;
        }
        while ((int)(time(NULL) - start < 2))
        {
            clear_bitmap(buffer);
            affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
            //dessin_bloc_unique(buffer, joueur[i].x, joueur[i].y, matrice, 0, 220, 0);
            affichage_joueurs_respiration(buffer, joueur, i, nb_joueurs, matrice, respiration_joueur, 5);
            draw_sprite(buffer, joueur[i].classe.anim_attaques[1][joueur[i].direction][0], matrice[joueur[i].x][joueur[i].y].x_bloc - 22,  matrice[joueur[i].x][joueur[i].y].y_bloc - 52);
            draw_sprite(buffer, joueur[i].classe.spell[0].animation_sort[num_bitmap], matrice[joueur[i].x][joueur[i].y].x_bloc - 20,  matrice[joueur[i].x][joueur[i].y].y_bloc - 60);
            num_bitmap = (num_bitmap + 1) % 4;
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

void sort2_mage(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, BITMAP* buffer_map, t_bloc matrice[23][23], int x_souris, int y_souris, BITMAP *cursor, BITMAP *map, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP *desc_sorts)
{
    int attaque = 0;
    BITMAP *buffer_pixels;
    buffer_pixels = create_bitmap(1280,720);
    int sort_lance = 0;
    int annulation = 0;
    int red_temp, green_temp, blue_temp;
    int longueur_ligne = 4;
    int id_ennemi;

    while(!attaque)
    {
        clear_bitmap(buffer);

        blit(map, buffer, 0,0,0,0, SCREEN_W,SCREEN_H);
        affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
        ///dessin limite zone d'attaque autour du perso
        dessin_ligne(joueur, i, nb_joueurs, buffer, buffer_pixels, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts, longueur_ligne);
        affichage_joueurs(buffer, joueur, i, nb_joueurs, matrice);
        display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);

        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        lecture_pixels_buffer_map(buffer_map, &red_temp, &green_temp,&blue_temp); /// recupere position de la souris par rapport aux couleurs sur le buffer
        reperage_bloc_souris(&x_souris, &y_souris, red_temp, green_temp, blue_temp, matrice, joueur, i); /// repere la couleur du bloc sous la souris grace a la ligne d avant
        if (matrice[x_souris][y_souris].occuper != matrice[joueur[i].x][joueur[i].y].occuper && matrice[x_souris][y_souris].occuper != 0 && mouse_b&1)
        {
            id_ennemi = matrice[x_souris][y_souris].occuper - 1;
            if (x_souris < joueur[matrice[x_souris][y_souris].occuper - 1].x && y_souris == joueur[matrice[x_souris][y_souris].occuper - 1].y)
            {
                animation_attaque_de_base(buffer, map, joueur, i, matrice, nb_joueurs, 1);
            }
            /// SUD EST
            if (x_souris > joueur[matrice[x_souris][y_souris].occuper - 1].x && y_souris == joueur[matrice[x_souris][y_souris].occuper - 1].y)
            {
                animation_attaque_de_base(buffer, map, joueur, i, matrice, nb_joueurs, 3);
            }
            /// SUD OUEST
            if (x_souris == joueur[matrice[x_souris][y_souris].occuper - 1].x && y_souris < joueur[matrice[x_souris][y_souris].occuper - 1].y)
            {
                animation_attaque_de_base(buffer, map, joueur, i, matrice, nb_joueurs, 0);
            }
            /// NORD EST
            if (x_souris == joueur[matrice[x_souris][y_souris].occuper - 1].x && y_souris > joueur[matrice[x_souris][y_souris].occuper - 1].y)
            {
                animation_attaque_de_base(buffer, map, joueur, i, matrice, nb_joueurs, 2);
            }
            joueur[id_ennemi].brulure = 1;
            attaque = 1;
        }
        textprintf_ex(buffer, font, 0, 5, makecol(0, 0, 0), -1, "Occuper souris : %d", matrice[x_souris][y_souris].occuper);
        textprintf_ex(buffer, font, 0, 15, makecol(0, 0, 0), -1, "Occuper joueur: %d", matrice[joueur[(i + 1) % nb_joueurs].x][joueur[(i + 1) % nb_joueurs].y].occuper);
        if (mouse_x >= 370 && mouse_x <= 400 && mouse_y >= 670 && mouse_y <= 700 && mouse_b&1)
        {
            attaque = 1; // le joueur a annulé son attaque, l'attaque est considéré comme faite mais sans dégâts
        }
    }
}

void sort3_mage(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, BITMAP* buffer_map, t_bloc matrice[23][23], int x_souris, int y_souris, BITMAP *cursor, BITMAP *map, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP *desc_sorts)
{
    BITMAP *buffer_pixels;
    buffer_pixels = create_bitmap(1280,720);
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
        lecture_pixels_buffer_map(buffer_map, &red_temp, &green_temp,&blue_temp);
        reperage_bloc_souris(&x_souris, &y_souris, red_temp, green_temp, blue_temp, matrice, joueur, i);
        // on attaque le joueur ennemi1 sur on clique et que la souris est sur lui
        if (matrice[x_souris][y_souris].occuper != matrice[joueur[i].x][joueur[i].y].occuper && matrice[x_souris][y_souris].occuper != 0 && mouse_b&1)
        {
            /// NORD OUEST
            if (x_souris < joueur[matrice[x_souris][y_souris].occuper - 1].x && y_souris == joueur[matrice[x_souris][y_souris].occuper - 1].y)
            {
                animation_attaque_de_base(buffer, map, joueur, i, matrice, nb_joueurs, 1);
            }
            /// SUD EST
            if (x_souris > joueur[matrice[x_souris][y_souris].occuper - 1].x && y_souris == joueur[matrice[x_souris][y_souris].occuper - 1].y)
            {
                animation_attaque_de_base(buffer, map, joueur, i, matrice, nb_joueurs, 3);
            }
            /// SUD OUEST
            if (x_souris == joueur[matrice[x_souris][y_souris].occuper - 1].x && y_souris < joueur[matrice[x_souris][y_souris].occuper - 1].y)
            {
                animation_attaque_de_base(buffer, map, joueur, i, matrice, nb_joueurs, 0);
            }
            /// NORD EST
            if (x_souris == joueur[matrice[x_souris][y_souris].occuper - 1].x && y_souris > joueur[matrice[x_souris][y_souris].occuper - 1].y)
            {
                animation_attaque_de_base(buffer, map, joueur, i, matrice, nb_joueurs, 2);
            }

            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest(20);
            attaque = 1; // on a attaqué, on peut sortir de la boucle en infligeant les dégâts, avec le % de chance
        }

        textprintf_ex(buffer, font, 0, 0, makecol(0, 0, 0), -1, "Mouse X : %d", x_souris);
        textprintf_ex(buffer, font, 0, 10, makecol(0, 0, 0), -1, "Mouse Y : %d", y_souris);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        printf("occuper : %d\n", matrice[x_souris][y_souris].occuper);
        printf("occuper : %d\n", matrice[joueur[(i + 1) % nb_joueurs].x][joueur[(i + 1) % nb_joueurs].y].occuper);
        if (mouse_x >= 405 && mouse_x <= 435 && mouse_y >= 670 && mouse_y <= 700 && mouse_b&1)
        {
            attaque = 1; // le joueur a annulé son attaque, l'attaque est considéré comme faite mais sans dégâts
        }
    }
}

void sort4_mage(BITMAP *buffer_map, BITMAP * map,BITMAP * cursor, BITMAP *buffer, t_joueur* joueur, int i, t_bloc matrice[23][23], int *red_mouse, int * green_mouse, int *blue_mouse, int *ligne_souris,
                int *colonne_souris, int nb_joueurs, BITMAP * hud_icone, BITMAP * desc_sorts, BITMAP **hud_joueur, BITMAP **icone_classes)
{
    BITMAP*buffer_pixels;
    buffer_pixels = create_bitmap(SCREEN_W, SCREEN_H);
    int sort_lance = 0;
    int annulation = 0;
    int red_temp, green_temp, blue_temp;
    int red_mouse2, green_mouse2, blue_mouse2;
    ///dessin limite zone d'attaque autour du perso

    blit(map, buffer_pixels, 0,0,0,0, SCREEN_W,SCREEN_H);
    /// dessin gros retangle central
    for(int j = joueur[i].x-1; j<= joueur[i].x +1; j++)
    {
        for (int k = joueur[i].y -2; k <= joueur[i].y +2; k++)
        {
            ///condition affichage en vert cases disponibles
            if (matrice[j][k].accessible == 1)
            {
                dessin_bloc_unique(buffer_pixels, j, k, matrice, 0, 255,0);
            }
        }
    }
    /// dessin ligne de 3 blocs en haut et en bas
    for (int k = joueur[i].y -1; k <= joueur[i].y +1; k++)
    {
        ///condition affichage en vert cases disponibles
        if (matrice[joueur[i].x+2][k].accessible == 1)
        {
            dessin_bloc_unique(buffer_pixels, joueur[i].x +2, k, matrice, 0, 255, 0);
        }
        if (matrice[joueur[i].x-2][k].accessible == 1)
        {
            dessin_bloc_unique(buffer_pixels, joueur[i].x -2, k, matrice, 0, 255, 0);
        }

    }
    /// dessin 4 blocs aux extremités
    if (matrice[joueur[i].x-3][joueur[i].y].accessible == 1 && (joueur[i].x-3 >=0 && joueur[i].x-3 <= 22) && (joueur[i].y >= 0 && joueur[i].y <= 22))
    {
        dessin_bloc_unique(buffer_pixels, joueur[i].x-3, joueur[i].y, matrice, 0, 255, 0);
    }
    if (matrice[joueur[i].x+3][joueur[i].y].accessible == 1 && (joueur[i].x+3 >=0 && joueur[i].x+3 <= 22) && (joueur[i].y >= 0 && joueur[i].y <= 22))
    {
        dessin_bloc_unique(buffer_pixels, joueur[i].x+3, joueur[i].y, matrice, 0, 255, 0);
    }
    if (matrice[joueur[i].x][joueur[i].y-3].accessible == 1 && (joueur[i].x >=0 && joueur[i].x <= 22) && (joueur[i].y -3 >= 0 && joueur[i].y -3 <= 22))
    {
        dessin_bloc_unique(buffer_pixels, joueur[i].x, joueur[i].y-3, matrice, 0, 255, 0);
    }
    if (matrice[joueur[i].x][joueur[i].y+3].accessible == 1 && (joueur[i].x >=0 && joueur[i].x <= 22) && (joueur[i].y +3 >= 0 && joueur[i].y +3 <= 22))
    {
        dessin_bloc_unique(buffer_pixels, joueur[i].x, joueur[i].y +3, matrice, 0, 255, 0);
    }
    int num_bitmap = 0;
    while(sort_lance == 0 && annulation == 0)
    {
        lecture_pixels_buffer_map(buffer_pixels, &red_mouse2, &green_mouse2, &blue_mouse2);
        if(mouse_b &1 && green_mouse2 == 255)
        {
            rest(80);
            sort_lance = 1;
            reperage_bloc_souris(ligne_souris, colonne_souris, red_mouse2, green_mouse2, blue_mouse2, matrice);
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
            lecture_pixels_buffer_map(buffer_pixels, &red_temp, &green_temp, &blue_temp);
            if(green_temp == 255)
            {
                for(int k = *ligne_souris-3; k < *ligne_souris+4; k++)
                {
                    for (int l = *colonne_souris-3; l< *colonne_souris+4; l++)
                    {
                        if(matrice[k][l].accessible == 1 && (k >=0 && k <= 22) && (l >= 0 && l <= 22))
                        {
                            dessin_bloc_unique(buffer, k, l, matrice, 0,255,0);
                        }
                    }
                }
            }
            affichage_hud_sorts(joueur, i, nb_joueurs, buffer, hud_icone, desc_sorts); // Blit de 5 logos (les mêmes pour la barre d'action, à changer après...)
            affichage_hud_joueur(buffer, hud_joueur, joueur, i,icone_classes);
            for (int j = 0; j< nb_joueurs; j++)
            {
                if (joueur[j].vivant)
                {
                    //couleur_sous_joueur(buffer, joueur[j].x, joueur[j].y, matrice);
                    masked_blit(joueur[j].classe.deplacement[0][0], buffer, 0, 0, matrice[joueur[j].x][joueur[j].y].x_bloc - 22, matrice[joueur[j].x][joueur[j].y].y_bloc - 52, 49, 64);
                }
            } // affiche du hud joueur, avec pv, pa, pm
            display_cursor(cursor, buffer, mouse_x-5, mouse_y-5);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        }
    }
    if (sort_lance == 1)
    {
        for(int l = 0; l< 2 ; l++)
        {
            for (int k = 0; k < 4; k++)
            {
                blit(map, buffer, 0,0,0,0, SCREEN_W, SCREEN_H);
                affichage_hud_sorts(joueur, i, nb_joueurs, buffer, hud_icone, desc_sorts); // Blit de 5 logos (les mêmes pour la barre d'action, à changer après...)
                affichage_hud_joueur(buffer, hud_joueur, joueur, i,icone_classes);
                for (int j = 0; j< nb_joueurs; j++)
                {
                    if (joueur[j].vivant)
                    {
                        //couleur_sous_joueur(buffer, joueur[j].x, joueur[j].y, matrice);
                        masked_blit(joueur[j].classe.deplacement[0][0], buffer, 0, 0, matrice[joueur[j].x][joueur[j].y].x_bloc - 22, matrice[joueur[j].x][joueur[j].y].y_bloc - 52, 49, 64);
                    }
                } // affiche du hud joueur, avec pv, pa, pm
                printf("avant draw\n");
                draw_sprite(buffer, joueur[i].classe.spell[3].animation_sort[k], matrice[*ligne_souris][*colonne_souris].x_bloc - 161, matrice[*ligne_souris][*colonne_souris].y_bloc - 91);
                draw_sprite(buffer, joueur[i].classe.spell[3].animation_sort[k], matrice[*ligne_souris][*colonne_souris].x_bloc - 128, matrice[*ligne_souris][*colonne_souris].y_bloc - 70);
                printf("avant draw\n");
                affichage_autres_joueurs(joueur, buffer, i,nb_joueurs, matrice);
                display_cursor(cursor, buffer, mouse_x-5, mouse_y-5);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                rest(300);
            }
        }
    }
    clear_bitmap(buffer_pixels);
}
