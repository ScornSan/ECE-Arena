#include "../prototypes.h"
#include "../structures.h"

void desc_sort1(t_joueur * joueur, int i, BITMAP * buffer)
{
    switch(joueur[i].id_classe)
    {
    case 1:
        textprintf_ex(buffer, font, 355, 580, makecol(255,0,0), -1, "X"); // degats
        textprintf_ex(buffer, font, 323, 600, makecol(0,0,255), -1, "2"); // pa
        textprintf_ex(buffer, font, 355, 620, makecol(255,255,255), -1, "X"); // portée
        textprintf_ex(buffer, font, 370, 640, makecol(0,0,0), -1, "90%"); // % chance
        break;
    case 2:
        textprintf_ex(buffer, font, 355, 580, makecol(255,0,0), -1, "X");
        textprintf_ex(buffer, font, 323, 600, makecol(0,0,255), -1, "2");
        textprintf_ex(buffer, font, 355, 620, makecol(255,255,255), -1, "X");
        textprintf_ex(buffer, font, 370, 640, makecol(0,0,0), -1, "90%");
        break;
    case 3:
        textprintf_ex(buffer, font, 355, 580, makecol(255,0,0), -1, "X");
        textprintf_ex(buffer, font, 323, 600, makecol(0,0,255), -1, "2");
        textprintf_ex(buffer, font, 355, 620, makecol(255,255,255), -1, "2");
        textprintf_ex(buffer, font, 370, 640, makecol(0,0,0), -1, "90%");
        break;
    case 4:
        textprintf_ex(buffer, font, 355, 580, makecol(255,0,0), -1, "X");
        textprintf_ex(buffer, font, 323, 600, makecol(0,0,255), -1, "2");
        textprintf_ex(buffer, font, 355, 620, makecol(255,255,255), -1, "X");
        textprintf_ex(buffer, font, 370, 640, makecol(0,0,0), -1, "90%");
        break;
    }
}

void desc_sort2(t_joueur * joueur, int i, BITMAP * buffer)
{
    switch(joueur[i].id_classe)
    {
    case 1:
        textprintf_ex(buffer, font, 355, 580, makecol(255,0,0), -1, "6-12");
        textprintf_ex(buffer, font, 323, 600, makecol(0,0,255), -1, "4");
        textprintf_ex(buffer, font, 355, 620, makecol(255,255,255), -1, "2");
        textprintf_ex(buffer, font, 370, 640, makecol(0,0,0), -1, "80%");
        break;
    case 2:
        textprintf_ex(buffer, font, 355, 580, makecol(255,0,0), -1, "X");
        textprintf_ex(buffer, font, 323, 600, makecol(0,0,255), -1, "4");
        textprintf_ex(buffer, font, 355, 620, makecol(255,255,255), -1, "4");
        textprintf_ex(buffer, font, 370, 640, makecol(0,0,0), -1, "80%");
        break;
    case 3:
        textprintf_ex(buffer, font, 355, 580, makecol(255,0,0), -1, "5-10");
        textprintf_ex(buffer, font, 323, 600, makecol(0,0,255), -1, "4");
        textprintf_ex(buffer, font, 355, 620, makecol(255,255,255), -1, "2");
        textprintf_ex(buffer, font, 370, 640, makecol(0,0,0), -1, "80%");
        break;
    case 4:
        textprintf_ex(buffer, font, 355, 580, makecol(255,0,0), -1, "4-8");
        textprintf_ex(buffer, font, 323, 600, makecol(0,0,255), -1, "2");
        textprintf_ex(buffer, font, 355, 620, makecol(255,255,255), -1, "4");
        textprintf_ex(buffer, font, 370, 640, makecol(0,0,0), -1, "80%");
        break;
    }
}

void desc_sort3(t_joueur * joueur, int i, BITMAP * buffer)
{
    switch(joueur[i].id_classe)
    {
    case 1:
        textprintf_ex(buffer, font, 355, 580, makecol(255,0,0), -1, "X");
        textprintf_ex(buffer, font, 323, 600, makecol(0,0,255), -1, "4");
        textprintf_ex(buffer, font, 355, 620, makecol(255,255,255), -1, "2");
        textprintf_ex(buffer, font, 370, 640, makecol(0,0,0), -1, "70%");
        break;
    case 2:
        textprintf_ex(buffer, font, 355, 580, makecol(255,0,0), -1, "X");
        textprintf_ex(buffer, font, 323, 600, makecol(0,0,255), -1, "4");
        textprintf_ex(buffer, font, 355, 620, makecol(255,255,255), -1, "3");
        textprintf_ex(buffer, font, 370, 640, makecol(0,0,0), -1, "70%");
        break;
    case 3:
        textprintf_ex(buffer, font, 355, 580, makecol(255,0,0), -1, "X");
        textprintf_ex(buffer, font, 323, 600, makecol(0,0,255), -1, "4");
        textprintf_ex(buffer, font, 355, 620, makecol(255,255,255), -1, "4");
        textprintf_ex(buffer, font, 370, 640, makecol(0,0,0), -1, "70%");
        break;
    case 4:
        textprintf_ex(buffer, font, 355, 580, makecol(255,0,0), -1, "X");
        textprintf_ex(buffer, font, 323, 600, makecol(0,0,255), -1, "4");
        textprintf_ex(buffer, font, 355, 620, makecol(255,255,255), -1, "X");
        textprintf_ex(buffer, font, 370, 640, makecol(0,0,0), -1, "70%");
        break;
    }
}

void desc_sort4(t_joueur * joueur, int i, BITMAP * buffer)
{
    switch(joueur[i].id_classe)
    {
    case 1:
        textprintf_ex(buffer, font, 355, 580, makecol(255,0,0), -1, "X");
        textprintf_ex(buffer, font, 323, 600, makecol(0,0,255), -1, "5");
        textprintf_ex(buffer, font, 355, 620, makecol(255,255,255), -1, "X");
        textprintf_ex(buffer, font, 370, 640, makecol(0,0,0), -1, "60%");
        break;
    case 2:
        textprintf_ex(buffer, font, 355, 580, makecol(255,0,0), -1, "5-10");
        textprintf_ex(buffer, font, 323, 600, makecol(0,0,255), -1, "5");
        textprintf_ex(buffer, font, 355, 620, makecol(255,255,255), -1, "3");
        textprintf_ex(buffer, font, 370, 640, makecol(0,0,0), -1, "60%");
        break;
    case 3:
        textprintf_ex(buffer, font, 355, 580, makecol(255,0,0), -1, "5-10");
        textprintf_ex(buffer, font, 323, 600, makecol(0,0,255), -1, "5");
        textprintf_ex(buffer, font, 355, 620, makecol(255,255,255), -1, "3");
        textprintf_ex(buffer, font, 370, 640, makecol(0,0,0), -1, "60%");
        break;
    case 4:
        textprintf_ex(buffer, font, 355, 580, makecol(255,0,0), -1, "X");
        textprintf_ex(buffer, font, 323, 600, makecol(0,0,255), -1, "5");
        textprintf_ex(buffer, font, 355, 620, makecol(255,255,255), -1, "3");
        textprintf_ex(buffer, font, 370, 640, makecol(0,0,0), -1, "60%");
        break;
    }
}
