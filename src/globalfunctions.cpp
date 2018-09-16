/*
Filename: GlobalFunctions
Description: the global functions of the game
Version: 1.0
Date: 09/04/2018
*/

#include <cmath>
#include "uunit.h"
#include "globalfunctions.h"


int g_GenerateRandomNumber(const int range_min, const int range_max)
{
    //srand((unsigned)time(NULL));
    if(range_max == range_min)
    {
        return range_max;
    }
    int x = (rand() % (range_max - range_min)) + range_min;
    return x;
}


void g_GenerateRandomPlace
(int *place_x, int *place_y, const int range_x_min, const int range_x_max, const int range_y_min, const int range_y_max)
{
    //srand((unsigned)time(NULL));
    if(range_x_min == range_x_max)
    {
        *place_x = range_x_min;
    }
    else
    {
        *place_x = (rand() % (range_x_max - range_x_min)) + range_x_min;
    }

    //srand((unsigned)time(NULL));
    if(range_y_min == range_y_max)
    {
        *place_y = range_y_min;
    }
    else
    {
        *place_y = (rand() % (range_y_max - range_y_min)) + range_y_min;
    }
}




double g_GetDistance(const double place_x, const double place_y, UUnit* const final_object)
{
    double final_place_x, final_place_y;
    final_object -> m_GetPlace(&final_place_x, &final_place_y);
    const double x_dist = place_x - final_place_x;
    const double y_dist = place_y - final_place_y;
    double distance = sqrt(x_dist * x_dist + y_dist * y_dist);
    return distance;
}



double g_GetDistance(UUnit* const begin_object, UUnit* const final_object)
{
    double begin_place_x, begin_place_y;
    begin_object -> m_GetPlace(&begin_place_x, &begin_place_y);
    double final_place_x, final_place_y;
    final_object -> m_GetPlace(&final_place_x, &final_place_y);
    const double x_dist = begin_place_x - final_place_x;
    const double y_dist = begin_place_y - final_place_y;
    double distance = sqrt(x_dist * x_dist + y_dist * y_dist);
    return distance;
}
