/*
Filename: USteward.cpp
Description: the father class of stewards
Version: 2.0
Date: 09/10/2018
*/

#include <QObject>
#include <QPixmap>
#include <QFile>
#include <QTextStream>
#include "uunit.h"
#include "constant.hpp"
#include "resources.h"
#include "globalfunctions.h"
#include "usteward.h"

USteward::USteward(const double place_x, const double place_y)
{
    //what do not change in a game
    m_SpeedFull = m_cSpeed;
    m_HealthFull = 1;
    m_PictureOriginal = m_cPictureOriginal;
    m_PictureHide = m_cPictureHide;

    //what changes
    m_WhetherIsValid = 1;
    m_WhetherIsActive = 1;
    m_HealthNow = m_HealthFull;
    m_PictureShow = m_PictureOriginal;
    m_Place_x = place_x;
    m_Place_y = place_y;
}

void USteward::m_UpdateStatus()
{
    if(m_WhetherIsActive == 1)
    {
        m_PictureShow = m_PictureOriginal;
    }
    else
    {
        m_PictureShow = m_PictureHide;
    }
}

void USteward::m_Wander()
{
    m_SpeedNow = m_SpeedFull * m_cWanderSpeedRatio;
    srand((unsigned)time(NULL));
    const double temp_angle = 2 * Constant::g_Pi *(rand() % Constant::g_AllAngle) / Constant::g_AllAngle;
    const double final_x = m_Place_x + cos(temp_angle);
    const double final_y = m_Place_y + cos(temp_angle);
    m_SeekRoute(final_x,final_y);
}

void USteward::m_ChaseTarget(const int final_x, const int final_y)
{
    m_SpeedNow = m_SpeedFull;
    m_SeekRoute(final_x, final_y);
}

void USteward::m_OutPut(QString file)
{
    QFile save_file(file);
    if(!save_file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
        return;
    }
    QTextStream save_stream(&save_file);
    save_stream << m_Place_x <<' '<< m_Place_y << '\n';
    save_file.close();

}
