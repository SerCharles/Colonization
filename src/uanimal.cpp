/*
Filename: UAnimal.cpp
Description: the father class of all animals
Version: 1.1
Date: 09/02/2018
*/


#include <QObject>
#include <QFile>
#include <QTextStream>
#include <cstdlib>
#include <cmath>
#include "uunit.h"
#include "uanimal.h"
#include "constant.hpp"


void UAnimal::m_Wander()
{
    m_SpeedNow = m_SpeedFull * m_cWanderSpeedRatio;
    srand((unsigned)time(NULL));
    const double temp_angle = 2 * Constant::g_Pi *(rand() % Constant::g_AllAngle) / Constant::g_AllAngle;
    const double final_x = m_Place_x + cos(temp_angle);
    const double final_y = m_Place_y + cos(temp_angle);
    m_SeekRoute(final_x,final_y);
}

void UAnimal::m_Forage(const int final_x, const int final_y)
{
    if(m_Status == 2)
    {
        m_SpeedNow = (m_cHungryPointFull - m_HungryPoint) * m_SpeedFull * 0.6;
    }
    if(m_Status == 3)
    {
        m_SpeedNow = (m_cHungryPointFull - m_HungryPoint) * m_SpeedFull ;
    }
    m_SeekRoute(final_x, final_y);
}

void UAnimal::m_UpdateStatus()
{
    m_UpdatePicture();
    if(m_Status == 4)
    {
        m_UpdateDeath();
        return;
    }
    m_UpdateHealth();
    m_UpdateHungry();
    m_UpdateProduce();
}

void UAnimal::m_UpdatePicture()
{
    if(m_Status == 1 || m_Status == 2)
    {
        m_PictureShow = m_PictureOriginal;
    }
    else if (m_Status == 3)
    {
        m_PictureShow = m_PictureHungry;
    }
    else
    {
        m_PictureShow = m_PictureDead;
    }
}

void UAnimal::m_UpdateDeath()
{
    if(m_TimeAfterDeath >= m_cShowTimeAfterDeath)
    {
        m_WhetherIsValid = 0;
    }
    m_TimeAfterDeath ++;
}

void UAnimal::m_UpdateHealth()
{
    if(m_Status == 4)
    {
        return;
    }
    if(m_HealthNow <= 0)
    {
        m_Status = 4;
    }
}

void UAnimal::m_UpdateHungry()
{
    m_HungryPoint -= m_cHungryDecrease;
    if(m_Status == 4)
    {
        return;
    }
    if(m_HungryPoint >= m_cEatRatio)
    {
        m_Status = 1;
    }
    else if(m_HungryPoint >= m_cHungryRatio)
    {
        m_Status = 2;
    }
    else if(m_HungryPoint >0)
    {
        m_Status = 3;
    }
    else
    {
        m_Status = 4;
    }
}

void UAnimal::m_UpdateProduce()
{
    if(m_Status == 4)
    {
        return;
    }
    if(m_Status == 1 || m_Status == 2)
    {
        if(m_ProduceValue >= m_cProduceThreshold)
        {
            emit m_BonusProduced(m_MoneyProduct, m_MaterialProduct, m_Place_x, m_Place_y);
            m_ProduceValue = 0;
        }
        m_ProduceValue ++;
    }
    else
    {
        m_ProduceValue = 0;
    }
}

void UAnimal::m_BeingEaten()
{
    m_WhetherIsValid = 0;
    m_Status = 4;
}

void UAnimal::m_BeingAttack(const int damage)
{
    m_HealthNow -= damage;
}

void UAnimal::m_GiveFood(int *health_add, double *hungry_add)
{
    *health_add = m_HealthAdd;
    *hungry_add = m_HungryPointAdd;
}

void UAnimal::m_EatFood(const int health_add, const double hungry_point_add)
{
    m_HealthNow += health_add;
    if(m_HealthNow > m_HealthFull)
    {
        m_HealthNow = m_HealthFull;
    }
    m_HungryPoint += hungry_point_add;
    if(m_HungryPoint > m_cHungryPointFull)
    {
        m_HungryPoint = m_cHungryPointFull;
    }
}

void UAnimal::m_OutPut(QString file)
{
    QFile save_file(file);
    if(!save_file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
        return;
    }
    QTextStream save_stream(&save_file);
    save_stream << m_Species <<' '<< m_HealthNow <<' '<< m_HungryPoint <<' '<< m_Place_x <<' '<< m_Place_y <<' '<< m_ProduceValue <<'\n';
    save_file.close();

}
