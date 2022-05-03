#ifndef PROTOTYOPES_H_INCLUDED
#define PROTOTYOPES_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <string.h>

#define NB_BUFFERS 3

void display_cursor();
void choix_classe();
void creation_classes();
void deplacement_joueur();
void tour_joueur();
int menu();
void quadrillage_test();
void distribution_couleur_blocs();
void definition_accessible();
void definition_occuper();

#endif // PROTOTYOPES_H_INCLUDED
