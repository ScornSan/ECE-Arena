#include "../prototypes.h"
#include "../structures.h"

void reset_color(BITMAP *image)
{
    for (int x = 0; x<image->w; x++)
        for (int y = 0; y<image->h; y++)
        {
            int temp;
            int r;
            int g;
            int b;
            int nouv;
            temp = getpixel(image, x, y);
            if (temp != makecol(255, 0, 255))
            {
                r = getr(temp);
                g = getg(temp);
                b = getb(temp);
                nouv = makecol(r, g, b);
                putpixel(image, x, y, nouv);
            }
        }
}

void change_color(BITMAP *image)
{
    for (int x = 0; x<image->w; x++)
        for (int y = 0; y<image->h; y++)
        {
            int temp;
            int r;
            int g;
            int b;
            int nouv;
            temp = getpixel(image, x, y);
            if (temp != makecol(255, 0, 255))
            {
                r = getr(temp);
                g = getg(temp);
                b = getb(temp);
                nouv = makecol(r, g, b) + 1;
                putpixel(image, x, y, nouv);
            }
        }
}

char* ecriture_classe(int i)
{
    switch(i)
    {
    case 0:
        return "GUERRIER";
    case 1:
        return " MAGE";
    case 2:
        return "VAMPIRE";
    case 3:
        return "ASSASSIN";
    }
    return 0;
}

void affichage_classe(t_joueur* joueur, BITMAP* buffer, BITMAP *bg, BITMAP* classe[], BITMAP* desc_classe[], int *nb,  FONT* myfont, FONT* myfont2 )
{
    int x_depart = 40;
    char texte[50];

    blit(bg, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    sprintf(texte, "%s, choisissez votre classe", joueur[*nb].pseudo);
    textprintf_ex(buffer, myfont2, 500, 20, makecol(joueur[*nb].red, joueur[*nb].green, joueur[*nb].blue), -1, texte);
    for (int i = 0; i < 4; i++)
    {
        reset_color(classe[0]);
        textprintf_ex(buffer, myfont2, x_depart , 440, makecol(0, 0, 0), -1, ecriture_classe(i));
        masked_blit(classe[i], buffer, 0, 0, 120 * i*3, 150, classe[i]->w, classe[i]->h);
        x_depart = x_depart+366;

    }
    textprintf_ex(buffer,font,96,36,makecol(0,255,0), makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);
    /// CLASSE GUERRIER
    if(mouse_x >= 30 && mouse_x <= 120 && mouse_y >= 150 && mouse_y <= 450)
    {
        textprintf_ex(buffer, myfont2, 40 , 440, makecol(255, 255, 255), -1, "GUERRIER");
        blit(desc_classe[0], buffer, 0, 0, 330, 480, SCREEN_W, SCREEN_H);
        if (mouse_b&1)
        {
            joueur[*nb].id_classe = 1;
            *nb = *nb + 1;
            rest(100);
        }
    }
    /// CLASSE MAGE
    if(mouse_x >= 400 && mouse_x <= 500 && mouse_y >= 150 && mouse_y <= 450)
    {
        textprintf_ex(buffer, myfont2, 406 , 440, makecol(255, 255, 255), -1, " MAGE");
        blit(desc_classe[1], buffer, 0, 0, 330, 480, SCREEN_W, SCREEN_H);
        if (mouse_b&1)
        {
            joueur[*nb].id_classe = 2;
            *nb = *nb + 1;
            rest(100);
        }
    }
    /// CLASSE VAMPIRE
    if(mouse_x >= 750 && mouse_x <= 840 && mouse_y >= 150 && mouse_y <= 450)
    {
        textprintf_ex(buffer, myfont2, 782-10 , 440, makecol(255, 255, 255), -1, "VAMPIRE");
        blit(desc_classe[2], buffer, 0, 0, 330, 480, SCREEN_W, SCREEN_H);
        if (mouse_b&1)
        {
            joueur[*nb].id_classe = 3;
            *nb = *nb + 1;
            rest(100);
        }
    }
    /// CLASSE ASSASSIN
    if(mouse_x >= 1100 && mouse_x <= 1200 && mouse_y >= 150 && mouse_y <= 450)
    {
        textprintf_ex(buffer, myfont2, 1148-10 , 440, makecol(255, 255, 255), -1, "ASSASSIN");
        blit(desc_classe[3], buffer, 0, 0, 330, 480, SCREEN_W, SCREEN_H);
        if (mouse_b&1)
        {
            joueur[*nb].id_classe = 4;
            *nb = *nb + 1;
            rest(100);
        }
    }
}

void choix_classe(BITMAP *buffer, BITMAP *fond, BITMAP* cursor, t_joueur* joueur, int nb_joueurs,  FONT* myfont, FONT* myfont2, SAMPLE* son_menu, BITMAP* son_on, BITMAP* son_off)
{
    // Déclaration du pointeur sur BITMAP devant recevoir l'image
    BITMAP *classe[4];
    BITMAP *desc_classe[4];
    int nb = 0;
    char nom_perso[20];
    char nom_classe[40];
    int clic = 0;

    // Chargement de l'image (l'allocation a lieu en même temps)
    for (int i = 0; i < 4; i++)
    {
        sprintf(nom_perso, "BITMAP/persoo%d.bmp", i);
        classe[i] = load_bitmap(nom_perso,NULL);
        if (!classe[i])
        {
            allegro_message("pas pu trouver choix classe/charger mon_image.bmp");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < 4; i++)
    {
        sprintf(nom_classe, "BITMAP/DESC_CLASSES/desc_classe%d.bmp", i);
        desc_classe[i] = load_bitmap(nom_classe,NULL);
        if (!desc_classe[i])
        {
            allegro_message("pas pu trouver/charger les desc des classes");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }

    clear_bitmap(buffer);


    // Boucle d'animation (quand on arrive aux nombres de joueurs, ici 3, c'est que la selection pour chaque joueur a été faite)
    while (nb != nb_joueurs)
    {
        clear_bitmap(buffer);
        affichage_classe(joueur, buffer, fond, classe, desc_classe, &nb, myfont, myfont2);
        affichage_son(buffer, cursor, son_menu, &clic);
        if (clic)
        {
            draw_sprite(buffer, son_off, 0, 0);
        }
        else
        {
            draw_sprite(buffer, son_on, 0, 0);
        }
        display_cursor(cursor, buffer, mouse_x, mouse_y);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        // 4) ON FAIT UNE PETITE PAUSE à chaque fois sinon ça va trop vite...
        //rest(20);
        rest(20);
    }
    stop_sample(son_menu);
    rest(50);
}
