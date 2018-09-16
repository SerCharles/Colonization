/*
Filename: UEnemyEater.cpp
Description: the father class of eaters
Version: 2.0
Date: 09/08/2018
*/



#include <QObject>
#include <QPixmap>
#include <QFile>
#include <QTextStream>
#include "constant.hpp"
#include "resources.h"
#include "globalfunctions.h"
#include "uunit.h"
#include "uenemy.h"
#include "uenemyeater.h"

UEnemyEater::UEnemyEater(const int place_x, const int place_y)
{
    //what do not change
    m_HealthFull = m_cHealthFull;
    m_PictureOriginal = m_cPicture;
    m_SpeedFull = m_cSpeedFull;
    m_Species = 2;
    m_MoneyProduce = m_cMoneyProduce;
    m_MaterialProduce = m_cMaterialProduce;

    //what changes
    m_HealthNow = m_HealthFull;
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_PictureShow = m_PictureOriginal;
}

UEnemyEater::UEnemyEater(const int health, const double place_x, const double place_y)
{
    //what do not change
    m_HealthFull = m_cHealthFull;
    m_PictureOriginal = m_cPicture;
    m_SpeedFull = m_cSpeedFull;
    m_Species = 2;
    m_MoneyProduce = m_cMoneyProduce;
    m_MaterialProduce = m_cMaterialProduce;

    //what changes
    m_HealthNow = health;
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_PictureShow = m_PictureOriginal;
}

void UEnemyEater::m_EatFood(const int health_add, const double hungry_point_add)
{
    m_HealthNow -= health_add;
}

void UEnemyEater::m_UpdateStatus()
{
    m_UpdateHealth();
}

void UEnemyEater::m_OutPut(QString file)
{
    QFile save_file(file);
    if(!save_file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
        return;
    }
    QTextStream save_stream(&save_file);
    save_stream <<  m_Species <<' '<< m_HealthNow <<' '<< m_Place_x <<' '<< m_Place_y  <<'\n';
    save_file.close();

}
