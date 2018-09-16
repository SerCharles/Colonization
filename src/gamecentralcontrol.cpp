/*
Filename: GameCentralControl.cpp
Description: the central control of the game
Version: 1.1
Date: 09/04/2018
*/

//system
#include <QObject>
#include <QList>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <cstdlib>

#include "constant.hpp"
#include "resources.h"
#include "globalfunctions.h"

//units
#include "uunit.h"

#include "uanimal.h"
#include "uanimalgrass.h"
#include "uanimalmaterial.h"
#include "uanimalmeat.h"
#include "uanimalmother.h"
#include "uanimalmaterialmother.h"
#include "uanimalking.h"

#include "uenemy.h"
#include "uenemybarbarian.h"
#include "uenemyeater.h"
#include "uenemynative.h"

#include "uarmy.h"
#include "uarmykinds.h"
#include "usteward.h"

#include "ubonus.h"
#include "ufood.h"
#include "uammo.h"

#include "gamecentralcontrol.h"

//initialize and delete
GameCentralControl::GameCentralControl(const int country)
{
    m_Steward = NULL;
    //values
    m_Country = country;
    m_Food = m_cFoodStart;
    m_Money = m_cMoneyStart;
    m_Material = m_cMaterialStart;
    m_BombDamage = m_cBombDamageStart;
    if(m_Country == 3)//spain
    {
        m_Food *= 1.5;
        m_Money *= 2;
        m_Material *= 1.5;
    }
    m_FoodLandLevel = 1;
    m_FoodSeaLevel = 1;
    m_FoodMaxNumberLevel = 1;
    m_WallLevel = 0;
    m_FarmLevel = 0;
    m_FactoryLevel = 0;
    m_HarborLevel = 0;
    m_MarketLevel = 0;
    m_BarrackLevel = 0;
    m_StableLevel = 0;
    m_ArsenalLevel = 0;
    
    m_FoodMaxNumber = m_cFoodMaxNumberByLevel[1];
    m_AnimalKingNumbers = 0;

    //war
    m_WarReadyPoint = 0;
    m_WarTriggerPoint = 0;
}

GameCentralControl::GameCentralControl(const QString file)
{
    QFile save_file(file);
    save_file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream save_stream(&save_file);

    //load numbers
    save_stream >> m_Country >> m_Money >> m_Food >> m_Material;
    save_stream >> m_WallLevel >> m_FarmLevel >> m_FactoryLevel >> m_MarketLevel;
    save_stream >> m_HarborLevel >> m_BarrackLevel >> m_StableLevel >> m_ArsenalLevel;
    save_stream >> m_FoodLandLevel >> m_FoodSeaLevel >> m_FoodMaxNumberLevel;

    m_AnimalKingNumbers = 0;
    m_BombDamage = m_cBombDamageStart;
    //war

    //load units
    //animals
    int t_animal_number;
    save_stream >> t_animal_number;
    int t_enemy_number;
    save_stream >> t_enemy_number;
    int t_army_number;
    save_stream >> t_army_number;
    int t_food_number;
    save_stream >> t_food_number;
    int t_bonus_number;
    save_stream >> t_bonus_number;
    int t_ammo_number;
    save_stream >> t_ammo_number;
    int t_steward_number;
    save_stream >> t_steward_number;

    //animals
    for(int i = 1; i <= t_animal_number; i ++)
    {
        int t_species, t_level, t_experience, t_health;
        double t_hungry, t_place_x, t_place_y;
        int t_produce_value;
        save_stream >> t_species;
        if(t_species == 1 || t_species == 4 || t_species == 5)
        {
            save_stream >> t_level >> t_experience >> t_health >> t_hungry
                    >> t_place_x >> t_place_y >> t_produce_value;
        }
        else
        {
            save_stream >> t_health >> t_hungry
                    >> t_place_x >> t_place_y >> t_produce_value;
        }
        if(t_species == 1)
        {
            UAnimalGrass* t_animal;
            t_animal = new UAnimalGrass(t_level, t_experience, t_health, t_hungry
                                                  ,t_place_x, t_place_y, t_produce_value);
            m_AnimalList.append(t_animal);
            connect(m_AnimalList[m_AnimalList.length()-1], SIGNAL(m_BonusProduced(int,int,int,int)), this, SLOT(m_GenerateBonus(int,int,int,int)));
        }
        if(t_species == 2)
        {
            UAnimalMeatSmall* t_animal;
            t_animal = new UAnimalMeatSmall(t_health, t_hungry,
                                            t_place_x, t_place_y, t_produce_value);
            m_AnimalList.append(t_animal);
            connect(m_AnimalList[m_AnimalList.length()-1], SIGNAL(m_BonusProduced(int,int,int,int)),
                    this, SLOT(m_GenerateBonus(int,int,int,int)));
        }
        if(t_species == 3)
        {
            UAnimalMeatBig* t_animal;
            t_animal = new UAnimalMeatBig(t_health, t_hungry,
                                          t_place_x, t_place_y, t_produce_value);
            m_AnimalList.append(t_animal);
            connect(m_AnimalList[m_AnimalList.length()-1], SIGNAL(m_BonusProduced(int,int,int,int)),
                    this, SLOT(m_GenerateBonus(int,int,int,int)));
        }
        if(t_species == 4)
        {
            UAnimalMother* t_animal;
            t_animal = new UAnimalMother(t_level, t_experience, t_health, t_hungry
                                                  ,t_place_x, t_place_y, t_produce_value);
            m_AnimalList.append(t_animal);
            connect(m_AnimalList[m_AnimalList.length()-1], SIGNAL(m_ChildProduced(int,int)),
                    this, SLOT(m_GenerateAnimalGrass(int,int)));
        }
        if(t_species == 5)
        {
            UAnimalMaterial* t_animal;
            t_animal = new UAnimalMaterial(t_level, t_experience, t_health, t_hungry
                                                  ,t_place_x, t_place_y, t_produce_value);
            m_AnimalList.append(t_animal);
            connect(m_AnimalList[m_AnimalList.length()-1], SIGNAL(m_BonusProduced(int,int,int,int)),
                    this, SLOT(m_GenerateBonus(int,int,int,int)));
        }
        if(t_species == 6)
        {
            UAnimalMaterialMother* t_animal;
            t_animal = new UAnimalMaterialMother(t_health, t_hungry,
                                          t_place_x, t_place_y, t_produce_value);
            m_AnimalList.append(t_animal);
            connect(m_AnimalList[m_AnimalList.length()-1], SIGNAL(m_ChildProduced(int,int)),
                    this, SLOT(m_GenerateAnimalMaterial(int,int)));
        }
        if(t_species == 7)
        {
            UAnimalKing* t_animal;
            t_animal = new UAnimalKing(t_health, t_hungry,
                                          t_place_x, t_place_y, t_produce_value);
            m_AnimalList.append(t_animal);
            connect(m_AnimalList[m_AnimalList.length()-1], SIGNAL(m_BonusProduced(int,int,int,int)),
                    this, SLOT(m_GenerateBonus(int,int,int,int)));
        }

    }

    //enemies

    if(t_enemy_number != 0)
    {
        m_WhetherIsPeace = 0;
    }
    else
    {
        m_WhetherIsPeace = 1;
    }
    m_WarReadyPoint = 0;
    m_WarTriggerPoint = 0;
    for(int i = 1; i <= t_enemy_number; i ++)
    {
        int t_species,  t_health;
        double  t_place_x, t_place_y;
        int t_attack_value;
        save_stream >> t_species;
        if(t_species == 2)
        {
            save_stream >> t_health >> t_place_x >> t_place_y;
        }
        else
        {
            save_stream >> t_health >> t_place_x >> t_place_y >> t_attack_value;
        }

        if(t_species == 1)
        {
            UEnemyBarbarian* new_enemy;
           new_enemy = new UEnemyBarbarian(t_health, t_place_x, t_place_y, t_attack_value);
           m_EnemyList.append(new_enemy);
        }
        if(t_species == 2)
        {
            UEnemyEater* new_enemy;
           new_enemy = new UEnemyEater(t_health, t_place_x, t_place_y);
           m_EnemyList.append(new_enemy);
        }
        if(t_species == 3)
        {
            UEnemyNativeWarrior* new_enemy;
           new_enemy = new UEnemyNativeWarrior(t_health, t_place_x, t_place_y, t_attack_value);
           m_EnemyList.append(new_enemy);
        }
        if(t_species == 4)
        {
            UEnemyNativeGunner* new_enemy;
           new_enemy = new UEnemyNativeGunner(t_health, t_place_x, t_place_y, t_attack_value);
           m_EnemyList.append(new_enemy);
           connect(m_EnemyList[m_EnemyList.length()-1], SIGNAL(m_AmmoShooted(int,int,int,int,int,int)), this, SLOT(m_GenerateAmmo(int,int,int,int,int,int)));
        }
        if(t_species == 5)
        {
            UEnemyNativeShaman* new_enemy;
           new_enemy = new UEnemyNativeShaman(t_health, t_place_x, t_place_y, t_attack_value);
           m_EnemyList.append(new_enemy);
        }
    }

    //armies
    for(int i = 1; i <= t_army_number; i ++)
    {
        int t_ammo, t_species,  t_health;
        double  t_place_x, t_place_y;
        int t_attack_value;
        save_stream >> t_species;
        if(t_species == 1 || t_species == 4 || t_species == 5)
        {
            save_stream >> t_ammo >> t_health >> t_place_x >> t_place_y >> t_attack_value;
        }
        else
        {
            save_stream >> t_health >> t_place_x >> t_place_y >> t_attack_value;
        }
        if(t_species == 1)
        {
            UArmyInfantry* t_army;
            t_army = new UArmyInfantry(t_ammo, t_health, t_place_x, t_place_y, m_Country, t_attack_value);
            m_ArmyList.append(t_army);
            connect(m_ArmyList[m_ArmyList.length()-1], SIGNAL(m_AmmoShooted(int,int,int,int,int,int)), this, SLOT(m_GenerateAmmo(int,int,int,int,int,int)));
        }
        if(t_species == 2)
        {
            UArmyLight* t_army;
            t_army = new UArmyLight(t_health, t_place_x, t_place_y, m_Country, t_attack_value);
            m_ArmyList.append(t_army);
            connect(m_ArmyList[m_ArmyList.length()-1], SIGNAL(m_AmmoShooted(int,int,int,int,int,int)), this, SLOT(m_GenerateAmmo(int,int,int,int,int,int)));
        }
        if(t_species == 3)
        {
            UArmyCalvary* t_army;
            t_army = new UArmyCalvary(t_health, t_place_x, t_place_y, m_Country, t_attack_value);
            m_ArmyList.append(t_army);
        }
        if(t_species == 4)
        {
            UArmyGrenadier* t_army;
            t_army = new UArmyGrenadier(t_ammo, t_health, t_place_x, t_place_y, m_Country, t_attack_value);
            m_ArmyList.append(t_army);
            connect(m_ArmyList[m_ArmyList.length()-1], SIGNAL(m_AmmoShooted(int,int,int,int,int,int)), this, SLOT(m_GenerateAmmo(int,int,int,int,int,int)));
        }
        if(t_species == 5)
        {
            UArmyInfantryEngland* t_army;
            t_army = new UArmyInfantryEngland(t_ammo, t_health, t_place_x, t_place_y, t_attack_value);
            m_ArmyList.append(t_army);
            connect(m_ArmyList[m_ArmyList.length()-1], SIGNAL(m_AmmoShooted(int,int,int,int,int,int)), this, SLOT(m_GenerateAmmo(int,int,int,int,int,int)));
        }
        if(t_species == 6)
        {
            UArmyCalvaryFrance* t_army;
            t_army = new UArmyCalvaryFrance(t_health, t_place_x, t_place_y, t_attack_value);
            m_ArmyList.append(t_army);
        }
        if(t_species == 7)
        {
            m_AnimalKingNumbers = 1;
            UArmyLightSpain* t_army;
            t_army = new UArmyLightSpain(t_health, t_place_x, t_place_y, t_attack_value);
            m_ArmyList.append(t_army);
            connect(m_ArmyList[m_ArmyList.length()-1], SIGNAL(m_AmmoShooted(int,int,int,int,int,int)), this, SLOT(m_GenerateAmmo(int,int,int,int,int,int)));
        }
    }

    //food

    for(int i = 1; i <= t_food_number; i ++)
    {
        int t_species, t_level;
        double t_place_x, t_place_y;
        save_stream >> t_species >> t_level >> t_place_x >> t_place_y;
        if(t_species == 1)
        {
            UFoodLand* t_food;
            t_food = new UFoodLand(t_level, t_place_x, t_place_y);
            m_FoodList.append(t_food);
        }
        if(t_species == 2)
        {
            UFoodSea* t_food;
            t_food = new UFoodSea(t_level, t_place_x, t_place_y);
            m_FoodList.append(t_food);
        }
    }

    //bonus

    for(int i = 1; i <= t_bonus_number; i ++)
    {
        int t_species, t_level;
        double t_place_x, t_place_y;
        save_stream >> t_species >> t_level >> t_place_x >> t_place_y;
        if(t_species == 1)
        {
            UBonusMoney* t_bonus;
            t_bonus = new UBonusMoney(t_level, t_place_x, t_place_y);
            m_BonusList.append(t_bonus);
        }
        if(t_species == 2)
        {
            UBonusMaterial* t_bonus;
            t_bonus = new UBonusMaterial(t_level, t_place_x, t_place_y);
            m_BonusList.append(t_bonus);
        }
    }

    //ammo

    for(int i = 1; i <= t_ammo_number; i ++)
    {
        int t_species, t_damage;
        double t_place_x, t_place_y, t_final_x, t_final_y;
        save_stream >> t_species >> t_damage >> t_place_x >> t_place_y >> t_final_x >> t_final_y;
            UAmmo* t_ammo;
            t_ammo = new UAmmo(t_species, t_damage, t_place_x, t_place_y, t_final_x, t_final_y);
            m_AmmoList.append(t_ammo);
        
    }
    
    //steward

    m_Steward = NULL;
    for(int i = 1; i <= t_steward_number; i ++)
    {
        double t_place_x, t_place_y;
        save_stream >> t_place_x >> t_place_y;
        m_Steward = new USteward(t_place_x, t_place_y);
    }
    m_FoodMaxNumber = m_cFoodMaxNumberByLevel[m_FoodMaxNumberLevel];

}

void GameCentralControl::m_OutPut(QString file)
{
    QFile save_file(file);
    if(!save_file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)){
        return;
    }
    QTextStream save_stream(&save_file);
    save_stream << m_Country << '\n';
    save_stream << m_Money<<' ' << m_Food <<' ' << m_Material << '\n';
    save_stream << m_WallLevel <<' '<< m_FarmLevel <<' '<< m_FactoryLevel <<' '<< m_MarketLevel << '\n';
    save_stream << m_HarborLevel <<' '<< m_BarrackLevel <<' '<< m_StableLevel <<' '<< m_ArsenalLevel << '\n';
    save_stream << m_FoodLandLevel <<' '<< m_FoodSeaLevel <<' '<< m_FoodMaxNumberLevel << '\n';

    save_stream << m_AnimalList.length() << '\n';
    save_stream << m_EnemyList.length() << '\n';
    save_stream << m_ArmyList.length() << '\n';
    save_stream << m_FoodList.length() << '\n';
    save_stream << m_BonusList.length() << '\n';
    save_stream << m_AmmoList.length() << '\n';
    if(m_Steward != NULL)
    {
        save_stream << 1 << '\n';
    }
    else
    {
        save_stream << 0 << '\n';
    }
    save_file.close();

    for(int i = 0; i < m_AnimalList.length(); i ++)
    {
        m_AnimalList[i] -> m_OutPut(file);
    }

    for(int i = 0; i < m_EnemyList.length(); i ++)
    {
        m_EnemyList[i] -> m_OutPut(file);
    }

    for(int i = 0; i < m_ArmyList.length(); i ++)
    {
        m_ArmyList[i] -> m_OutPut(file);
    }

    for(int i = 0; i < m_FoodList.length(); i ++)
    {
        m_FoodList[i] -> m_OutPut(file);
    }

    for(int i = 0; i < m_BonusList.length(); i ++)
    {
        m_BonusList[i] -> m_OutPut(file);
    }

    for(int i = 0; i < m_AmmoList.length(); i ++)
    {
        m_AmmoList[i] -> m_OutPut(file);
    }

    if(m_Steward != NULL)
    {
        m_Steward -> m_OutPut(file);
    }


}



GameCentralControl::~GameCentralControl()
{
    for(int i = 0; i < m_AnimalList.length(); i ++)
    {
        delete m_AnimalList[i];
    }
    m_AnimalList.clear();

    for(int i = 0; i < m_EnemyList.length(); i ++)
    {
        delete m_EnemyList[i];
    }
    m_EnemyList.clear();

    for(int i = 0; i < m_ArmyList.length(); i ++)
    {
        delete m_ArmyList[i];
    }
    m_ArmyList.clear();

    for(int i = 0; i < m_FoodList.length(); i ++)
    {
        delete m_FoodList[i];
    }
    m_FoodList.clear();

    for(int i = 0; i < m_BonusList.length(); i ++)
    {
        delete m_BonusList[i];
    }
    m_BonusList.clear();

    for(int i = 0; i < m_AmmoList.length(); i ++)
    {
        delete m_AmmoList[i];
    }
    m_AmmoList.clear();

    if(m_Steward != NULL)
    {
        delete(m_Steward);
        m_Steward = NULL;
    }
}

//main turn
//step 1:clear dead objects
void GameCentralControl::m_ClearDeath()
{
    for(int i = 0; i < m_AnimalList.length(); i ++)
    {
        if(m_AnimalList[i] -> m_WhetherIsValid == 0)
        {
            m_AnimalList[i] -> deleteLater();
            m_AnimalList.removeAt(i);
        }
    }
    for(int i = 0; i < m_EnemyList.length(); i ++)
    {
        if(m_EnemyList[i] -> m_WhetherIsValid == 0)
        {
            m_EnemyList[i] -> deleteLater();
            m_EnemyList.removeAt(i);
        }
    }
    for(int i = 0; i < m_ArmyList.length(); i ++)
    {
        if(m_ArmyList[i] -> m_WhetherIsValid == 0)
        {
            m_ArmyList[i] -> deleteLater();
            m_ArmyList.removeAt(i);
        }
    }
    for(int i = 0; i < m_FoodList.length(); i ++)
    {
        if(m_FoodList[i] -> m_WhetherIsValid == 0)
        {
            m_FoodList[i] -> deleteLater();
            m_FoodList.removeAt(i);
        }
    }
    for(int i = 0; i < m_BonusList.length(); i ++)
    {
        if(m_BonusList[i] -> m_WhetherIsValid == 0)
        {
            m_BonusList[i] -> deleteLater();
            m_BonusList.removeAt(i);
        }
    }
    for(int i = 0; i < m_AmmoList.length(); i ++)
    {
        if(m_AmmoList[i] -> m_WhetherIsValid == 0)
        {
            m_AmmoList[i] -> deleteLater();
            m_AmmoList.removeAt(i);
        }
    }
    if(m_Steward != NULL && m_Steward -> m_WhetherIsValid == 0)
    {
        delete(m_Steward);
        m_Steward = NULL;
    }
}
//step 2:update object status
void GameCentralControl::m_UpdateStatus()
{
    m_AnimalKingNumbers = 0;
    for(int i = 0; i < m_AnimalList.length(); i ++)
    {
        m_AnimalList[i] -> m_UpdateStatus();
        if(m_AnimalList[i] -> m_Species == 7)
        {
            m_AnimalKingNumbers ++;
        }
    }

    for(int i = 0; i < m_EnemyList.length(); i ++)
    {
        m_EnemyList[i] -> m_UpdateStatus();
    }

    for(int i = 0; i < m_ArmyList.length(); i ++)
    {
        m_ArmyList[i] -> m_UpdateStatus();
    }

    for(int i = 0; i < m_AmmoList.length(); i ++)
    {
        m_AmmoList[i] -> m_UpdateStatus();
    }
    if(m_Steward != NULL)
    {
        m_Steward -> m_UpdateStatus();
    }
}
//step 3:update object eating
void GameCentralControl::m_UpdateEating()
{
    for(int i = 0; i < m_AnimalList.length(); i ++)
    {
        if(m_AnimalList[i] -> m_Status == 2 || m_AnimalList[i] -> m_Status == 3 )
        {
            if(m_AnimalList[i] -> m_Species == 1|| m_AnimalList[i] -> m_Species == 4
                    || m_AnimalList[i] -> m_Species == 5 || m_AnimalList[i] -> m_Species == 6)  //Grass_eat
            {
                for(int j = 0; j < m_FoodList.length(); j ++)
                {
                    double distance = g_GetDistance(m_AnimalList[i], m_FoodList[j]);
                    if(distance <= m_cMeleeInteractRange)
                    {
                        m_ManageEating(m_AnimalList[i], m_FoodList[j]);
                    }
                }
            }

            if(m_AnimalList[i] -> m_Species == 2)  //small meat eat
            {
                for(int j = 0; j < m_AnimalList.length(); j ++)
                {
                    if(m_AnimalList[j] ->m_Species == 1)
                    {
                        if(m_AnimalList[j] -> m_Level != 1)
                        {
                            continue;
                        }
                        if(m_AnimalList[j] -> m_Status == 4)
                        {
                            continue;
                        }
                        double distance = g_GetDistance(m_AnimalList[i], m_AnimalList[j]);
                        if(distance <= m_cMeleeInteractRange)
                        {
                            m_ManageEating(m_AnimalList[i], m_AnimalList[j]);
                        }
                    }
                }
            }

            if(m_AnimalList[i] -> m_Species == 3)  //big meat eat
            {
                for(int j = 0; j < m_AnimalList.length(); j ++)
                {
                    if(m_AnimalList[j] -> m_Status == 4)
                    {
                        continue;
                    }
                    if(m_AnimalList[j]->m_Species == 2)
                    {
                        double distance = g_GetDistance(m_AnimalList[i], m_AnimalList[j]);
                        if(distance <= m_cMeleeInteractRange)
                        {
                            m_ManageEating(m_AnimalList[i], m_AnimalList[j]);
                        }
                    }
                }
            }
        }
    }

    for(int i = 0; i < m_EnemyList.length(); i ++)
    {
        if(m_EnemyList[i] -> m_Species == 2)
        {
            for(int j = 0; j < m_AnimalList.length(); j++)
            {
                if(m_AnimalList[j] -> m_Status == 4)
                {
                    continue;
                }
                double temp_distance = g_GetDistance(m_EnemyList[i], m_AnimalList[j]);
                if(temp_distance <= m_cMeleeInteractRange)
                {
                    m_ManageEating(m_EnemyList[i], m_AnimalList[j]);
                    break;
                }
            }
            for(int j = 0; j < m_FoodList.length(); j ++)
            {
                double temp_distance = g_GetDistance(m_EnemyList[i], m_FoodList[j]);
                if(temp_distance <= m_cMeleeInteractRange)
                {
                    m_ManageEating(m_EnemyList[i], m_FoodList[j]);
                    break;
                }
            }
        }
    }

    if(m_Steward != NULL)
    {
        if(m_Steward -> m_WhetherIsActive == 1)
        {
            for(int i = 0 ;i < m_BonusList.length(); i ++)
            {
                double temp_distance = g_GetDistance(m_Steward, m_BonusList[i]);
                if(temp_distance <= m_cMeleeInteractRange)
                {
                    m_GetBonus(i);
                }
            }
        }
    }
}
//step 4:update object movement
void GameCentralControl::m_UpdateMovement()
{
    for(int i = 0; i < m_AnimalList.length(); i ++)
    {
        if(m_AnimalList[i] -> m_Status == 2 || m_AnimalList[i] -> m_Status == 3)
        {
            if(m_FindTarget(m_AnimalList[i]) == 0)
            {
                m_AnimalList[i] -> m_Wander();
            }
        }
        else if (m_AnimalList[i] -> m_Status == 1)
        {
            m_AnimalList[i] -> m_Wander();
        }
    }


    for(int i = 0; i < m_EnemyList.length(); i ++)                // also update ranged unit's shooting
    {
        if(m_EnemyList[i] -> m_Species == 1 || m_EnemyList[i] -> m_Species == 2)
        {
            if(m_FindTarget(m_EnemyList[i]) == 0)
            {
                m_EnemyList [i] -> m_Wander();
            }
        }

        if(m_EnemyList[i] -> m_Species == 3)
        {
            if(m_FindTarget(m_EnemyList[i]) == 0)
            {
                m_EnemyList[i] -> m_Wander();
            }
        }

        if(m_EnemyList[i] -> m_Species == 4 || m_EnemyList[i] -> m_Species == 5)
        {
            if(m_FindShoot(m_EnemyList[i]) == 0)
            {
                if(m_FindTarget(m_EnemyList[i]) == 0)
                {
                    m_EnemyList[i] -> m_Wander();
                }
            }
        }

    }


    for(int i = 0; i < m_ArmyList.length(); i ++)                  // also update ranged unit's shooting
    {
        if(m_ArmyList[i] -> m_Species == 1 || m_ArmyList[i] -> m_Species == 4 || m_ArmyList[i] -> m_Species == 5)
        {
                if(m_FindShoot(m_ArmyList[i]) == 0)                //melee mode, or have no enemies
                {
                    if(m_FindTarget(m_ArmyList[i]) == 0)
                    {
                        m_ArmyList[i] -> m_Wander();                //no target in sight
                    }
                }
        }

        if(m_ArmyList[i] -> m_Species == 2 || m_ArmyList[i] -> m_Species == 7)
        {
            m_ArmyList[i] -> m_Wander();
        }

        if(m_ArmyList[i] -> m_Species == 3 || m_ArmyList[i] -> m_Species == 6)
        {
            if(m_FindTarget(m_ArmyList[i]) == 0)
            {
               m_ArmyList[i] -> m_Wander();                //no target in sight
            }
        }
    }


    for(int i = 0; i< m_FoodList.length(); i ++)
    {
        m_FoodList[i] -> m_MoveDown();
    }

    if(m_Steward != NULL)
    {
        if(m_Steward -> m_WhetherIsActive == 1)
        {
            for(int i = 0; i < m_BonusList.length(); i ++)
            {
                if(m_FindTarget(m_Steward) == 0)
                {
                    m_Steward -> m_Wander();
                }
            }
        }
    }
}
//step 5:update attack
void GameCentralControl::m_UpdateAttacking()
{
    for(int i = 0; i < m_EnemyList.length(); i ++)
    {
        if(m_EnemyList[i] -> m_WhetherCanAttack == 0)
        {
            continue;
        }
        if(m_EnemyList[i] -> m_Species == 1)
        {
            for(int j = 0; j < m_AnimalList.length(); j ++)
            {
                if(m_AnimalList[j] -> m_Status == 4)
                {
                    continue;
                }
                double distance = g_GetDistance(m_EnemyList[i], m_AnimalList[j]);
                if(distance < m_cMeleeInteractRange)
                {
                    m_ManageAttack(m_EnemyList[i], m_AnimalList[j]);
                    break;
                }
            }
        }
        
        if(m_EnemyList[i] -> m_Species == 3)
        {
            for(int j = 0; j < m_ArmyList.length(); j ++)
            {
                double distance = g_GetDistance(m_EnemyList[i], m_ArmyList[j]);
                if(distance < m_cMeleeInteractRange)
                {
                    m_ManageAttack(m_EnemyList[i], m_ArmyList[j]);
                    break;
                }
            }
        }    
    }

    for(int i = 0; i < m_ArmyList.length(); i ++)
    {
        if(m_ArmyList[i] -> m_WhetherCanAttack == 0)
        {
            continue;
        }
        if(m_ArmyList[i] -> m_AttackType == 2)                      //calvary, melee-moded grenadiers or infantry
        {
            for(int j = 0; j < m_EnemyList.length(); j ++)
            {
                double distance = g_GetDistance(m_ArmyList[i], m_EnemyList[j]);
                if(distance < m_cMeleeInteractRange)
                {
                    m_ManageAttack(m_ArmyList[i], m_EnemyList[j]);
                    break;
                }
            }
        }
        if(m_ArmyList[i] -> m_Species == 2 || m_ArmyList[i] -> m_Species == 7)                         //light infantry
        {
            m_FindShoot(m_ArmyList[i]);
        }
    }
}
//step 8:update war and peace
void GameCentralControl::m_UpdatePeaceWar()
{
    if(m_WhetherIsPeace == 0)           //war
    {
        if(m_Steward != NULL)
        {
            m_Steward -> m_WhetherIsActive = 0;
        }
        if(m_EnemyList.length() == 0)
        {
            m_WhetherIsPeace = 1;       //stop war
            //todo:bgm change,etc
        }
        m_WarTriggerPoint = 0;
        m_WarReadyPoint = 0;
    }
    else if(m_WhetherIsPeace == -1)     //ready to war
    {
        if(m_Steward != NULL)
        {
            m_Steward -> m_WhetherIsActive = 1;
        }
        m_WarTriggerPoint = 0;
        m_WarReadyPoint ++;
        if(m_WarReadyPoint == m_cWarWarningTime)
        {
            emit m_ShowWarWarningSign(0);
        }
        if(m_WarReadyPoint >= m_cWarReadyTime)
        {
            m_WarReadyPoint = 0;
            m_WhetherIsPeace = 0;
            m_GenerateEnemies();
        }
    }
    else                                //peace
    {
        if(m_Steward != NULL)
        {
            m_Steward -> m_WhetherIsActive = 1;
        }
        m_WarTriggerPoint ++;
        m_WarReadyPoint = 0;
        if(m_WarTriggerPoint >= m_cWarBeginThreshold)
        {
            int rand_number = g_GenerateRandomNumber(1,101);
            int possible_range;
            if(m_Country == 1)//england
            {
               possible_range = m_cWarBeginPossibility - 10;  
            }
            else
            {
               possible_range = m_cWarBeginPossibility; 
            }
            if(rand_number <= possible_range)
            {
                m_WhetherIsPeace = -1;
                emit m_ShowWarWarningSign(1);
            }
            m_WarTriggerPoint = 0;
        }
    }
}
//last step:update building
void GameCentralControl::m_UpdateBuilding()
{
    m_Food += m_cFarmFoodProduceByTurn[m_FarmLevel];
    m_Material += m_cFactoryMaterialProduceByTurn[m_FactoryLevel];
    if(m_HarborLevel == 1)
    {
        m_Food += m_cFarmFoodProduceByTurn[m_FarmLevel] * (m_cHarborBonus / 100);
        m_Material += m_cFactoryMaterialProduceByTurn[m_FactoryLevel] * (m_cHarborBonus / 100);
    }

}


//generate unit slots
//generate animals
void GameCentralControl::m_GenerateAnimalGrass()
{
    if(m_Money < m_cAnimalGrassMoneyCost)
    {
        return;
    }
    m_Money -= m_cAnimalGrassMoneyCost;
    //random generate one
    int new_place_x, new_place_y;
    g_GenerateRandomPlace(&new_place_x, &new_place_y, m_cAnimalRangeMin_x, m_cAnimalRangeMax_x, m_cAnimalRangeMin_y, m_cAnimalRangeMax_y);
    UAnimalGrass* new_animal_grass = new UAnimalGrass(new_place_x, new_place_y);
    m_AnimalList.append(new_animal_grass);
    connect(m_AnimalList[m_AnimalList.length()-1], SIGNAL(m_BonusProduced(int,int,int,int)), this, SLOT(m_GenerateBonus(int,int,int,int)));
}

void GameCentralControl::m_GenerateAnimalGrass(const int place_x, const int place_y)
{

    UAnimalGrass* new_animal_grass = new UAnimalGrass(place_x, place_y);
    m_AnimalList.append(new_animal_grass);
    connect(m_AnimalList[m_AnimalList.length()-1], SIGNAL(m_BonusProduced(int,int,int,int)), this, SLOT(m_GenerateBonus(int,int,int,int)));
}

void GameCentralControl::m_GenerateAnimalMaterial()
{
    if(m_Money < m_cAnimalMaterialMoneyCost)
    {
        return;
    }
    m_Money -= m_cAnimalMaterialMoneyCost;
    //random generate one
    int new_place_x, new_place_y;
    g_GenerateRandomPlace(&new_place_x, &new_place_y, m_cAnimalRangeMin_x, m_cAnimalRangeMax_x, m_cAnimalRangeMin_y, m_cAnimalRangeMax_y);
    UAnimalMaterial* new_animal_material= new UAnimalMaterial(new_place_x, new_place_y);
    m_AnimalList.append(new_animal_material);
    connect(m_AnimalList[m_AnimalList.length()-1], SIGNAL(m_BonusProduced(int,int,int,int)), this, SLOT(m_GenerateBonus(int,int,int,int)));
}

void GameCentralControl::m_GenerateAnimalMaterial(const int place_x, const int place_y)
{

    UAnimalMaterial* new_animal_material = new UAnimalMaterial(place_x, place_y);
    m_AnimalList.append(new_animal_material);
    connect(m_AnimalList[m_AnimalList.length()-1], SIGNAL(m_BonusProduced(int,int,int,int)), this, SLOT(m_GenerateBonus(int,int,int,int)));
}

void GameCentralControl::m_GenerateAnimalMeatSmall()
{
    if(m_Money < m_cAnimalMeatSmallMoneyCost)
    {
        return;
    }
    m_Money -= m_cAnimalMeatSmallMoneyCost;
    //random generate one
    int new_place_x, new_place_y;
    g_GenerateRandomPlace(&new_place_x, &new_place_y, m_cAnimalRangeMin_x, m_cAnimalRangeMax_x, m_cAnimalRangeMin_y, m_cAnimalRangeMax_y);
    UAnimalMeatSmall* new_animal_meat = new UAnimalMeatSmall(new_place_x, new_place_y);
    m_AnimalList.append(new_animal_meat);
    connect(m_AnimalList[m_AnimalList.length()-1], SIGNAL(m_BonusProduced(int,int,int,int)), this, SLOT(m_GenerateBonus(int,int,int,int)));
}

void GameCentralControl::m_GenerateAnimalMeatBig()
{
    if(m_Money < m_cAnimalMeatBigMoneyCost)
    {
        return;
    }
    m_Money -= m_cAnimalMeatBigMoneyCost;
    //random generate one
    int new_place_x, new_place_y;
    g_GenerateRandomPlace(&new_place_x, &new_place_y, m_cAnimalRangeMin_x, m_cAnimalRangeMax_x, m_cAnimalRangeMin_y, m_cAnimalRangeMax_y);
    UAnimalMeatBig* new_animal_meat = new UAnimalMeatBig(new_place_x, new_place_y);
    m_AnimalList.append(new_animal_meat);
    connect(m_AnimalList[m_AnimalList.length()-1], SIGNAL(m_BonusProduced(int,int,int,int)), this, SLOT(m_GenerateBonus(int,int,int,int)));
}

void GameCentralControl::m_GenerateAnimalMother()
{
    if(m_Money < m_cAnimalMotherMoneyCost)
    {
        return;
    }
    m_Money -= m_cAnimalMotherMoneyCost;
    //random generate one
    int new_place_x, new_place_y;
    g_GenerateRandomPlace(&new_place_x, &new_place_y, m_cAnimalRangeMin_x, m_cAnimalRangeMax_x, m_cAnimalRangeMin_y, m_cAnimalRangeMax_y);
    UAnimalMother* new_animal_mother = new UAnimalMother(new_place_x, new_place_y);
    m_AnimalList.append(new_animal_mother);
    connect(m_AnimalList[m_AnimalList.length()-1], SIGNAL(m_ChildProduced(int,int)), this, SLOT(m_GenerateAnimalGrass(int,int)));
}

void GameCentralControl::m_GenerateAnimalMaterialMother()
{
    if(m_Money < m_cAnimalMaterialMotherMoneyCost)
    {
        return;
    }
    m_Money -= m_cAnimalMaterialMotherMoneyCost;
    //random generate one
    int new_place_x, new_place_y;
    g_GenerateRandomPlace(&new_place_x, &new_place_y, m_cAnimalRangeMin_x, m_cAnimalRangeMax_x, m_cAnimalRangeMin_y, m_cAnimalRangeMax_y);
    UAnimalMaterialMother* new_animal_mother = new UAnimalMaterialMother(new_place_x, new_place_y);
    m_AnimalList.append(new_animal_mother);
    connect(m_AnimalList[m_AnimalList.length()-1], SIGNAL(m_ChildProduced(int,int)), this, SLOT(m_GenerateAnimalMaterial(int,int)));
}

void GameCentralControl::m_GenerateAnimalKing()
{
    if(m_Money < m_cAnimalKingMoneyCost)
    {
        return;
    }
    if(m_AnimalKingNumbers >= m_cAnimalKingMaxNumber)
    {
        return;
    }
    m_Money -= m_cAnimalKingMoneyCost;
    //random generate one
    int new_place_x, new_place_y;
    g_GenerateRandomPlace(&new_place_x, &new_place_y, m_cAnimalRangeMin_x, m_cAnimalRangeMax_x, m_cAnimalRangeMin_y, m_cAnimalRangeMax_y);
    UAnimalKing* new_animal_king = new UAnimalKing(new_place_x, new_place_y);
    m_AnimalList.append(new_animal_king);
    m_AnimalKingNumbers ++;
    connect(m_AnimalList[m_AnimalList.length()-1], SIGNAL(m_BonusProduced(int,int,int,int)), this, SLOT(m_GenerateBonus(int,int,int,int)));
}

//generate enemies
void GameCentralControl::m_GenerateEnemies()
{
    for (int i = 1; i <= m_cEnemyBarbarianNumberByLevel[m_WallLevel]; i ++)
    {
        m_GenerateEnemyBarbarian();
    }
    for (int i = 1; i <= m_cEnemyEaterNumberByLevel[m_WallLevel]; i ++)
    {
        m_GenerateEnemyEater();
    }
    for (int i = 1; i <= m_cEnemyNativeWarriorNumberByLevel[m_WallLevel]; i ++)
    {
        m_GenerateEnemyNativeWarrior();
    }
    for (int i = 1; i <= m_cEnemyNativeGunnerNumberByLevel[m_WallLevel]; i ++)
    {
        m_GenerateEnemyNativeGunner();
    }
    for (int i = 1; i <= m_cEnemyNativeShamanNumberByLevel[m_WallLevel]; i ++)
    {
        m_GenerateEnemyNativeShaman();
    }


}

void GameCentralControl::m_GenerateEnemyBarbarian()
{
    //random generate one
    int new_place_x, new_place_y;
    g_GenerateRandomPlace(&new_place_x, &new_place_y, m_cEnemyRangeMin_x, m_cEnemyRangeMax_x, m_cEnemyRangeMin_y, m_cEnemyRangeMax_y);
    UEnemyBarbarian* new_enemy = new UEnemyBarbarian(new_place_x, new_place_y);
    m_EnemyList.append(new_enemy);
    connect(m_EnemyList[m_EnemyList.length()-1], SIGNAL(m_BonusProduced(int,int,int,int)), this, SLOT(m_GenerateBonus(int,int,int,int)));

}

void GameCentralControl::m_GenerateEnemyBarbarian(const int place_x, const int place_y)                                     //turn
{
    UEnemyBarbarian* new_enemy = new UEnemyBarbarian(place_x, place_y);
    m_EnemyList.append(new_enemy);
    connect(m_EnemyList[m_EnemyList.length()-1], SIGNAL(m_BonusProduced(int,int,int,int)), this, SLOT(m_GenerateBonus(int,int,int,int)));

}

void GameCentralControl::m_GenerateEnemyEater()
{
    //random generate one
    int new_place_x, new_place_y;
    g_GenerateRandomPlace(&new_place_x, &new_place_y, m_cEnemyRangeMin_x, m_cEnemyRangeMax_x, m_cEnemyRangeMin_y, m_cEnemyRangeMax_y);
    UEnemyEater* new_enemy = new UEnemyEater(new_place_x, new_place_y);
    m_EnemyList.append(new_enemy);
    connect(m_EnemyList[m_EnemyList.length()-1], SIGNAL(m_BonusProduced(int,int,int,int)), this, SLOT(m_GenerateBonus(int,int,int,int)));

}

void GameCentralControl::m_GenerateEnemyNativeWarrior()
{
    //random generate one
    int new_place_x, new_place_y;
    g_GenerateRandomPlace(&new_place_x, &new_place_y, m_cEnemyRangeMin_x, m_cEnemyRangeMax_x, m_cEnemyRangeMin_y, m_cEnemyRangeMax_y);
    UEnemyNativeWarrior* new_enemy = new UEnemyNativeWarrior(new_place_x, new_place_y);
    m_EnemyList.append(new_enemy);
    connect(m_EnemyList[m_EnemyList.length()-1], SIGNAL(m_BonusProduced(int,int,int,int)), this, SLOT(m_GenerateBonus(int,int,int,int)));

}

void GameCentralControl::m_GenerateEnemyNativeGunner()
{
    //random generate one
    int new_place_x, new_place_y;
    g_GenerateRandomPlace(&new_place_x, &new_place_y, m_cEnemyRangeMin_x, m_cEnemyRangeMax_x, m_cEnemyRangeMin_y, m_cEnemyRangeMax_y);
    UEnemyNativeGunner* new_enemy = new UEnemyNativeGunner(new_place_x, new_place_y);
    m_EnemyList.append(new_enemy);
    connect(m_EnemyList[m_EnemyList.length()-1], SIGNAL(m_AmmoShooted(int,int,int,int,int,int)), this, SLOT(m_GenerateAmmo(int,int,int,int,int,int)));
    connect(m_EnemyList[m_EnemyList.length()-1], SIGNAL(m_BonusProduced(int,int,int,int)), this, SLOT(m_GenerateBonus(int,int,int,int)));
}

void GameCentralControl::m_GenerateEnemyNativeShaman()
{
    //random generate one
    int new_place_x, new_place_y;
    g_GenerateRandomPlace(&new_place_x, &new_place_y, m_cEnemyRangeMin_x, m_cEnemyRangeMax_x, m_cEnemyRangeMin_y, m_cEnemyRangeMax_y);
    UEnemyNativeShaman* new_enemy = new UEnemyNativeShaman(new_place_x, new_place_y);
    m_EnemyList.append(new_enemy);
    connect(m_EnemyList[m_EnemyList.length()-1], SIGNAL(m_BonusProduced(int,int,int,int)), this, SLOT(m_GenerateBonus(int,int,int,int)));
}

//generate armies
void GameCentralControl::m_GenerateArmyInfantry()
{
    if(m_BarrackLevel < 1)
    {
        return;
    }
    if(m_Money < m_cArmyInfantryMoneyCost)
    {
        return;
    }
    if(m_Material < m_cArmyInfantryMaterialCost)
    {
        return;
    }
    m_Money -= m_cArmyInfantryMoneyCost;
    m_Material -= m_cArmyInfantryMaterialCost;
    //random generate one
    int new_place_x, new_place_y;
    g_GenerateRandomPlace(&new_place_x, &new_place_y, m_cArmyRangeMin_x, m_cArmyRangeMax_x, m_cArmyRangeMin_y, m_cArmyRangeMax_y);
    UArmyInfantry* new_army = new UArmyInfantry(new_place_x,new_place_y,m_Country);
    m_ArmyList.append(new_army);
    connect(m_ArmyList[m_ArmyList.length()-1], SIGNAL(m_AmmoShooted(int,int,int,int,int,int)), this, SLOT(m_GenerateAmmo(int,int,int,int,int,int)));
}

void GameCentralControl::m_GenerateArmyLight()
{
    if(m_BarrackLevel < 1)
    {
        return;
    }
    if(m_Money < m_cArmyLightMoneyCost)
    {
        return;
    }
    if(m_Material < m_cArmyLightMaterialCost)
    {
        return;
    }
    m_Money -= m_cArmyLightMoneyCost;
    m_Material -= m_cArmyLightMaterialCost;
    //random generate one
    int new_place_x, new_place_y;
    g_GenerateRandomPlace(&new_place_x, &new_place_y, m_cArmyRangeMin_x, m_cArmyRangeMax_x, m_cArmyRangeMin_y, m_cArmyRangeMax_y);
    UArmyLight* new_army = new UArmyLight(new_place_x,new_place_y,m_Country);
    m_ArmyList.append(new_army);
    connect(m_ArmyList[m_ArmyList.length()-1], SIGNAL(m_AmmoShooted(int,int,int,int,int,int)), this, SLOT(m_GenerateAmmo(int,int,int,int,int,int)));
}

void GameCentralControl::m_GenerateArmyCalvary()
{
    if(m_StableLevel < 1)
    {
        return;
    }
    if(m_Money < m_cArmyCalvaryMoneyCost)
    {
        return;
    }
    if(m_Material < m_cArmyCalvaryMaterialCost)
    {
        return;
    }
    m_Money -= m_cArmyCalvaryMoneyCost;
    m_Material -= m_cArmyCalvaryMaterialCost;
    //random generate one
    int new_place_x, new_place_y;
    g_GenerateRandomPlace(&new_place_x, &new_place_y, m_cArmyRangeMin_x, m_cArmyRangeMax_x, m_cArmyRangeMin_y, m_cArmyRangeMax_y);
    UArmyCalvary* new_army = new UArmyCalvary(new_place_x,new_place_y,m_Country);
    m_ArmyList.append(new_army);
}

void GameCentralControl::m_GenerateArmyGrenadier()
{
    if(m_ArsenalLevel < 1)
    {
        return;
    }
    if(m_Money < m_cArmyGrenadierMoneyCost)
    {
        return;
    }
    if(m_Material < m_cArmyGrenadierMaterialCost)
    {
        return;
    }
    m_Money -= m_cArmyGrenadierMoneyCost;
    m_Material -= m_cArmyGrenadierMaterialCost;
    //random generate one
    int new_place_x, new_place_y;
    g_GenerateRandomPlace(&new_place_x, &new_place_y, m_cArmyRangeMin_x, m_cArmyRangeMax_x, m_cArmyRangeMin_y, m_cArmyRangeMax_y);
    UArmyGrenadier* new_army = new UArmyGrenadier(new_place_x,new_place_y,m_Country);
    m_ArmyList.append(new_army);
    connect(m_ArmyList[m_ArmyList.length()-1], SIGNAL(m_AmmoShooted(int,int,int,int,int,int)), this, SLOT(m_GenerateAmmo(int,int,int,int,int,int)));
}

void GameCentralControl::m_GenerateArmySpecial()
{
    if(m_WallLevel < 3)
    {
        return;
    }
    if(m_Money < m_cArmySpecialMoneyCost)
    {
        return;
    }
    if(m_Material < m_cArmySpecialMaterialCost)
    {
        return;
    }
    m_Money -= m_cArmySpecialMoneyCost;
    m_Material -= m_cArmySpecialMaterialCost;
    //random generate one
    int new_place_x, new_place_y;
    g_GenerateRandomPlace(&new_place_x, &new_place_y, m_cArmyRangeMin_x, m_cArmyRangeMax_x, m_cArmyRangeMin_y, m_cArmyRangeMax_y);
    if(m_Country == 1)
    {
        UArmyInfantryEngland* new_army = new UArmyInfantryEngland(new_place_x,new_place_y);
        m_ArmyList.append(new_army);
        connect(m_ArmyList[m_ArmyList.length()-1], SIGNAL(m_AmmoShooted(int,int,int,int,int,int)), this, SLOT(m_GenerateAmmo(int,int,int,int,int,int)));
    }
    if(m_Country == 2)
    {
        UArmyCalvaryFrance* new_army = new UArmyCalvaryFrance(new_place_x,new_place_y);
        m_ArmyList.append(new_army);
    }
    if(m_Country == 3)
    {
        UArmyLightSpain* new_army = new UArmyLightSpain(new_place_x,new_place_y);
        m_ArmyList.append(new_army);
        connect(m_ArmyList[m_ArmyList.length()-1], SIGNAL(m_AmmoShooted(int,int,int,int,int,int)), this, SLOT(m_GenerateAmmo(int,int,int,int,int,int)));
    }
}

void GameCentralControl::m_GenerateSteward()
{
    if(m_WallLevel < 1)
    {
        return;
    }
    if(m_Money < m_cStewardMoneyCost)
    {
        return;
    }
    if(m_Steward != NULL)
    {
        return;
    }

    if(m_Steward == NULL)
    {
        m_Money -= m_cStewardMoneyCost;
        int new_place_x, new_place_y;
        g_GenerateRandomPlace(&new_place_x, &new_place_y, m_cArmyRangeMin_x, m_cArmyRangeMax_x, m_cArmyRangeMin_y, m_cArmyRangeMax_y);
        m_Steward = new USteward(new_place_x, new_place_y);
    }
}


//generate food
void GameCentralControl::m_GenerateFoodLand(const int place_x, const int place_y)
{
    if(m_FoodList.length() >= m_FoodMaxNumber)
    {
        return;
    }
    if(m_Money >= m_cFoodLandMoneyCostByLevel[m_FoodLandLevel] && m_Food >= m_cFoodLandFoodCostByLevel[m_FoodLandLevel])
    {
        m_Money -= m_cFoodLandMoneyCostByLevel[m_FoodLandLevel];
        m_Food -= m_cFoodLandFoodCostByLevel[m_FoodLandLevel];
        UFoodLand* newfood = new UFoodLand(m_FoodLandLevel, place_x, place_y);
        newfood -> m_RepairOverBorder();
        m_FoodList.push_back(newfood);
    }
}

void GameCentralControl::m_GenerateFoodSea(const int place_x, const int place_y)
{
    if(m_FoodList.length() >= m_FoodMaxNumber)
    {
        return;
    }
    if(m_Money >= m_cFoodSeaMoneyCostByLevel[m_FoodSeaLevel] && m_Food >= m_cFoodSeaFoodCostByLevel[m_FoodSeaLevel])
    {
        m_Money -= m_cFoodSeaMoneyCostByLevel[m_FoodSeaLevel];
        m_Food -= m_cFoodSeaFoodCostByLevel[m_FoodSeaLevel];
        UFoodSea* newfood = new UFoodSea(m_FoodSeaLevel, place_x, place_y);
        newfood -> m_RepairOverBorder();
        m_FoodList.push_back(newfood);
    }
}

//generate bonus
void GameCentralControl::m_GenerateBonus(const int bonus_money, const int bonus_material, const int place_x, const int place_y)
{
    if(bonus_money != 0)
    {
        UBonusMoney* new_money = new UBonusMoney(bonus_money, place_x, place_y);
        new_money -> m_RepairOverBorder();
        m_BonusList.append(new_money);
    }
    if(bonus_material != 0)
    {
        UBonusMaterial* new_material = new UBonusMaterial(bonus_material, place_x, place_y);
        new_material -> m_RepairOverBorder();
        m_BonusList.append(new_material);
    }
}

//generate ammo
void GameCentralControl::m_GenerateAmmo
(const int type, const int damage, const int place_x, const int place_y, const int final_x, const int final_y)
{
    if(type != 3)
    {
        g_Resources -> GunSound ->play();
    }
    UAmmo* new_Ammo = new UAmmo(type, damage, place_x, place_y, final_x, final_y);
    m_AmmoList.append(new_Ammo);
    connect(m_AmmoList[m_AmmoList.length()-1], SIGNAL(m_AmmoExploded(int,int,int,int)), this, SLOT(m_ExplodeAmmo(int,int,int,int)));
}


//upgrade buildings slots
void GameCentralControl::m_UpgradeFoodLand()
{
    if(m_Money >= m_cFoodLandUpgradeMoneyCostByLevel[m_FoodLandLevel])
    {
        m_Money -= m_cFoodLandUpgradeMoneyCostByLevel[m_FoodLandLevel];
        m_FoodLandLevel ++;
    }
}

void GameCentralControl::m_UpgradeFoodSea()
{
    if(m_Money >= m_cFoodSeaUpgradeMoneyCostByLevel[m_FoodSeaLevel])
    {
        m_Money -= m_cFoodSeaUpgradeMoneyCostByLevel[m_FoodSeaLevel];
        m_FoodSeaLevel ++;
    }
}

void GameCentralControl::m_UpgradeFoodMaxNumber()
{
    if(m_Money >= m_cFoodNumberUpgradeMoneyCostByLevel[m_FoodMaxNumberLevel])
    {
        m_Money -= m_cFoodNumberUpgradeMoneyCostByLevel[m_FoodMaxNumberLevel];
        m_FoodMaxNumberLevel ++;
        m_FoodMaxNumber = m_cFoodMaxNumberByLevel[m_FoodMaxNumberLevel];
    }
}

void GameCentralControl::m_UpgradeWall()
{
    if(m_WallLevel >= m_cWallLevelMax)
    {
        return;
    }

    if(m_Money < m_cWallMoneyCostByLevel[m_WallLevel + 1] || m_Material < m_cWallMaterialCostByLevel[m_WallLevel + 1] ||
             m_Food < m_cWallFoodCostByLevel[m_WallLevel + 1])
    {
        return;
    }
    m_Money -= m_cWallMoneyCostByLevel[m_WallLevel + 1];
    m_Material -= m_cWallMaterialCostByLevel[m_WallLevel + 1];
    m_Food -= m_cWallFoodCostByLevel[m_WallLevel + 1];
    m_WallLevel ++;
    emit m_ShowUpgradeHintSign(m_WallLevel);
}

void GameCentralControl::m_UpgradeFarm()
{
    if(m_FarmLevel >= m_cFarmLevelMax)
    {
        return;
    }
    if(m_WallLevel < m_cFarmBuildingRequirement[m_FarmLevel + 1])
    {
        return;
    }
    if(m_Money < m_cFarmMoneyCostByLevel[m_FarmLevel + 1] || m_Material < m_cFarmMaterialCostByLevel[m_FarmLevel + 1])
    {
        return;
    }
    m_Money -= m_cFarmMoneyCostByLevel[m_FarmLevel + 1];
    m_Material -= m_cFarmMaterialCostByLevel[m_FarmLevel + 1];
    m_FarmLevel ++;
}

void GameCentralControl::m_UpgradeFactory()
{
    if(m_FactoryLevel >= m_cFactoryLevelMax)
    {
        return;
    }
    if(m_WallLevel < m_cFactoryBuildingRequirement[m_FactoryLevel + 1])
    {
        return;
    }
    if(m_Money < m_cFactoryMoneyCostByLevel[m_FactoryLevel + 1] || m_Material < m_cFactoryMaterialCostByLevel[m_FactoryLevel + 1])
    {
        return;
    }
    m_Money -= m_cFactoryMoneyCostByLevel[m_FactoryLevel + 1];
    m_Material -= m_cFactoryMaterialCostByLevel[m_FactoryLevel + 1];
    m_FactoryLevel ++;
}

void GameCentralControl::m_UpgradeMarket()
{
    if(m_MarketLevel >= 1)
    {
        return;
    }
    if(m_WallLevel < m_cMarketBuildingRequirement)
    {
        return;
    }
    if(m_Money < m_cMarketMoneyCost || m_Material < m_cMarketMaterialCost)
    {
        return;
    }
    m_Money -= m_cMarketMoneyCost;
    m_Material -= m_cMarketMaterialCost;
    m_MarketLevel ++;
}

void GameCentralControl::m_UpgradeHarbor()
{
    if(m_HarborLevel >= 1)
    {
        return;
    }
    if(m_WallLevel < m_cHarborBuildingRequirement)
    {
        return;
    }
    if(m_Money < m_cHarborMoneyCost || m_Material < m_cHarborMaterialCost)
    {
        return;
    }
    m_Money -= m_cHarborMoneyCost;
    m_Material -= m_cHarborMaterialCost;
    m_HarborLevel ++;
}

void GameCentralControl::m_UpgradeBarrack()
{
    if(m_BarrackLevel >= 1)
    {
        return;
    }
    if(m_WallLevel < m_cBarrackBuildingRequirement)
    {
        return;
    }
    if(m_Money < m_cBarrackMoneyCost || m_Material < m_cBarrackMaterialCost)
    {
        return;
    }
    m_Money -= m_cBarrackMoneyCost;
    m_Material -= m_cBarrackMaterialCost;
    m_BarrackLevel ++;
}

void GameCentralControl::m_UpgradeStable()
{
    if(m_StableLevel >= 1)
    {
        return;
    }
    if(m_WallLevel < m_cStableBuildingRequirement)
    {
        return;
    }
    if(m_Money < m_cStableMoneyCost || m_Material < m_cStableMaterialCost)
    {
        return;
    }
    m_Money -= m_cStableMoneyCost;
    m_Material -= m_cStableMaterialCost;
    m_StableLevel ++;
}

void GameCentralControl::m_UpgradeArsenal()
{
    if(m_ArsenalLevel >= 1)
    {
        return;
    }
    if(m_WallLevel < m_cArsenalBuildingRequirement)
    {
        return;
    }
    if(m_Money < m_cArsenalMoneyCost || m_Material < m_cArsenalMaterialCost)
    {
        return;
    }
    m_Money -= m_cArsenalMoneyCost;
    m_Material -= m_cArsenalMaterialCost;
    m_ArsenalLevel ++;
}

void GameCentralControl::m_ExplodeAmmo(int type, int damage, int place_x, int place_y)
{
    if(type == 1)
    {
        for(int i = 0; i < m_EnemyList.length(); i ++)
        {
            double distance = g_GetDistance(place_x, place_y, m_EnemyList[i]);
            if(distance < m_cBombRangeBySpecies[type])
            {
                m_EnemyList[i] -> m_BeingAttack(damage);
                break;
            }
        }
    }

    if(type == 2)
    {
        for(int i = 0; i < m_ArmyList.length(); i ++)
        {
            double distance = g_GetDistance(place_x, place_y, m_ArmyList[i]);
            if(distance < m_cBombRangeBySpecies[type])
            {
                m_ArmyList[i] -> m_BeingAttack(damage);
                break;
            }
        }
    }
    if(type == 3)
    {
        g_Resources ->BombSound ->play();
        for(int i = 0; i < m_AnimalList.length(); i ++)
        {
            double distance = g_GetDistance(place_x, place_y, m_AnimalList[i]);
            if(distance < m_cBombRangeBySpecies[type])
            {
                m_AnimalList[i] -> m_BeingAttack(damage);
                double object_x, object_y;
                m_AnimalList[i] -> m_GetPlace(&object_x, &object_y);
                m_AnimalList[i] -> m_InstantMove(object_x - place_x, object_y - place_y);
            }
        }
        for(int i = 0; i < m_ArmyList.length(); i ++)
        {
            double distance = g_GetDistance(place_x, place_y, m_ArmyList[i]);
            if(distance < m_cBombRangeBySpecies[type])
            {
                m_ArmyList[i] -> m_BeingAttack(damage);
                double object_x, object_y;
                m_ArmyList[i] -> m_GetPlace(&object_x, &object_y);
                m_ArmyList[i] -> m_InstantMove(object_x - place_x, object_y - place_y);
            }
        }
        for(int i = 0; i < m_EnemyList.length(); i ++)
        {
            double distance = g_GetDistance(place_x, place_y, m_EnemyList[i]);
            if(distance < m_cBombRangeBySpecies[type])
            {
                m_EnemyList[i] -> m_BeingAttack(damage);
                double object_x, object_y;
                m_EnemyList[i] -> m_GetPlace(&object_x, &object_y);
                m_EnemyList[i] -> m_InstantMove(object_x - place_x, object_y - place_y);
            }
        }
    }


}

//get bonus
void GameCentralControl::m_GetBonus(int bonus_place)
{
    int type, quantity;
    m_BonusList[bonus_place] -> m_GiveBonus(&type, &quantity);
    if(type == 1)
    {
        m_Money += quantity;
        if(m_Country == 2) //france
        {
            m_Money += int(0.2 * quantity);
        }
        if(m_MarketLevel == 1)
        {
            m_Money += int(0.5 * quantity);
        }
        if(m_HarborLevel == 1)
        {
            m_Money += int(0.5 * quantity);
        }
    }
    else
    {
        m_Material += quantity;
        if(m_Country == 2) //france
        {
            m_Material += int(0.2 * quantity);
        }
        if(m_HarborLevel == 1)
        {
            m_Material += int(0.5 * quantity);
        }
    }
    m_BonusList[bonus_place] -> m_BeingTaken();
}

//manage target seeking
bool GameCentralControl::m_FindTarget(UAnimal *seeker)
{
    if(seeker -> m_Species == 1 || seeker -> m_Species == 4|| seeker -> m_Species == 5 || seeker -> m_Species == 6) //grass eater
    {
        double distance_min = m_cRangedInteractRange;
        int min_food = -1;
        for(int i = 0; i < m_FoodList.length(); i++)
        {
            double temp_distance = g_GetDistance(seeker, m_FoodList[i]);
            if(temp_distance < distance_min)
            {
                distance_min = temp_distance;
                min_food = i;
            }
        }
        if(min_food == -1)
        {
            return 0;               //no target
        }
        else
        {
            double final_x, final_y;
            m_FoodList[min_food] -> m_GetPlace(&final_x, &final_y);
            seeker ->m_Forage(final_x, final_y);
            return 1;
        }
    }
    
    if(seeker -> m_Species == 2) //small meat eater
    {
        double distance_min = m_cRangedInteractRange;
        int min_food = -1;
        for(int i = 0; i < m_AnimalList.length(); i++)
        {
            if(m_AnimalList[i] -> m_Species == 1)
            {
                if(m_AnimalList[i] -> m_Level != 1)
                {
                    continue;
                }
                if(m_AnimalList[i] -> m_Status == 4)
                {
                    continue;
                }
                double temp_distance = g_GetDistance(seeker, m_AnimalList[i]);
                if(temp_distance < distance_min)
                {
                    distance_min = temp_distance;
                    min_food = i;
                }
            }
        }
        if(min_food == -1)
        {
            return 0;               //no target
        }
        else
        {
            double final_x, final_y;
            m_AnimalList[min_food] -> m_GetPlace(&final_x, &final_y);
            seeker ->m_Forage(final_x, final_y);
            return 1;
        }
    }
    
    if(seeker -> m_Species == 3) //big meat eater
    {
        double distance_min = m_cRangedInteractRange;
        int min_food = -1;
        for(int i = 0; i < m_AnimalList.length(); i++)
        {
            if(m_AnimalList[i] -> m_Species == 2)
            {
                if(m_AnimalList[i] -> m_Status == 4)
                {
                    continue;
                }
                double temp_distance = g_GetDistance(seeker, m_AnimalList[i]);
                if(temp_distance < distance_min)
                {
                    distance_min = temp_distance;
                    min_food = i;
                }
            }
        }
        if(min_food == -1)
        {
            return 0;               //no target
        }
        else
        {
            double final_x, final_y;
            m_AnimalList[min_food] -> m_GetPlace(&final_x, &final_y);
            seeker ->m_Forage(final_x, final_y);
            return 1;
        }
    }

    if(seeker -> m_Species == 7)
    {
        return 0;
    }
}

bool GameCentralControl::m_FindTarget(UEnemy *seeker)
{
    if(seeker -> m_Species == 1 || seeker -> m_Species == 5)
    {
        int min_victim = -1;
        double min_distance = m_cRangedInteractRange;
        for(int i = 0; i < m_AnimalList.length(); i ++)
        {
            if(m_AnimalList[i] -> m_Status == 4)
            {
                continue;
            }
            double temp_distance = g_GetDistance(seeker, m_AnimalList[i]);   
            if(temp_distance < min_distance)
            {
                min_distance = temp_distance;
                min_victim = i;
            }
        }
        if(min_victim == -1)
        {
            return 0;
        }
        else
        {
            double final_x, final_y;
            m_AnimalList[min_victim] ->m_GetPlace(&final_x, &final_y);
            seeker -> m_ChaseTarget(final_x, final_y);
            return 1;
        }
    }
    
    if(seeker -> m_Species == 2)
    {
        int min_victim = -1;
        int min_type;
        double min_distance = m_cRangedInteractRange;
        for(int i = 0; i < m_AnimalList.length(); i ++)
        {
            if(m_AnimalList[i] -> m_Status == 4)
            {
                continue;
            }
            double temp_distance = g_GetDistance(seeker, m_AnimalList[i]);   
            if(temp_distance < min_distance)
            {
                min_distance = temp_distance;
                min_victim = i;
                min_type = 1;
            }
        }
        for (int i = 0; i < m_FoodList.length(); i ++)
        {
            double temp_distance = g_GetDistance(seeker, m_FoodList[i]);   
            if(temp_distance < min_distance)
            {
                min_distance = temp_distance;
                min_victim = i;
                min_type = 2;
            }
        }
        if(min_victim == -1)
        {
            return 0;
        }
        else
        {
            double final_x, final_y;
            if(min_type == 1)
            {
                m_AnimalList[min_victim] ->m_GetPlace(&final_x, &final_y);
            }
            else
            {
                m_FoodList[min_victim] ->m_GetPlace(&final_x, &final_y);
            }
            seeker -> m_ChaseTarget(final_x, final_y);
            return 1;
        }
    }
    
    if(seeker -> m_Species == 3 || seeker -> m_Species == 4 )
    {
        int min_victim = -1;
        double min_distance = m_cRangedInteractRange;
        for(int i = 0; i < m_ArmyList.length(); i ++)
        {
            double temp_distance = g_GetDistance(seeker, m_ArmyList[i]);   
            if(temp_distance < min_distance)
            {
                min_distance = temp_distance;
                min_victim = i;
            }
        }
        if(min_victim == -1)
        {
            return 0;
        }
        else
        {
            double final_x, final_y;
            m_ArmyList[min_victim] ->m_GetPlace(&final_x, &final_y);
            seeker -> m_ChaseTarget(final_x, final_y);
            return 1;
        }
    }
}

bool GameCentralControl::m_FindTarget(UArmy *seeker)
{
    if(seeker -> m_Species == 1 || seeker -> m_Species == 3 || seeker -> m_Species == 4 || seeker -> m_Species == 5 ||seeker -> m_Species == 6)
    {
        int min_enemy = -1;
        double min_distance = m_cRangedInteractRange;
        for(int i = 0; i < m_EnemyList.length(); i ++)
        {
            double temp_distance = g_GetDistance(seeker, m_EnemyList[i]);
            if(temp_distance < min_distance)
            {
                min_distance = temp_distance;
                min_enemy = i;
            }
        }
        if(min_enemy == -1)
        {
            return 0;
        }
        else
        {
            double final_x, final_y;
            m_EnemyList[min_enemy] ->m_GetPlace(&final_x, &final_y);
            seeker -> m_ChaseTarget(final_x, final_y);
            return 1;
        }
    }
}

bool GameCentralControl::m_FindTarget(USteward* seeker)
{
    int min_bonus = -1;
    double min_distance = m_cRangedInteractRange;
    for(int i = 0; i < m_BonusList.length(); i ++)
    {
        double temp_distance = g_GetDistance(seeker, m_BonusList[i]);
        if(temp_distance < min_distance)
        {
            min_distance = temp_distance;
            min_bonus = i;
        }
    }
    if(min_bonus == -1)
    {
        return 0;
    }
    else
    {
        double final_x, final_y;
        m_BonusList[min_bonus] ->m_GetPlace(&final_x, &final_y);
        seeker -> m_ChaseTarget(final_x, final_y);
        return 1;
    }
}

bool GameCentralControl::m_FindShoot(UArmy *seeker)
{
    if(seeker -> m_Species == 1 || seeker -> m_Species == 4 || seeker -> m_Species == 5)
    {
        if(seeker -> m_AttackType == 2)
        {
            return 0;
        }
        int min_enemy = -1;
        double min_distance = m_cMiddleInteractRange;
        for(int i = 0; i < m_EnemyList.length(); i ++)
        {
            double temp_distance = g_GetDistance(seeker, m_EnemyList[i]);
            if(temp_distance < min_distance)
            {
                min_distance = temp_distance;
                min_enemy = i;
            }
        }
        if(min_enemy == -1)
        {
            return 0;
        }
        else
        {
            double final_x, final_y;
            m_EnemyList[min_enemy] ->m_GetPlace(&final_x, &final_y);
            if(seeker -> m_WhetherCanAttack == 1)
            {
                seeker -> m_ShootAmmo(final_x, final_y);
            }
            return 1;
        }
    }

    if(seeker -> m_Species == 2 || seeker -> m_Species == 7)
    {
        int min_enemy = -1;
        double min_distance = m_cRangedInteractRange;
        for(int i = 0; i < m_EnemyList.length(); i ++)
        {
            double temp_distance = g_GetDistance(seeker, m_EnemyList[i]);
            if(temp_distance < min_distance)
            {
                min_distance = temp_distance;
                min_enemy = i;
            }
        }
        if(min_enemy == -1)
        {
            return 0;
        }
        else
        {
            double final_x, final_y;
            m_EnemyList[min_enemy] ->m_GetPlace(&final_x, &final_y);
            if(seeker -> m_WhetherCanAttack == 1)
            {
                seeker -> m_ShootAmmo(final_x, final_y);
            }
            return 1;
        }
    }
}

bool GameCentralControl::m_FindShoot(UEnemy *seeker)
{

    if(seeker -> m_Species == 4)
  {
        int min_victim = -1;
        double min_distance = m_cMiddleInteractRange;
    for(int i = 0; i < m_ArmyList.length(); i ++)
    {
        double temp_distance = g_GetDistance(seeker, m_ArmyList[i]);
        if(temp_distance < min_distance)
        {
            min_distance = temp_distance;
            min_victim = i;
        }
    }
    if(min_victim == -1)
    {
        return 0;
    }
    else
    {
        double final_x, final_y;
        m_ArmyList[min_victim] ->m_GetPlace(&final_x, &final_y);
            if(seeker -> m_WhetherCanAttack == 1)
            {
                seeker -> m_ShootAmmo(final_x, final_y);                    
            }

        return 1;
    }
  }
    if(seeker -> m_Species == 5)
  {
        int min_victim = -1;
        double min_distance = m_cMiddleInteractRange;

        for(int i = 0; i < m_AnimalList.length(); i ++)
        {
            if(m_AnimalList[i] -> m_Status == 4)
            {
                continue;
            }

            double temp_distance = g_GetDistance(seeker, m_AnimalList[i]);
            if(temp_distance < min_distance)
            {
                min_distance = temp_distance;
                min_victim = i;
            }
        }
        if(min_victim == -1)
        {
            return 0;
        }
        else
        {
            double final_x, final_y;
            m_AnimalList[min_victim] ->m_GetPlace(&final_x, &final_y);
                if(seeker -> m_WhetherCanAttack == 1)
                {
                    m_AnimalList[min_victim] -> m_BeingEaten();
                    m_GenerateEnemyBarbarian(final_x, final_y);
                    seeker -> m_ShootAmmo(final_x, final_y);                    
                }
    
            return 1;
        }
  }
}
