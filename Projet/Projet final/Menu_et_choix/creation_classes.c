#include "../prototypes.h"
#include "../structures.h"

void creation_icones_classes(t_joueur* joueur)
{
    char classe_guerrier[50];
    char sorts_guerrier[50];
    char mvt_guerrier[50];
    char classe_mage[50];
    char sorts_mage[50];
    char mvt_mage[50];
    char classe_mutant[50];
    char sorts_mutant[50];
    char mvt_mutant[50];
    char classe_assassin[50];
    char sorts_assassin[50];
    char mvt_assassin[50];
    int i;
    int j;
    int k;
    for (i = 0; i < 4; i++)
    {
        switch(joueur[i].id_classe)
        {
        case 1: // creation d'une classe guerrier
            for (j = 0; j < NB_SORTS; j++)
            {
                sprintf(classe_guerrier, "BITMAP/DESC_SORTS/desc_guerrier_sort%d.bmp", j + 1);
                sprintf(sorts_guerrier, "BITMAP/sort%d_guerrier.bmp", j + 1);
                joueur[i].classe.spell[j].description = load_bitmap(classe_guerrier, NULL);
                joueur[i].classe.spell[j].logo = load_bitmap(sorts_guerrier, NULL);
                for (k = 0; k < NB_BITMAPS_D; k++)
                {
                    sprintf(mvt_guerrier, "SPRITES/GUERRIER/MARCHE/walking_%d_%d.bmp", j, k);
                    joueur[i].classe.deplacement[j][k] = load_bitmap(mvt_guerrier, NULL);
                }
                if (!joueur[i].classe.spell[j].description || !joueur[i].classe.spell[j].logo || !joueur[i].classe.deplacement[j][0])
                {
                    allegro_message("erreur creation classe guerrier");
                    allegro_exit();
                    exit(EXIT_FAILURE);
                }
            }
            break;
        case 2: // creation d'une classe mage
            for (j = 0; j < 4; j++)
            {
                sprintf(classe_mage, "BITMAP/DESC_SORTS/desc_mage_sort%d.bmp", j + 1);
                sprintf(sorts_mage, "BITMAP/sort%d_mage.bmp", j + 1);
                joueur[i].classe.spell[j].description = load_bitmap(classe_mage, NULL);
                joueur[i].classe.spell[j].logo = load_bitmap(sorts_mage, NULL);
                if (!joueur[i].classe.spell[j].description || !joueur[i].classe.spell[j].logo)
                {
                    allegro_message("erreur creation classe mage");
                    allegro_exit();
                    exit(EXIT_FAILURE);
                }
            }
            break;
        case 3: // creation d'une classe mutant
            for (j = 0; j < 4; j++)
            {
                sprintf(classe_mutant, "BITMAP/DESC_SORTS/desc_mutant_sort%d.bmp", j + 1);
                sprintf(sorts_mutant, "BITMAP/sort%d_mutant.bmp", j + 1);
                joueur[i].classe.spell[j].description = load_bitmap(classe_mutant, NULL);
                joueur[i].classe.spell[j].logo = load_bitmap(sorts_mutant, NULL);
                if (!joueur[i].classe.spell[j].description || !joueur[i].classe.spell[j].logo)
                {
                    allegro_message("erreur creation classe vampire");
                    allegro_exit();
                    exit(EXIT_FAILURE);
                }
            }
            break;
        case 4: // creation d'une classe assassin
            for (j = 0; j < 4; j++)
            {
                sprintf(classe_assassin,"BITMAP/DESC_SORTS/desc_assassin_sort%d.bmp", j + 1);
                sprintf(sorts_assassin, "BITMAP/sort%d_assassin.bmp", j + 1);
                joueur[i].classe.spell[j].description = load_bitmap(classe_assassin, NULL);
                joueur[i].classe.spell[j].logo = load_bitmap(sorts_assassin, NULL);
                if (!joueur[i].classe.spell[j].description || !joueur[i].classe.spell[j].logo)
                {
                    allegro_message("erreur creation classe assassin");
                    allegro_exit();
                    exit(EXIT_FAILURE);
                }
            }
            break;
        }
    }
}

void creation_classes(t_joueur* joueur, int nb_joueurs)
{
    int i;
    for (i = 0; i < nb_joueurs; i++)
    {
        joueur[i].pv = 55;
        joueur[i].pm = 3;
        joueur[i].pa = 6;
        joueur[i].classe.attaque = 5;
        joueur[i].vivant = 1;
        joueur[i].classe.logo_attaque = load_bitmap("BITMAP/sort_attaque.bmp", NULL);
        if (i == 2)
        {
            joueur[2].red = 0;
            joueur[2].green = 170;
            joueur[2].blue = 0;
        }
        if (i == 3)
        {
            joueur[3].red = 0;
            joueur[3].green = 230;
            joueur[3].blue = 230;
        }
    }
    //creation des couleurs joueurs
    joueur[0].red = 170;
    joueur[0].green = 0;
    joueur[0].blue = 0;

    joueur[1].red = 0;
    joueur[1].green = 0;
    joueur[1].blue = 170;
}

