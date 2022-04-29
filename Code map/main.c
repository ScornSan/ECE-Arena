#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>

void initialisationAllegro()
{
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
}

void encadrement_souris(BITMAP * buffer, int vert)
{
    int r,g,b;
    if(vert == 222)
    {
        r = 222;
        g = 222;
        b = 0;
    }
    else if(vert == 0)
    {
        r = 222;
        g = 0;
        b = 0;
    }
    else
    {
        r = 0;
        g = 0;
        b = 0;
    }
    line(buffer, mouse_x -20, mouse_y , mouse_x , mouse_y -12, makecol(r,g,b));
    line(buffer, mouse_x -20, mouse_y, mouse_x, mouse_y +12, makecol(r,g,b));
    line(buffer, mouse_x, mouse_y -12, mouse_x + 20, mouse_y, makecol(r,g,b));
    line(buffer, mouse_x, mouse_y +12, mouse_x +20, mouse_y, makecol(r,g,b));
}
void deplacement_haut_droite(int *x_joueur, int *y_joueur, int x_souris, int y_souris)
{
    int etat_x = 0, etat_y = 0;
    while (etat_x == 0 || etat_y == 0)
    {
        if (*x_joueur >= x_souris)
        {
            etat_x = 1;
        }
        else
        {
            *x_joueur = *x_joueur + 5;
        }
        if (*y_joueur <= y_souris)
        {
            etat_y = 1;
        }
        else
        {
            *y_joueur = *y_joueur - 5;
        }
        circlefill(screen, *x_joueur, *y_joueur, 8, makecol(0,0,0));
        usleep(30000);
    }
}

void deplacement_haut_gauche(int *x_joueur, int *y_joueur, int x_souris, int y_souris)
{
    int etat_x = 0, etat_y = 0;
    while (etat_x == 0 || etat_y == 0)
    {
        if (*x_joueur <= x_souris)
        {
            etat_x = 1;
        }
        else
        {
            *x_joueur = *x_joueur - 5;
        }
        if (*y_joueur <= y_souris)
        {
            etat_y = 1;
        }
        else
        {
            *y_joueur = *y_joueur - 5;
        }
        circlefill(screen, *x_joueur, *y_joueur, 8, makecol(0,0,0));
        usleep(30000);
    }
}

void deplacement_bas_droite(int *x_joueur, int *y_joueur, int x_souris, int y_souris)
{
    int etat_x = 0, etat_y = 0;
    while (etat_x == 0 || etat_y == 0)
    {
        if (*x_joueur >= x_souris)
        {
            etat_x = 1;
        }
        else
        {
            *x_joueur = *x_joueur + 5;
        }
        if (*y_joueur >= y_souris)
        {
            etat_y = 1;
        }
        else
        {
            *y_joueur = *y_joueur + 5;
        }
        circlefill(screen, *x_joueur, *y_joueur, 8, makecol(0,0,0));
        usleep(30000);
    }
}

void deplacement_bas_gauche(int *x_joueur, int *y_joueur, int x_souris, int y_souris)
{
    int etat_x = 0, etat_y = 0;
    while (etat_x == 0 || etat_y == 0)
    {
        if (*x_joueur <= x_souris)
        {
            etat_x = 1;
        }
        else
        {
            *x_joueur = *x_joueur - 5;
        }
        if (*y_joueur >= y_souris)
        {
            etat_y = 1;
        }
        else
        {
            *y_joueur = *y_joueur + 5;
        }
        circlefill(screen, *x_joueur, *y_joueur, 8, makecol(0,0,0));
        usleep(30000);
    }
}


void deplacement_joueur(BITMAP * buffer, int *x_joueur, int *y_joueur, int x_souris, int y_souris)
{
    if ((*x_joueur - x_souris <= 0) && (*y_joueur - y_souris >= 0))
    {
        deplacement_haut_droite(x_joueur, y_joueur, x_souris, y_souris);
    }
    else if ((*x_joueur - x_souris > 0) && (*y_joueur - y_souris >= 0))
    {
        deplacement_haut_gauche(x_joueur, y_joueur, x_souris, y_souris);
    }
    else if ((*x_joueur - x_souris <= 0) && (*y_joueur - y_souris < 0))
    {
        deplacement_bas_droite(x_joueur, y_joueur, x_souris, y_souris);
    }
    else if ((*x_joueur - x_souris > 0) && (*y_joueur - y_souris < 0))
    {
        deplacement_bas_gauche(x_joueur, y_joueur, x_souris, y_souris);
    }
}

int main()
{
    srand(time(NULL));
    initialisationAllegro();
    show_mouse(screen);
    BITMAP * imagechargee;
    BITMAP * buffer;
    imagechargee =load_bitmap("map.bmp",NULL);
    buffer =create_bitmap(1280,720);
    int x_joueur = 482 , y_joueur = 462;
    int x_souris, y_souris;
    while (!key[KEY_ESC])
    {
        rectfill(buffer, 400, 400, 900,600, makecol(222,222,0));
        rectfill(buffer, 400, 200, 900,399, makecol(222,0,0));
        int vert = getg(getpixel(buffer, mouse_x, mouse_y));
        blit(imagechargee, buffer, 0, 0, 0, 0, imagechargee->w, imagechargee->h);
        if(mouse_b && 1)
        {
            x_souris = mouse_x;
            y_souris = mouse_y;
            deplacement_joueur(buffer, &x_joueur, &y_joueur, x_souris, y_souris);
        }
        circlefill(buffer, x_joueur, y_joueur, 8, makecol(0,0,0));
        encadrement_souris(buffer, vert);
        textprintf_ex(buffer, font, 415, 710, makecol(0,255,0), -1, "position de la souris : x = %d et y = %d", mouse_x, mouse_y);
        blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
    }
    destroy_bitmap(imagechargee);
    destroy_bitmap(buffer);
    return 0;
}END_OF_MAIN() ;
