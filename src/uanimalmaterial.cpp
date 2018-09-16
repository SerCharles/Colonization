/*
Filename: UAnimalMaterial.cpp
Description: the father class of material-produce animals
Version: 2.0
Date: 09/07/2018
*/

#include <QObject>
#include <QPixmap>
#include <QFile>
#include <QTextStream>
#include "globalfunctions.h"
#include "uunit.h"
#include "uanimal.h"
#include "uanimalmaterial.h"


UAnimalMaterial::UAnimalMaterial(const int place_x, const int place_y)
{
    //What do not change in a game,unless upgrade
    m_Level = 1;
    m_Species = 5;
    m_MoneyProduct = m_cMoneyProductByLevel[1];
    m_MaterialProduct = m_cMaterialProductByLevel[1];
    m_HealthFull = m_cHealthFullByLevel[1];
    m_PictureOriginal = m_cPictureOriginalByLevel[1];
    m_PictureHungry = m_cPictureHungryByLevel[1];
    m_PictureDead = m_cPictureDeadByLevel[1];
    m_SpeedFull = m_cSpeedFullByLevel[1];
    m_HealthAdd = m_cHealthAdd;

    //What changes in a game
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_Status = 1;
    m_HealthNow = m_HealthFull;
    m_Experience = 0;
    m_PictureShow = m_cPictureOriginalByLevel[1];
    m_TimeAfterDeath = 0;
}

UAnimalMaterial::UAnimalMaterial(const int level, const int experience, const int health,
                                 const double hungry, const double place_x, const double place_y, const int produce)
{
    //What do not change in a game,unless upgrade
    m_Level = level;
    m_Species = 5;
    m_MoneyProduct = m_cMoneyProductByLevel[level];
    m_MaterialProduct = m_cMaterialProductByLevel[level];
    m_HealthFull = m_cHealthFullByLevel[level];
    m_PictureOriginal = m_cPictureOriginalByLevel[level];
    m_PictureHungry = m_cPictureHungryByLevel[level];
    m_PictureDead = m_cPictureDeadByLevel[level];
    m_SpeedFull = m_cSpeedFullByLevel[level];
    m_HealthAdd = m_cHealthAdd;

    //What changes in a game
    m_Place_x = place_x;
    m_Place_y = place_y;
    m_Status = 1;
    m_HealthNow = health;
    m_HungryPoint = hungry;
    m_ProduceValue = produce;
    m_Experience = experience;
    m_PictureShow = m_cPictureOriginalByLevel[level];
    m_TimeAfterDeath = 0;
}

void UAnimalMaterial::m_Upgrade()
{
    //reset consts
    m_Level ++;
    m_MoneyProduct = m_cMoneyProductByLevel[m_Level];
    m_MaterialProduct = m_cMaterialProductByLevel[m_Level];
    m_HealthFull = m_cHealthFullByLevel[m_Level];
    m_PictureOriginal = m_cPictureOriginalByLevel[m_Level];
    m_PictureHungry = m_cPictureHungryByLevel[m_Level];
    m_PictureDead = m_cPictureDeadByLevel[m_Level];
    m_SpeedFull = m_cSpeedFullByLevel[m_Level];

    //renew health and exp
    m_HealthNow = m_HealthFull;
    m_Experience = 0;
    m_ProduceValue = 0;
    m_PictureShow = m_cPictureOriginalByLevel[m_Level];
}


void UAnimalMaterial::m_UpdateGrade()
{
    if(m_Level == m_cMaxLevel || m_Status == 3 || m_Status == 4 ) //MaxLevel or hungry or dead: no upgrade or exp accumulation
    {
        return;
    }
    if(m_Status == 1 || m_Status == 2)
    {
        if(m_Experience >= m_cExperienceRequiredUpgrade[m_Level])
        {
                m_Upgrade();
        }
    }
}

void UAnimalMaterial::m_UpdateStatus()
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
    m_UpdateGrade();
}

void UAnimalMaterial::m_EatFood(const int health_add, const double hungry_point_add)
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
    m_Experience += (100 * hungry_point_add + health_add);
}

void UAnimalMaterial::m_OutPut(QString file)
{
    QFile save_file(file);
    if(!save_file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
        return;
    }
    QTextStream save_stream(&save_file);
    save_stream << m_Species <<' '<< m_Level <<' '<< m_Experience <<' '<< m_HealthNow <<' '<< m_HungryPoint <<' '<< m_Place_x <<' '<< m_Place_y <<' '<< m_ProduceValue <<'\n';
    save_file.close();

}

