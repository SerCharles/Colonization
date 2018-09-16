/*
Filename: UAnimalGrass.h
Description: the father class of grass-eat animals
Version: 1.1
Date: 09/04/2018
*/

#ifndef UANIMAL_GRASS_H
#define UANIMAL_GRASS_H


#include <QObject>
#include <QPixmap>
#include "uunit.h"
#include "uanimal.h"
#include "resources.h"

class UAnimalGrass:public UAnimal
{
    Q_OBJECT
public:
    //constants of a animal grass, east to change , used in constructions
    const int m_cMaxLevel{4};                                       //The max level of Grass-eat animals
    const int m_cHealthFullByLevel[5]{0,50, 70, 90 ,150};
    const int m_cExperienceRequiredUpgrade[4]{0,200,800,3000};
    const int m_cHealthAddByLevel{40};                              //Only useful on 1-level members
    const double m_cHungryAddByLevel{0.5};                          //Only useful on 1-level members
    const int m_cMoneyProductByLevel[5]{0,0,1,2,3};
    const int m_cMaterialProductByLevel[5]{0,0,0,0,0};
    const double m_cSpeedFullByLevel[5]{0,3,2.5,2,3};
    QPixmap* m_cPictureOriginalByLevel[5]
    {NULL, g_Resources->AnimalGrassLV1Normal, g_Resources->AnimalGrassLV2Normal, g_Resources->AnimalGrassLV3Normal, g_Resources->AnimalGrassLV4Normal};
    QPixmap* m_cPictureHungryByLevel[5]
    {NULL, g_Resources->AnimalGrassLV1Hungry, g_Resources->AnimalGrassLV2Hungry, g_Resources->AnimalGrassLV3Hungry, g_Resources->AnimalGrassLV4Hungry};
    QPixmap* m_cPictureDeadByLevel[5]
    {NULL, g_Resources->AnimalGrassLV1Dead, g_Resources->AnimalGrassLV2Dead, g_Resources->AnimalGrassLV3Dead, g_Resources->AnimalGrassLV4Dead};
protected:

    //What do not change in the game, unless upgrading
    int m_Experience;                   //Experience gain, used to judge update
protected:
    /*
     *function: update its experience, judge whether it can upgrade
     */
    void m_UpdateGrade();



    /*
     * function:upgrade the unit, change its data and its pictures
     */
    void m_Upgrade();
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

public:

    //construction: set initial values
    //variables:its place
    UAnimalGrass(const int place_x, const int place_y);


    //constuction:construct it from saving files
    UAnimalGrass(const int level, const int experience, const int health, const double hungry,
                 const double place_x, const double place_y, const int produce);
    ~UAnimalGrass(){}
};



#endif // UANIMAL_GRASS_H
