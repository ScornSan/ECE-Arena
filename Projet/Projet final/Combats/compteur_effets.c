#include "../prototypes.h"
#include "../structures.h"

void compteur_effet(t_joueur* joueur, int i)
{
    /// BOUCLIER
    if (joueur[i].bouclier && joueur[i].compteur_bouclier >= 2)
    {
        joueur[i].bouclier = 0;
        joueur[i].compteur_bouclier = 0;
    }
    else
    {
        joueur[i].compteur_bouclier = joueur[i].compteur_bouclier + 1;
    }
    /// BRULURE
    if (joueur[i].brulure && joueur[i].compteur_bouclier >= 3)
    {
        joueur[i].brulure = 0;
        joueur[i].compteur_brulure = 0;
    }
    else
    {
        joueur[i].compteur_brulure = joueur[i].compteur_brulure + 1;
    }
    /// GEL
    if (joueur[i].gel && joueur[i].compteur_gel >= 2)
    {
        joueur[i].gel = 0;
        joueur[i].compteur_gel = 0;
    }
    else
    {
        joueur[i].compteur_gel = joueur[i].compteur_gel + 1;
    }
    /// HEMORRAGIE
    if (joueur[i].hemorragie && joueur[i].compteur_hemorragie >= 2)
    {
        joueur[i].hemorragie = 0;
        joueur[i].compteur_hemorragie = 0;
    }
    else
    {
        joueur[i].compteur_hemorragie = joueur[i].compteur_hemorragie + 1;
    }
    /// LUCIDE
    if (joueur[i].lucide && joueur[i].compteur_lucide >= 2)
    {
        joueur[i].lucide = 0;
        joueur[i].compteur_lucide = 0;
    }
    else
    {
        joueur[i].compteur_lucide = joueur[i].compteur_lucide + 1;
    }
    /// MORTEL
    if (joueur[i].mortel && joueur[i].compteur_mortel >= 2)
    {
        joueur[i].mortel = 0;
        joueur[i].compteur_mortel = 0;
    }
    else
    {
        joueur[i].compteur_mortel = joueur[i].compteur_mortel + 1;
    }
    /// LUCIDE
    if (joueur[i].rage && joueur[i].compteur_rage >= 2)
    {
        joueur[i].rage = 0;
        joueur[i].compteur_rage = 0;
    }
    else
    {
        joueur[i].compteur_rage = joueur[i].compteur_rage + 1;
    }
}
