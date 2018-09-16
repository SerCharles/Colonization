/*
Filename: UEnemyNative.cpp
Description: the father class of native enemies
Version: 2.0
Date: 09/09/2018
*/

#include <QObject>
#include <QPixmap>
#include "constant.hpp"
#include "resources.h"
#include "globalfunctions.h"
#include "uunit.h"
#include "uenemy.h"
#include "uenemynative.h"

UEnemyNativeWarrior::UEnemyNativeWarrior(const int place_x, const int place_y)
{
    //what do not change
    m_AttackDamage = m_cAttackDamage;
    m_HealthFull = m_cHealthFull;
    m_AttackThreshold = m_cMeleeAttackSpan;
    m_PictureOriginal = m_cPicture;
    m_SpeedFull = m_cSpeedFull;
    m_Species = 3;
    m_MoneyProduce = m_cMoneyProduce;
    m_MaterialProduce = m_cMaterialProduce;

    //what changes
    m_HealthNow = m_HealthFull;
    m_AttackPoint = m_AttackThreshold;
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_PictureShow = m_PictureOriginal;
}

UEnemyNativeWarrior::UEnemyNativeWarrior(const int health, const double place_x, const double place_y, const int attackvalue)
{
    //what do not change
    m_AttackDamage = m_cAttackDamage;
    m_HealthFull = m_cHealthFull;
    m_AttackThreshold = m_cMeleeAttackSpan;
    m_PictureOriginal = m_cPicture;
    m_SpeedFull = m_cSpeedFull;
    m_Species = 3;
    m_MoneyProduce = m_cMoneyProduce;
    m_MaterialProduce = m_cMaterialProduce;

    //what changes
    m_HealthNow = health;
    m_AttackPoint = attackvalue;
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_PictureShow = m_PictureOriginal;
}

int UEnemyNativeWarrior::m_PerformAttack()
{
    m_AttackPoint = m_AttackThreshold;
    m_WhetherCanAttack = 0;
    return m_AttackDamage;
}

UEnemyNativeGunner::UEnemyNativeGunner(const int place_x, const int place_y)
{
    //what do not change
    m_AttackDamage = m_cAttackDamage;
    m_HealthFull = m_cHealthFull;
    m_AttackThreshold = m_cRangedAttackSpan;
    m_PictureOriginal = m_cPicture;
    m_SpeedFull = m_cSpeedFull;
    m_Species = 4;
    m_MoneyProduce = m_cMoneyProduce;
    m_MaterialProduce = m_cMaterialProduce;

    //what changes
    m_HealthNow = m_HealthFull;
    m_AttackPoint = m_AttackThreshold;
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_PictureShow = m_PictureOriginal;
}

UEnemyNativeGunner::UEnemyNativeGunner(const int health, const double place_x, const double place_y, const int attackvalue)
{
    //what do not change
    m_AttackDamage = m_cAttackDamage;
    m_HealthFull = m_cHealthFull;
    m_AttackThreshold = m_cRangedAttackSpan;
    m_PictureOriginal = m_cPicture;
    m_SpeedFull = m_cSpeedFull;
    m_Species = 4;
    m_MoneyProduce = m_cMoneyProduce;
    m_MaterialProduce = m_cMaterialProduce;

    //what changes
    m_HealthNow = health;
    m_AttackPoint = attackvalue;
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_PictureShow = m_PictureOriginal;
}

void UEnemyNativeGunner::m_ShootAmmo(const int final_x, const int final_y)
{
    m_WhetherCanAttack = 0;
    m_AttackPoint = 0;
    emit m_AmmoShooted(2, m_AttackDamage, m_Place_x, m_Place_y, final_x, final_y);
}

UEnemyNativeShaman::UEnemyNativeShaman(const int place_x, const int place_y)
{
    //what do not change
    m_AttackDamage = m_cAttackDamage;
    m_HealthFull = m_cHealthFull;
    m_AttackThreshold = m_cRangedAttackSpan;
    m_PictureOriginal = m_cPicture;
    m_SpeedFull = m_cSpeedFull;
    m_Species = 5;
    m_MoneyProduce = m_cMoneyProduce;
    m_MaterialProduce = m_cMaterialProduce;

    //what changes
    m_HealthNow = m_HealthFull;
    m_AttackPoint = m_AttackThreshold;
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_PictureShow = m_PictureOriginal;
}

UEnemyNativeShaman::UEnemyNativeShaman(const int health, const double place_x, const double place_y, const int attackvalue)
{
    //what do not change
    m_AttackDamage = m_cAttackDamage;
    m_HealthFull = m_cHealthFull;
    m_AttackThreshold = m_cRangedAttackSpan;
    m_PictureOriginal = m_cPicture;
    m_SpeedFull = m_cSpeedFull;
    m_Species = 5;
    m_MoneyProduce = m_cMoneyProduce;
    m_MaterialProduce = m_cMaterialProduce;

    //what changes
    m_HealthNow = health;
    m_AttackPoint = attackvalue;
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_PictureShow = m_PictureOriginal;
}

void UEnemyNativeShaman::m_ShootAmmo(const int final_x, const int final_y)
{
    m_WhetherCanAttack = 0;
    m_AttackPoint = 0;
}
