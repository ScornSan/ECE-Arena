#include <stdio.h>
#include <stdlib.h>

typedef struct sorts
{
    int portee_min;
    int portee_max;
    int cout;
    int degats;
    int chance;
    int zone;
}t_sort;

typedef struct classes
{
    int attaque;
    t_sort sort1;
    t_sort sort2;
    t_sort sort3;
    t_sort sort4;

}t_classe;


typedef struct Joueur
{
    BITMAP* skin;
    int x;
    int y;
    int dx;
    int dy;
    int pv;
    int pm;
    int pa;
    t_classe classe;
}

int main()
{
    printf("Hello world!\n");
    return 0;
}
