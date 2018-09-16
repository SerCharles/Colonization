/*
Filename: UEnemyBarbarian.h
Description: the father class of barbarians
Version: 2.0
Date: 09/07/2018
*/

#ifndef UENEMYBARBARIAN_H
#define UENEMYBARBARIAN_H

#include <QObject>
#include <QPixmap>
#include "constant.hpp"
#include "resources.h"
#include "globalfunctions.h"
#include "uunit.h"
#include "uenemy.h"


class UEnemyBarbarian: public UEnemy
{
    Q_OBJECT
public:
    //constants
    const int m_cHealthFull{100};
    const double m_cSpeedFull{2};
    const int m_cAttackDamage{100};
    const int m_cMoneyProduce{3};
    const int m_cMaterialProduce{0};
    QPixmap* m_cPicture{g_Resources -> EnemyBarbarian};
public:

    /* override father class function
     * returns your attack damage
     * public interface, used to give your attack point when managing an attack
     */
    virtual int m_PerformAttack();

    //build a new one
    UEnemyBarbarian(const int place_x, const int place_y);

    //load one from save file
    UEnemyBarbarian(const int health, const double place_x, const double place_y, const int attackvalue );
    ~UEnemyBarbarian(){}

};

#endif // UENEMYBARBARIAN_H
