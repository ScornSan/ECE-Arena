#include "../prototypes.h"
#include "../structures.h"

void creation_icones_classes(t_joueur* joueur)
{
    char classe_guerrier[50];
    char classe_mage[50];
    char classe_mutant[50];
    char classe_assassin[50];
    int i;
    int j;
    for (i = 0; i < 4; i++)
    {
        switch(joueur[i].id_classe)
        {
        case 1: // creation d'une classe guerrier
            //joueur[i].skin
            joueur[i].classe.sort1.logo = load_bitmap("BITMAP/sort1_guerrier2.bmp", NULL);
            joueur[i].classe.sort2.logo = load_bitmap("BITMAP/sort2_guerrier2.bmp", NULL);
            joueur[i].classe.sort3.logo = load_bitmap("BITMAP/sort3_guerrier2.bmp", NULL);
            joueur[i].classe.sort4.logo = load_bitmap("BITMAP/sort4_guerrier.bmp", NULL);
            for (j = 0; j < 4; j++)
            {
                sprintf(classe_guerrier, "BITMAP/DESC_SORTS/desc_guerrier_sort%d.bmp", j + 1);
                joueur[i].classe.sorts[j] = load_bitmap(classe_guerrier, NULL);
            }
            break;
        case 2: // creation d'une classe mage
            //joueur[i].skin
            joueur[i].classe.sort1.logo = load_bitmap("BITMAP/sort2_mage2.bmp", NULL);
            joueur[i].classe.sort2.logo = load_bitmap("BITMAP/sort1_mage2.bmp", NULL);
            joueur[i].classe.sort3.logo = load_bitmap("BITMAP/sort3_mage2.bmp", NULL);
            joueur[i].classe.sort4.logo = load_bitmap("BITMAP/sort4_mage2.bmp", NULL);
            for (j = 0; j < 4; j++)
            {
                sprintf(classe_mage, "BITMAP/DESC_SORTS/desc_mage_sort%d.bmp", j + 1);
                joueur[i].classe.sorts[j] = load_bitmap(classe_mage, NULL);
            }
            break;
        case 3: // creation d'une classe mutant
            //joueur[i].skin
            joueur[i].classe.sort1.logo = load_bitmap("BITMAP/sort1_mutant.bmp", NULL);
            joueur[i].classe.sort2.logo = load_bitmap("BITMAP/sort2_mutant.bmp", NULL);
            joueur[i].classe.sort3.logo = load_bitmap("BITMAP/sort3_mutant2.bmp", NULL);
            joueur[i].classe.sort4.logo = load_bitmap("BITMAP/sort4_mutant2.bmp", NULL);
            for (j = 0; j < 4; j++)
            {
                sprintf(classe_mutant, "BITMAP/DESC_SORTS/desc_mutant_sort%d.bmp", j + 1);
                joueur[i].classe.sorts[j] = load_bitmap(classe_mutant, NULL);
            }
            break;
        case 4: // creation d'une classe assassin
            //joueur[i].skin

            joueur[i].classe.sort1.logo = load_bitmap("BITMAP/sort1_assassin2.bmp", NULL);
            joueur[i].classe.sort2.logo = load_bitmap("BITMAP/sort2_assassin.bmp", NULL);
            joueur[i].classe.sort3.logo = load_bitmap("BITMAP/sort3_assassin.bmp", NULL);
            joueur[i].classe.sort4.logo = load_bitmap("BITMAP/sort4_assassin.bmp", NULL);
            for (j = 0; j < 4; j++)
            {
                sprintf(classe_assassin,"BITMAP/DESC_SORTS/desc_assassin_sort%d.bmp", j + 1);
                joueur[i].classe.sorts[j] = load_bitmap(classe_assassin, NULL);
            }
            break;
        }
    }
}

void creation_classes(t_joueur* joueur)
{
    int i;
    int j;
    for (i = 0; i < 4; i++)
    {
        joueur[i].pv = 55;
        joueur[i].pm = 3;
        joueur[i].pa = 6;
        joueur[i].classe.attaque = 5;
        joueur[i].vivant = 1;
        joueur[i].classe.logo_attaque = load_bitmap("BITMAP/sort_attaque.bmp", NULL);
        joueur[i].r = 0;
        joueur[i].g = 0;
        joueur[i].b = i * 85;

    }
    joueur[0].r = 200;
    joueur[0].g = 0;
    joueur[0].b = 0;

    joueur[1].r = 0;
    joueur[1].g = 200;
    joueur[1].b = 0;
}
