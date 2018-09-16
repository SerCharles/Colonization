/*
Filename: UEnemyNative.h
Description: the father class of native enemies
Version: 2.0
Date: 09/09/2018
*/


#ifndef UENEMYNATIVE_H
#define UENEMYNATIVE_H

#include <QObject>
#include <QPixmap>
#include "constant.hpp"
#include "resources.h"
#include "globalfunctions.h"
#include "uunit.h"
#include "uenemy.h"

class UEnemyNativeWarrior: public UEnemy
{
    Q_OBJECT
public:
    //constants
    const int m_cHealthFull{100};
    const double m_cSpeedFull{2};
    const int m_cAttackDamage{50};
    const int m_cMoneyProduce{0};
    const int m_cMaterialProduce{0};
    QPixmap* m_cPicture{g_Resources -> EnemyNativeWarrior};
public:

    /* override father class function
     * returns your attack damage
     * public interface, used to give your attack point when managing an attack
     */
    virtual int m_PerformAttack();

    //construct a new one
    UEnemyNativeWarrior(const int place_x, const int place_y);

    //construct an old one from save files
    UEnemyNativeWarrior(const int health, const double place_x, const double place_y, const int attackvalue);
    ~UEnemyNativeWarrior(){}

};

class UEnemyNativeGunner: public UEnemy
{
    Q_OBJECT
public:
    //constants
    const int m_cHealthFull{100};
    const double m_cSpeedFull{5};
    const int m_cAttackDamage{70};
    const int m_cMoneyProduce{0};
    const int m_cMaterialProduce{0};
    QPixmap* m_cPicture{g_Resources -> EnemyNativeGunner};
public:
    UEnemyNativeGunner(const int place_x, const int place_y);
    UEnemyNativeGunner(const int health, const double place_x, const double place_y, const int attackvalue);
    ~UEnemyNativeGunner(){}


    /*the public interface in managing ranged attack, an ammo will be shoot to the enemy
     * use:when the enemy gunner shoot an ammo
     * variables:the place of enemy
     * */
    virtual void m_ShootAmmo(const int final_x, const int final_y);

};

class UEnemyNativeShaman: public UEnemy
{
    Q_OBJECT
public:
    //constants
    const int m_cHealthFull{100};
    const double m_cSpeedFull{3};
    const int m_cAttackDamage{0};
    const int m_cMoneyProduce{0};
    const int m_cMaterialProduce{0};
    QPixmap* m_cPicture{g_Resources -> EnemyNativeShaman};
public:
    UEnemyNativeShaman(const int place_x, const int place_y);
    UEnemyNativeShaman(const int health, const double place_x, const double place_y, const int attackvalue);
    ~UEnemyNativeShaman(){}


    /*the public interface in updating attack points
     * use:when switching an animal into an enemy
     * variables:useless, just to override and use strategy mode
     * */
    virtual void m_ShootAmmo(const int final_x, const int final_y);

};

#endif // UENEMYNATIVE_H
