#include "../prototypes.h"
#include "../structures.h"

void deplacement_personnage(BITMAP * buffer,BITMAP * fond, t_joueur* joueur, int i, int ligne_souris, int colonne_souris, t_bloc matrice[23][23], int *deplacement_effectuer, int nb_joueurs, int respiration_joueur[])
{
    int compteur = 0;
    /// affichage du message d'erreur apres changement de prog et avec chrono :::::: A REGLER
    /*while(1)
    {
        if ((int) time(NULL) - chrono1 < 2 && *erreur1 == 1)
        {
            blit(fond, buffer, 0, 0, 0, 0, fond->w, fond->h);
            textout_ex(buffer, font,"Vous ne pouvez pas vous deplacer en dehors de la carte !! ",15, 30, makecol(255,0,0), -1);
            circlefill(buffer, matrice[ligne_joueur][colonne_joueur].x_bloc, matrice[ligne_joueur][colonne_joueur].y_bloc, 9, makecol(0,0,0));
            textprintf_ex(buffer, font, 415, 710, makecol(0,255,0), -1, "position de la souris : x = %d et y = %d", mouse_x, mouse_y);
            quadrillage_test(buffer);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        }
        else
        {
            blit(fond, buffer, 0, 0, 0, 0, fond->w, fond->h);
            circlefill(buffer, matrice[ligne_joueur][colonne_joueur].x_bloc, matrice[ligne_joueur][colonne_joueur].y_bloc, 9, makecol(0,0,0));
            textprintf_ex(buffer, font, 415, 710, makecol(0,255,0), -1, "position de la souris : x = %d et y = %d", mouse_x, mouse_y);
            quadrillage_test(buffer);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            *erreur1 = 0;
        }
    }*/

    int x_augmente;
    int y_augmente;

    if (joueur[i].x <= ligne_souris)
        x_augmente = 1;
    else
        x_augmente = 0;
    if (joueur[i].y <= colonne_souris)
        y_augmente = 1;
    else
        y_augmente = 0;

    matrice[joueur[i].x][joueur[i].y].occuper = 0;
    while (!joueur[i].gel && (joueur[i].x != ligne_souris || joueur[i].y != colonne_souris) && (abs(joueur[i].x - ligne_souris) + abs(joueur[i].y - colonne_souris)) <= joueur[i].pm && !matrice[ligne_souris][colonne_souris].occuper && matrice[ligne_souris][colonne_souris].accessible)
    {
        compteur++;
        clear_bitmap(buffer);
        /// le joueur va vers le sud est
        while(x_augmente && joueur[i].x != ligne_souris && matrice[joueur[i].x + 1][joueur[i].y].accessible)
        {
            joueur[i].direction = 3;
            blit(fond, buffer, 0, 0, 0, 0, fond->w, fond->h);
            animation_deplacement(buffer, fond, joueur, i, matrice, nb_joueurs, respiration_joueur);
            joueur[i].x = joueur[i].x +1;
            //joueur[i].pm--;
            //masked_blit(joueur[i].classe.deplacement[direction][0], buffer, matrice[joueur[i].x][joueur[i].y].x_bloc, matrice[joueur[i].x][joueur[i].y].y_bloc, matrice[joueur[i].x][joueur[i].y].x_bloc + 49, matrice[joueur[i].x][joueur[i].y].y_bloc + 64, SCREEN_W, SCREEN_H);
            //circlefill(buffer, matrice[joueur[i].x][joueur[i].y].x_bloc, matrice[joueur[i].x][joueur[i].y].y_bloc, 9, makecol(0,0,0));
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            joueur[i].casesparcourues += 1;
        }
        /// le joueur va vers le nord ouest
        while(!x_augmente && joueur[i].x != ligne_souris && matrice[joueur[i].x - 1][joueur[i].y].accessible)
        {
            joueur[i].direction = 1;
            blit(fond, buffer, 0, 0, 0, 0, fond->w, fond->h);
            animation_deplacement(buffer, fond, joueur, i, matrice, nb_joueurs, respiration_joueur);
            joueur[i].x = joueur[i].x -1;
            //joueur[i].pm--;
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            joueur[i].casesparcourues += 1;
        }
        /// le joueur va vers le nord est
        while(y_augmente && joueur[i].y != colonne_souris && matrice[joueur[i].x][joueur[i].y + 1].accessible)
        {
            joueur[i].direction = 2;
            blit(fond, buffer, 0, 0, 0, 0, fond->w, fond->h);
            animation_deplacement(buffer, fond, joueur, i, matrice, nb_joueurs, respiration_joueur);
            joueur[i].y = joueur[i].y +1;
            //joueur[i].pm--;
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            joueur[i].casesparcourues += 1;
        }
        /// le joueur va vers le sud ouest
        while(!y_augmente && joueur[i].y != colonne_souris && matrice[joueur[i].x][joueur[i].y - 1].accessible)
        {
            joueur[i].direction = 0;
            blit(fond, buffer, 0, 0, 0, 0, fond->w, fond->h);
            animation_deplacement(buffer, fond, joueur, i, matrice, nb_joueurs, respiration_joueur);
            joueur[i].y = joueur[i].y -1;

            //joueur[i].pm--;
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            joueur[i].casesparcourues += 1;
        }
        if (compteur == 2)
        {
            break;
        }
        *deplacement_effectuer = *deplacement_effectuer +1;

    }
    matrice[joueur[i].x][joueur[i].y].occuper = i + 1;
    rest(20);
}
