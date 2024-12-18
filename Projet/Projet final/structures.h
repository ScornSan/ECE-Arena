#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

#include <allegro.h>
#define TEMPS_TOUR 16
#define NB_SORTS 4
#define DIRECTIONS 4
#define NB_BITMAPS_D 4
#define NB_BITMAPS_R 4
#define NB_BITMAPS_A 4
#define NB_CLASSES 4
#define TEMPS_CHOIX 15
#define PV_JOUEUR 3
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

typedef struct bloc
{
    int red;
    int green;
    int blue;
    int x_bloc;
    int y_bloc;
    int accessible;
    int occuper;
    int id_case;
} t_bloc;

typedef struct sorts
{
    int portee_min;
    int portee_max;
    int degats_min;
    int degats_max;
    int chance;
    int dispo;
    BITMAP* logo;
    BITMAP* animation_sort[4];
    BITMAP* animation_sort_perso[DIRECTIONS][4];
    BITMAP *anim_attaque_cible[DIRECTIONS][2];
    BITMAP* description;
}t_sort;

typedef struct classes
{
    int attaque;
    BITMAP *logo_attaque;
    BITMAP *anim_attaques[NB_CLASSES][DIRECTIONS][NB_BITMAPS_A];
    BITMAP *respiration[DIRECTIONS][2];
    BITMAP *deplacement[DIRECTIONS][NB_BITMAPS_D];
    t_sort spell[NB_SORTS];
}t_classe;


typedef struct Players
{
    char pseudo[20];
    int id_classe;
    int id_joueur;
    int direction;
    int x;
    int y;
    int nb_pm;
    int pv;
    int pm;
    int pa;
    int attaque_dispo;
    int rage;
    int compteur_rage;
    int hemorragie;
    int compteur_hemorragie;
    int brulure;
    int compteur_brulure;
    int gel;
    int compteur_gel;
    int mortel;
    int compteur_mortel;
    int lucide;
    int compteur_lucide;
    int bouclier;
    int compteur_bouclier;
    int invincible;
    int compteur_invincible;
    int vivant;
    int elimine;
    int red;
    int green;
    int blue;
    int place_manuellement;
    int choix_double;
    int casesparcourues;
    int degatstotal;
    BITMAP *shield;
    BITMAP *skull;
    BITMAP *rageux;
    BITMAP *fin;
    BITMAP *barre_temps;
    clock_t temps_tour;
    t_classe classe;
}t_joueur;


#endif // STRUCTURES_H_INCLUDED
