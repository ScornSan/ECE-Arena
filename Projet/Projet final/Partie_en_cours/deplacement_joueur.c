#include "../prototypes.h"
#include "../structures.h"

void deplacement_joueur(BITMAP *buffer, BITMAP *buffer_pixels, BITMAP *buffer_map, BITMAP *fond, BITMAP *cursor, t_joueur* joueur, t_bloc matrice[23][23], BITMAP * croix_rouge, BITMAP * croix_bleue, int ligne_joueur, int colonne_joueur, int ligne_souris, int colonne_souris, int i)
{
    cursor = load_bitmap("cursor.bmp", NULL);
    int x_souris;
    time_t chrono1 = time (NULL);
    time_t chrono2 = time (NULL);
    int erreur1 = 0;
    int erreur2 = 0;
    int clic = 0;
    int deplacement_effectuer = 0;
    int autorisation_dep = 0;
    int nombre_pm = 3;
    //int x = 114, y = 399;
    //quadrillage_test(screen);

    int green_mouse, red_mouse, blue_mouse;

    while (deplacement_effectuer != 50)
    {
        lecture_pixels_buffer_map(buffer_map, &red_mouse, &green_mouse, &blue_mouse);
        blit(fond, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        reperage_bloc_souris(&ligne_souris, &colonne_souris, red_mouse, green_mouse, blue_mouse, matrice, &autorisation_dep);
        //effacement_bloc_unique(buffer_pixels,buffer, ligne_joueur, colonne_joueur+2, joueur[i].position, 255,100,255);
        if(mouse_b && autorisation_dep == 1)
        {
            /// variables contenant les parametres de la souris au moment du clic
            lecture_pixels_buffer_map(buffer_map, &red_mouse, &green_mouse, &blue_mouse);
            /// recherche du bloc correspondant sous la souris au moment du clic
            reperage_bloc_souris(&ligne_souris, &colonne_souris, red_mouse, green_mouse, blue_mouse, matrice, &autorisation_dep);
            printf("reperage2\n");
            /// condition si la souris clic sur un bloc valable
            if (joueur[i].position[ligne_souris][colonne_souris].accessible == 0)
            {
                textout_ex(screen, font,"Vous ne pouvez pas vous deplacer en dehors de la carte !! ",15, 30, makecol(255,0,0), -1); /////// A CHANGER PLUS TARD
                sleep(3); ///////// A CHANGER PLUS TARD
                chrono1 = time(NULL);
                erreur1 =1;
            }
            else if (joueur[i].position[ligne_souris][colonne_souris].occuper == 1)
            {
                textout_ex(screen, font,"Cette case est deja occupee par un joueur ou un obstacle !! ", 800, 30, makecol(255,255,0), -1); /////// A CHANGER PLUS TARD
                sleep(3); ///////// A CHANGER PLUS TARD
                chrono2 = time(NULL);
                erreur2 =1;
            }
            else
            {
                clic = 1;
                deplacement_personnage(buffer,fond, &ligne_joueur,&colonne_joueur, ligne_souris, colonne_souris, joueur[i].position, &deplacement_effectuer/*, chrono1, &erreur1*/);
                autorisation_dep = 0;
            }
        }
        display_cursor(cursor, buffer, mouse_x - 5, mouse_y - 5);
        /// Chrono a finir d'integrer plus tard
        /*if ((int) (time (NULL) - chrono1) < 2 && erreur1 == 1)
        {
            textout_ex(buffer, font,"Vous ne pouvez pas vous deplacer en dehors de la carte !! ",15, 30, makecol(255,0,0), -1);
        }
        else
        {
            erreur1 = 0;
        }*/
        //couleur_sous_joueur(buffer, ligne_joueur, colonne_joueur, joueur[i].position);
        textprintf_ex(buffer, font, 415, 710, makecol(0,255,0), -1, "position de la souris : x = %d et y = %d", mouse_x, mouse_y);
        quadrillage_test(buffer);
        //affichage_croix_bleue(buffer, croix_bleue, ligne_souris, colonne_souris, joueur[i].position);
        //affichage_croix_rouge(buffer, croix_rouge, ligne_souris, colonne_souris, joueur[i].position);
        //encadrement_souris(buffer, red_mouse, green_mouse, blue_mouse);
        deplacement_nombre_pm(buffer_pixels, buffer, ligne_joueur, colonne_joueur, joueur[i].position, &nombre_pm, &clic, cursor);
        circlefill(buffer, joueur[i].position[ligne_joueur][colonne_joueur].x_bloc, joueur[i].position[ligne_joueur][colonne_joueur].y_bloc, 9, makecol(0,0,0));
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
    textout_ex(screen, font,"Au tour du joueur suivant ",15, 100, makecol(255,255,255), -1);
}
