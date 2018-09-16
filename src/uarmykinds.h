/*
Filename: UArmyKinds.h
Description: the father class of all armies
Version: 2.0
Date: 09/08/2018
*/
#ifndef UARMYKINDS_H
#define UARMYKINDS_H

#include <QObject>
#include <QPixmap>
#include "constant.hpp"
#include "resources.h"
#include "globalfunctions.h"
#include "uunit.h"
#include "uarmy.h"

//line infantry
class UArmyInfantry: public UArmy
{
public:
    //constants
    const int m_cMeleeAttackSpan{50};                           //The time between each melee attack
    const int m_cRangedAttackSpan{100};                         //The time between each ranged attack
    const int m_cAttackDamageRanged{40};
    const int m_cAttackDamageMelee{50};
    const int m_cHealth{150};
    const double m_cSpeed{3};
    const int m_cAmmoMax{3};
    QPixmap* m_cPictureByCountry[4]
    {NULL,g_Resources->ArmyInfantryEngland,g_Resources->ArmyInfantryFrance,g_Resources->ArmyInfantrySpain};

    //what changes in a game
protected:
    //constants
    int m_AmmoLeft;                                             //left ammo, no ammo army will become melee-attack army
    virtual void m_UpdateAttackType();                          //update attack type:meele or ranged
public:

    //construct a new one
    UArmyInfantry(const int place_x, const int place_y, const int country);

    //construct an old one from file
    UArmyInfantry(const int ammo_left, const int health, const double place_x, const double place_y,
                  const int country, const int attack_value);

    //used for its children classes
    UArmyInfantry();
    ~UArmyInfantry(){}


    //override father class function
    //add the update of ammo left
    virtual void m_ShootAmmo(const int final_x, const int final_y);


    //override father class function
    //add the update of attack type
    virtual void m_UpdateStatus();

    //override father class function
    //add ammo_left
    virtual void m_OutPut(QString file);

};

//light infantry
class UArmyLight: public UArmy
{
public:
    //constants
    const int m_cRangedAttackSpan{300};                         //The time between each ranged attack
    const int m_cAttackDamage{70};
    const int m_cHealth{100};
    const double m_cSpeed{5};
    QPixmap* m_cPictureByCountry[4]
    {NULL,g_Resources->ArmyLightEngland,g_Resources->ArmyLightFrance,g_Resources->ArmyLightSpain};
public:

    //build a new one
    UArmyLight(const int place_x, const int place_y, const int country);


    //build an old one from loaded files
    UArmyLight(const int health, const double place_x, const double place_y, const int country, const int attack_value);


    //for its children class
    UArmyLight();
    ~UArmyLight(){}

    //override father class function
    //shoot an ammo to its final place
    //variable:destination
    virtual void m_ShootAmmo(const int final_x, const int final_y);

};

//calvary
class UArmyCalvary: public UArmy
{
public:
    const int m_cMeleeAttackSpan{50};
    const int m_cAttackDamage{70};
    const int m_cHealth{150};
    const double m_cSpeed{5};
    QPixmap* m_cPictureByCountry[4]
    {NULL,g_Resources->ArmyCalvaryEngland,g_Resources->ArmyCalvaryFrance,g_Resources->ArmyCalvarySpain};
public:

    //new one
    UArmyCalvary(const int place_x, const int place_y, const int country);

    //load from file
    UArmyCalvary(const int health, const double place_x, const double place_y, const int country, const int attack_value);

    //for its children class
    UArmyCalvary();
    ~UArmyCalvary(){}

};


//line infantry
class UArmyGrenadier: public UArmy
{
public:
    //constants
    const int m_cMeleeAttackSpan{50};                           //The time between each melee attack
    const int m_cRangedAttackSpan{100};                         //The time between each ranged attack
    const int m_cAttackDamageRanged{40};
    const int m_cAttackDamageMelee{70};
    const int m_cHealth{220};
    const double m_cSpeed{2};
    const int m_cAmmoMax{1};
    QPixmap* m_cPictureByCountry[4]
    {NULL,g_Resources->ArmyGrenadierEngland,g_Resources->ArmyGrenadierFrance,g_Resources->ArmyGrenadierSpain};

    //what changes in a game
protected:
    //constants
    int m_AmmoLeft;                                             //left ammo

    //update attack type:ranged or melee
    void m_UpdateAttackType();
public:

    //new one
    UArmyGrenadier(const int place_x, const int place_y, const int country);

    //old one
    UArmyGrenadier(const int ammo_left, const int health, const double place_x,
                   const double place_y, const int country, const int attack_value);
    ~UArmyGrenadier(){}


    //throw a bomb to its destination
    virtual void m_ShootAmmo(const int final_x, const int final_y);

    //need to update attack type
    virtual void m_UpdateStatus();


    //save file
    //override father class, need to output ammo_left
    virtual void m_OutPut(QString file);

};

//only change the picture and values of armyinfantry, no functional change
class UArmyInfantryEngland: public UArmyInfantry
{
public:
    const int m_cHealthNew{200};
    const int m_cAttackDamageMeleeNew{80};
    const int m_cAttackDamageRangedNew{70};
    const int m_cRangedAttackSpanNew{70};
    QPixmap* m_cPictureNew{g_Resources -> ArmySpecialEngland};

    //new
    UArmyInfantryEngland(const int place_x, const int place_y);

    //old
    UArmyInfantryEngland(const int ammo_left, const int health, const double place_x, const double place_y, const int attack_value);
    ~UArmyInfantryEngland(){}

protected:
    void m_UpdateAttackType();
};



//only change the picture and values of armycalvary, no functional change
class UArmyCalvaryFrance: public UArmyCalvary
{
public:
    const int m_cHealthNew{200};
    const int m_cAttackDamageNew{80};
    QPixmap* m_cPictureNew{g_Resources -> ArmySpecialFrance};

    //new
    UArmyCalvaryFrance(const int place_x, const int place_y);

    //load
    UArmyCalvaryFrance(const int health, const double place_x, const double place_y, const int attack_value);
    ~UArmyCalvaryFrance(){}

};


//only change the picture and values of armylight, no functional change
class UArmyLightSpain: public UArmyLight
{
public:
    const int m_cHealthNew{150};
    const int m_cAttackDamageNew{100};
    const int m_cRangedAttackSpanNew{200};
    QPixmap* m_cPictureNew{g_Resources -> ArmySpecialSpain};

    //new
    UArmyLightSpain(const int place_x, const int place_y);

    //load
    UArmyLightSpain(const int health, const double place_x, const double place_y, const int attack_value);
    ~UArmyLightSpain(){}

};
#endif // UARMYKINDS_H
