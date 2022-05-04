#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

#include <allegro.h>
#define TEMPS_TOUR 15

typedef struct bloc
{
    int red;
    int green;
    int blue;
    int x_bloc;
    int y_bloc;
    int accessible;
    int occuper;
} t_bloc;

typedef struct sorts
{
    int portee_min;
    int portee_max;
    int cout_pa;
    int degats_min;
    int degats_max;
    int chance;
    BITMAP* logo;
    BITMAP* animation_sort;
    char* description;
}t_sort;

typedef struct classes
{
    int attaque;
    BITMAP* logo_attaque;
    BITMAP* sorts[4];
    t_sort sort1;
    t_sort sort2;
    t_sort sort3;
    t_sort sort4;

}t_classe;


typedef struct Players
{
    char pseudo[20];
    int id_classe;
    BITMAP* skin;
    t_bloc position[23][23];
    int ligne_joueur;
    int colonne_joueur;
    int nb_pm;
    int pv;
    int pm;
    int pa;
    int statut;
    int vivant;
    int red;
    int green;
    int blue;
    t_classe classe;
}t_joueur;


#endif // STRUCTURES_H_INCLUDED
