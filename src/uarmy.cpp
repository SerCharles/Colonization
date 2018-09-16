/*
Filename: UArmy.cpp
Description: the father class of all armies
Version: 2.0
Date: 09/07/2018
*/


#include <QObject>
#include <cstdlib>
#include <QFile>
#include <QTextStream>
#include <cmath>
#include "uunit.h"
#include "uarmy.h"
#include "constant.hpp"

void UArmy::m_Wander()
{
    m_SpeedNow = m_SpeedFull * m_cWanderSpeedRatio;
    srand((unsigned)time(NULL));
    const double temp_angle = 2 * Constant::g_Pi *(rand() % Constant::g_AllAngle) / Constant::g_AllAngle;
    const double final_x = m_Place_x + cos(temp_angle);
    const double final_y = m_Place_y + cos(temp_angle);
    m_SeekRoute(final_x,final_y);
}

void UArmy::m_ChaseTarget(const int final_x, const int final_y)
{
    m_SpeedNow = m_SpeedFull;
    m_SeekRoute(final_x, final_y);
}

void UArmy::m_UpdateHealth()
{
    if(m_HealthNow <= 0)
    {
        m_WhetherIsValid = 0;
    }
}

void UArmy::m_UpdateAttack()
{
    m_AttackPoint ++;
    if(m_AttackPoint >= m_AttackThreshold)
    {
        m_AttackPoint = m_AttackThreshold;
        m_WhetherCanAttack = 1;
    }
    else
    {
        m_WhetherCanAttack = 0;
    }
}

void UArmy::m_UpdateStatus()
{
    m_UpdateAttack();
    m_UpdateHealth();
}

void UArmy::m_BeingAttack(const int damage)
{
    m_HealthNow -= damage;
}

int UArmy::m_PerformAttack()
{
    m_AttackPoint = 0;
    m_WhetherCanAttack = 0;
    return m_AttackDamage;
}

void UArmy::m_OutPut(QString file)
{
    QFile save_file(file);
    if(!save_file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
        return;
    }
    QTextStream save_stream(&save_file);
    save_stream << m_Species <<' '<< m_HealthNow <<' '<< m_Place_x <<' '<< m_Place_y  <<' '<< m_AttackPoint <<'\n';
    save_file.close();

}
