/*
Filename: UFood.h
Description: the father class of all food
Version: 1.1
Date: 09/02/2018
*/


#include <QObject>
#include <QFile>
#include <QTextStream>
#include "uunit.h"
#include "ufood.h"
#include "constant.hpp"

void UFood::m_MoveDown()
{
    m_SeekRoute(m_Place_x,m_Place_y + 1);
    if(m_Place_y == Constant::g_BorderMax_y)
    {
        m_WhetherIsValid = 0;
    }
}

void UFood::m_BeingEaten()
{
    m_WhetherIsValid = 0;
}

UFood::UFood()
{
    m_HealthNow = 1;
    m_HealthFull = 1;
}

void UFood::m_GiveFood(int *health_add, double *hungry_add)
{
    *health_add = m_HealthAdd;
    *hungry_add = m_HungryPointAdd;
}

void UFood::m_OutPut(QString file)
{
    QFile save_file(file);
    if(!save_file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
        return;
    }
    QTextStream save_stream(&save_file);
    save_stream <<  m_Species <<' '<< m_Level <<' '<< m_Place_x <<' '<< m_Place_y << '\n';
    save_file.close();

}


UFoodLand::UFoodLand(const int level, const int place_x, const int place_y)
{
    m_Level = level;
    m_Species = 1;
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_HealthAdd = m_cHealthAddByLevel[level];
    m_HungryPointAdd = m_cHungryPointAddByLevel[level];
    m_SpeedFull = 0;
    m_SpeedNow = m_SpeedFull;
    m_PictureOriginal = m_PictureByLevel[m_Level];
    m_PictureShow = m_PictureOriginal;
}

UFoodSea::UFoodSea(const int level, const int place_x, const int place_y)
{
    m_Level = level;
    m_Species = 2;
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_HealthAdd = m_cHealthAddByLevel[level];
    m_HungryPointAdd = m_cHungryPointAddByLevel[level];
    m_SpeedFull = m_cSpeedByLevel[level];
    m_SpeedNow = m_SpeedFull;
    m_PictureOriginal = m_PictureByLevel[m_Level];
    m_PictureShow = m_PictureOriginal;
}


