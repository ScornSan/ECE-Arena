#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>


int main()
{
    // Déclaration du pointeur sur BITMAP devant recevoir l'image
    BITMAP *buffer;
    BITMAP *cursor;
    BITMAP *sort;
    BITMAP *map;

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

    // Chargement de l'image (l'allocation a lieu en m�me temps)
    cursor= load_bitmap("cursor.bmp",NULL);
    sort = load_bitmap("sort.bmp", NULL);
    map = load_bitmap("terraintest.bmp", NULL);

    if (cursor == NULL || sort == NULL)
    {
        allegro_message("pas pu trouver/charger mon_image.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    buffer = create_bitmap(1280, 720);
    clear_bitmap(buffer);


    // Affichage du curseur personnalisé
    void display_cursor(BITMAP* cursor, BITMAP* buffer, int mouse_x, int mouse_y)
    {
        masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, cursor->w, cursor->h);
    }

    // Boucle d'animation
    while (!key[KEY_ESC])
    {
        clear_bitmap(buffer);
        blit(map, buffer, 250, 100, 0, 0, 1280, 720);
        // Blit de 5 logos (les mêmes pour la barre d'action, à changer après...)
        blit(sort, buffer, 0, 0, 5, 650, SCREEN_W, SCREEN_H);
        blit(sort, buffer, 0, 0, 40, 650, SCREEN_W, SCREEN_H);
        blit(sort, buffer, 0, 0, 75, 650, SCREEN_W, SCREEN_H);
        blit(sort, buffer, 0, 0, 110, 650, SCREEN_W, SCREEN_H);
        blit(sort, buffer, 0, 0, 145, 650, SCREEN_W, SCREEN_H);
        display_cursor(cursor, buffer, mouse_x, mouse_y);
        blit(buffer, screen, 0, 0, 0 , 0, SCREEN_W, SCREEN_H);
        rest(20);
    }
    return 0;
}
END_OF_MAIN();
