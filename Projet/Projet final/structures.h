#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

#include <allegro.h>
#define TEMPS_TOUR 15

typedef struct sorts
{
    int portee_min;
    int portee_max;
    int cout;
    int degats;
    int chance;
    int zone;
    BITMAP* logo;
    BITMAP* animation_sort;
}t_sort;

typedef struct classes
{
    int attaque;
    BITMAP* logo_attaque;
    t_sort sort1;
    t_sort sort2;
    t_sort sort3;
    t_sort sort4;

}t_classe;


typedef struct Players
{
    int id_classe;
    BITMAP* skin;
    int position[23][23];
    int x;
    int y;
    int dx;
    int dy;
    int pv;
    int pm;
    int pa;
    t_classe classe;
}t_joueur;

#endif // STRUCTURES_H_INCLUDED
