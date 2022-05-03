#include "../prototypes.h"
#include "../structures.h"

void definition_accessible(t_bloc tab_bloc[23][23])
{
    for (int i = 0; i<23; i++)
    {
        for (int j = 0; j<23; j++)
        {
            /// partie supérieur droite et gauche en double rectancgle

            if (i <= 4 && (j <= 8 || j >= 16))
            {
                tab_bloc[i][j].accessible = 0;
            }
            if (((i >= 5 && i<= 7) && j <= 5) || (i == 5 && j >= 18) || (i == 6 && j >= 18))
            {
                tab_bloc[i][j].accessible = 0;
            }

            /// partie inférieur droite et gauche en double rectangle

            if (i >= 17 && (j <= 7 || j >= 15))
            {
                tab_bloc[i][j].accessible = 0;
            }
            if (((i >= 14 && i<= 16) && j >= 18) || (i == 15 && j <= 5) || (i == 16 && j <= 5))
            {
                tab_bloc[i][j].accessible = 0;
            }
        }
    }

    /// partie supérieur droite et gauche, exceptions

    tab_bloc[0][9].accessible = 0;
    tab_bloc[5][6].accessible = 0;
    tab_bloc[5][7].accessible = 0;
    tab_bloc[6][6].accessible = 0;
    tab_bloc[8][0].accessible = 0;
    tab_bloc[0][15].accessible = 0;
    tab_bloc[5][17].accessible = 0;
    tab_bloc[7][22].accessible = 0;

    ///partie inférieur droite et gauche, exceptions

    tab_bloc[16][6].accessible = 0;
    tab_bloc[14][0].accessible = 0;
    tab_bloc[22][8].accessible = 0;
    tab_bloc[22][14].accessible = 0;
    tab_bloc[16][16].accessible = 0;
    tab_bloc[16][17].accessible = 0;
    tab_bloc[15][17].accessible = 0;
    tab_bloc[13][22].accessible = 0;
}

void definition_occuper(t_bloc tab_bloc[23][23])
{
    tab_bloc[0][13].occuper = 1;
    tab_bloc[7][6].occuper = 1;
    tab_bloc[8][4].occuper = 1;
    tab_bloc[12][22].occuper = 1;

    tab_bloc[15][16].occuper = 1;
    tab_bloc[21][13].occuper = 1;
    tab_bloc[17][14].occuper = 1;
    tab_bloc[18][14].occuper = 1;

    tab_bloc[7][15].occuper = 1;
    tab_bloc[8][14].occuper = 1;
    tab_bloc[5][16].occuper = 1;
    tab_bloc[6][16].occuper = 1;

    tab_bloc[7][16].occuper = 1;
    tab_bloc[9][12].occuper = 1;
    tab_bloc[9][13].occuper = 1;
    tab_bloc[9][14].occuper = 1;

    tab_bloc[11][11].occuper = 1;
    tab_bloc[11][12].occuper = 1;
    tab_bloc[12][10].occuper = 1;
    tab_bloc[12][11].occuper = 1;

    tab_bloc[13][9].occuper = 1;
    tab_bloc[13][10].occuper = 1;
    tab_bloc[13][11].occuper = 1;
    tab_bloc[15][7].occuper = 1;

    tab_bloc[12][2].occuper = 1;
    tab_bloc[12][3].occuper = 1;
    tab_bloc[13][2].occuper = 1;
    tab_bloc[13][3].occuper = 1;

    tab_bloc[20][9].occuper = 1;
    tab_bloc[20][10].occuper = 1;
    tab_bloc[21][9].occuper = 1;
    tab_bloc[21][10].occuper = 1;
    tab_bloc[19][9].occuper = 1;
    tab_bloc[19][10].occuper = 1;

    tab_bloc[5][10].occuper = 1;
    tab_bloc[5][11].occuper = 1;
    tab_bloc[6][10].occuper = 1;
    tab_bloc[6][11].occuper = 1;

    tab_bloc[6][11].occuper = 1;
    tab_bloc[6][11].occuper = 1;
    tab_bloc[6][11].occuper = 1;
    tab_bloc[6][11].occuper = 1;

    tab_bloc[15][8].occuper = 1;
    tab_bloc[15][9].occuper = 1;
    tab_bloc[16][7].occuper = 1;

    for (int i = 0; i<23; i++)
    {
        for (int j = 0; j<23; j++)
        {
            if ((i >= 1 && i<= 3) &&(j >= 9 && j <= 11))
            {
                tab_bloc[i][j].occuper = 1;
            }
            if ((i == 7 && j >= 19 && j<= 21) || (i == 8 && j >= 19 && j<= 21))
            {
                tab_bloc[i][j].occuper = 1;
            }
        }
    }
}
