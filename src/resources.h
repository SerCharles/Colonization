/*
Filename: Resources.h
Description: the global resources.
Version: 1.0
Date: 09/04/2018
*/

#ifndef RESOURCES_H
#define RESOURCES_H

#include <QObject>
#include <QPixmap>
#include <QtMultimedia/QSound>

class Resources
{
public:
    //background
    QPixmap* BackGroundPicture;
    QPixmap* LoadingPicture;
    QPixmap* VictoryPicture;
    QPixmap* LosePicture;
    QPixmap* GamePicture;
    QPixmap* PausePicture;


    //show icon
    QPixmap* FoodIcon;
    QPixmap* MoneyIcon;
    QPixmap* MaterialIcon;
    QPixmap* CityIcon;
    QPixmap* FoodMaxIcon;
    QPixmap* LevelMaxIcon;
    QPixmap* WarWarningIcon;
    QPixmap* TownAdvanceHint;
    QPixmap* LargeTownAdvanceHint;
    QPixmap* CityAdvanceHint;

    //food
    QPixmap* FoodLandLV1;
    QPixmap* FoodLandLV2;
    QPixmap* FoodLandLV3;
    QPixmap* FoodLandLV4;
    QPixmap* FoodLandLV5;

    QPixmap* FoodSeaLV1;
    QPixmap* FoodSeaLV2;
    QPixmap* FoodSeaLV3;

    QPixmap* FoodMaxLV2;
    QPixmap* FoodMaxLV3;
    QPixmap* FoodMaxLV4;



    //bonus
    QPixmap* BonusMoneyLV1;
    QPixmap* BonusMoneyLV2;
    QPixmap* BonusMoneyLV3;
    QPixmap* BonusMoneyLV4;

    QPixmap* BonusMaterialLV1;
    QPixmap* BonusMaterialLV2;
    QPixmap* BonusMaterialLV3;


    //animals
    QPixmap* AnimalGrassLV1Normal;
    QPixmap* AnimalGrassLV1Hungry;
    QPixmap* AnimalGrassLV1Dead;
    QPixmap* AnimalGrassLV2Normal;
    QPixmap* AnimalGrassLV2Hungry;
    QPixmap* AnimalGrassLV2Dead;
    QPixmap* AnimalGrassLV3Normal;
    QPixmap* AnimalGrassLV3Hungry;
    QPixmap* AnimalGrassLV3Dead;
    QPixmap* AnimalGrassLV4Normal;
    QPixmap* AnimalGrassLV4Hungry;
    QPixmap* AnimalGrassLV4Dead;

    QPixmap* AnimalMeatSmallNormal;
    QPixmap* AnimalMeatSmallHungry;
    QPixmap* AnimalMeatSmallDead;

    QPixmap* AnimalMeatBigNormal;
    QPixmap* AnimalMeatBigHungry;
    QPixmap* AnimalMeatBigDead; 

    QPixmap* AnimalMotherLV1Normal;
    QPixmap* AnimalMotherLV1Hungry;
    QPixmap* AnimalMotherLV1Dead;
    QPixmap* AnimalMotherLV2Normal;
    QPixmap* AnimalMotherLV2Hungry;
    QPixmap* AnimalMotherLV2Dead;

    QPixmap* AnimalMaterialLV1Normal;
    QPixmap* AnimalMaterialLV1Hungry;
    QPixmap* AnimalMaterialLV1Dead;
    QPixmap* AnimalMaterialLV2Normal;
    QPixmap* AnimalMaterialLV2Hungry;
    QPixmap* AnimalMaterialLV2Dead;
    QPixmap* AnimalMaterialLV3Normal;
    QPixmap* AnimalMaterialLV3Hungry;
    QPixmap* AnimalMaterialLV3Dead;

    QPixmap* AnimalMaterialMotherNormal;
    QPixmap* AnimalMaterialMotherHungry;
    QPixmap* AnimalMaterialMotherDead;

    QPixmap* AnimalKingNormal;
    QPixmap* AnimalKingHungry;
    QPixmap* AnimalKingDead;


    //enemies
    QPixmap* EnemyBarbarian;
    QPixmap* EnemyEater;
    QPixmap* EnemyNativeWarrior;
    QPixmap* EnemyNativeGunner;
    QPixmap* EnemyNativeShaman;

    //soldier
    QPixmap* ArmyInfantryEngland;
    QPixmap* ArmyInfantryFrance;
    QPixmap* ArmyInfantrySpain;

    QPixmap* ArmyLightEngland;
    QPixmap* ArmyLightFrance;
    QPixmap* ArmyLightSpain;

    QPixmap* ArmyCalvaryEngland;
    QPixmap* ArmyCalvaryFrance;
    QPixmap* ArmyCalvarySpain;

    QPixmap* ArmyGrenadierEngland;
    QPixmap* ArmyGrenadierFrance;
    QPixmap* ArmyGrenadierSpain;

    QPixmap* ArmySpecialEngland;
    QPixmap* ArmySpecialFrance;
    QPixmap* ArmySpecialSpain;

    QPixmap* StewardNormal;
    QPixmap* StewardHide;

    //ammo
    QPixmap* AmmoBullet;
    QPixmap* AmmoBomb;

    //building
    QPixmap* BuildingWallLV1;
    QPixmap* BuildingWallLV2;
    QPixmap* BuildingWallLV3;
    QPixmap* BuildingWallLV4;
    
    QPixmap* BuildingFarmLV1;
    QPixmap* BuildingFarmLV2;
    QPixmap* BuildingFarmLV3;
    QPixmap* BuildingFarmLV4;

    QPixmap* BuildingFactoryLV1;
    QPixmap* BuildingFactoryLV2;
    QPixmap* BuildingFactoryLV3;

    QPixmap* BuildingMarket;
    QPixmap* BuildingHarbor;
    QPixmap* BuildingBarrack;
    QPixmap* BuildingStable;
    QPixmap* BuildingArsenal;


    //bgm
    QSound* MainTheme;
    QSound* GameTheme;

    //soundtrack
    QSound* BombSound;
    QSound* GunSound;
    QSound* MeleeSound;


public:
    Resources();
    ~Resources();

};

extern Resources* g_Resources;


#endif // RESOURCES_H
