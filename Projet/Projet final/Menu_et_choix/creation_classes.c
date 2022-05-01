#include "../prototypes.h"
#include "../structures.h"

void creation_joueurs(t_joueur* joueur)
{
    for (int i = 0; i < 4; i++)
    {
        joueur[i].pv = 55;
        joueur[i].pm = 3;
        joueur[i].pa = 6;
        joueur[i].classe.attaque = 5;
        joueur[i].classe.logo_attaque = load_bitmap("BITMAP/assassin_attaque1_gauche.bmp", NULL);
        switch(joueur[i].id_classe)
        {
        case 1: // creation d'une classe guerrier
            //joueur[i].skin
            joueur[i].classe.sort1.logo = load_bitmap("BITMAP/sort1_guerrier2.bmp", NULL);
            joueur[i].classe.sort2.logo = load_bitmap("BITMAP/sort2_guerrier2.bmp", NULL);
            joueur[i].classe.sort3.logo = load_bitmap("BITMAP/sort3_guerrier2.bmp", NULL);
            joueur[i].classe.sort4.logo = load_bitmap("BITMAP/sort4_guerrier.bmp", NULL);
            break;
        case 2: // creation d'une classe mage
            //joueur[i].skin
            joueur[i].classe.sort1.logo = load_bitmap("BITMAP/sort1_mage2.bmp", NULL);
            joueur[i].classe.sort2.logo = load_bitmap("BITMAP/sort2_mage2.bmp", NULL);
            joueur[i].classe.sort3.logo = load_bitmap("BITMAP/sort3_mage2.bmp", NULL);
            joueur[i].classe.sort4.logo = load_bitmap("BITMAP/sort4_mage2.bmp", NULL);
            break;
        case 3: // creation d'une classe mutant
            //joueur[i].skin
            joueur[i].classe.sort1.logo = load_bitmap("BITMAP/sort1_mutant.bmp", NULL);
            joueur[i].classe.sort2.logo = load_bitmap("BITMAP/sort2_mutant.bmp", NULL);
            joueur[i].classe.sort3.logo = load_bitmap("BITMAP/sort3_mutant2.bmp", NULL);
            joueur[i].classe.sort4.logo = load_bitmap("BITMAP/sort4_mutant2.bmp", NULL);

            break;
        case 4: // creation d'une classe assassin
            //joueur[i].skin

            joueur[i].classe.sort1.logo = load_bitmap("BITMAP/sort1_assassin2.bmp", NULL);
            joueur[i].classe.sort2.logo = load_bitmap("BITMAP/sort2_assassin.bmp", NULL);
            joueur[i].classe.sort3.logo = load_bitmap("BITMAP/sort3_assassin.bmp", NULL);
            joueur[i].classe.sort4.logo = load_bitmap("BITMAP/sort4_assassin.bmp", NULL);
            break;
        }
    }
}
