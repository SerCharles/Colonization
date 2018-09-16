/*
Filename: UAnimalMeat.h
Description: the father class of meat_eat animals
Version: 2.0
Date: 09/06/2018
*/

#ifndef UANIMALMEAT_H
#define UANIMALMEAT_H

#include <QObject>
#include <QPixmap>
#include "uunit.h"
#include "uanimal.h"
#include "resources.h"


class UAnimalMeatSmall:public UAnimal
{
    Q_OBJECT
public:
    //constants
    const int m_cHealthFull{150};
    const double m_cSpeedFull{3};
    const int m_cMoneyProduct{3};
    const int m_cMaterialProduct{0};
    const int m_cHealthAdd{60};                              
    const double m_cHungryAdd{1};                          
    QPixmap* m_cPictureOriginal{g_Resources -> AnimalMeatSmallNormal};
    QPixmap* m_cPictureHungry{g_Resources -> AnimalMeatSmallHungry};
    QPixmap* m_cPictureDead{g_Resources ->AnimalMeatSmallDead};
public:


    //construct a new small meateat animal, variable is its place
    UAnimalMeatSmall(const int place_x, const int place_y);


    //construct a old small meateat animal from file, when loading a game
    UAnimalMeatSmall(const int health, const double hungry,
                 const double place_x, const double place_y, const int produce);
    ~UAnimalMeatSmall(){}

};

class UAnimalMeatBig:public UAnimal
{
    Q_OBJECT
public:
    //constants
    const int m_cHealthFull{300};
    const double m_cSpeedFull{2.5};
    const int m_cMoneyProduct{4};
    const int m_cMaterialProduct{0};
    const int m_cHealthAdd{100};
    const double m_cHungryAdd{0};                          
    QPixmap* m_cPictureOriginal{g_Resources -> AnimalMeatBigNormal};
    QPixmap* m_cPictureHungry{g_Resources -> AnimalMeatBigHungry};
    QPixmap* m_cPictureDead{g_Resources ->AnimalMeatBigDead};
public:

    //construct a new big meateat animal, variable is its place
    UAnimalMeatBig(const int place_x, const int place_y);

    //construct a old small meateat animal from file, when loading a game
    UAnimalMeatBig(const int health, const double hungry,
                 const double place_x, const double place_y, const int produce);
    ~UAnimalMeatBig(){}

};

#endif // UANIMALMEAT_H
