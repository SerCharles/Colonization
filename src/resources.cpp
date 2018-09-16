/*
Filename: Resources.cpp
Description: the global resources.
Version: 1.0
Date: 09/04/2018
*/

#include <QtMultimedia/QSound>
#include "resources.h"

Resources::Resources()
{
//background
    BackGroundPicture = new QPixmap(":/picture/res/Background.png");
    LoadingPicture = new QPixmap(":/picture/res/Loading.png");
    VictoryPicture = new QPixmap(":/picture/res/BackGround_Victory.png");
    LosePicture = new QPixmap(":/picture/res/BackGround_Lose.png");
    GamePicture = new QPixmap(":/picture/res/Game_BackGround.jpg");
    PausePicture = new QPixmap(":/picture/res/Pause_Backround.png");

//show icon
    FoodIcon = new QPixmap(":/picture/res/FoodIcon.png");
    MoneyIcon = new QPixmap(":/picture/res/MoneyIcon.png");
    MaterialIcon = new QPixmap(":/picture/res/MaterialIcon.png");
    CityIcon = new QPixmap(":/picture/res/CityPicture.png");
    FoodMaxIcon = new QPixmap(":/picture/res/FoodMaxIcon.png");
    LevelMaxIcon = new QPixmap(":/picture/res/LevelMaxIcon.png");
    WarWarningIcon = new QPixmap(":/picture/res/WarWarningIcon.png");
    TownAdvanceHint = new QPixmap(":/picture/res/TownIcon.png");
    LargeTownAdvanceHint = new QPixmap(":/picture/res/LargeTownIcon.png");
    CityAdvanceHint = new QPixmap(":/picture/res/CityIcon.png");


//food
    FoodLandLV1 = new QPixmap(":/picture/res/Food_Land_LV1.png");
    FoodLandLV2 = new QPixmap(":/picture/res/Food_Land_LV2.png");
    FoodLandLV3 = new QPixmap(":/picture/res/Food_Land_LV3.png");
    FoodLandLV4 = new QPixmap(":/picture/res/Food_Land_LV4.png");
    FoodLandLV5 = new QPixmap(":/picture/res/Food_Land_LV5.png");

    FoodSeaLV1 = new QPixmap(":/picture/res/Food_Sea_LV1.png");
    FoodSeaLV2 = new QPixmap(":/picture/res/Food_Sea_LV2.png");
    FoodSeaLV3 = new QPixmap(":/picture/res/Food_Sea_LV3.png");

    FoodMaxLV2 = new QPixmap(":/picture/res/Food_Number_LV2.png");
    FoodMaxLV3 = new QPixmap(":/picture/res/Food_Number_LV3.png");
    FoodMaxLV4 = new QPixmap(":/picture/res/Food_Number_LV4.png");



//bonus
    BonusMoneyLV1 = new QPixmap(":/picture/res/Bonus_Money_LV1.png");
    BonusMoneyLV2 = new QPixmap(":/picture/res/Bonus_Money_LV2.png");
    BonusMoneyLV3 = new QPixmap(":/picture/res/Bonus_Money_LV3.png");
    BonusMoneyLV4 = new QPixmap(":/picture/res/Bonus_Money_LV4.png");

    BonusMaterialLV1 = new QPixmap(":/picture/res/Bonus_Material_LV1.png");
    BonusMaterialLV2 = new QPixmap(":/picture/res/Bonus_Material_LV2.png");
    BonusMaterialLV3 = new QPixmap(":/picture/res/Bonus_Material_LV3.png");



//animal
    AnimalGrassLV1Normal = new QPixmap(":/picture/res/Animal_Grass_LV1_Normal.png");
    AnimalGrassLV1Hungry = new QPixmap(":/picture/res/Animal_Grass_LV1_Hungry.png");
    AnimalGrassLV1Dead = new QPixmap(":/picture/res/Animal_Grass_LV1_Dead.png");
    AnimalGrassLV2Normal = new QPixmap(":/picture/res/Animal_Grass_LV2_Normal.png");
    AnimalGrassLV2Hungry = new QPixmap(":/picture/res/Animal_Grass_LV2_Hungry.png");
    AnimalGrassLV2Dead = new QPixmap(":/picture/res/Animal_Grass_LV2_Dead.png");
    AnimalGrassLV3Normal = new QPixmap(":/picture/res/Animal_Grass_LV3_Normal.png");
    AnimalGrassLV3Hungry = new QPixmap(":/picture/res/Animal_Grass_LV3_Hungry.png");
    AnimalGrassLV3Dead = new QPixmap(":/picture/res/Animal_Grass_LV3_Dead.png");
    AnimalGrassLV4Normal = new QPixmap(":/picture/res/Animal_Grass_LV4_Normal.png");
    AnimalGrassLV4Hungry = new QPixmap(":/picture/res/Animal_Grass_LV4_Hungry.png");
    AnimalGrassLV4Dead = new QPixmap(":/picture/res/Animal_Grass_LV4_Dead.png");

    AnimalMeatSmallNormal = new QPixmap(":/picture/res/Animal_Meat_Small_Normal.png");
    AnimalMeatSmallHungry = new QPixmap(":/picture/res/Animal_Meat_Small_Hungry.png");
    AnimalMeatSmallDead = new QPixmap(":/picture/res/Animal_Meat_Small_Dead.png"); 

    AnimalMeatBigNormal = new QPixmap(":/picture/res/Animal_Meat_Big_Normal.png");
    AnimalMeatBigHungry = new QPixmap(":/picture/res/Animal_Meat_Big_Hungry.png");
    AnimalMeatBigDead = new QPixmap(":/picture/res/Animal_Meat_Big_Dead.png");

    AnimalMotherLV1Normal = new QPixmap(":/picture/res/Animal_Mother_LV1_Normal.png");
    AnimalMotherLV1Hungry = new QPixmap(":/picture/res/Animal_Mother_LV1_Hungry.png");
    AnimalMotherLV1Dead = new QPixmap(":/picture/res/Animal_Mother_LV1_Dead.png");
    AnimalMotherLV2Normal = new QPixmap(":/picture/res/Animal_Mother_LV2_Normal.png");
    AnimalMotherLV2Hungry = new QPixmap(":/picture/res/Animal_Mother_LV2_Hungry.png");
    AnimalMotherLV2Dead = new QPixmap(":/picture/res/Animal_Mother_LV2_Dead.png");

    AnimalMaterialLV1Normal = new QPixmap(":/picture/res/Animal_Material_LV1_Normal.png");
    AnimalMaterialLV1Hungry = new QPixmap(":/picture/res/Animal_Material_LV1_Hungry.png");
    AnimalMaterialLV1Dead = new QPixmap(":/picture/res/Animal_Material_LV1_Dead.png");
    AnimalMaterialLV2Normal = new QPixmap(":/picture/res/Animal_Material_LV2_Normal.png");
    AnimalMaterialLV2Hungry = new QPixmap(":/picture/res/Animal_Material_LV2_Hungry.png");
    AnimalMaterialLV2Dead = new QPixmap(":/picture/res/Animal_Material_LV2_Dead.png");
    AnimalMaterialLV3Normal = new QPixmap(":/picture/res/Animal_Material_LV3_Normal.png");
    AnimalMaterialLV3Hungry = new QPixmap(":/picture/res/Animal_Material_LV3_Hungry.png");
    AnimalMaterialLV3Dead = new QPixmap(":/picture/res/Animal_Material_LV3_Dead.png"); 

    AnimalMaterialMotherNormal = new QPixmap(":/picture/res/Animal_Material_Mother_Normal.png");
    AnimalMaterialMotherHungry = new QPixmap(":/picture/res/Animal_Material_Mother_Hungry.png");
    AnimalMaterialMotherDead = new QPixmap(":/picture/res/Animal_Material_Mother_Dead.png");

    AnimalKingNormal = new QPixmap(":/picture/res/Animal_King_Normal.png");
    AnimalKingHungry = new QPixmap(":/picture/res/Animal_King_Hungry.png");
    AnimalKingDead = new QPixmap(":/picture/res/Animal_King_Dead.png");


    //enemy
    EnemyBarbarian = new QPixmap(":/picture/res/Enemy_Barbarian.png");
    EnemyEater = new QPixmap(":/picture/res/Enemy_Eater.png");
    EnemyNativeWarrior = new QPixmap(":/picture/res/Enemy_Native_Warrior.png");
    EnemyNativeGunner = new QPixmap(":/picture/res/Enemy_Native_Gunner.png");
    EnemyNativeShaman = new QPixmap(":/picture/res/Enemy_Native_Shaman.png");


    //army
    ArmyInfantryEngland = new QPixmap(":/picture/res/Army_Infantry_England.png");
    ArmyInfantryFrance = new QPixmap(":/picture/res/Army_Infantry_France.png");
    ArmyInfantrySpain = new QPixmap(":/picture/res/Army_Infantry_Spain.png");
    ArmyLightEngland = new QPixmap(":/picture/res/Army_Light_England.png");
    ArmyLightFrance = new QPixmap(":/picture/res/Army_Light_France.png");
    ArmyLightSpain = new QPixmap(":/picture/res/Army_Light_Spain.png");
    ArmyCalvaryEngland = new QPixmap(":/picture/res/Army_Calvary_England.png");
    ArmyCalvaryFrance = new QPixmap(":/picture/res/Army_Calvary_France.png");
    ArmyCalvarySpain = new QPixmap(":/picture/res/Army_Calvary_Spain.png");
    ArmyGrenadierEngland = new QPixmap(":/picture/res/Army_Grenadier_England.png");
    ArmyGrenadierFrance = new QPixmap(":/picture/res/Army_Grenadier_France.png");
    ArmyGrenadierSpain = new QPixmap(":/picture/res/Army_Grenadier_Spain.png");
    ArmySpecialEngland = new QPixmap(":/picture/res/Army_Special_England.png");
    ArmySpecialFrance = new QPixmap(":/picture/res/Army_Special_France.png");
    ArmySpecialSpain = new QPixmap(":/picture/res/Army_Special_Spain.png");

    //steward
    StewardNormal = new QPixmap(":/picture/res/Steward_Normal.png");
    StewardHide = new QPixmap(":/picture/res/Steward_Hide.png");
    
    //ammo
    AmmoBullet = new QPixmap(":/picture/res/Ammo_Bullet.png");
    AmmoBomb = new QPixmap(":/picture/res/Ammo_Bomb.png");
    
    
    //building
    BuildingWallLV1 = new QPixmap(":/picture/res/Building_Wall_LV1.png");
    BuildingWallLV2 = new QPixmap(":/picture/res/Building_Wall_LV2.png");
    BuildingWallLV3 = new QPixmap(":/picture/res/Building_Wall_LV3.png");
    BuildingWallLV4 = new QPixmap(":/picture/res/Building_Wall_LV4.png");
    
    BuildingFarmLV1 = new QPixmap(":/picture/res/Building_Farm_LV1.png");
    BuildingFarmLV2 = new QPixmap(":/picture/res/Building_Farm_LV2.png");
    BuildingFarmLV3 = new QPixmap(":/picture/res/Building_Farm_LV3.png");
    BuildingFarmLV4 = new QPixmap(":/picture/res/Building_Farm_LV4.png");
    
    BuildingFactoryLV1 = new QPixmap(":/picture/res/Building_Factory_LV1.png");
    BuildingFactoryLV2 = new QPixmap(":/picture/res/Building_Factory_LV2.png");
    BuildingFactoryLV3 = new QPixmap(":/picture/res/Building_Factory_LV3.png");

    BuildingMarket = new QPixmap(":/picture/res/Building_Market.png");
    BuildingHarbor = new QPixmap(":/picture/res/Building_Harbor.png");
    BuildingBarrack = new QPixmap(":/picture/res/Building_Barrack.png");
    BuildingStable = new QPixmap(":/picture/res/Building_Stable.png");
    BuildingArsenal = new QPixmap(":/picture/res/Building_Arsenal.png");



   //bgm
    MainTheme = new QSound(":/audio/audio/MainTheme.wav");
    GameTheme = new QSound(":/audio/audio/GameTheme.wav");

    MainTheme -> setLoops(-1);
    GameTheme -> setLoops(-1);

    //soundeffect
    GunSound = new QSound(":/audio/audio/Sound_Gun.wav");
    BombSound = new QSound(":/audio/audio/Sound_Bomb.wav");
    MeleeSound = new QSound(":/audio/audio/Sound_Attack.wav");

}

Resources::~Resources()
{
    //background
    delete(BackGroundPicture);
    delete(LoadingPicture);
    delete(VictoryPicture);
    delete(LosePicture);
    delete(GamePicture);
    delete(PausePicture);

    //Icon
    delete(FoodIcon);
    delete(MoneyIcon);
    delete(MaterialIcon);
    delete(CityIcon);
    delete(FoodMaxIcon);
    delete(LevelMaxIcon);
    delete(WarWarningIcon);
    delete(TownAdvanceHint);
    delete(LargeTownAdvanceHint);
    delete(CityAdvanceHint);

    //food
    delete(FoodLandLV1);
    delete(FoodLandLV2);
    delete(FoodLandLV3);
    delete(FoodLandLV4);
    delete(FoodLandLV5);
    delete(FoodSeaLV1);
    delete(FoodSeaLV2);
    delete(FoodSeaLV3);
    delete(FoodMaxLV2);
    delete(FoodMaxLV3);
    delete(FoodMaxLV4);

    //bonus
    delete(BonusMoneyLV1);
    delete(BonusMoneyLV2);
    delete(BonusMoneyLV3);
    delete(BonusMoneyLV4);
    delete(BonusMaterialLV1);
    delete(BonusMaterialLV2);
    delete(BonusMaterialLV3);


    //animal
    delete(AnimalGrassLV1Normal);
    delete(AnimalGrassLV1Hungry);
    delete(AnimalGrassLV1Dead);
    delete(AnimalGrassLV2Normal);
    delete(AnimalGrassLV2Hungry);
    delete(AnimalGrassLV2Dead);
    delete(AnimalGrassLV3Normal);
    delete(AnimalGrassLV3Hungry);
    delete(AnimalGrassLV3Dead);
    delete(AnimalGrassLV4Normal);
    delete(AnimalGrassLV4Hungry);
    delete(AnimalGrassLV4Dead);

    delete(AnimalMeatSmallNormal);
    delete(AnimalMeatSmallHungry);
    delete(AnimalMeatSmallDead);

    delete(AnimalMeatBigNormal);
    delete(AnimalMeatBigHungry);
    delete(AnimalMeatBigDead);

    delete(AnimalMotherLV1Dead);
    delete(AnimalMotherLV1Hungry);
    delete(AnimalMotherLV1Normal);
    delete(AnimalMotherLV2Dead);
    delete(AnimalMotherLV2Hungry);
    delete(AnimalMotherLV2Normal);

    delete(AnimalMaterialLV1Dead);
    delete(AnimalMaterialLV1Hungry);
    delete(AnimalMaterialLV1Normal);
    delete(AnimalMaterialLV2Dead);
    delete(AnimalMaterialLV2Hungry);
    delete(AnimalMaterialLV2Normal);
    delete(AnimalMaterialLV3Dead);
    delete(AnimalMaterialLV3Hungry);
    delete(AnimalMaterialLV3Normal);

    delete(AnimalMaterialMotherDead);
    delete(AnimalMaterialMotherHungry);
    delete(AnimalMaterialMotherNormal);

    delete(AnimalKingDead);
    delete(AnimalKingHungry);
    delete(AnimalKingNormal);

    //enemies
    delete(EnemyBarbarian);
    delete(EnemyEater);
    delete(EnemyNativeWarrior);
    delete(EnemyNativeGunner);
    delete(EnemyNativeShaman);

    //armies
    delete(ArmyInfantryEngland);
    delete(ArmyInfantryFrance);
    delete(ArmyInfantrySpain);
    delete(ArmyLightEngland);
    delete(ArmyLightFrance);
    delete(ArmyLightSpain);
    delete(ArmyCalvaryEngland);
    delete(ArmyCalvaryFrance);
    delete(ArmyCalvarySpain);
    delete(ArmyGrenadierEngland);
    delete(ArmyGrenadierFrance);
    delete(ArmyGrenadierSpain);
    delete(ArmySpecialEngland);
    delete(ArmySpecialFrance);
    delete(ArmySpecialSpain);

    delete(StewardNormal);
    delete(StewardHide);


    //ammos
    delete(AmmoBullet);
    delete(AmmoBomb);


    //buildings
    delete(BuildingWallLV1);
    delete(BuildingWallLV2);
    delete(BuildingWallLV3);
    delete(BuildingWallLV4);

    delete(BuildingFarmLV1);
    delete(BuildingFarmLV2);
    delete(BuildingFarmLV3);
    delete(BuildingFarmLV4);

    delete(BuildingFactoryLV1);
    delete(BuildingFactoryLV2);
    delete(BuildingFactoryLV3);

    delete(BuildingMarket);
    delete(BuildingHarbor);
    delete(BuildingBarrack);
    delete(BuildingStable);
    delete(BuildingArsenal);


    //bgm
    delete(MainTheme);
    delete(GameTheme);

    //soundeffect
    delete(GunSound);
    delete(BombSound);
    delete(MeleeSound);


}


Resources* g_Resources;
