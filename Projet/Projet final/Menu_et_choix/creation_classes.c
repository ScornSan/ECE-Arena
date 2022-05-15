#include "../prototypes.h"
#include "../structures.h"

void creation_icones_classes(t_joueur* joueur)
{
    char chargement[80];
    char mvt[50];
    char respiration[100];
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
                sprintf(chargement, "BITMAP/DESC_SORTS/desc_guerrier_sort%d.bmp", j + 1);
                joueur[i].classe.spell[j].description = load_bitmap(chargement, NULL);
                sprintf(chargement, "BITMAP/sort%d_guerrier.bmp", j + 1);
                joueur[i].classe.spell[j].logo = load_bitmap(chargement, NULL);
                sprintf(chargement, "SPRITES/CHEVALIER/ATTAQUE/attack_%d.bmp", j);
                joueur[i].classe.anim_attaques[0][j][0] = load_bitmap(chargement, NULL);
                for (k = 0; k < NB_BITMAPS_D; k++)
                {
                    sprintf(mvt, "SPRITES/CHEVALIER/MARCHE/walking_%d_%d.bmp", j, k + 1);
                    joueur[i].classe.deplacement[j][k] = load_bitmap(mvt, NULL);
                    if (k < 2)
                    {
                        sprintf(respiration, "SPRITES/CHEVALIER/RESPIRATION/breath_%d_%d.bmp", j, k);
                        joueur[i].classe.respiration[j][k] = load_bitmap(respiration, NULL);
                    }
                }
                if (!joueur[i].classe.spell[j].description || !joueur[i].classe.spell[j].logo || !joueur[i].classe.deplacement[j][0] || !joueur[i].classe.respiration[j][0])
                {
                    allegro_message("erreur creation classe guerrier");
                    allegro_exit();
                    exit(EXIT_FAILURE);
                }
                /// initialisation degats :
            }
            joueur[i].classe.spell[1].degats_max = 12;
            joueur[i].classe.spell[1].degats_min = 6;
            break;
        case 2: // creation d'une classe mage
            for (j = 0; j < 4; j++)
            {
                sprintf(chargement, "BITMAP/DESC_SORTS/desc_mage_sort%d.bmp", j + 1);
                joueur[i].classe.spell[j].description = load_bitmap(chargement, NULL);
                sprintf(chargement, "BITMAP/sort%d_mage.bmp", j + 1);
                joueur[i].classe.spell[j].logo = load_bitmap(chargement, NULL);
                sprintf(chargement, "SPRITES/MAGE/SORTS/meteorite_%d.bmp", j);
                joueur[i].classe.spell[3].animation_sort[j] = load_bitmap(chargement, NULL); // sort 4
                sprintf(chargement, "SPRITES/MAGE/SOINS/heal_%d.bmp", j);
                joueur[i].classe.spell[0].animation_sort[j] = load_bitmap(chargement, NULL); // sort 1
                for (k = 0; k < NB_BITMAPS_D; k++)
                {
                    sprintf(mvt, "SPRITES/MAGE/MARCHE/walk_%d_%d.bmp", j, k + 1);
                    joueur[i].classe.deplacement[j][k] = load_bitmap(mvt, NULL);
                    if (k < 2)
                    {
                        sprintf(chargement, "SPRITES/MAGE/ATTAQUE/attack_%d_%d.bmp", j, k);
                        joueur[i].classe.anim_attaques[1][j][k] = load_bitmap(chargement, NULL);
                        sprintf(respiration, "SPRITES/MAGE/RESPIRATION/breath_%d_%d.bmp", j, k);
                        joueur[i].classe.respiration[j][k] = load_bitmap(respiration, NULL);
                    }
                }
                if (!joueur[i].classe.spell[j].description || !joueur[i].classe.spell[j].logo || !joueur[i].classe.respiration[j][0])
                {
                    allegro_message("erreur creation classe mage");
                    allegro_exit();
                    exit(EXIT_FAILURE);
                }
            }
            /// HEAL du mage
            joueur[i].classe.spell[0].degats_max = 10;
            joueur[i].classe.spell[0].degats_min = 4;
            /// Sol grondant
            joueur[i].classe.spell[3].degats_max = 10;
            joueur[i].classe.spell[3].degats_min = 5;
            break;
        case 3: // creation d'une classe vampire
            for (j = 0; j < 4; j++)
            {
                sprintf(chargement, "BITMAP/DESC_SORTS/desc_mutant_sort%d.bmp", j + 1);
                joueur[i].classe.spell[j].description = load_bitmap(chargement, NULL);
                sprintf(chargement, "BITMAP/sort%d_mutant.bmp", j + 1);
                joueur[i].classe.spell[j].logo = load_bitmap(chargement, NULL);
                sprintf(chargement, "SPRITES/VAMPIRE/ATTAQUE/attack_%d.bmp", j);
                joueur[i].classe.anim_attaques[2][j][j] = load_bitmap(chargement, NULL);
                if(j<2)
                {
                    sprintf(chargement, "SPRITES/VAMPIRE/SORTS/bats_%d.bmp", j);
                    joueur[i].classe.spell[3].animation_sort[j] = load_bitmap(chargement, NULL);
                }
                for (k = 0; k < NB_BITMAPS_D; k++)
                {
                    sprintf(mvt, "SPRITES/VAMPIRE/MARCHE/walk_%d_%d.bmp", j, k + 1);
                    joueur[i].classe.deplacement[j][k] = load_bitmap(mvt, NULL);
                    if (k < 2)
                    {
                        sprintf(respiration, "SPRITES/VAMPIRE/RESPIRATION/breath_%d_%d.bmp", j, k);
                        joueur[i].classe.respiration[j][k] = load_bitmap(respiration, NULL);
                    }
                }
                if (!joueur[i].classe.spell[j].description || !joueur[i].classe.spell[j].logo || !joueur[i].classe.respiration[j][0])
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
                sprintf(chargement,"BITMAP/DESC_SORTS/desc_assassin_sort%d.bmp", j + 1);
                joueur[i].classe.spell[j].description = load_bitmap(chargement, NULL);
                sprintf(chargement, "BITMAP/sort%d_assassin.bmp", j + 1);
                joueur[i].classe.spell[j].logo = load_bitmap(chargement, NULL);
                sprintf(chargement, "SPRITES/NINJA/ATTAQUE/attack_%d.bmp", j);
                joueur[i].classe.anim_attaques[3][j][j] = load_bitmap(chargement, NULL);
                if(j<2)
                {
                    sprintf(chargement, "SPRITES/NINJA/SORTS/smoke_%d.bmp", j);
                    joueur[i].classe.spell[3].animation_sort[j] = load_bitmap(chargement, NULL);
                    sprintf(chargement, "SPRITES/NINJA/SHURIKEN/shuriken_%d.bmp", j);
                    joueur[i].classe.spell[1].animation_sort[j] = load_bitmap(chargement, NULL);
                }
                for (k = 0; k < NB_BITMAPS_D; k++)
                {
                    sprintf(mvt, "SPRITES/NINJA/MARCHE/walk_%d_%d.bmp", j, k + 1);
                    joueur[i].classe.deplacement[j][k] = load_bitmap(mvt, NULL);
                    if (k < 2)
                    {
                        sprintf(respiration, "SPRITES/NINJA/RESPIRATION/breath_%d_%d.bmp", j, k);
                        joueur[i].classe.respiration[j][k] = load_bitmap(respiration, NULL);
                    }
                }
                if (!joueur[i].classe.spell[j].description || !joueur[i].classe.spell[j].logo || !joueur[i].classe.respiration[j][0])
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
        joueur[i].elimine = 0;
        joueur[i].bouclier = 0;
        joueur[i].brulure = 0;
        joueur[i].compteur_brulure = 0;
        joueur[i].gel = 0;
        joueur[i].compteur_gel = 0;
        joueur[i].lucide = 0;
        joueur[i].compteur_lucide = 0;
        joueur[i].mortel = 0;
        joueur[i].compteur_mortel = 0;
        joueur[i].hemorragie = 0;
        joueur[i].compteur_hemorragie = 0;
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

