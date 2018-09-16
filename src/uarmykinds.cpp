/*
Filename: UArmyKinds.cpp
Description: the father class of all armies
Version: 2.0
Date: 09/09/2018
*/


#include <QObject>
#include <QPixmap>
#include <QFile>
#include <QTextStream>
#include "constant.hpp"
#include "resources.h"
#include "globalfunctions.h"
#include "uunit.h"
#include "uarmy.h"
#include "uarmykinds.h"


//line infantry
UArmyInfantry::UArmyInfantry(const int place_x, const int place_y, const int country)
{
    //What do not change
    m_HealthFull = m_cHealth;
    m_SpeedFull = m_cSpeed;
    m_Country = country;
    m_PictureOriginal = m_cPictureByCountry[country];
    m_PictureShow = m_PictureOriginal;
    m_Species = 1;

    //what changes only if type changes
    m_AttackType = 1;
    m_AttackThreshold = m_cRangedAttackSpan;
    m_AttackDamage = m_cAttackDamageRanged;

    //what changes
    m_AmmoLeft = m_cAmmoMax;
    m_HealthNow = m_HealthFull;
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_AttackPoint = m_AttackThreshold;
}

UArmyInfantry::UArmyInfantry()
{
        //What do not change
        m_HealthFull = m_cHealth;
        m_SpeedFull = m_cSpeed;
        m_Species = 1;

        //what changes only if type changes
        m_AttackType = 1;
        m_AttackThreshold = m_cRangedAttackSpan;
        m_AttackDamage = m_cAttackDamageRanged;

        //what changes
        m_AmmoLeft = m_cAmmoMax;
        m_HealthNow = m_HealthFull;
        m_AttackPoint = m_AttackThreshold;
}

UArmyInfantry::UArmyInfantry(const int ammo_left, const int health,
                             const double place_x, const double place_y, const int country, const int attack_value)
{
    //What do not change
    m_HealthFull = m_cHealth;
    m_SpeedFull = m_cSpeed;
    m_Country = country;
    m_PictureOriginal = m_cPictureByCountry[country];
    m_PictureShow = m_PictureOriginal;
    m_Species = 1;

    //what changes only if type changes
    m_AttackType = 1;
    m_AttackThreshold = m_cRangedAttackSpan;
    m_AttackDamage = m_cAttackDamageRanged;

    //what changes
    m_AmmoLeft = ammo_left;
    m_HealthNow = health;
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_AttackPoint = attack_value;
}

void UArmyInfantry::m_UpdateAttackType()
{
    if(m_AmmoLeft > 0)
    {
        m_AttackType = 1;
        m_AttackThreshold = m_cRangedAttackSpan;
        m_AttackDamage = m_cAttackDamageRanged;
    }
    else
    {
        m_AttackType = 2;
        m_AttackThreshold = m_cMeleeAttackSpan;
        m_AttackDamage = m_cAttackDamageMelee;
    }
}

void UArmyInfantry::m_UpdateStatus()
{
        m_UpdateAttack();
        m_UpdateAttackType();
        m_UpdateHealth();
}

void UArmyInfantry::m_ShootAmmo(const int final_x, const int final_y)
{
    m_AmmoLeft -= 1;
    m_WhetherCanAttack = 0;
    m_AttackPoint = 0;
    emit m_AmmoShooted(1, m_AttackDamage, m_Place_x, m_Place_y, final_x, final_y);
}

void UArmyInfantry::m_OutPut(QString file)
{
    QFile save_file(file);
    if(!save_file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
        return;
    }
    QTextStream save_stream(&save_file);
    save_stream <<m_Species<<' '<< m_AmmoLeft <<' '<< m_HealthNow <<' '<< m_Place_x <<' '<< m_Place_y <<' '<< m_AttackPoint <<'\n';
    save_file.close();

}

//light infantry
UArmyLight::UArmyLight(const int place_x, const int place_y, const int country)
{
    //What do not change
    m_HealthFull = m_cHealth;
    m_SpeedFull = m_cSpeed;
    m_AttackDamage = m_cAttackDamage;
    m_AttackThreshold = m_cRangedAttackSpan;
    m_Country = country;
    m_PictureOriginal = m_cPictureByCountry[country];
    m_PictureShow = m_PictureOriginal;
    m_Species = 2;
    m_AttackType = 1;

    //what changes
    m_HealthNow = m_HealthFull;
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_AttackPoint = m_AttackThreshold;
}

UArmyLight::UArmyLight()
{
    //What do not change
    m_HealthFull = m_cHealth;
    m_SpeedFull = m_cSpeed;
    m_AttackDamage = m_cAttackDamage;
    m_AttackThreshold = m_cRangedAttackSpan;
    m_Species = 2;
    m_AttackType = 1;

    //what changes
    m_HealthNow = m_HealthFull;
    m_AttackPoint = m_AttackThreshold;
}

UArmyLight::UArmyLight(const int health, const double place_x, const double place_y, const int country, const int attack_value)
{
    //What do not change
    m_HealthFull = m_cHealth;
    m_SpeedFull = m_cSpeed;
    m_AttackDamage = m_cAttackDamage;
    m_AttackThreshold = m_cRangedAttackSpan;
    m_Country = country;
    m_PictureOriginal = m_cPictureByCountry[country];
    m_PictureShow = m_PictureOriginal;
    m_Species = 2;
    m_AttackType = 1;

    //what changes
    m_HealthNow = health;
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_AttackPoint = attack_value;
}

void UArmyLight::m_ShootAmmo(const int final_x, const int final_y)
{
    m_WhetherCanAttack = 0;
    m_AttackPoint = 0;
    emit m_AmmoShooted(1, m_AttackDamage, m_Place_x, m_Place_y, final_x, final_y);
}


//calvary
UArmyCalvary::UArmyCalvary(const int place_x, const int place_y, const int country)
{
    //What do not change
    m_HealthFull = m_cHealth;
    m_SpeedFull = m_cSpeed;
    m_AttackDamage = m_cAttackDamage;
    m_AttackThreshold = m_cMeleeAttackSpan;
    m_Country = country;
    m_PictureOriginal = m_cPictureByCountry[country];
    m_PictureShow = m_PictureOriginal;
    m_Species = 3;
    m_AttackType = 2;

    //what changes
    m_HealthNow = m_HealthFull;
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_AttackPoint = m_AttackThreshold;
}

UArmyCalvary::UArmyCalvary()
{
    //What do not change
    m_HealthFull = m_cHealth;
    m_SpeedFull = m_cSpeed;
    m_AttackDamage = m_cAttackDamage;
    m_AttackThreshold = m_cMeleeAttackSpan;
    m_Species = 3;
    m_AttackType = 2;

    //what changes
    m_HealthNow = m_HealthFull;
    m_AttackPoint = m_AttackThreshold;
}

UArmyCalvary::UArmyCalvary(const int health, const double place_x, const double place_y, const int country, const int attack_value)
{
    //What do not change
    m_HealthFull = m_cHealth;
    m_SpeedFull = m_cSpeed;
    m_AttackDamage = m_cAttackDamage;
    m_AttackThreshold = m_cMeleeAttackSpan;
    m_Country = country;
    m_PictureOriginal = m_cPictureByCountry[country];
    m_PictureShow = m_PictureOriginal;
    m_Species = 3;
    m_AttackType = 2;

    //what changes
    m_HealthNow = health;
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_AttackPoint = attack_value;
}

//grenadiers
UArmyGrenadier::UArmyGrenadier(const int place_x, const int place_y, const int country)
{
    //What do not change
    m_HealthFull = m_cHealth;
    m_SpeedFull = m_cSpeed;
    m_Country = country;
    m_PictureOriginal = m_cPictureByCountry[country];
    m_PictureShow = m_PictureOriginal;
    m_Species = 4;

    //what changes only if type changes
    m_AttackType = 1;
    m_AttackThreshold = m_cRangedAttackSpan;
    m_AttackDamage = m_cAttackDamageRanged;

    //what changes
    m_AmmoLeft = m_cAmmoMax;
    m_HealthNow = m_HealthFull;
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_AttackPoint = m_AttackThreshold;
}

UArmyGrenadier::UArmyGrenadier(const int ammo_left, const int health,
                               const double place_x, const double place_y, const int country, const int attack_value)
{
    //What do not change
    m_HealthFull = m_cHealth;
    m_SpeedFull = m_cSpeed;
    m_Country = country;
    m_PictureOriginal = m_cPictureByCountry[country];
    m_PictureShow = m_PictureOriginal;
    m_Species = 4;

    //what changes only if type changes
    m_AttackType = 1;
    m_AttackThreshold = m_cRangedAttackSpan;
    m_AttackDamage = m_cAttackDamageRanged;

    //what changes
    m_AmmoLeft = ammo_left;
    m_HealthNow = health;
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_AttackPoint = attack_value;
}

void UArmyGrenadier::m_OutPut(QString file)
{
    QFile save_file(file);
    if(!save_file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
        return;
    }
    QTextStream save_stream(&save_file);
    save_stream <<m_Species<<' '<< m_AmmoLeft <<' '<< m_HealthNow <<' '<< m_Place_x <<' '<< m_Place_y  <<' '<< m_AttackPoint <<'\n';
    save_file.close();
}

void UArmyGrenadier::m_UpdateAttackType()
{
    if(m_AmmoLeft > 0)
    {
        m_AttackType = 1;
        m_AttackThreshold = m_cRangedAttackSpan;
        m_AttackDamage = m_cAttackDamageRanged;
    }
    else
    {
        m_AttackType = 2;
        m_AttackThreshold = m_cMeleeAttackSpan;
        m_AttackDamage = m_cAttackDamageMelee;
    }
}

void UArmyGrenadier::m_UpdateStatus()
{
        m_UpdateAttack();
        m_UpdateAttackType();
        m_UpdateHealth();
}

void UArmyGrenadier::m_ShootAmmo(const int final_x, const int final_y)
{
    m_AmmoLeft -= 1;
    m_WhetherCanAttack = 0;
    m_AttackPoint = 0;
    emit m_AmmoShooted(3, m_AttackDamage, m_Place_x, m_Place_y, final_x, final_y);
}

UArmyInfantryEngland::UArmyInfantryEngland(const int place_x, const int place_y)
{
    //What do not change
    m_HealthFull = m_cHealthNew;
    m_SpeedFull = m_cSpeed;
    m_Country = 1;
    m_PictureOriginal = m_cPictureNew;
    m_PictureShow = m_PictureOriginal;
    m_Species = 5;

    //what changes only if type changes
    m_AttackType = 1;
    m_AttackThreshold = m_cRangedAttackSpanNew;
    m_AttackDamage = m_cAttackDamageRangedNew;

    //what changes
    m_AmmoLeft = m_cAmmoMax;
    m_HealthNow = m_HealthFull;
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_AttackPoint = m_AttackThreshold;
}

UArmyInfantryEngland::UArmyInfantryEngland(const int ammo_left, const int health,
                                           const double place_x, const double place_y, const int attack_value)
{
    //What do not change
    m_HealthFull = m_cHealthNew;
    m_SpeedFull = m_cSpeed;
    m_Country = 1;
    m_PictureOriginal = m_cPictureNew;
    m_PictureShow = m_PictureOriginal;
    m_Species = 5;

    //what changes only if type changes
    m_AttackType = 1;
    m_AttackThreshold = m_cRangedAttackSpanNew;
    m_AttackDamage = m_cAttackDamageRangedNew;

    //what changes
    m_AmmoLeft = ammo_left;
    m_HealthNow = health;
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_AttackPoint = attack_value;
}

void UArmyInfantryEngland::m_UpdateAttackType()
{
    if(m_AmmoLeft > 0)
    {
        m_AttackType = 1;
        m_AttackThreshold = m_cRangedAttackSpanNew;
        m_AttackDamage = m_cAttackDamageRangedNew;
    }
    else
    {
        m_AttackType = 2;
        m_AttackThreshold = m_cMeleeAttackSpan;
        m_AttackDamage = m_cAttackDamageMeleeNew;
    }
}

UArmyCalvaryFrance::UArmyCalvaryFrance(const int place_x, const int place_y)
{
    //What do not change
    m_HealthFull = m_cHealthNew;
    m_SpeedFull = m_cSpeed;
    m_AttackDamage = m_cAttackDamageNew;
    m_AttackThreshold = m_cMeleeAttackSpan;
    m_Country = 2;
    m_PictureOriginal = m_cPictureNew;
    m_PictureShow = m_PictureOriginal;
    m_Species = 6;
    m_AttackType = 2;

    //what changes
    m_HealthNow = m_HealthFull;
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_AttackPoint = m_AttackThreshold;
}

UArmyCalvaryFrance::UArmyCalvaryFrance(const int health, const double place_x, const double place_y, const int attack_value)
{
    //What do not change
    m_HealthFull = m_cHealthNew;
    m_SpeedFull = m_cSpeed;
    m_AttackDamage = m_cAttackDamageNew;
    m_AttackThreshold = m_cMeleeAttackSpan;
    m_Country = 2;
    m_PictureOriginal = m_cPictureNew;
    m_PictureShow = m_PictureOriginal;
    m_Species = 6;
    m_AttackType = 2;

    //what changes
    m_HealthNow = health;
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_AttackPoint = attack_value;
}

UArmyLightSpain::UArmyLightSpain(const int place_x, const int place_y)
{
    //What do not change
    m_HealthFull = m_cHealthNew;
    m_SpeedFull = m_cSpeed;
    m_AttackDamage = m_cAttackDamageNew;
    m_AttackThreshold = m_cRangedAttackSpanNew;
    m_Country = 3;
    m_PictureOriginal = m_cPictureNew;
    m_PictureShow = m_PictureOriginal;
    m_Species = 7;
    m_AttackType = 1;

    //what changes
    m_HealthNow = m_HealthFull;
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_AttackPoint = m_AttackThreshold;
}

UArmyLightSpain::UArmyLightSpain(const int health, const double place_x, const double place_y, const int attack_value)
{
    //What do not change
    m_HealthFull = m_cHealthNew;
    m_SpeedFull = m_cSpeed;
    m_AttackDamage = m_cAttackDamageNew;
    m_AttackThreshold = m_cRangedAttackSpanNew;
    m_Country = 3;
    m_PictureOriginal = m_cPictureNew;
    m_PictureShow = m_PictureOriginal;
    m_Species = 7;
    m_AttackType = 1;

    //what changes
    m_HealthNow = health;
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_AttackPoint = attack_value;
}




