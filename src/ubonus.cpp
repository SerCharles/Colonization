/*
Filename: UBonus.cpp
Description: the father class of bonuses, including two types
Version: 1.1
Date: 09/04/2018
*/

#include <QObject>
#include <QFile>
#include <QTextStream>
#include "uunit.h"
#include "ubonus.h"
#include "constant.hpp"

UBonus::UBonus()
{
    //Useless Data
    m_HealthFull = 1;
    m_HealthNow = 1;
    m_SpeedFull = 0;
    m_SpeedNow = 0;
}

void UBonus::m_GiveBonus(int *type, int *quantity)
{
    *type = m_Type;
    *quantity = m_BonusQuantity;
}

void UBonus::m_RepairOverBorder()
{
    if(m_Place_x < Constant::g_BonusBorderMin_x)
    {
        m_Place_x = Constant::g_BonusBorderMin_x;
    }
    if(m_Place_x > Constant::g_BonusBorderMax_x)
    {
        m_Place_x = Constant::g_BonusBorderMax_x;
    }
    if(m_Place_y < Constant::g_BonusBorderMin_y)
    {
        m_Place_y = Constant::g_BonusBorderMin_y;
    }
    if(m_Place_y > Constant::g_BonusBorderMax_y)
    {
        m_Place_y = Constant::g_BonusBorderMax_y;
    }
}

void UBonus::m_BeingTaken()
{
    m_WhetherIsValid = 0;
}

void UBonus::m_OutPut(QString file)
{
    QFile save_file(file);
    if(!save_file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
        return;
    }
    QTextStream save_stream(&save_file);
    save_stream <<  m_Type <<' '<< m_Level <<' '<< m_Place_x <<' '<< m_Place_y << '\n';
    save_file.close();

}

UBonusMoney::UBonusMoney(const int level, const int place_x, const int place_y)
{
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_Level = level;
    m_Type = 1;
    m_BonusQuantity = m_cBonusQuantityByLevel[m_Level];
    m_PictureOriginal = m_PictureByLevel[m_Level];
    m_PictureShow = m_PictureOriginal;
}

UBonusMaterial::UBonusMaterial(const int level, const int place_x, const int place_y)
{
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_Level = level;
    m_Type = 2;
    m_BonusQuantity = m_cBonusQuantityByLevel[m_Level];
    m_PictureOriginal = m_PictureByLevel[m_Level];
    m_PictureShow = m_PictureOriginal;
}
