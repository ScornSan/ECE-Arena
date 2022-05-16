#include "../prototypes.h"
#include "../structures.h"

void classement_fin(BITMAP * buffer, t_joueur * joueur, int nb_joueurs, int classement[])
{
    BITMAP *ecran_fin = NULL;
    int y_affiche = 40;
    int elimine = 1;
    int compteur_fin = nb_joueurs - 1;
    ecran_fin=load_bitmap("BITMAP/GAMEOVER.bmp",NULL);
    if (!ecran_fin)
    {
        allegro_message("pas pu trouver tour joueur/charger mon_image de fin.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    blit(ecran_fin, buffer, 0,0,0,0,SCREEN_W, SCREEN_H);
    blit(buffer, screen,0,0,0,0, SCREEN_W, SCREEN_H);

    while (elimine != nb_joueurs - 1)
    {
        for (int i = 0; i < nb_joueurs; i++)
        {
            if (joueur[i].elimine == elimine)
            {
                classement[compteur_fin] = i;
                compteur_fin--; // Ce compteur est égal à nb_joueur - 1 au début
                /// 1 - 4eme
                /// 2 - 3eme
                /// 3 - 2eme
                /// 4 - 1er
                /// (dans le cas des 4 joueurs)
            }
        }
        elimine++;
    }
    /// Test pour le joueur pas éliminé, qui sera premier
    for (int i = 0; i < nb_joueurs; i++)
    {
        if (joueur[i].elimine == 0) // le joueur i n'est pas éliminé car pas mort
        {
            classement[compteur_fin] = i;
        }
    }

    if (compteur_fin == 0)
    {
        for (int i = 0; i < nb_joueurs; i++)
        {
            if (joueur[i].vivant == 1)
            {
                ecran_fin=load_bitmap("BITMAP/GAMEOVER.bmp",NULL);
                classement[compteur_fin] = i;
            }
        }
        clear_bitmap(buffer);
        blit(ecran_fin, buffer, 0,0,0,0,SCREEN_W, SCREEN_H);

        for (int i = nb_joueurs; i < 0; i--)
        {
            textprintf_ex(buffer,font,96,y_affiche,makecol(0,255,0), makecol(0,0,0),"%deme : Joueur %d", i, classement[i]);
            y_affiche += 10;
        }
        blit(buffer, screen,0,0,0,0, SCREEN_W, SCREEN_H);
    }
    // Après ces étapes, nous sommes censé obtenir un tableau classement de la taille de nb_joueurs
    // qui contient la numéro du joueur en fonction de sa place (ordre du tableau : case 0, premier)
}
