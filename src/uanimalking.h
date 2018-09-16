/*
Filename: UAnimalKing.h
Description: the father class of animal king, which is only one
Version: 2.0
Date: 09/07/2018
*/

#ifndef UANIMALKING_H
#define UANIMALKING_H

#include <QObject>
#include <QPixmap>
#include "uunit.h"
#include "uanimal.h"
#include "resources.h"

class UAnimalKing: public UAnimal
{
    Q_OBJECT
public:
    //constants
    const int m_cHealthFull{300};
    const double m_cSpeedFull{5};
    const int m_cMoneyProduct{3};
    const int m_cMaterialProduct{3};
    const int m_cHealthAdd{100};
    const double m_cHungryAdd{0};
    QPixmap* m_cPictureOriginal{g_Resources -> AnimalKingNormal};
    QPixmap* m_cPictureHungry{g_Resources -> AnimalKingHungry};
    QPixmap* m_cPictureDead{g_Resources ->AnimalKingDead};
public:

     //construct a new one by its place
     UAnimalKing(const int place_x, const int place_y);

     //construct an old one with information in saved files
     UAnimalKing(const int health, const double hungry,
                  const double place_x, const double place_y, const int produce);
    ~UAnimalKing(){}

protected:

    //override its father class function
    // it will not be hungry forever
    virtual void m_UpdateHungry();

};









#endif // UANIMALKING_H
