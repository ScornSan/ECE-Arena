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
    SAMPLE* son_menu; //definir un sample de son
    BITMAP *cursor;
    BITMAP *fond;
    BITMAP *buffer;
    t_joueur* joueur;
    FONT* myfont;
    FONT* myfont2;


    // Lancer allegro et le mode graphique
    allegro_init();
    install_mouse();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT,1280,720,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    if (install_sound(DIGI_AUTODETECT, MIDI_NONE, 0) != 0)
    {
        printf("Error initialising sound: %s\n", allegro_error);
        return 1;
    }

    son_menu=  load_wav("SOUND/sound_hub.wav"); //charger un wav
    myfont = load_font("FONT/tempus.pcx", NULL, NULL);
    myfont2 = load_font("FONT/franklin.pcx", NULL, NULL);

    if (!son_menu)   //blindage
    {
        printf("Error loading sound!");
        return 1;
    }

    play_sample(son_menu, 255, 128, 1000, 1); //lancer la musique en boucle

    cursor=load_bitmap("BITMAP/cursor.bmp",NULL);
    fond = load_bitmap("BITMAP/fond.bmp", NULL);

    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(buffer);

    char pseudo[4][20]; // creation pseudo temporaires qui seront stocker dans les structures joueurs

    // Boucle du programme, tant qu'on ne clique pas sur quitter
    while (1) /// changer la valeur du 1 en un boolen jeu qui passe par adresse dans le menu,
              ///et si on clique sur quitter a la fin de la partie, on change la valeur du boolen pour quitter la boucle
    {
        nb_joueurs = menu(buffer, fond, cursor, pseudo, son_menu, myfont, myfont2 );


        joueur = (t_joueur*)malloc(sizeof(t_joueur) * nb_joueurs); // allocation dynamiques des structures joueurs
        if (joueur == NULL)
        {
            allegro_message("Erreur allocation dynamique");
            allegro_exit();
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < nb_joueurs; i++)
        {
            strcpy(joueur[i].pseudo, pseudo[i]);
        }
        creation_classes(joueur, nb_joueurs);
        choix_classe(buffer, fond, cursor, joueur, nb_joueurs, myfont, myfont2);
        tour_joueur_alea(joueur, nb_joueurs);
        stop_sample(son_menu);
        tour_joueur(buffer, cursor, joueur, nb_joueurs);
    }
    destroy_bitmap(cursor);
    destroy_bitmap(buffer);
    free(joueur);
    return 0;
}
END_OF_MAIN();
