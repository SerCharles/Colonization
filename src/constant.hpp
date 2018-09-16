/*
Filename: Constant.hpp
Description: the global constants.
Version: 1.0
Date: 09/02/2018
*/

#ifndef CONSTANT_HPP
#define CONSTANT_HPP


class Constant
{
public:
    //mathematical constants
    static constexpr double g_Pi{3.1415926};       //pi
    static constexpr int g_AllAngle{360};          //2*pi by angle

    //constants about the map
    //the game borders, all the game units appear only inside the border
    static const int g_BorderMax_x{1200};
    static const int g_BorderMax_y{700};
    static const int g_BorderMin_x{50};
    static const int g_BorderMin_y{100};

    //the game bonus borders, all the game bonuses appear only inside the border
    static const int g_BonusBorderMax_x{1150};
    static const int g_BonusBorderMax_y{650};
    static const int g_BonusBorderMin_x{100};
    static const int g_BonusBorderMin_y{150};

    static const int g_RadiusVerySmallObject{7};   //The radius of very small objects, such as bullet
    static const int g_RadiusSmallObject{15};      //The radius of small objects, such as bonus and food
    static const int g_RadiusMediumObject{25};     //The radius of medium objects, such as animals, armies and enemies
};

#endif // CONSTANT_H
