/*
Filename: UUnit.cpp
Description: the father class of all units, including animals, enemies and army.
Version: 1.1
Date: 09/02/2018
*/
#include<QObject>
#include<QPixmap>
#include<cmath>
#include"uunit.h"
#include "constant.hpp"

void UUnit::m_SeekRoute(double final_x,double final_y)
{
    const double temp_distance_x = final_x - m_Place_x;
    const double temp_distance_y = final_y - m_Place_y;
    const double temp_distance = sqrt(temp_distance_x * temp_distance_x + temp_distance_y * temp_distance_y);
    const double temp_component_x = temp_distance_x / temp_distance;
    const double temp_component_y = temp_distance_y / temp_distance;
    m_Place_x += (temp_component_x * m_SpeedNow);
    m_Place_y += (temp_component_y * m_SpeedNow);
    m_RepairOverBorder();
}


void UUnit::m_RepairOverBorder()
{
    if(m_Place_x < Constant::g_BorderMin_x)
    {
        m_Place_x = Constant::g_BorderMin_x;
    }
    if(m_Place_x > Constant::g_BorderMax_x)
    {
        m_Place_x = Constant::g_BorderMax_x;
    }
    if(m_Place_y < Constant::g_BorderMin_y)
    {
        m_Place_y = Constant::g_BorderMin_y;
    }
    if(m_Place_y > Constant::g_BorderMax_y)
    {
        m_Place_y = Constant::g_BorderMax_y;
    }
}

void UUnit::m_GetPlace(double* place_x, double* place_y)
{
    *place_x = m_Place_x;
    *place_y = m_Place_y;
}

void UUnit::m_InstantMove(const double move_x, const double move_y)
{
    m_Place_x += move_x;
    m_Place_y += move_y;
    m_RepairOverBorder();
}
