#include "../prototypes.h"
#include "../structures.h"

void sort1_assassin(t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, BITMAP *buffer_map, t_bloc matrice[23][23], int x_souris, int y_souris, BITMAP *cursor, BITMAP *map, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP *desc_sorts, int respiration_joueur[])
{
    time_t start = (int)(time(NULL));
    int num_bitmap = 0;
    /// tant qu'on ne clique pas sur l'icone de l'attaque de base, ou qu'on a lanc� l'attaque
    if (pourcentage_de_chance() < 9 && !joueur[i].lucide && joueur[i].pa >= 2)
    {
        if (joueur[i].pa >= 6 || joueur[i].pm >= 3)
        {
            textprintf_ex(buffer, font, mouse_x - 10, mouse_y - 70, makecol(joueur[i].red, joueur[i].green, joueur[i].blue), -1, "PV MAX atteints !");
        }
        else
        {
            joueur[i].pa += 3;
            joueur[i].pm += 2;
            if (joueur[i].pa >= 6 || joueur[i].pm >= 3)
            {
                joueur[i].pa = 6;
                joueur[i].pm = 3;
            }
            while ((int)(time(NULL)) - start < 2)
            {
                clear_bitmap(buffer);
                affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
                affichage_joueurs_respiration(buffer, joueur, i, nb_joueurs, matrice, respiration_joueur, 5);
                draw_sprite(buffer, joueur[i].classe.spell[0].animation_sort[num_bitmap], matrice[joueur[i].x][joueur[i].y].x_bloc - 20,  matrice[joueur[i].x][joueur[i].y].y_bloc - 60);
                num_bitmap = (num_bitmap + 1) % 4;
                display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                rest(80);
            }
        }
    }
    else
    {
        while ((int)(time(NULL)) - start < 2)
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

void sort2_assassin(time_t start, t_joueur* joueur, int i, int nb_joueurs, BITMAP *buffer, BITMAP* buffer_map, t_bloc matrice[23][23], int x_souris, int y_souris, BITMAP *cursor, BITMAP *map, BITMAP **hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP *desc_sorts)
{
    int attaque = 3;
    BITMAP *buffer_pixels;
    buffer_pixels = create_bitmap(SCREEN_W,SCREEN_H);
    int red_temp, green_temp, blue_temp;
    int longueur_ligne = 4;
    int mess = 0, chance;
    int temps, compteur = 0;
    int x_augmente = 0, x_temp;
    int y_augmente = 0, y_temp;
    int num_bitmap = 0;
    int pos_x_ennemi;
    int pos_y_ennemi;

    while(attaque == 3 || mess == 0)
    {
        clear_bitmap(buffer);
        blit(map, buffer, 0,0,0,0, SCREEN_W,SCREEN_H);
        affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
        ///dessin limite zone d'attaque autour du perso
        dessin_ligne(joueur, i, nb_joueurs, buffer, buffer_pixels, matrice, x_souris, y_souris, cursor, map, hud_joueur, icone_classes, hud_icone, desc_sorts, longueur_ligne);
        affichage_joueurs(buffer, joueur, i, nb_joueurs, matrice);
        display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);

        lecture_pixels_buffer_map(buffer_map, &red_temp, &green_temp,&blue_temp); /// recupere position de la souris par rapport aux couleurs sur le buffer
        reperage_bloc_souris(&x_souris, &y_souris, red_temp, green_temp, blue_temp, matrice, joueur, i); /// repere la couleur du bloc sous la souris grace a la ligne d avant
        lecture_pixels_buffer_map(buffer, &red_temp, &green_temp,&blue_temp); /// lis la couleur des pixels sur le buffer pixels, sert a verifier la bonne position de la souris
        if (matrice[x_souris][y_souris].occuper != matrice[joueur[i].x][joueur[i].y].occuper && matrice[x_souris][y_souris].occuper != 0 && mouse_b&1 && attaque == 3)
        {
            chance = random(1,10);
            if(chance < 9)
            {
                /// attaque reussie
                chance = random(4,8);
                x_temp = x_souris;
                y_temp = y_souris;
                joueur[matrice[x_souris][y_souris].occuper -1].pv = joueur[matrice[x_souris][y_souris].occuper -1].pv - chance;
                pos_x_ennemi = joueur[matrice[x_souris][y_souris].occuper -1].x;
                pos_y_ennemi = joueur[matrice[x_souris][y_souris].occuper -1].y;
                attaque = 1;
                if (matrice[joueur[i].x][joueur[i].y].x_bloc < matrice[x_souris][y_souris].x_bloc)
                    x_augmente = 2;
                else if(matrice[joueur[i].x][joueur[i].y].x_bloc > matrice[x_souris][y_souris].x_bloc)
                    x_augmente = -2;
                if (matrice[joueur[i].x][joueur[i].y].y_bloc < matrice[x_souris][y_souris].y_bloc)
                    y_augmente = 1;
                else if(matrice[joueur[i].x][joueur[i].y].y_bloc > matrice[x_souris][y_souris].y_bloc)
                    y_augmente = -1;
                temps = (float)((time(NULL)) - start);
            }
            else
            {
                /// attaque manqu�e
                attaque = 2;
                temps = (float)((time(NULL)) - start);
            }
        }
        else if (mouse_x >= 370 && mouse_x <= 400 && mouse_y >= 670 && mouse_y <= 700 && mouse_b &&1 && attaque == 3)
        {
            attaque = 0;// le joueur a annul� son attaque, l'attaque est consid�r� comme faite mais sans d�g�ts
            mess = 1;
        }
        if(attaque == 1)
        {
            int cond1 = matrice[joueur[i].x][joueur[i].y].x_bloc + compteur*x_augmente;
            int cond2 = matrice[joueur[i].x][joueur[i].y].x_bloc + compteur*y_augmente;
            if ((cond1 <= matrice[x_temp][y_temp].x_bloc -2 - 5*x_augmente|| cond1 >= matrice[x_temp][y_temp].x_bloc - 5*x_augmente +2) && (cond2 <= matrice[x_temp][y_temp].y_bloc -2 -10*y_augmente|| cond2 >= matrice[x_temp][y_temp].y_bloc -10*y_augmente +2))
            {
                compteur++;
                draw_sprite(buffer, joueur[i].classe.spell[1].animation_sort[num_bitmap], matrice[joueur[i].x][joueur[i].y].x_bloc + compteur*x_augmente -29,  matrice[joueur[i].x][joueur[i].y].y_bloc + compteur*y_augmente -42);
                num_bitmap = (num_bitmap + 1) % 2;
                rest(40);
            }
            textout_ex(buffer, font,"ATTAQUE REUSSIE !!", matrice[pos_x_ennemi][pos_y_ennemi].x_bloc - 15, matrice[pos_x_ennemi][pos_y_ennemi].y_bloc - 80, makecol(255,0,0), -1);
            if(temps +3 == (float)((time(NULL)) - start))
            {
                mess = 1;
            }
        }
        else if(attaque == 2)
        {
            textout_ex(buffer, font,"ATTAQUE MANQUEE !!", matrice[pos_x_ennemi][pos_y_ennemi].x_bloc - 15, matrice[pos_x_ennemi][pos_y_ennemi].y_bloc - 80, makecol(0,0,0), -1);
            if(temps +3 == (float)((time(NULL)) - start))
            {
                mess = 1;
            }
        }
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
}


void sort4_assassin(BITMAP *buffer_map, BITMAP * map,BITMAP * cursor, BITMAP *buffer, t_joueur* joueur, int i, t_bloc matrice[23][23], int *red_mouse, int * green_mouse, int *blue_mouse, int *ligne_souris,
                    int *colonne_souris, int nb_joueurs, BITMAP * hud_icone, BITMAP * desc_sorts, BITMAP **hud_joueur, BITMAP **icone_classes)
{
    int sort_lance = 0;
    int annulation = 0;
    BITMAP* buffer_pixels;
    buffer_pixels = create_bitmap(1280,720);
    int red_temp, green_temp, blue_temp;
    int red_mouse2, green_mouse2, blue_mouse2;
    ///dessin limite zone d'attaque autour du perso
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
    /// dessin 4 blocs aux extremit�s
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
                            dessin_bloc_unique(buffer, k, l, matrice, 213,210,117);
                        }
                    }
                }
            }
            affichage_hud_sorts(joueur, i, nb_joueurs, buffer, hud_icone, desc_sorts); // Blit de 5 logos (les m�mes pour la barre d'action, � changer apr�s...)
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
        for(int l = 0; l< 5 ; l++)
        {
            for (int k = 0; k < 2; k++)
            {
                blit(map, buffer, 0,0,0,0, SCREEN_W, SCREEN_H);
                affichage_hud_sorts(joueur, i, nb_joueurs, buffer, hud_icone, desc_sorts); // Blit de 5 logos (les m�mes pour la barre d'action, � changer apr�s...)
                affichage_hud_joueur(buffer, hud_joueur, joueur, i,icone_classes);
                for (int j = 0; j< nb_joueurs; j++)
                {
                    if (joueur[j].vivant)
                    {
                        //couleur_sous_joueur(buffer, joueur[j].x, joueur[j].y, matrice);
                        masked_blit(joueur[j].classe.deplacement[0][0], buffer, 0, 0, matrice[joueur[j].x][joueur[j].y].x_bloc - 22, matrice[joueur[j].x][joueur[j].y].y_bloc - 52, 49, 64);
                    }
                } // affiche du hud joueur, avec pv, pa, pm
                draw_sprite(buffer, joueur[i].classe.spell[3].animation_sort[k], matrice[*ligne_souris][*colonne_souris].x_bloc - 161, matrice[*ligne_souris][*colonne_souris].y_bloc - 100);
                affichage_autres_joueurs(joueur, buffer, i,nb_joueurs, matrice);
                display_cursor(cursor, buffer, mouse_x-5, mouse_y-5);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                rest(400);
            }
        }
    }
    clear_bitmap(buffer_pixels);
}
