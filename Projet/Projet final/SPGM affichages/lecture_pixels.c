#include "../prototypes.h"
#include "../structures.h"

void lecture_pixels_buffer_map(BITMAP * buffer_map, int *red_mouse, int *green_mouse, int *blue_mouse)
{
    *green_mouse = getg(getpixel(buffer_map, mouse_x, mouse_y));
    *red_mouse = getr(getpixel(buffer_map, mouse_x, mouse_y));
    *blue_mouse = getb(getpixel(buffer_map, mouse_x, mouse_y));
}

void reperage_bloc_souris(int *ligne_souris, int *colonne_souris, int red_mouse, int green_mouse, int blue_mouse, t_bloc matrice[23][23], int *autorisation_dep, t_joueur* j, int i)
{
    for (int j = 0; j<23; j++)
    {
        for (int k = 0; k<23; k++)
        {
            if (matrice[j][k].red == red_mouse && matrice[j][k].green == green_mouse && matrice[j][k].blue == blue_mouse)
            {
                *ligne_souris = j;
                *colonne_souris = k;
            }
        }
    }
    /// blindage souris pour clic en dehros de la zone verte
    /*if(getr(getpixel(screen, mouse_x, mouse_y)) == j[i].red && getg(getpixel(screen, mouse_x, mouse_y)) == j[i].green && getb(getpixel(screen, mouse_x, mouse_y)) == j[i].blue)
    {
        *autorisation_dep = 1;
    }
    else
    {
        *autorisation_dep = 0;
    }*/
}
