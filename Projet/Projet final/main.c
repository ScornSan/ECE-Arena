#include "structures.h"
#include "prototypes.h"

int random(int min, int max)
{
    srand(time(NULL));
    int resultat;
    resultat = min + rand()%(min - max +1);
    return resultat;
}

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
    SAMPLE* son_battle;
    BITMAP *cursor;
    BITMAP *fond;
    BITMAP *buffer;
    BITMAP *son_on;
    BITMAP *son_off;
    t_joueur* joueur;
    FONT* myfont;
    FONT* myfont2;
    int quitter = 0;
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
    son_battle= load_wav("SOUND/sound_battle.wav"); //charger un wav
    son_on = load_bitmap("BITMAP/son_on.bmp", NULL);
    son_off = load_bitmap("BITMAP/son_off.bmp", NULL);
    myfont = load_font("FONT/tempus.pcx", NULL, NULL);
    myfont2 = load_font("FONT/franklin.pcx", NULL, NULL);

    if (!son_menu)   //blindage
    {
        printf("Error loading sound!");
        return 1;
    }

    cursor=load_bitmap("BITMAP/cursor.bmp",NULL);
    fond = load_bitmap("BITMAP/fond.bmp", NULL);

    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(buffer);

    char pseudo[4][20]; // creation pseudo temporaires qui seront stocker dans les structures joueurs

    // Boucle du programme, tant qu'on ne clique pas sur quitter
    /// changer la valeur du 1 en un boolen jeu qui passe par adresse dans le menu,
    ///et si on clique sur quitter a la fin de la partie, on change la valeur du boolen pour quitter la boucle
    while (!quitter)
    {
        play_sample(son_menu, 255, 128, 1000, 1); //lancer la musique en boucle
        nb_joueurs = menu(buffer, fond, cursor, pseudo, son_menu, myfont, son_on, son_off);
        int classement[nb_joueurs];

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
        choix_classe(buffer, fond, cursor, joueur, nb_joueurs, myfont, myfont2, son_menu, son_on, son_off);
        //tour_joueur_alea(joueur, nb_joueurs);
        stop_sample(son_menu);
        tour_joueur(buffer, cursor, joueur, nb_joueurs, son_battle, son_on, son_off, classement);
        stop_sample(son_battle);
        classement_fin(buffer, joueur, nb_joueurs, classement);
    }

    destroy_bitmap(cursor);
    destroy_bitmap(buffer);
    free(joueur);
    return 0;
}
END_OF_MAIN();
