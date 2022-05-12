#ifndef PROTOTYOPES_H_INCLUDED
#define PROTOTYOPES_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <string.h>

void creation_icones_classes();
void reperage_bloc_souris();
void reperage_chemin();
void lecture_pixels_buffer_map();
void sleep();
void deplacement_nombre_pm();
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
void deplacement_personnage();
void affichage_croix_bleue();
void affichage_croix_rouge();
void dessin_bloc_unique();
void usleep();
void zone_max_deplacement_0pm();
void zone_max_deplacement_1pm();
void zone_max_deplacement_2pm();
void zone_max_deplacement_3pm();
void anomalie_case_deplacement();
int classement_fin();

#endif // PROTOTYOPES_H_INCLUDED
