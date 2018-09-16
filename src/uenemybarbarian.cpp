/*
Filename: UEnemyBarbarian.cpp
Description: the father class of barbarians
Version: 2.0
Date: 09/07/2018
*/



#include <QObject>
#include <QPixmap>
#include "constant.hpp"
#include "resources.h"
#include "globalfunctions.h"
#include "uunit.h"
#include "uenemy.h"
#include "uenemybarbarian.h"

UEnemyBarbarian::UEnemyBarbarian(const int place_x, const int place_y)
{
    //what do not change
    m_AttackDamage = m_cAttackDamage;
    m_HealthFull = m_cHealthFull;
    m_AttackThreshold = m_cMeleeAttackSpan;
    m_PictureOriginal = m_cPicture;
    m_SpeedFull = m_cSpeedFull;
    m_Species = 1;
    m_MoneyProduce = m_cMoneyProduce;
    m_MaterialProduce = m_cMaterialProduce;

    //what changes
    m_HealthNow = m_HealthFull;
    m_AttackPoint = m_AttackThreshold;
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_PictureShow = m_PictureOriginal;
}

UEnemyBarbarian::UEnemyBarbarian(const int health, const double place_x, const double place_y, const int attackvalue)
{
    //what do not change
    m_AttackDamage = m_cAttackDamage;
    m_HealthFull = m_cHealthFull;
    m_AttackThreshold = m_cMeleeAttackSpan;
    m_PictureOriginal = m_cPicture;
    m_SpeedFull = m_cSpeedFull;
    m_Species = 1;
    m_MoneyProduce = m_cMoneyProduce;
    m_MaterialProduce = m_cMaterialProduce;

    //what changes
    m_HealthNow = health;
    m_AttackPoint = attackvalue;
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_PictureShow = m_PictureOriginal;
}

int UEnemyBarbarian::m_PerformAttack()
{
    m_AttackPoint = 0;
    m_WhetherCanAttack = 0;
    return m_AttackDamage;
}
