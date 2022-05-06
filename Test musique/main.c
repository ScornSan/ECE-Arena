#include <allegro.h>
#include <stdio.h>

int main()
{
    SAMPLE* s; //definir un sample de son

    if (allegro_init() != 0)
    {
        printf("Error initialising Allegro.\n");
        return 1;
    }

    install_keyboard();
    install_mouse();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,640,480,0,0)!=0)
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

    s=  load_wav("sound_hub.wav"); //charger un wav

    if (!s)   //blindage
    {
        printf("Error loading sound!");
        return 1;
    }

    printf("Playing music now !\n");

    play_sample(s, 255, 128, 1000, 1); //lancer la musique en boucle



    while (!key[KEY_ESC])
    {
        if (mouse_b&1)
        {
            play_sample(s, 255, 128, 1000, 1); //lancer la musique en boucle
        }
        if (mouse_b&2)
        {
            stop_sample(s);
            //play_sample(s, 255, 128, 1000, 1); //lancer la musique en boucle
        }
    } //va tourner en boucle tant qu'on n'appuie pas sur echape

    destroy_sample(s);

    allegro_exit();

    return 0;
}
END_OF_MAIN();
