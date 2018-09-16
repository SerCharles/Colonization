/*
Filename: GlobalFunctions.h
Description: the Global Functions, including random place generating, and get distance, of the game
Version: 1.1
Date: 09/05/2018
*/
#ifndef GLOBALFUNCTIONS_H
#define GLOBALFUNCTIONS_H
#include "uunit.h"

/*
  function:generate a random number between range_min and range_max
  return:return the random number
  warning: range_min must <= range_max, or unexpected error will happen
*/
extern int g_GenerateRandomNumber(const int range_min, const int range_max);



/*
    function:generate a random place in a range
    return:place_x and place_y will become the x and y of the random place
    warning:range_min must <= range_max, or unexpected error will happen
*/
extern void  g_GenerateRandomPlace
(int* place_x, int* place_y, const int range_x_min, const int range_x_max, const int range_y_min, const int range_y_max);



/*
  function:get distance between a certain place and an unit, return the distance
  variables:place_x, place_y:the place you choose, final_object:the pointer of the object unit
  return:distance
 */
extern double g_GetDistance(const double place_x, const double place_y, UUnit* const final_object);



/*
  function:get distance between two units, return the distance
  return:distance
 */
extern double g_GetDistance(UUnit* const begin_object, UUnit* const final_object);

#endif // GLOBALFUNCTIONS_H
