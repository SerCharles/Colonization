/*
Filename: UAnimalMaterial.h
Description: the father class of material_produce animals
Version: 2.0
Date: 09/07/2018
*/

#ifndef UANIMALMATERIAL_H
#define UANIMALMATERIAL_H

#include <QObject>
#include <QPixmap>
#include "uunit.h"
#include "uanimal.h"
#include "resources.h"

class UAnimalMaterial:public UAnimal
{
    Q_OBJECT
public:
    //constants
    const int m_cMaxLevel{3};                                       //The max level of Grass-eat animals
    const int m_cHealthFullByLevel[4]{0,50, 70, 100};
    const int m_cExperienceRequiredUpgrade[3]{0,500,1000};
    const int m_cMoneyProductByLevel[4]{0,0,0,0};
    const int m_cMaterialProductByLevel[4]{0,1,2,3};
    const int m_cHealthAdd{40};
    const double m_cSpeedFullByLevel[4]{0,3,3,3};
    QPixmap* m_cPictureOriginalByLevel[4]
    {NULL, g_Resources->AnimalMaterialLV1Normal, g_Resources->AnimalMaterialLV2Normal, g_Resources->AnimalMaterialLV3Normal};
    QPixmap* m_cPictureHungryByLevel[4]
    {NULL, g_Resources->AnimalMaterialLV1Hungry, g_Resources->AnimalMaterialLV2Hungry, g_Resources->AnimalMaterialLV3Hungry};
    QPixmap* m_cPictureDeadByLevel[4]
    {NULL, g_Resources->AnimalMaterialLV1Dead, g_Resources->AnimalMaterialLV2Dead, g_Resources->AnimalMaterialLV3Dead};
protected:

    //What do not change in the game, unless upgrading
    int m_Experience;                   //Experience gain, used to judge update
protected:
    void m_UpdateGrade();               //Judge Whether it can upgrade, and automaticly upgrade;
    void m_Upgrade();                   //Upgrade
public:
    void m_UpdateStatus();              //update the status of full,foraging,hungry and dead, and trigger other Updates
    virtual void m_EatFood(const int health_add, const double hungry_point_add);        //eat something
    virtual void m_OutPut(QString file);                        //save file

public:
    UAnimalMaterial(const int place_x, const int place_y);
    UAnimalMaterial(const int level, const int experience, const int health, const double hungry,
                 const double place_x, const double place_y, const int produce);
    ~UAnimalMaterial(){}

};

#endif // UANIMALMATERIAL_H
