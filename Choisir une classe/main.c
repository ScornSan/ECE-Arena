#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>

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

void display_cursor(BITMAP* cursor, BITMAP* buffer, int mouse_x, int mouse_y)
{
    masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, cursor->w, cursor->h);
}

char* ecriture_classe(int i)
{
    switch(i)
    {
    case 0:
        return "GUERRIER";
    case 1:
        return "  MAGE";
    case 2:
        return " ARCHER";
    case 3:
        return "ASSASSIN";
    }
}

void affichage_classe(BITMAP* buffer, BITMAP* classe[], BITMAP* layer, int *nb)
{
    int x_depart = 70;
    char texte[50];
    /*rectfill(buffer, x_depart, 150, 150, 450, makecol(255, 0, 0));
    rectfill(buffer, 100 * 2, 150, 300, 450, makecol(255, 0, 0));
    rectfill(buffer, x_depart + 100 * 3, 150, 450, 450, makecol(255, 0, 0));
    rectfill(buffer, 100 * 5, 150, 600, 450, makecol(255, 0, 0));
    rectfill(buffer, x_depart + 100 * 6, 150, 750, 450, makecol(255, 0, 0));*/
    sprintf(texte, "Joueur %d, choisissez votre classe", *nb + 1);
    textprintf_ex(buffer, font, 500, 20, makecol(255, 0, 0), -1, texte);
    for (int i = 0; i < 4; i++)
    {
        reset_color(classe[0]);
        textprintf(buffer, font, x_depart + 120 * i * 3, 500, makecol(255, 0, 0), ecriture_classe(i));
        masked_blit(classe[i], buffer, 0, 0, 120 * i*3, 150, classe[i]->w, classe[i]->h);
    }
    if(mouse_x >= 30 && mouse_x <= 120 && mouse_y >= 150 && mouse_y <= 450)
    {
        rectfill(buffer, x_depart, 510, x_depart + 56, 512, makecol(255, 0, 0));
        if (mouse_b&1)
        {
            *nb = *nb + 1;
            rest(300);
        }

    }
    if(mouse_x >= 400 && mouse_x <= 500 && mouse_y >= 150 && mouse_y <= 450)
    {
        rectfill(buffer, x_depart + 120 * 3, 510, x_depart + 120 * 3 + 56, 512, makecol(255, 0, 0));
        if (mouse_b&1)
        {
            *nb = *nb + 1;
            rest(300);
        }
    }
    if(mouse_x >= 750 && mouse_x <= 840 && mouse_y >= 150 && mouse_y <= 450)
    {
        rectfill(buffer, x_depart + 120 * 6, 510, x_depart + 120 * 6 + 56, 512, makecol(255, 0, 0));
        if (mouse_b&1)
        {
            *nb = *nb + 1;
            rest(300);
        }
    }
    if(mouse_x >= 1100 && mouse_x <= 1200 && mouse_y >= 150 && mouse_y <= 450)
    {
        rectfill(buffer, x_depart + 120 * 9, 510, x_depart + 120 * 9 + 56, 512, makecol(255, 0, 0));
        if (mouse_b&1)
        {
            *nb = *nb + 1;
            rest(300);
        }

    }
}

int main()
{
    // Déclaration du pointeur sur BITMAP devant recevoir l'image
    BITMAP *buffer;
    BITMAP *cursor;
    BITMAP *layer;
    BITMAP *classe[4];
    int nb = 0;
    char nom_perso[20];
    // paramètres de l'élément à animer
    int posx,posy;    // coordonnées
    int tx,ty;        // taille (largeur et hauteur)
    int depx,depy;    // vecteur déplacement effectif en x et y

    // Lancer allegro et le mode graphique
    allegro_init();
    install_keyboard();
    install_mouse();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT,1280,720,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    // Chargement de l'image (l'allocation a lieu en même temps)
    cursor=load_bitmap("cursor.bmp",NULL);
    layer = load_bitmap("layer.bmp", NULL);

    for (int i = 0; i < 4; i++)
    {
        sprintf(nom_perso, "perso%d.bmp", i);
        classe[i] = load_bitmap(nom_perso,NULL);
    }
    if (!cursor || !classe ||!layer)
    {
        allegro_message("pas pu trouver/charger mon_image.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(buffer);


    // Initialisation des paramètres de l'élément à animer

    // La taille est directement récupérée dans les champs w et h

    // Position initiale au centre


    // mouvements vers la droite et vers le bas
    // on pourrait initialiser aléatoirement ici...

    // Boucle d'animation (quand on arrive aux nombres de joueurs, ici 3, c'est que la selection pour chaque joueur a été faite)
    while (nb != 3)
    {
        clear_bitmap(buffer);
        affichage_classe(buffer, classe, layer, &nb);

        display_cursor(cursor, buffer, mouse_x, mouse_y);
        blit(buffer, screen, 0, 0, 0 , 0, SCREEN_W, SCREEN_H);

        // 4) ON FAIT UNE PETITE PAUSE à chaque fois sinon ça va trop vite...
        rest(20);
    }
    return 0;
}
END_OF_MAIN();
