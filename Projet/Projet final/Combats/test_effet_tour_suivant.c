#include "../prototypes.h"
#include "../structures.h"

void test_effets(t_joueur* joueur, int i)
{
    /// BRULURE
    if (joueur[i].brulure)
    {
        joueur[i].pv = joueur[i].pv - random(3, 6);
    }
    /// GEL
    if (joueur[i].gel)
    {
        joueur[i].pm = 0;
    }
    /// HEMORRAGIE
    if (joueur[i].hemorragie)
    {
        joueur[i].pv = joueur[i].pv - random(5, 10);
    }
    /// LUCIDE
    if (joueur[i].lucide)
    {
        joueur[i].pa = 8;
        joueur[i].pa = 5;
    }
    /// RAGE
    if (joueur[i].rage)
    {
        joueur[i].classe.spell[1].degats_min = 8;
        joueur[i].classe.spell[1].degats_max = 12;
        joueur[i].pm = 4;
    }
}
