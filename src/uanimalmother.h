/*
Filename: UAnimalMother.h
Description: the father class of grass-eat animal mothers
Version: 1.1
Date: 09/06/2018
*/

#ifndef UANIMALMOTHER_H
#define UANIMALMOTHER_H

#include <QObject>
#include <QPixmap>
#include "uunit.h"
#include "uanimal.h"
#include "resources.h"

class UAnimalMother:public UAnimal
{
    Q_OBJECT
public:
    //constants
    const int m_cMaxLevel{2};                                       //The max level of Grass-eat animals
    const int m_cHealthFullByLevel[3]{0,100,200};
    const int m_cExperienceRequiredUpgrade{500};
    const int m_cProduceThresholdByLevel[3]{0,500,250};
    const double m_cSpeedFullByLevel[3]{0,3,3};
    const int m_cHealthAdd{50};
    QPixmap* m_cPictureOriginalByLevel[3]
    {NULL, g_Resources->AnimalMotherLV1Normal, g_Resources->AnimalMotherLV2Normal};
    QPixmap* m_cPictureHungryByLevel[3]
    {NULL, g_Resources->AnimalMotherLV1Hungry, g_Resources->AnimalMotherLV2Hungry};
    QPixmap* m_cPictureDeadByLevel[3]
    {NULL, g_Resources->AnimalMotherLV1Dead, g_Resources->AnimalMotherLV2Dead};
protected:
    int m_Experience;                   //Experience gain, used to judge update
    int m_ProduceThreshold;             //use to judge production
protected:

    /*
     *function: update its experience, judge whether it can upgrade
     */
    void m_UpdateGrade();


    /*
     * function:upgrade the unit, change its data and its pictures
     */
    void m_Upgrade();

    /*override the same function in its father class
     * produce animal rather than bonus
     */
    void m_UpdateProduce();
public:

    /*
     * override the same function in its father class, add the function of updating grades
     */
    virtual void m_UpdateStatus();


    /*
     * override the same function in its father class, add the function of adding experiences
     */
    virtual void m_EatFood(const int health_add, const double hungry_point_add);

    /*
     * override the same function in its father class, add the function of saving levels and experiences
     */
    virtual void m_OutPut(QString file);

signals:
    //produce a child of LV1 Grass animal
    void m_ChildProduced(const int place_x,const int place_y);

public:
    //construct a new one with its place
     UAnimalMother(const int place_x, const int place_y);

     //when loading, construct an old one
     UAnimalMother(const int level, const int experience, const int health, const double hungry,
                  const double place_x, const double place_y, const int produce);
    ~UAnimalMother(){}

};


#endif // UANIMALMOTHER_H
