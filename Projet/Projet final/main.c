#include "structures.h"
#include "prototypes.h"

void chrono()
{
    time_t start = time (NULL);
    while ((float) (time (NULL) - start)<= 2.1)
    {
        printf ("Duree = %fs\n", (float) (time (NULL) - start));
    }
}

int pourcentage_de_chance() // Retourne u nombre entre 1 et 10
{
    return rand() % 10 + 1; // On appellera le spgm quand on lancera une attaque, et on test pour savoir si l'attaque reussi
}

void display_cursor(BITMAP* cursor, BITMAP* buffer, int mouse_x, int mouse_y)
{
    masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, cursor->w, cursor->h);
}

int main()
{
    srand(time(NULL));
    int nb_joueurs;
    BITMAP *cursor;
    BITMAP *fond;
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
    fond = load_bitmap("BITMAP/fond.bmp", NULL);

    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(buffer);

    t_joueur* joueur = (t_joueur*)malloc(sizeof(t_joueur) * 4);
    if (joueur == NULL)
    {
        allegro_message("Erreur allocation dynamique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    creation_classes(joueur);

    // Boucle d'animation (quand on arrive aux nombres de joueurs, ici 3, c'est que la selection pour chaque joueur a �t� faite)
    while (key != KEY_ESC)
    {
        nb_joueurs = menu(buffer, fond, cursor, joueur);
        choix_classe(buffer, fond, cursor, joueur, nb_joueurs);
        tour_joueur(buffer, cursor, joueur, nb_joueurs);
    }
    destroy_bitmap(cursor);
    destroy_bitmap(buffer);
    free(joueur);
    return 0;
}
END_OF_MAIN();
