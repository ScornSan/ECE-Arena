#include "../prototypes.h"
#include "../structures.h"

void affichage_hud_sorts(t_joueur* joueur, int i, BITMAP* buffer, BITMAP* hud_icone, BITMAP* desc_sorts)
{
    masked_blit(hud_icone, buffer, 0, 0, 280, 660, SCREEN_W, SCREEN_H);
    masked_blit(joueur[i].classe.logo_attaque, buffer, 0, 0, 300, 670, SCREEN_W, SCREEN_H);
    blit(joueur[i].classe.sort1.logo, buffer, 0, 0, 335, 670, SCREEN_W, SCREEN_H);
    blit(joueur[i].classe.sort2.logo, buffer, 0, 0, 370, 670, SCREEN_W, SCREEN_H);
    blit(joueur[i].classe.sort3.logo, buffer, 0, 0, 405, 670, SCREEN_W, SCREEN_H);
    blit(joueur[i].classe.sort4.logo, buffer, 0, 0, 440, 670, SCREEN_W, SCREEN_H);
    if (mouse_x >= 300 && mouse_x <= 330 && mouse_y >= 670 && mouse_y <= 700) // attaque de bas
    {
        masked_blit(desc_sorts, buffer, 0, 0, 279, 560, SCREEN_W, SCREEN_H);
    }
    if (mouse_x >= 335 && mouse_x <= 365 && mouse_y >= 670 && mouse_y <= 700) // sort 1
    {
        masked_blit(desc_sorts, buffer, 0, 0, 279, 560, SCREEN_W, SCREEN_H); // affichage bitmap description
        masked_blit(joueur[i].classe.sorts[0], buffer, 0, 0, 279, 560, SCREEN_W, SCREEN_H); // affichage description sort 1

    }
    if (mouse_x >= 370 && mouse_x <= 400 && mouse_y >= 670 && mouse_y <= 700) // sort 2
    {
        masked_blit(desc_sorts, buffer, 0, 0, 279, 560, SCREEN_W, SCREEN_H); // affichage stats sorts
        masked_blit(joueur[i].classe.sorts[1], buffer, 0, 0, 279, 560, SCREEN_W, SCREEN_H); // affichage bitmap description sort 2

    }
    if (mouse_x >= 405 && mouse_x <= 435 && mouse_y >= 670 && mouse_y <= 700) // sort 3
    {
        masked_blit(desc_sorts, buffer, 0, 0, 279, 560, SCREEN_W, SCREEN_H); // affichage stats sorts
        masked_blit(joueur[i].classe.sorts[2], buffer, 0, 0, 279, 560, SCREEN_W, SCREEN_H); // affichage description sort 3

    }
    if (mouse_x >= 440 && mouse_x <= 470 && mouse_y >= 670 && mouse_y <= 700) // sort 4
    {
        masked_blit(desc_sorts, buffer, 0, 0, 279, 560, SCREEN_W, SCREEN_H); // affichage stats sort
        masked_blit(joueur[i].classe.sorts[3], buffer, 0, 0, 279, 560, SCREEN_W, SCREEN_H); // affichage description sort 4
    }
}

void affichage_hud_joueur(BITMAP* buffer, BITMAP* hud, t_joueur* joueur, int i)
{
    rectfill(buffer, 72, 650, 74 + joueur[i].pv * 3, 673, makecol(255, 0, 0)); // rectangle pv a reduire quand il perd des hp
    rectfill(buffer, 68, 675, 70 + joueur[i].pa * 30, 685, makecol(0, 0, 255)); // rectangle pa a reduire quand il perd des hp
    rectfill(buffer, 66, 685, 70 + joueur[i].pm * 60, 695, makecol(0, 255, 0)); // rectangle pm a reduire quand il perd des hp
    masked_blit(hud, buffer, 0, 0, 3, 640, SCREEN_W, SCREEN_H);
    textprintf_ex(buffer, font, 120, 658, makecol(255, 255, 255), -1, "PV : %d/55", joueur[i].pv);
    textprintf_ex(buffer, font, 120, 676, makecol(255, 255, 255), -1, "PA : %d/6", joueur[i].pa);
    textprintf_ex(buffer, font, 120, 687, makecol(255, 255, 255), -1, "PM : %d/3", joueur[i].pm);
}

void tour_joueur(BITMAP* buffer, BITMAP *cursor, t_joueur* joueur, int nb_joueurs)
{
    // Déclaration du pointeur sur BITMAP devant recevoir l'image
    BITMAP *map;
    BITMAP *hud_joueur;
    BITMAP *hud_icone;
    BITMAP *desc_sorts;
    FONT *kristen12;
    FONT *fixedsys;

    BITMAP * buffer_pixels; // LE 2
    BITMAP * buffer_map; // LE 1
    BITMAP * croix_rouge;
    BITMAP * croix_bleue;

    int i = 0;
    t_bloc matrice[23][23];

    // Chargement de l'image (l'allocation a lieu en m�me temps)

    map = load_bitmap("BITMAP/map_reparation.bmp", NULL);
    hud_joueur = load_bitmap("BITMAP/hud_joueur2.bmp", NULL);
    hud_icone = load_bitmap("BITMAP/hud_icone_temp.bmp", NULL);
    desc_sorts = load_bitmap("BITMAP/desc_sorts.bmp", NULL);
    kristen12 = load_font("FONT/kristen12.pcx", NULL, NULL);
    fixedsys = load_font("FONT/fixedsys10.pcx", NULL, NULL);

    buffer =create_bitmap(SCREEN_W,SCREEN_H);
    buffer_map =create_bitmap(SCREEN_W,SCREEN_H);
    buffer_pixels =create_bitmap(SCREEN_W,SCREEN_H);
    croix_rouge = load_bitmap("BITMAP/croix_rouge.bmp", NULL);
    croix_bleue = load_bitmap("BITMAP/croix_bleue.bmp", NULL);


    //creations des classes pour chaque joueurs
    creation_icones_classes(joueur);

    // creation des calques sous la map, et initialisation des cases innacessibles, pour avoir le systeme de souris sur les blocs
    distribution_couleur_blocs(buffer_map, matrice);
    definition_accessible(matrice);
    definition_occuper(matrice);

    if (!map)
    {
        allegro_message("pas pu trouver tour joueur/charger mon_image.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    clear_bitmap(buffer);
    time_t start = time(NULL);
    int joueur_en_vie = 4;

    textout_ex(desc_sorts, font, "DEGATS:", 18, 20, makecol(255, 0, 0), -1);
    textout_ex(desc_sorts, font, "PA:", 18, 34, makecol(60, 0, 255), -1);
    textout_ex(desc_sorts, font, "PM:", 18, 48, makecol(0, 255, 0), -1);
    textout_ex(desc_sorts, font, "Portee:", 18, 62, makecol(255, 255, 255), -1);
    textout_ex(desc_sorts, font, "%", 18, 76, makecol(0, 0, 0), -1);
    textout_ex(desc_sorts, font, "chance:", 34, 76, makecol(0, 0, 0), -1);

    //textprintf_ex(desc_sorts, font, 80, 16, makecol(255, 0, 0), -1, "%d-%d", 1, joueur[i].classe.attaque);
    int ligne_souris, colonne_souris;
    int ligne_joueur = 10, colonne_joueur = 10;
    int green_mouse, red_mouse, blue_mouse;
    int autorisation_dep = 0;
    time_t chrono1 = time (NULL);
    time_t chrono2 = time (NULL);

    int erreur1 = 0;
    int erreur2 = 0;
    int clic = 0;
    int deplacement_effectuer = 0;
    int nombre_pm = 3;

    // Boucle d'animation
    while (joueur_en_vie != 1)
    {
        if (joueur[i].vivant) // on fait joueur le joueur i car il est vivant
        {
            clear_bitmap(buffer);
            blit(map, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            affichage_hud_sorts(joueur, i, buffer, hud_icone, desc_sorts); // Blit de 5 logos (les mêmes pour la barre d'action, à changer après...)
            affichage_hud_joueur(buffer, hud_joueur, joueur, i); // affiche du hud joueur, avec pv, pa, pm
            textprintf_ex(buffer, font, 0, 0, makecol(0, 0, 0), -1, "Mouse X : %d", mouse_x);
            textprintf_ex(buffer, font, 0, 10, makecol(0, 0, 0), -1, "Mouse Y : %d", mouse_y);
            textprintf_ex(buffer, font, 0, 20, makecol(0, 0, 0), -1, "Temps: %f", (float)((time(NULL)) - start));
            rectfill(buffer, 1000, 650, 1000 - (int)((time(NULL)) - start) * 5, 673, makecol(255, 0, 0)); // barre de temps

            lecture_pixels_buffer_map(buffer_map, &red_mouse, &green_mouse, &blue_mouse);
            reperage_bloc_souris(&ligne_souris, &colonne_souris, red_mouse, green_mouse, blue_mouse, matrice, &autorisation_dep, joueur, i);
            reperage_chemin(buffer, &ligne_joueur, &colonne_joueur, ligne_souris, colonne_souris, matrice, joueur[i], i, &autorisation_dep);
            if(autorisation_dep == 1)
            {
                /*/// variables contenant les parametres de la souris au moment du clic
                lecture_pixels_buffer_map(buffer_map, &red_mouse, &green_mouse, &blue_mouse);
                /// recherche du bloc correspondant sous la souris au moment du clic
                reperage_bloc_souris(&ligne_souris, &colonne_souris, red_mouse, green_mouse, blue_mouse, matrice, &autorisation_dep);*/

                /// condition si la souris clic sur un bloc valable
                if (matrice[ligne_souris][colonne_souris].accessible == 0)
                {
                    textout_ex(screen, font,"Vous ne pouvez pas vous deplacer en dehors de la carte !! ",15, 30, makecol(255,0,0), -1); /////// A CHANGER PLUS TARD
                    sleep(3); ///////// A CHANGER PLUS TARD
                    chrono1 = time(NULL);
                    erreur1 =1;
                }
                else if (matrice[ligne_souris][colonne_souris].occuper == 1)
                {
                    textout_ex(screen, font,"Cette case est deja occupee par un joueur ou un obstacle !! ", 800, 30, makecol(255,255,0), -1); /////// A CHANGER PLUS TARD
                    sleep(3); ///////// A CHANGER PLUS TARD
                    chrono2 = time(NULL);
                    erreur2 =1;
                }
                else
                {
                    deplacement_personnage(buffer,map, &ligne_joueur,&colonne_joueur, ligne_souris, colonne_souris, matrice, &deplacement_effectuer/*, chrono1, &erreur1*/);
                    autorisation_dep = 0;
                }
            }
            //lecture_pixels_buffer_map(buffer_map, &red_mouse, &green_mouse, &blue_mouse); // ca bug

            //quadrillage_test(buffer);
            affichage_croix_bleue(buffer, croix_bleue, ligne_souris, colonne_souris, matrice); // bug
            affichage_croix_rouge(buffer, croix_rouge, ligne_souris, colonne_souris, matrice); // bug
            //encadrement_souris(buffer, red_mouse, green_mouse, blue_mouse);
            display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
            //deplacement_nombre_pm(buffer_pixels, buffer, ligne_joueur, colonne_joueur, matrice, &nombre_pm, &clic, cursor);
            circlefill(buffer, matrice[ligne_joueur][colonne_joueur].x_bloc, matrice[ligne_joueur][colonne_joueur].y_bloc, 9, makecol(0,0,0));
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            if ((int)(time(NULL) - start >= TEMPS_TOUR) || (mouse_b&1 && (mouse_x >= 900 && mouse_x <= 1000 && mouse_y >= 600 && mouse_y <= 700)))
            {
                start = time(NULL);
                joueur[i].pm = 3; // on remet les pm et pa du joueur au nombre initial
                joueur[i].pa = 6;
                i = (i + 1) % nb_joueurs; // On boucle car temps finis ou on a cliqué sur le bouton
            }
        }
        else
        {
            i = (i + 1) % nb_joueurs; // On boucle car le joueur est mort
        }
        rest(20);
    }
    /// On fera une espèce d'animation de fin de jeu, on affiche le classement et on appuie sur un bouton quand on veut continuer
    /// on revient donc au menu (insérez le programme de Sarah)

    for (int i = 0; i < 4; i++)
    {
        destroy_bitmap(joueur[i].classe.logo_attaque);
        destroy_bitmap(joueur[i].classe.sort1.logo);
        destroy_bitmap(joueur[i].classe.sort2.logo);
        destroy_bitmap(joueur[i].classe.sort3.logo);
        destroy_bitmap(joueur[i].classe.sort4.logo);
    }
    destroy_bitmap(map);
    destroy_bitmap(hud_joueur);
    destroy_bitmap(hud_icone);
}
