#include "../prototypes.h"
#include "../structures.h"

void quadrillage_test(BITMAP *buffer)
{
    for( int i = 0; i<24; i++)
    {
        line(buffer, 114 +i*23, 399 +i*13, 642 +i*23, 100 +i*13, makecol(255,0,0));
        line(buffer, 115 +i*23, 399 -i*13, 643 +i*23, 697 -i*13, makecol(255,0,0));
    }
}
