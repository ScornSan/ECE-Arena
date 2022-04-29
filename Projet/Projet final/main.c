#include "structures.h"
#include "prototypes.h"

void display_cursor(BITMAP* cursor, BITMAP* buffer, int mouse_x, int mouse_y)
{
    masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, cursor->w, cursor->h);
}

int main()
{
    BITMAP *cursor;
    BITMAP *buffer;
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

    cursor=load_bitmap("BITMAP/cursor.bmp",NULL);
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(buffer);

    t_joueur* joueur = (t_joueur*)malloc(sizeof(t_joueur) * 4);

    // Boucle d'animation (quand on arrive aux nombres de joueurs, ici 3, c'est que la selection pour chaque joueur a été faite)
    while (key != KEY_ESC)
    {
        choix_classe(buffer, cursor, joueur);
        tour_joueur(buffer, cursor, joueur);
    }
    destroy_bitmap(cursor);
    destroy_bitmap(buffer);
    return 0;
}
END_OF_MAIN();
