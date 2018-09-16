/*
Filename: UAnimalMaterialMother.cpp
Description: the father class of material mother animals
Version: 2.0
Date: 09/07/2018
*/


#include <QFile>
#include <QTextStream>
#include "globalfunctions.h"
#include "uunit.h"
#include "uanimal.h"
#include "uanimalgrass.h"
#include "uanimalmaterialmother.h"

UAnimalMaterialMother::UAnimalMaterialMother(const int place_x, const int place_y)
{
    //What do not change in a game,unless upgrade
    m_Level = 1;
    m_Species = 6;
    m_HealthFull = m_cHealthFull;
    m_PictureOriginal = m_cPictureOriginal;
    m_PictureHungry = m_cPictureHungry;
    m_PictureDead = m_cPictureDead;
    m_SpeedFull = m_cSpeedFull;
    m_ProduceThreshold = m_cProduceThreshold;
    m_HealthAdd = m_cHealthAdd;
    //What changes in a game
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_Status = 1;
    m_HealthNow = m_HealthFull;
    m_PictureShow = m_cPictureOriginal;
    m_TimeAfterDeath = 0;
}

UAnimalMaterialMother::UAnimalMaterialMother(const int health, const double hungry, const double place_x, const double place_y,
                                             const int produce)
{
    //What do not change in a game,unless upgrade
    m_Level = 1;
    m_Species = 6;
    m_HealthFull = m_cHealthFull;
    m_PictureOriginal = m_cPictureOriginal;
    m_PictureHungry = m_cPictureHungry;
    m_PictureDead = m_cPictureDead;
    m_SpeedFull = m_cSpeedFull;
    m_ProduceThreshold = m_cProduceThreshold;
    m_HealthAdd = m_cHealthAdd;
    //What changes in a game
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_Status = 1;
    m_HealthNow = health;
    m_HungryPoint = hungry;
    m_ProduceValue = produce;
    m_PictureShow = m_cPictureOriginal;
    m_TimeAfterDeath = 0;
}

//update produce
void UAnimalMaterialMother::m_UpdateProduce()
{
    if(m_Status == 4)
    {
        return;
    }
    if(m_Status == 1 || m_Status == 2)
    {
        if(m_ProduceValue >= m_ProduceThreshold)
        {
            emit m_ChildProduced(m_Place_x, m_Place_y);
            m_ProduceValue = 0;
        }
        m_ProduceValue ++;
    }
    else
    {
        m_ProduceValue = 0;
    }
}


