#include "../prototypes.h"
#include "../structures.h"

void affichage_hud_sorts(t_joueur* joueur, int i, BITMAP* buffer, BITMAP* hud_icone)
{
    masked_blit(hud_icone, buffer, 0, 0, 280, 660, SCREEN_W, SCREEN_H);
    masked_blit(joueur[i].classe.logo_attaque, buffer, 0, 0, 300, 670, SCREEN_W, SCREEN_H);
    blit(joueur[i].classe.sort1.logo, buffer, 0, 0, 335, 670, SCREEN_W, SCREEN_H);
    blit(joueur[i].classe.sort2.logo, buffer, 0, 0, 370, 670, SCREEN_W, SCREEN_H);
    blit(joueur[i].classe.sort3.logo, buffer, 0, 0, 405, 670, SCREEN_W, SCREEN_H);
    blit(joueur[i].classe.sort4.logo, buffer, 0, 0, 440, 670, SCREEN_W, SCREEN_H);
    if (mouse_x >= 300 && mouse_x <= 330 && mouse_y >= 670 && mouse_y <= 700) // attaque de bas
    {
        textprintf_ex(buffer, font, 280, 650, makecol(255, 255, 0), -1, "%s", joueur[i].classe.description_attaque);
        textprintf(buffer, font, 280, 660, makecol(255, 255, 0), "A 1 chance sur 10 d'échouer");
    }
    if (mouse_x >= 335 && mouse_x <= 365 && mouse_y >= 670 && mouse_y <= 700) // sort 1
    if (mouse_x >= 370 && mouse_x <= 400 && mouse_y >= 670 && mouse_y <= 700) // sort 2
    if (mouse_x >= 405 && mouse_x <= 435 && mouse_y >= 670 && mouse_y <= 700) // sort 3
    if (mouse_x >= 440 && mouse_x <= 470 && mouse_y >= 670 && mouse_y <= 700) // sort 4
    i = (i + 1) % 4; // On change le hud des sorts joueur à la fin du tour
}

void affichage_hud_joueur(BITMAP* buffer, BITMAP* hud, t_joueur* joueur, int i)
{
    rectfill(buffer, 79, 650, 79 + joueur[i].pv * 3, 673, makecol(255, 0, 0)); // rectangle pv a reduire quand il perd des hp
    rectfill(buffer, 75, 675, 75 + joueur[i].pa * 35, 685, makecol(0, 0, 255)); // rectangle pa a reduire quand il perd des hp
    rectfill(buffer, 75, 685, 75 + joueur[i].pm * 70, 695, makecol(0, 255, 0)); // rectangle pm a reduire quand il perd des hp
    masked_blit(hud, buffer, 0, 0, 5, 640, SCREEN_W, SCREEN_H);
    textprintf_ex(buffer, font, 125, 658, makecol(255, 255, 255), -1, "PV : %d/55", joueur[i].pv);
    textprintf_ex(buffer, font, 125, 676, makecol(255, 255, 255), -1, "PA : %d/6", joueur[i].pa);
    textprintf_ex(buffer, font, 125, 687, makecol(255, 255, 255), -1, "PM : %d/3", joueur[i].pm);
    i = (i + 1) % 4; // on change le hud du joueur à la fin du tour
}

void tour_joueur(BITMAP* buffer, BITMAP *cursor, t_joueur* joueur)
{
    // Déclaration du pointeur sur BITMAP devant recevoir l'image
    BITMAP *map;
    BITMAP *hud_joueur;
    BITMAP *hud_icone;
    int i = 0;
    int j;

    // Declaration des phrases pour chaque commentaire sur les classes
    for (j = 0; j < 4; j++)
    {
        joueur[j].classe.description_attaque = "Inflige 1 à 5 de dégât à l'adversaire s'il est à la portée du coup (1 carreau).";
    }

    // Chargement de l'image (l'allocation a lieu en m�me temps)

    map = load_bitmap("BITMAP/terraintest.bmp", NULL);
    hud_joueur = load_bitmap("BITMAP/hud_joueur.bmp", NULL);
    hud_icone = load_bitmap("BITMAP/hud_icone_temp.bmp", NULL);

    creation_joueurs(joueur);

    if (!map)
    {
        allegro_message("pas pu trouver tour joueur/charger mon_image.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    clear_bitmap(buffer);
    time_t start = time(NULL);
    int joueur_en_vie = 4;
    // Boucle d'animation
    while (joueur_en_vie != 0)
    {
        clear_bitmap(buffer);
        blit(map, buffer, 250, 100, 0, 0, 1280, 720);
        affichage_hud_sorts(joueur, i, buffer, hud_icone); // Blit de 5 logos (les mêmes pour la barre d'action, à changer après...)
        affichage_hud_joueur(buffer, hud_joueur, joueur, i); // affiche du hud joueur, avec pv, pa, pm
        textprintf_ex(buffer, font, 0, 0, makecol(0, 0, 0), -1, "Mouse X : %d", mouse_x);
        textprintf_ex(buffer, font, 0, 10, makecol(0, 0, 0), -1, "Mouse Y : %d", mouse_y);
        textprintf_ex(buffer, font, 0, 20, makecol(0, 0, 0), -1, "Temps: %f", (float)((time(NULL)) - start));
        rectfill(buffer, 1000, 650, 1000 - (int)((time(NULL)) - start) * 5, 673, makecol(255, 0, 0)); // barre de temps
        display_cursor(cursor, buffer, mouse_x, mouse_y);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        if ((int)(time(NULL) - start >= TEMPS_TOUR) || (mouse_b&1 && (mouse_x >= 900 && mouse_x <= 1000 && mouse_y >= 600 && mouse_y <= 700)))
        {
            start = time(NULL);
            joueur[i].pm = 3; // on remet les pm et pa du joueur au nombre initial
            joueur[i].pa = 6;
            i = (i + 1) % 4;
        }
        rest(20);
    }
    for (int i = 0; i < 4; i++)
    {
        destroy_bitmap(joueur[i].classe.logo_attaque);
        destroy_bitmap(joueur[i].classe.sort1.logo);
        destroy_bitmap(joueur[i].classe.sort2.logo);
        destroy_bitmap(joueur[i].classe.sort3.logo);
        destroy_bitmap(joueur[i].classe.sort4.logo);
    }
    destroy_bitmap(map);
    destroy_bitmap(hud_joueur);
    destroy_bitmap(hud_icone);
}
