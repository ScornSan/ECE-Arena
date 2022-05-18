#include "../prototypes.h"
#include "../structures.h"

void affichage_hud_sorts(t_joueur* joueur, int i, int nb_joueurs, BITMAP* buffer, BITMAP* hud_icone, BITMAP* desc_sorts)
{
    masked_blit(hud_icone, buffer, 0, 0, 280, 660, SCREEN_W, SCREEN_H);
    masked_blit(joueur[i].classe.logo_attaque, buffer, 0, 0, 300, 670, SCREEN_W, SCREEN_H);
    blit(joueur[i].classe.spell[0].logo, buffer, 0, 0, 335, 670, SCREEN_W, SCREEN_H);
    blit(joueur[i].classe.spell[1].logo, buffer, 0, 0, 370, 670, SCREEN_W, SCREEN_H);
    blit(joueur[i].classe.spell[2].logo, buffer, 0, 0, 405, 670, SCREEN_W, SCREEN_H);
    blit(joueur[i].classe.spell[3].logo, buffer, 0, 0, 440, 670, SCREEN_W, SCREEN_H);
    if (mouse_x >= 300 && mouse_x <= 330 && mouse_y >= 670 && mouse_y <= 700) // attaque de bas
    {
        masked_blit(desc_sorts, buffer, 0, 0, 279, 560, SCREEN_W, SCREEN_H);
    }
    if (mouse_x >= 335 && mouse_x <= 365 && mouse_y >= 670 && mouse_y <= 700) // sort 1
    {
        masked_blit(desc_sorts, buffer, 0, 0, 279, 560, SCREEN_W, SCREEN_H); // affichage bitmap description
        masked_blit(joueur[i].classe.spell[0].description, buffer, 0, 0, 279, 560, SCREEN_W, SCREEN_H); // affichage description sort 1

    }
    if (mouse_x >= 370 && mouse_x <= 400 && mouse_y >= 670 && mouse_y <= 700) // sort 2
    {
        masked_blit(desc_sorts, buffer, 0, 0, 279, 560, SCREEN_W, SCREEN_H); // affichage stats sorts
        masked_blit(joueur[i].classe.spell[1].description, buffer, 0, 0, 279, 560, SCREEN_W, SCREEN_H); // affichage bitmap description sort 2

    }
    if (mouse_x >= 405 && mouse_x <= 435 && mouse_y >= 670 && mouse_y <= 700) // sort 3
    {
        masked_blit(desc_sorts, buffer, 0, 0, 279, 560, SCREEN_W, SCREEN_H); // affichage stats sorts
        masked_blit(joueur[i].classe.spell[2].description, buffer, 0, 0, 279, 560, SCREEN_W, SCREEN_H); // affichage description sort 3

    }
    if (mouse_x >= 440 && mouse_x <= 470 && mouse_y >= 670 && mouse_y <= 700) // sort 4
    {
        masked_blit(desc_sorts, buffer, 0, 0, 279, 560, SCREEN_W, SCREEN_H); // affichage stats sort
        masked_blit(joueur[i].classe.spell[3].description, buffer, 0, 0, 279, 560, SCREEN_W, SCREEN_H); // affichage description sort 4
    }
}

void affichage_hud_joueur(BITMAP* buffer, BITMAP** hud, t_joueur* joueur, int i, BITMAP **icone_classes)
{
    if (joueur[i].pv <= 55)
    {
        rectfill(buffer, 72, 650, 74 + joueur[i].pv * 3, 673, makecol(255, 0, 0)); // rectangle pv a reduire quand il perd des hp
    }
    else
    {
        rectfill(buffer, 72, 650, 74 + 55 * 3, 673, makecol(250, 240, 0)); // rectangle pv a reduire quand il perd des hp
    }
    rectfill(buffer, 68, 675, 70 + joueur[i].pa * 30, 685, makecol(0, 0, 255)); // rectangle pa a reduire quand il perd des hp
    rectfill(buffer, 66, 685, 70 + joueur[i].pm * 60, 695, makecol(0, 255, 0)); // rectangle pm a reduire quand il perd des hp
    masked_blit(icone_classes[joueur[i].id_classe - 1], buffer, 0, 0, 3, 640, SCREEN_W, SCREEN_H);
    masked_blit(hud[i], buffer, 0, 0, 3, 640, SCREEN_W, SCREEN_H);
    textprintf_ex(buffer, font, 120, 658, makecol(255, 255, 255), -1, "PV : %d/55", joueur[i].pv);
    textprintf_ex(buffer, font, 120, 676, makecol(255, 255, 255), -1, "PA : %d/6", joueur[i].pa);
    textprintf_ex(buffer, font, 120, 687, makecol(255, 255, 255), -1, "PM : %d/3", joueur[i].pm);
}

void affichage_general(BITMAP *buffer, BITMAP *map, t_joueur* joueur, int i, int nb_joueurs, BITMAP** hud_joueur, BITMAP **icone_classes, BITMAP *hud_icone, BITMAP *desc_sorts)
{
    // Affichage de la map
    blit(map, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    affichage_hud_sorts(joueur, i, nb_joueurs, buffer, hud_icone, desc_sorts); // Blit de 5 logos (les mêmes pour la barre d'action, à changer après...)
    affichage_hud_joueur(buffer, hud_joueur, joueur, i, icone_classes); // affiche du hud joueur, avec pv, pa, pm
}
