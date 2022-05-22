#include "../prototypes.h"
#include "../structures.h"

void test_effets(t_joueur* joueur, int j)
{
    /// BRULURE
    if (joueur[j].brulure)
    {
        joueur[j].pv = joueur[j].pv - random(3, 6);
    }
    /// GEL
    if (joueur[j].gel)
    {
        joueur[j].pm = 0;
    }
    /// HEMORRAGIE
    if (joueur[j].hemorragie)
    {
        printf("saignement\n");
        joueur[j].pv = joueur[j].pv - random(4, 8);
    }
    /// RAGE
    if (joueur[j].rage)
    {
        joueur[j].classe.spell[1].degats_min = 10;
        joueur[j].classe.spell[1].degats_max = 15;
        joueur[j].classe.spell[2].degats_min = 8;
        joueur[j].classe.spell[2].degats_max = 12;
        joueur[j].pm = 4;
    }
}
