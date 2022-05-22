#include "../prototypes.h"
#include "../structures.h"

void definition_accessible(t_bloc matrice[23][23])
{
    for (int i = 0; i<23; i++)
    {
        for (int j = 0; j<23; j++)
        {
            matrice[i][j].id_case = 0;
            /// partie supérieur droite et gauche en double rectancgle

            if (i <= 4 && (j <= 8 || j >= 16))
            {
                matrice[i][j].accessible = 0;
            }
            if (((i >= 5 && i<= 7) && j <= 5) || (i == 5 && j >= 18) || (i == 6 && j >= 18))
            {
                matrice[i][j].accessible = 0;
            }

            /// partie inférieur droite et gauche en double rectangle

            if (i >= 17 && (j <= 7 || j >= 15))
            {
                matrice[i][j].accessible = 0;
            }
            if (((i >= 14 && i<= 16) && j >= 18) || (i == 15 && j <= 5) || (i == 16 && j <= 5))
            {
                matrice[i][j].accessible = 0;
            }
        }
    }

    /// partie supérieur droite et gauche, exceptions

    matrice[0][9].accessible = 0;
    matrice[5][6].accessible = 0;
    matrice[5][7].accessible = 0;
    matrice[6][6].accessible = 0;
    matrice[8][0].accessible = 0;
    matrice[0][15].accessible = 0;
    matrice[5][17].accessible = 0;
    matrice[7][22].accessible = 0;

    ///partie inférieur droite et gauche, exceptions

    matrice[16][6].accessible = 0;
    matrice[14][0].accessible = 0;
    matrice[22][8].accessible = 0;
    matrice[22][14].accessible = 0;
    matrice[16][16].accessible = 0;
    matrice[16][17].accessible = 0;
    matrice[15][17].accessible = 0;
    matrice[13][22].accessible = 0;
}

void definition_occuper(t_bloc matrice[23][23])
{
    matrice[0][13].accessible = 0;
    matrice[7][6].accessible = 0;
    matrice[8][4].accessible = 0;
    matrice[12][22].accessible = 0;

    matrice[15][16].accessible = 0;
    matrice[21][13].accessible = 0;
    matrice[17][14].accessible = 0;
    matrice[18][14].accessible = 0;

    matrice[7][15].accessible = 0;
    matrice[8][14].accessible = 0;
    matrice[5][16].accessible = 0;
    matrice[6][16].accessible = 0;

    matrice[7][16].accessible = 0;
    matrice[9][12].accessible = 0;
    matrice[9][13].accessible = 0;
    matrice[9][14].accessible = 0;

    matrice[11][11].accessible = 0;
    matrice[11][12].accessible = 0;
    matrice[12][10].accessible = 0;
    matrice[12][11].accessible = 0;

    matrice[13][9].accessible = 0;
    matrice[13][10].accessible = 0;
    matrice[13][11].accessible = 0;
    matrice[15][7].accessible = 0;

    matrice[12][2].accessible = 0;
    matrice[12][3].accessible = 0;
    matrice[13][2].accessible = 0;
    matrice[13][3].accessible = 0;

    matrice[20][9].accessible = 0;
    matrice[20][10].accessible = 0;
    matrice[21][9].accessible = 0;
    matrice[21][10].accessible = 0;
    matrice[19][9].accessible = 0;
    matrice[19][10].accessible = 0;

    matrice[5][10].accessible = 0;
    matrice[5][11].accessible = 0;
    matrice[6][10].accessible = 0;
    matrice[6][11].accessible = 0;

    matrice[6][11].accessible = 0;
    matrice[6][11].accessible = 0;
    matrice[6][11].accessible = 0;
    matrice[6][11].accessible = 0;

    matrice[15][8].accessible = 0;
    matrice[15][9].accessible = 0;
    matrice[16][7].accessible = 0;

    for (int i = 0; i<23; i++)
    {
        for (int j = 0; j<23; j++)
        {
            if ((i >= 1 && i<= 3) &&(j >= 9 && j <= 11))
            {
                matrice[i][j].accessible = 0;
            }
            if ((i == 7 && j >= 19 && j<= 21) || (i == 8 && j >= 19 && j<= 21))
            {
                matrice[i][j].accessible = 0;
            }
        }
    }
}
