#include "../prototypes.h"
#include "../structures.h"

void desc_sort1(t_joueur * joueur, int i, BITMAP * buffer)
{
    switch(joueur[i].id_classe)
    {
    case 1:
        textprintf_ex(buffer, font, 200, 20, makecol(255,255,255), -1, "AUCUN");
        textprintf_ex(buffer, font, 200, 40, makecol(255,255,255), -1, "2");
        textprintf_ex(buffer, font, 200, 60, makecol(255,255,255), -1, "AUCUNE");
        textprintf_ex(buffer, font, 200, 80, makecol(255,255,255), -1, "90%");
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    }
}
