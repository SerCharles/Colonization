/*
Filename: UAmmo.cpp
Description: the father class of all Ammos
Version: 2.0
Date: 09/08/2018
*/

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QPixmap>
#include "uunit.h"
#include "uammo.h"
#include "resources.h"
#include "constant.hpp"
#include "globalfunctions.h"

UAmmo::UAmmo(const int type, const int damage, const int place_x, const int place_y, const int final_x, const int final_y)
{
    //what do not change
    m_Species = type;
    m_Final_x = final_x;
    m_Final_y = final_y;
    m_HealthFull = 1;
    m_Damage = damage;
    m_PictureOriginal = m_cPictureBySpecies[type];
    m_SpeedFull = m_cSpeedBySpecies[type];


    //what changes
    m_PictureShow = m_PictureOriginal;
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_HealthNow = m_HealthFull;
    m_SpeedNow = m_SpeedFull;
    m_WhetherIsValid = 1;
}

void UAmmo::m_UpdateStatus()
{
    double temp_distance = g_GetDistance(m_Final_x, m_Final_y, this);
    if(temp_distance <= m_cWorkRange)
    {
        m_WhetherIsValid = 0;
        emit m_AmmoExploded(m_Species, m_Damage, m_Place_x, m_Place_y);
    }
    else
    {
        m_SeekRoute(m_Final_x, m_Final_y);
    }
}

void UAmmo::m_OutPut(QString file)
{
    QFile save_file(file);
    if(!save_file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
        return;
    }
    QTextStream save_stream(&save_file);
    save_stream <<  m_Species <<' '<< m_Damage <<' '<< m_Place_x <<' '<< m_Place_y <<' '<< m_Final_x <<' '<< m_Final_y << '\n';
}
