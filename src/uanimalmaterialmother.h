/*
Filename: UAnimalMaterialMother.h
Description: the father class of material animal mothers
Version: 2.0
Date: 09/07/2018
*/
#ifndef UANIMALMATERIALMOTHER_H
#define UANIMALMATERIALMOTHER_H

#include <QObject>
#include <QPixmap>
#include "uunit.h"
#include "uanimal.h"
#include "resources.h"

class UAnimalMaterialMother:public UAnimal
{
    Q_OBJECT
public:
    //constants
    const int m_cHealthFull{100};
    const int m_cProduceThreshold{400};
    const double m_cSpeedFull{3};
    const int m_cHealthAdd{40};
    QPixmap* m_cPictureOriginal{g_Resources->AnimalMaterialMotherNormal};
    QPixmap* m_cPictureHungry{g_Resources->AnimalMaterialMotherHungry};
    QPixmap* m_cPictureDead{g_Resources->AnimalMaterialMotherDead};
protected:
    int m_ProduceThreshold;             //use to judge production
protected:
    /*override the same function in its father class
     * produce animal rather than bonus
     */
    virtual void m_UpdateProduce();
signals:

    //produce a child of LV1 material animal
    void m_ChildProduced(const int place_x,const int place_y);
public:

    //construct a new one , variable is place
     UAnimalMaterialMother(const int place_x, const int place_y);

     //construct a old one, via loaded files
     UAnimalMaterialMother(const int health, const double hungry,
                  const double place_x, const double place_y, const int produce);
     ~UAnimalMaterialMother(){}
};



#endif // UANIMALMATERIALMOTHER_H
