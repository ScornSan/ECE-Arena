#include "../prototypes.h"
#include "../structures.h"

int classement_fin(BITMAP * screen, BITMAP * buffer, t_joueur * joueur, int nb_joueurs, int compteur_fin, int classement[])
{
    BITMAP * ecran_fin = NULL;
    int y_affiche = 40;
    ecran_fin=load_bitmap("BITMAP/GAMEOVER.bmp",NULL);
    blit(ecran_fin, buffer, 0,0,0,0,SCREEN_W, SCREEN_H);
    blit(buffer, screen,0,0,0,0, SCREEN_W, SCREEN_H);

    for (int i = 0; i < nb_joueurs; i++)
    {
        if (joueur[i].vivant == 0)
        {
            classement[compteur_fin] = i;
            compteur_fin--; // Ce compteur est égal à nb_joueur au début
            /// 1 - 4eme
            /// 2 - 3eme
            /// 3 - 2eme
            /// 4 - 1er
            /// (dans le cas des 4 joueurs)
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


    return compteur_fin;

}
