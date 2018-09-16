/*
Filename: UAnimalKing.cpp
Description: the father class of animal king
Version: 2.0
Date: 09/07/2018
*/


#include <QFile>
#include <QTextStream>
#include "globalfunctions.h"
#include "uunit.h"
#include "uanimal.h"
#include "uanimalking.h"


UAnimalKing::UAnimalKing(const int place_x, const int place_y)
{
    //What do not change in a game
    m_Species = 7;
    m_HealthAdd = m_cHealthAdd;
    m_HungryPointAdd = m_cHungryAdd;
    m_MoneyProduct = m_cMoneyProduct;
    m_MaterialProduct = m_cMaterialProduct;
    m_HealthFull = m_cHealthFull;
    m_PictureOriginal = m_cPictureOriginal;
    m_PictureHungry = m_cPictureHungry;
    m_PictureDead = m_cPictureDead;
    m_SpeedFull = m_cSpeedFull;
    m_Level = 1;


    //What changes in a game
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_Status = 1;
    m_HealthNow = m_HealthFull;
    m_PictureShow = m_cPictureOriginal;
    m_TimeAfterDeath = 0;
}

UAnimalKing::UAnimalKing(const int health, const double hungry, const double place_x, const double place_y, const int produce)
{
    //What do not change in a game
    m_Species = 7;
    m_HealthAdd = m_cHealthAdd;
    m_HungryPointAdd = m_cHungryAdd;
    m_MoneyProduct = m_cMoneyProduct;
    m_MaterialProduct = m_cMaterialProduct;
    m_HealthFull = m_cHealthFull;
    m_PictureOriginal = m_cPictureOriginal;
    m_PictureHungry = m_cPictureHungry;
    m_PictureDead = m_cPictureDead;
    m_SpeedFull = m_cSpeedFull;
    m_Level = 1;


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

void UAnimalKing::m_UpdateHungry()
{
    if(m_Status == 4)
    {
        return;
    }
    m_HungryPoint = m_cHungryPointFull;
    if(m_HealthNow > 0)
    {
        m_Status = 1;
    }
}



