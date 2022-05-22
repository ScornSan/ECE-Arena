#include "../prototypes.h"
#include "../structures.h"

void compteur_effet(t_joueur* joueur, int nb_joueurs, int i)
{
    for (int j = 0; j < nb_joueurs; j++)
    {
        /// BOUCLIER
        if (joueur[j].bouclier && joueur[j].compteur_bouclier > nb_joueurs)
        {
            if (joueur[i].pv >= 55)
            {
                joueur[i].pv = 55;
            }
            joueur[j].bouclier = 0;
            joueur[j].compteur_bouclier = 0;
        }
        else if (joueur[j].bouclier)
        {
            joueur[j].compteur_bouclier = joueur[j].compteur_bouclier + 1;
        }
        /// BRULURE
        if (joueur[j].brulure && joueur[j].compteur_brulure > 2 * nb_joueurs)
        {
            joueur[j].brulure = 0;
            joueur[j].compteur_brulure = 0;
        }
        else if (joueur[j].brulure)
        {
            joueur[j].compteur_brulure = joueur[j].compteur_brulure + 1;
        }
        /// GEL
        if (joueur[j].gel && joueur[j].compteur_gel >= 2)
        {
            joueur[j].gel = 0;
            joueur[j].compteur_gel = 0;
        }
        else if (joueur[j].gel)
        {
            joueur[j].compteur_gel = joueur[j].compteur_gel + 1;
        }
        /// HEMORRAGIE
        if (joueur[j].hemorragie && joueur[j].compteur_hemorragie > 1 * nb_joueurs)
        {
            joueur[j].hemorragie = 0;
            joueur[j].compteur_hemorragie = 0;
        }
        else if (joueur[j].hemorragie)
        {
            joueur[j].compteur_hemorragie = joueur[j].compteur_hemorragie + 1;
        }
        /// MORTEL
        if (joueur[j].mortel && joueur[j].compteur_mortel >= 2)
        {
            joueur[j].mortel = 0;
            joueur[j].compteur_mortel = 0;
        }
        else if (joueur[j].mortel)
        {
            joueur[j].compteur_mortel = joueur[j].compteur_mortel + 1;
        }
        /// RAGE
        if (joueur[j].rage && joueur[j].compteur_rage >= 2 * nb_joueurs)
        {
            joueur[j].rage = 0;
            joueur[j].compteur_rage = 0;
        }
        else if (joueur[j].rage)
        {
            joueur[j].compteur_rage = joueur[j].compteur_rage + 1;
        }
        /// INVINCIBLE
        if (joueur[j].invincible && joueur[j].compteur_invincible >= nb_joueurs)
        {
            joueur[j].invincible = 0;
            joueur[j].compteur_invincible = 0;
        }
        else if (joueur[j].invincible)
        {
            joueur[j].compteur_invincible = joueur[j].compteur_invincible + 1;
        }
        /// MORT JOUEUR
        if (joueur[j].pv <= 0)
        {
            joueur[j].vivant = 0;
        }
        /// ATTAQUE DISPONIBLE REMISE A 1
        if (i != j) /// On remet l'attaque dispo a tout les joueurs sauf celui qui est en train de jouer
        {
            joueur[j].attaque_dispo = 1;
            for (int k = 0; k < 4; k++)
            {
                joueur[j].classe.spell[k].dispo = 1;
            }
        }
    }
}
