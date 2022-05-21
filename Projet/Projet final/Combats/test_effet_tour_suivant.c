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
        joueur[j].pv = joueur[j].pv - random(5, 10);
    }
    /// LUCIDE
    if (joueur[j].lucide)
    {
        joueur[j].pa = 8;
        joueur[j].pm = 5;
    }
    /// RAGE
    if (joueur[j].rage)
    {

        joueur[j].classe.spell[1].degats_min = 8;
        joueur[j].classe.spell[1].degats_max = 12;
        joueur[j].pm = 4;
    }
    /// MORT
    if (joueur[j].pv <= 0)
    {
        joueur[j].vivant = 0;
    }
}
