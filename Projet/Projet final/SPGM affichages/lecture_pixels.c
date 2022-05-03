#include "../prototypes.h"
#include "../structures.h"

void lecture_pixels_buffer_map(BITMAP * buffer_map, int *red_mouse, int *green_mouse, int *blue_mouse)
{
    *green_mouse = getg(getpixel(buffer_map, mouse_x, mouse_y));
    *red_mouse = getr(getpixel(buffer_map, mouse_x, mouse_y));
    *blue_mouse = getb(getpixel(buffer_map, mouse_x, mouse_y));
}

void reperage_bloc_souris(int *ligne_souris, int *colonne_souris,int red_mouse, int green_mouse, int blue_mouse, t_bloc tab_bloc[23][23], int *autorisation_dep)
{
    for (int i = 0; i<23; i++)
    {
        for (int j = 0; j<23; j++)
        {
            if (tab_bloc[i][j].red == red_mouse && tab_bloc[i][j].green == green_mouse && tab_bloc[i][j].blue == blue_mouse)
            {
                *ligne_souris = i;
                *colonne_souris = j;
            }
        }
    }
    /// blindage souris pour clic en dehros de la zone verte
    if(getr(getpixel(screen, mouse_x, mouse_y)) == 0 && getg(getpixel(screen, mouse_x, mouse_y)) == 255 && getb(getpixel(screen, mouse_x, mouse_y)) == 0)
    {
        *autorisation_dep = 1;
    }
    else
    {
        *autorisation_dep = 0;
    }
}
