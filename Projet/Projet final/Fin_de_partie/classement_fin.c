#include "../prototypes.h"
#include "../structures.h"

void classement_fin(BITMAP * buffer, t_joueur * joueur, int nb_joueurs, int classement[])
{
    BITMAP *ecran_fin;


    ecran_fin=load_bitmap("BITMAP/GAMEOVER.bmp",NULL);
    if (!ecran_fin)
    {
        allegro_message("pas pu trouver tour joueur/charger mon_image de fin.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    if (nb_joueurs == 2)
    {
        textprintf_ex(buffer, font, 80, 100, makecol(255,255,255), -1, "1er : Joueur %d, %s", classement[0], joueur[classement[0]].pseudo);
        textprintf_ex(buffer, font, 80, 110, makecol(255,255,255), -1, "Degats infligés : %d", joueur[classement[0]].degatstotal);
        textprintf_ex(buffer, font, 80, 120, makecol(255,255,255), -1, "Cases parcourues : %d", joueur[classement[0]].casesparcourues);
        textprintf_ex(buffer, font, 130, 100, makecol(255,255,255), -1, "2eme : Joueur %d, %s", classement[1], joueur[classement[1]].pseudo);
        textprintf_ex(buffer, font, 130, 110, makecol(255,255,255), -1, "Degats infligés : %d", joueur[classement[1]].degatstotal);
        textprintf_ex(buffer, font, 130, 120, makecol(255,255,255), -1, "Cases parcourues : %d", joueur[classement[1]].casesparcourues);
    }
    if (nb_joueurs == 3)
    {
        textprintf_ex(buffer, font, 80, 100, makecol(255,255,255), -1, "1er : Joueur %d, %s", classement[0], joueur[classement[0]].pseudo);
        textprintf_ex(buffer, font, 80, 110, makecol(255,255,255), -1, "Degats infligés : %d", joueur[classement[0]].degatstotal);
        textprintf_ex(buffer, font, 80, 120, makecol(255,255,255), -1, "Cases parcourues : %d", joueur[classement[0]].casesparcourues);
        textprintf_ex(buffer, font, 130, 100, makecol(255,255,255), -1, "2eme : Joueur %d, %s", classement[1], joueur[classement[1]].pseudo);
        textprintf_ex(buffer, font, 130, 110, makecol(255,255,255), -1, "Degats infligés : %d", joueur[classement[1]].degatstotal);
        textprintf_ex(buffer, font, 130, 120, makecol(255,255,255), -1, "Cases parcourues : %d", joueur[classement[1]].casesparcourues);
        textprintf_ex(buffer, font, 200, 100, makecol(255,255,255), -1, "3eme : Joueur %d, %s", classement[2], joueur[classement[2]].pseudo);
        textprintf_ex(buffer, font, 200, 110, makecol(255,255,255), -1, "Degats infligés : %d", joueur[classement[2]].degatstotal);
        textprintf_ex(buffer, font, 200, 120, makecol(255,255,255), -1, "Cases parcourues : %d", joueur[classement[2]].casesparcourues);


    }
    if (nb_joueurs == 4)
    {
        textprintf_ex(buffer, font, 80, 100, makecol(255,255,255), -1, "1er : Joueur %d, %s", classement[0], joueur[classement[0]].pseudo);
        textprintf_ex(buffer, font, 80, 110, makecol(255,255,255), -1, "Degats infligés : %d", joueur[classement[0]].degatstotal);
        textprintf_ex(buffer, font, 80, 120, makecol(255,255,255), -1, "Cases parcourues : %d", joueur[classement[0]].casesparcourues);
        textprintf_ex(buffer, font, 130, 100, makecol(255,255,255), -1, "2eme : Joueur %d, %s", classement[1], joueur[classement[1]].pseudo);
        textprintf_ex(buffer, font, 130, 110, makecol(255,255,255), -1, "Degats infligés : %d", joueur[classement[1]].degatstotal);
        textprintf_ex(buffer, font, 130, 120, makecol(255,255,255), -1, "Cases parcourues : %d", joueur[classement[1]].casesparcourues);
        textprintf_ex(buffer, font, 200, 100, makecol(255,255,255), -1, "3eme : Joueur %d, %s", classement[2], joueur[classement[2]].pseudo);
        textprintf_ex(buffer, font, 200, 110, makecol(255,255,255), -1, "Degats infligés : %d", joueur[classement[2]].degatstotal);
        textprintf_ex(buffer, font, 200, 120, makecol(255,255,255), -1, "Cases parcourues : %d", joueur[classement[2]].casesparcourues);
        textprintf_ex(buffer, font, 260, 100, makecol(255,255,255), -1, "4eme : Joueur %d, %s", classement[3], joueur[classement[3]].pseudo);
        textprintf_ex(buffer, font, 260, 110, makecol(255,255,255), -1, "Degats infligés : %d", joueur[classement[3]].degatstotal);
        textprintf_ex(buffer, font, 260, 120, makecol(255,255,255), -1, "Cases parcourues : %d", joueur[classement[3]].casesparcourues);
    }

    blit(ecran_fin, buffer, 0,0,0,0,SCREEN_W, SCREEN_H);
    blit(buffer, screen,0,0,0,0, SCREEN_W, SCREEN_H);

}
