#include "../prototypes.h"
#include "../structures.h"

void creation_icones_classes(t_joueur* joueur)
{
    char classe_guerrier[50];
    char sorts_guerrier[50];
    char classe_mage[50];
    char sorts_mage[50];
    char classe_mutant[50];
    char sorts_mutant[50];
    char classe_assassin[50];
    char sorts_assassin[50];
    int i;
    int j;
    for (i = 0; i < 4; i++)
    {
        switch(joueur[i].id_classe)
        {
        case 1: // creation d'une classe guerrier
            //joueur[i].skin
            /*joueur[i].classe.sort1.logo = load_bitmap("BITMAP/sort1_guerrier2.bmp", NULL);
            joueur[i].classe.sort2.logo = load_bitmap("BITMAP/sort2_guerrier2.bmp", NULL);
            joueur[i].classe.sort3.logo = load_bitmap("BITMAP/sort3_guerrier2.bmp", NULL);
            joueur[i].classe.sort4.logo = load_bitmap("BITMAP/sort4_guerrier.bmp", NULL);*/
            for (j = 0; j < 4; j++)
            {
                sprintf(classe_guerrier, "BITMAP/DESC_SORTS/desc_guerrier_sort%d.bmp", j + 1);
                sprintf(sorts_guerrier, "BITMAP/sort%d_guerrier.bmp", j + 1);
                joueur[i].classe.spell[j].description = load_bitmap(classe_guerrier, NULL);
                joueur[i].classe.spell[j].logo = load_bitmap(sorts_guerrier, NULL);
                if (!joueur[i].classe.spell[j].description || !joueur[i].classe.spell[j].logo)
                {
                    allegro_message("erreur creation classe guerrier");
                    allegro_exit();
                    exit(EXIT_FAILURE);
                }
            }
            break;
        case 2: // creation d'une classe mage
            //joueur[i].skin
            /*joueur[i].classe.sort1.logo = load_bitmap("BITMAP/sort2_mage2.bmp", NULL);
            joueur[i].classe.sort2.logo = load_bitmap("BITMAP/sort1_mage2.bmp", NULL);
            joueur[i].classe.sort3.logo = load_bitmap("BITMAP/sort3_mage2.bmp", NULL);
            joueur[i].classe.sort4.logo = load_bitmap("BITMAP/sort4_mage2.bmp", NULL);*/
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
            //joueur[i].skin
            /*joueur[i].classe.sort1.logo = load_bitmap("BITMAP/sort1_mutant.bmp", NULL);
            joueur[i].classe.sort2.logo = load_bitmap("BITMAP/sort2_mutant.bmp", NULL);
            joueur[i].classe.sort3.logo = load_bitmap("BITMAP/sort3_mutant2.bmp", NULL);
            joueur[i].classe.sort4.logo = load_bitmap("BITMAP/sort4_mutant2.bmp", NULL);*/
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
            //joueur[i].skin

            /*joueur[i].classe.sort1.logo = load_bitmap("BITMAP/sort1_assassin2.bmp", NULL);
            joueur[i].classe.sort2.logo = load_bitmap("BITMAP/sort2_assassin.bmp", NULL);
            joueur[i].classe.sort3.logo = load_bitmap("BITMAP/sort3_assassin.bmp", NULL);
            joueur[i].classe.sort4.logo = load_bitmap("BITMAP/sort4_assassin.bmp", NULL);*/
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
    }
    //creation des couleurs joueurs
    joueur[0].red = 170;
    joueur[0].green = 0;
    joueur[0].blue = 0;

    joueur[1].red = 0;
    joueur[1].green = 0;
    joueur[1].blue = 170;

    joueur[2].red = 0;
    joueur[2].green = 170;
    joueur[2].blue = 0;

    joueur[3].red = 0;
    joueur[3].green = 230;
    joueur[3].blue = 230;

}
