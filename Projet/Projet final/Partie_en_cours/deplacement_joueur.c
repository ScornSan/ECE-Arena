#include "../prototypes.h"
#include "../structures.h"

void deplacement_joueur(BITMAP* buffer)
{
    if (mouse_x >= 194 && mouse_x <= 194 + 46 && mouse_y >= 492 && mouse_y <= 492 + 26)
    {
        rectfill(buffer, 0, 0, 100, 100, makecol(0, 0, 0));
    }
}
