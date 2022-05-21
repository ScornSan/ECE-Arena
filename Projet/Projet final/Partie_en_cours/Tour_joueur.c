#include "../prototypes.h"
#include "../structures.h"

void tour_joueur(BITMAP* buffer, BITMAP *cursor, t_joueur* joueur, int nb_joueurs, SAMPLE* son_battle, BITMAP *son_on, BITMAP *son_off, int classement[])
{
    // Déclaration du pointeur sur BITMAP devant recevoir l'image
    BITMAP *map;
    BITMAP **hud_joueur;
    BITMAP **icone_classes;
    BITMAP *hud_icone;
    BITMAP *desc_sorts;

    BITMAP * buffer_map;
    BITMAP * croix_rouge;
    BITMAP * croix_bleue;

    int clic_son = 0;
    int i = 0;
    int j;
    int n = nb_joueurs-1;
    t_bloc matrice[23][23];

    hud_joueur = (BITMAP **)malloc(sizeof(BITMAP *) * nb_joueurs);
    icone_classes = (BITMAP **)malloc(sizeof(BITMAP *) * 4);
    // Chargement de l'image (l'allocation a lieu en m�me temps)

    if (pourcentage_de_chance() < 3)
    {
        map = load_bitmap("BITMAP/map0.bmp", NULL);
        for (i = 0; i < nb_joueurs; i++)
        {
            char text_hud_joueur[30];
            sprintf(text_hud_joueur, "BITMAP/hud_joueur_%d.bmp", i);
            hud_joueur[i] = load_bitmap(text_hud_joueur, NULL);
        }
    }
    else if (pourcentage_de_chance() < 5)
    {
        map = load_bitmap("BITMAP/map1.bmp", NULL);
        for (i = 0; i < nb_joueurs; i++)
        {
            char text_hud_joueur[30];
            sprintf(text_hud_joueur, "BITMAP/hud_joueur_%d_1.bmp", i);
            hud_joueur[i] = load_bitmap(text_hud_joueur, NULL);
        }
    }
    else if (pourcentage_de_chance() < 8)
    {
        map = load_bitmap("BITMAP/map2.bmp", NULL);
        for (i = 0; i < nb_joueurs; i++)
        {
            char text_hud_joueur[30];
            sprintf(text_hud_joueur, "BITMAP/hud_joueur_%d_2.bmp", i);
            hud_joueur[i] = load_bitmap(text_hud_joueur, NULL);
        }
    }
    else
    {
        map = load_bitmap("BITMAP/map3.bmp", NULL);
        for (i = 0; i < nb_joueurs; i++)
        {
            char text_hud_joueur[30];
            sprintf(text_hud_joueur, "BITMAP/hud_joueur_%d_3.bmp", i);
            hud_joueur[i] = load_bitmap(text_hud_joueur, NULL);
        }
    }

    //hud_joueur = load_bitmap("BITMAP/hud_joueur_0.bmp", NULL);
    hud_icone = load_bitmap("BITMAP/hud_icone_temp.bmp", NULL);
    desc_sorts = load_bitmap("BITMAP/desc_sorts.bmp", NULL);

    buffer =create_bitmap(SCREEN_W,SCREEN_H);
    buffer_map =create_bitmap(SCREEN_W,SCREEN_H);
    croix_rouge = load_bitmap("BITMAP/croix_rouge.bmp", NULL);
    croix_bleue = load_bitmap("BITMAP/croix_bleue.bmp", NULL);

    for (j = 0; j < 4; j++)
    {
        char text_icone_classes[50];
        sprintf(text_icone_classes, "BITMAP/icone_hud_classe_%d.bmp", j);
        icone_classes[j] = load_bitmap(text_icone_classes, NULL);
    }


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

    if (!croix_bleue || !croix_rouge)
    {
        allegro_message("pas pu trouver les croix");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    clear_bitmap(buffer);
    time_t start = time(NULL);

    textout_ex(desc_sorts, font, "DEGATS:", 18, 20, makecol(255, 0, 0), -1);
    textout_ex(desc_sorts, font, "PA:", 18, 40, makecol(60, 0, 255), -1);
    textout_ex(desc_sorts, font, "Portee:", 18, 60, makecol(255, 255, 255), -1);
    textout_ex(desc_sorts, font, "%", 18, 80, makecol(0, 0, 0), -1);
    textout_ex(desc_sorts, font, "chance:", 34, 80, makecol(0, 0, 0), -1);

    //textprintf_ex(desc_sorts, font, 80, 16, makecol(255, 0, 0), -1, "%d-%d", 1, joueur[i].classe.attaque);
    int ligne_souris, colonne_souris;

    int green_mouse, red_mouse, blue_mouse, green_mouse2, red_mouse2, blue_mouse2;
    int joueur_en_vie = nb_joueurs;
    int autorisation_dep = 0;

    int deplacement_effectuer = 0;

    /// initialisation des coordonnées de chaque jour a la case x = 0, y = 0
    for (int i = 0; i<nb_joueurs; i++)
    {
        joueur[i].x = i;
        joueur[i].y = i;
        joueur[i].direction = 0;
    }
    int fini = 0, choix1= 0, choix2= 0, choix3= 0, choix4= 0;
    int respiration_joueur[nb_joueurs];
    i = 0;
    /// tant que tous les joueurs ne sont pas positionnés
    play_sample(son_battle, 255, 128, 1000, 1);
    time_t debut = time(NULL);

    while(fini != nb_joueurs)
    {
        blit(map, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        affichage_son(buffer, cursor, son_battle, &clic_son);
        if (clic_son)
        {
            draw_sprite(buffer, son_off, 0, 0);
        }
        else
        {
            draw_sprite(buffer, son_on, 0, 0);
        }
        /// dessin des zones de placement
        affichage_emplacement_depart(buffer, nb_joueurs, matrice, joueur);

        lecture_pixels_buffer_map(buffer_map, &red_mouse, &green_mouse, &blue_mouse);
        lecture_pixels_buffer_map(buffer, &red_mouse2, &green_mouse2, &blue_mouse2);
        /// condition de placement (CRASH QUAND ON MANTIENT LE CLIC)
        condition_positionnement_depart(&fini, ligne_souris, colonne_souris, matrice, joueur, &choix1, &choix2, &choix3, &choix4, red_mouse2, green_mouse2, blue_mouse2);
        textprintf_ex(buffer, font, 500, 100, makecol(255,255,255), -1, "%s, choisissez votre emplacement de depart", joueur[i].pseudo);
        reperage_bloc_souris(&ligne_souris, &colonne_souris, red_mouse, green_mouse, blue_mouse, matrice);
        ///affichage de tous les joueurs en meme temps
        for (int j = 0; j< nb_joueurs; j++)
        {
            couleur_sous_joueur(buffer, joueur[j].x, joueur[j].y, matrice, joueur, j);
            affichage_joueurs(buffer, joueur, i, nb_joueurs, matrice);
            //circlefill(buffer, matrice[joueur[j].x][joueur[j].y].x_bloc, matrice[joueur[j].x][joueur[j].y].y_bloc, 9, makecol(joueur[j].red,joueur[j].green,joueur[j].blue));
        }
        textprintf_ex(buffer,font,96,36,makecol(0,255,0), makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);
        //affichage_croix_bleue(buffer, croix_bleue, ligne_souris, colonne_souris, matrice);
        //affichage_croix_rouge(buffer, croix_rouge, ligne_souris, colonne_souris, matrice);
        if ((int)(time(NULL) - debut >= TEMPS_CHOIX))
        {
            placement_aleatoire(&fini, matrice, joueur, nb_joueurs);
        }
        display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
        rest(20);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
    //tour_joueur_alea(joueur, nb_joueurs);
    for (int i = 0; i<nb_joueurs; i++)
    {
        if (joueur[i].choix_double)
        {
            matrice[joueur[i].x][joueur[i].y].occuper = (i % 2) + 1;
            matrice[joueur[i].x][joueur[i].y].id_case = i + 1;
        }
        else
        {
            matrice[joueur[i].x][joueur[i].y].occuper = i + 1;
            matrice[joueur[i].x][joueur[i].y].id_case = i + 1;
        }
        respiration_joueur[i] = i * 5;
    }
    i = random(0, 3);

    /// Boucle du jeu jusqu'a que la partie soit terminé
    while (joueur_en_vie != 1)
    {
        if (joueur[i].pv <= 0)
        {
            joueur[i].vivant = 0;
        }
        if (joueur[i].vivant == 1) // on fait joueur le joueur i car il est vivant
        {
            if (n == 0)
            {
                classement[n] = i; //classement[0] = i
                break; // On break pour aller dans le classement fin (dans le main)

            }
            clear_bitmap(buffer);
            /// Affichage general qui est constamment présent meme pendant les actions du joueur
            affichage_general(buffer, map, joueur, i, nb_joueurs, hud_joueur, icone_classes, hud_icone, desc_sorts);
            affichage_son(buffer, cursor, son_battle, &clic_son);
            if (clic_son)
            {
                draw_sprite(buffer, son_off, 0, 0);
            }
            else
            {
                draw_sprite(buffer, son_on, 0, 0);
            }
            //textprintf_ex(buffer, font, 0, 0, makecol(0, 0, 0), -1, "Mouse X : %d", mouse_x);
            //textprintf_ex(buffer, font, 0, 10, makecol(0, 0, 0), -1, "Mouse Y : %d", mouse_y);
            //textprintf_ex(buffer, font, 0, 20, makecol(0, 0, 0), -1, "Temps: %f", (float)((time(NULL)) - start));
            //rectfill(buffer, 1000, 650, 1000 - (int)((time(NULL)) - start) * 5, 673, makecol(255, 0, 0)); // barre de temps

            lecture_pixels_buffer_map(buffer_map, &red_mouse, &green_mouse, &blue_mouse);
            reperage_bloc_souris(&ligne_souris, &colonne_souris, red_mouse, green_mouse, blue_mouse, matrice, joueur, i);
            reperage_chemin(buffer, joueur[i].x, joueur[i].y, ligne_souris, colonne_souris, matrice, joueur, i, &autorisation_dep);
            selection_sort(buffer_map,&ligne_souris, &colonne_souris,&red_mouse, &green_mouse, &blue_mouse, joueur, i, nb_joueurs, buffer, matrice, desc_sorts, ligne_souris, colonne_souris, cursor, map, hud_joueur, icone_classes, hud_icone, start, respiration_joueur);
            textprintf_ex(buffer, font, 0, 5, makecol(0, 0, 0), -1, "Occuper souris : %d", matrice[ligne_souris][colonne_souris].occuper);
            textprintf_ex(buffer, font, 20, 20, makecol(0, 0, 0), -1, "id case joueur : %d", matrice[ligne_souris][colonne_souris].id_case);
            textprintf_ex(buffer, font, 30, 30, makecol(0, 0, 0), -1, "Joueur en vie: %d", joueur[i].vivant);
            //printf("%d\n", matrice[ligne_souris][colonne_souris].occuper);
            //printf("%d\n", matrice[ligne_souris][colonne_souris].id_case);
            affichage_joueurs_respiration(buffer, joueur, i, nb_joueurs, matrice, respiration_joueur, 5);
            display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            if(autorisation_dep == 1)
            {
                deplacement_personnage(buffer, map, joueur, i, ligne_souris, colonne_souris, matrice, &deplacement_effectuer, nb_joueurs, respiration_joueur);
                autorisation_dep = 0;
            }

            /// LE JOUEUR A ATTEINT LE TEMPS IMPARTI, ON BOUCLE
            if ((int)(time(NULL) - start >= TEMPS_TOUR))
            {
                start = time(NULL);
                joueur[i].pm = 3; // on remet les pm et pa du joueur au nombre initial
                joueur[i].pa = 6;
                compteur_effet(joueur, nb_joueurs);
                test_effets(joueur, nb_joueurs);
                i = (i + 1) % nb_joueurs; // On boucle car temps finis ou on a cliqué sur le bouton
            }
        }
        else
        {
            classement[n] = i;
            n--;
            // Boucle qui permet de voir si le joueur est éliminé, si il l'est, il passe à la n ième case du tableau
            joueur[i].pm = 3; // on remet les pm et pa du joueur au nombre initial
            joueur[i].pa = 6;
            compteur_effet(joueur, nb_joueurs);
            test_effets(joueur, i);
            i = (i + 1) % nb_joueurs; // On boucle car le joueur est mort
        }
        rest(20);
        if (mouse_b & 1 && mouse_x < 1)
        {
            break;
        }
    }
    /// On fera une espèce d'animation de fin de jeu, on affiche le classement et on appuie sur un bouton quand on veut continuer
    /// on revient donc au menu (insérez le programme de Sarah)

    /*for (int i = 0; i < 4; i++)
    {
        destroy_bitmap(joueur[i].classe.logo_attaque);
        for (int j = 0; j < NB_SORTS; j++)
        {
            destroy_bitmap(joueur[i].classe.spell[j].description);
            destroy_bitmap(joueur[i].classe.spell[j].logo);
        }
    }*/
    //destroy_bitmap(map);
    //destroy_bitmap(*hud_joueur);
    //destroy_bitmap(hud_icone);
}
