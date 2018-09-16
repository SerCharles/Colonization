/*
Filename: GameCentralControl.h
Description: the central control of the game
Version: 1.1
Date: 09/04/2018
*/
#ifndef GAMECENTRALCONTROL_H
#define GAMECENTRALCONTROL_H
//system
#include <QObject>
#include <QList>
#include <QString>
#include <QtMultimedia/QSound>

#include "resources.h"
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


class GameWindow;
class GameCentralControl:public QObject
{
    friend class GameWindow;
    Q_OBJECT
      public:
        //constants
            //peace and war control
        const int m_cWarBeginThreshold{300};       //The min point to start a war
        const int m_cWarBeginPossibility{30};       //The possibility of starting a war
        const int m_cWarWarningTime{50};            //The min time of warning
        const int m_cWarReadyTime{300};             //The time between ready to war

            //start constants
        const int m_cFoodStart{500};
        const int m_cMaterialStart{500};
        const int m_cMoneyStart{1000};
        const int m_cBombDamageStart{50};

            //map restriction
        //animal start range
        const int m_cAnimalRangeMin_x{200};
        const int m_cAnimalRangeMax_x{900};
        const int m_cAnimalRangeMin_y{200};
        const int m_cAnimalRangeMax_y{600};

        //enemy start range
        const int m_cEnemyRangeMin_x{200};
        const int m_cEnemyRangeMax_x{1100};
        const int m_cEnemyRangeMin_y{200};
        const int m_cEnemyRangeMax_y{300};


        //army start range
        const int m_cArmyRangeMin_x{500};
        const int m_cArmyRangeMax_x{900};
        const int m_cArmyRangeMin_y{450};
        const int m_cArmyRangeMax_y{600};


        //interact range
        const int m_cMeleeInteractRange{20};     //The range of effective melee interact, such as melee attack and mouseclick;
        const int m_cMiddleInteractRange{200};   //The range of effective middle interact, such as infantry shooting;
        const int m_cRangedInteractRange{500};   //The range of effective ranged interact, such as finding food and ranged attack;
        const int m_cBombRangeBySpecies[4]{0,50,50,100};


        //eneny numbers per attack by the level of wall
        const int m_cEnemyBarbarianNumberByLevel[5]{1,2,3,4,0};
        const int m_cEnemyEaterNumberByLevel[5]{0,1,2,3,0};
        const int m_cEnemyNativeWarriorNumberByLevel[5]{0,0,1,2,0};
        const int m_cEnemyNativeGunnerNumberByLevel[5]{0,0,1,2,0};
        const int m_cEnemyNativeShamanNumberByLevel[5]{0,0,0,1,0};


        //buying price
        const int m_cAnimalGrassMoneyCost{100};
        const int m_cAnimalMaterialMoneyCost{200};
        const int m_cAnimalMeatSmallMoneyCost{1000};
        const int m_cAnimalMeatBigMoneyCost{10000};
        const int m_cAnimalMotherMoneyCost{200};
        const int m_cAnimalMaterialMotherMoneyCost{500};
        const int m_cAnimalKingMoneyCost{10000};
        const int m_cAnimalKingMaxNumber{1};


        //price of armies
        const int m_cArmyInfantryMoneyCost{200};
        const int m_cArmyInfantryMaterialCost{100};
        const int m_cArmyLightMoneyCost{200};
        const int m_cArmyLightMaterialCost{100};
        const int m_cArmyCalvaryMoneyCost{500};
        const int m_cArmyCalvaryMaterialCost{200};
        const int m_cArmyGrenadierMoneyCost{500};
        const int m_cArmyGrenadierMaterialCost{200};
        const int m_cArmySpecialMoneyCost{1000};
        const int m_cArmySpecialMaterialCost{300};
        const int m_cStewardMoneyCost{1000};


        //price of buildings
        const int m_cFoodLandLevelMax{5};
        const int m_cFoodSeaLevelMax{3};
        const int m_cFoodMaxNumberLevelMax{4};
        const int m_cFoodMaxNumberByLevel[5]{0,3,5,8,12};
        const int m_cFarmLevelMax{4};
        const int m_cFarmBuildingRequirement[5]{0,0,1,1,2};
        const int m_cFactoryLevelMax{3};
        const int m_cFactoryBuildingRequirement[4]{0,0,1,2};
        const int m_cMarketBuildingRequirement{1};
        const int m_cHarborBuildingRequirement{2};
        const int m_cBarrackBuildingRequirement{1};
        const int m_cStableBuildingRequirement{1};
        const int m_cArsenalBuildingRequirement{2};
        const int m_cWallLevelMax{4};

        const int m_cFoodLandUpgradeMoneyCostByLevel[5]{0,100,200,400,600};
        const int m_cFoodSeaUpgradeMoneyCostByLevel[3]{0,200,500};
        const int m_cFoodNumberUpgradeMoneyCostByLevel[4]{0,100,300,600};
        const int m_cFarmMoneyCostByLevel[5]{0,100,200,500,2000};
        const int m_cFarmMaterialCostByLevel[5]{0,0,0,0,0};
        const int m_cFarmFoodProduceByTurn[5]{0,1,2,3,5};
        const int m_cFactoryMoneyCostByLevel[4]{0,100,300,3000};
        const int m_cFactoryMaterialCostByLevel[4]{0,100,200,2000};
        const int m_cFactoryMaterialProduceByTurn[4]{0,1,2,5};
        const int m_cMarketMoneyCost{500};
        const int m_cMarketMaterialCost{300};
        const int m_cMarketBonus{50};
        const int m_cHarborMoneyCost{1000};
        const int m_cHarborMaterialCost{500};
        const int m_cHarborBonus{50};
        const int m_cBarrackMoneyCost{1000};
        const int m_cBarrackMaterialCost{500};
        const int m_cStableMoneyCost{3000};
        const int m_cStableMaterialCost{200};
        const int m_cArsenalMoneyCost{2000};
        const int m_cArsenalMaterialCost{2000};
        const int m_cWallMoneyCostByLevel[5]{0,200,2000,10000,30000};
        const int m_cWallMaterialCostByLevel[5]{0,200,2000,10000,30000};
        const int m_cWallFoodCostByLevel[5]{0,0,0,0,30000};

             //price of foods
        const int m_cFoodLandMoneyCostByLevel[6]{0,6,7,8,9,10};
        const int m_cFoodLandFoodCostByLevel[6]{0,6,7,8,9,10};
        const int m_cFoodSeaMoneyCostByLevel[4]{0,10,15,20};
        const int m_cFoodSeaFoodCostByLevel[4]{0,2,3,5};

        int m_AnimalKingNumbers;
      private:
        //What do not change in a game
        int m_Country;


        //What changes in a game
            //general state
        int m_WhetherIsPeace;   //0:war, 1:peace, -1:ready for war
        int m_WarTriggerPoint;  //accumulate the point to trigger war
        int m_WarReadyPoint;    //After War decleartion, accumulate the point to start the war
            //resources number
        int m_Food;
        int m_Material;
        int m_Money;
        int m_FoodMaxNumber;
        int m_BombDamage;
            //levels of buildings
        int m_FoodMaxNumberLevel;
        int m_FoodLandLevel;
        int m_FoodSeaLevel;
        int m_FarmLevel;
        int m_FactoryLevel;
        int m_MarketLevel;
        int m_HarborLevel;
        int m_WallLevel;
        int m_BarrackLevel;
        int m_StableLevel;
        int m_ArsenalLevel;

     private:
        //data list
        QList <UAnimal*>m_AnimalList;
        QList <UArmy*>m_ArmyList;
        QList <UEnemy*>m_EnemyList;
        QList <UFood*>m_FoodList;
        QList <UBonus*>m_BonusList;
        QList <UAmmo*>m_AmmoList;
        USteward* m_Steward;
     private:

        //manage T1 unit eat T2 unit
        template<class T1,class T2>
        void m_ManageEating(T1 eater, T2 pray)
        {
            int health_add;
            double hungry_add;
            //add things to eater
            pray -> m_GiveFood(&health_add, &hungry_add);
            eater ->m_EatFood (health_add, hungry_add);
            pray -> m_BeingEaten();
        }

        //manage T1 unit attack T2 unit
        template<class T1,class T2>
        void m_ManageAttack(T1 attacker, T2 victim)
        {
            int damage = attacker -> m_PerformAttack();
            victim -> m_BeingAttack(damage);
            g_Resources -> MeleeSound ->play();
        }

        //used in getting bonus, the central control obtains the value of bonus.
        //the variable is the place of the bonus you want to get in the BonusList
        void m_GetBonus(int bonus_place);


        //the functions for the seeker to find its target for ranged attacking or moving
        bool m_FindTarget(UAnimal* seeker);
        bool m_FindTarget(UEnemy* seeker);
        bool m_FindTarget(UArmy* seeker);
        bool m_FindTarget(USteward* seeker);
        bool m_FindShoot(UArmy* seeker);
        bool m_FindShoot(UEnemy* seeker);


        void m_ClearDeath();                                 //step 1 of the main turn:clear death
        void m_UpdateStatus();                               //step 2 of the main turn:update units' personal status
        void m_UpdateEating();                               //step 3 of the main turn:update eating activities
        void m_UpdateMovement();                             //step 4 of the main turn:update movement
        void m_UpdateAttacking();                            //step 5 of the main turn:update attack
        void m_UpdatePeaceWar();                             //step 6 of the main turn:update peace and war using rand()
        void m_UpdateBuilding();                             //the last step of the main turn:update the building level and update victory

     signals:
        //used for calling unit generating
        void m_FoodLandGenerated(int place_x, int place_y);
        void m_FoodSeaGenerated(int place_x, int place_y);
        void m_EnemyBarbarianGenerated();

        //show the war warning sign
        void m_ShowWarWarningSign(bool whether);

        //show the upgrade hint sign
        void m_ShowUpgradeHintSign(int level);

     public slots:
        //Generate Animals
        //no variable:press the button, and the animal will be generated in a random place
        //has variable:mother animal will produce on near itself, the variable is the new animal's born place
        void m_GenerateAnimalGrass();
        void m_GenerateAnimalGrass(const int place_x, const int place_y);
        void m_GenerateAnimalMaterial();
        void m_GenerateAnimalMaterial(const int place_x, const int place_y);
        void m_GenerateAnimalMeatSmall();
        void m_GenerateAnimalMeatBig();
        void m_GenerateAnimalMother();
        void m_GenerateAnimalMaterialMother();
        void m_GenerateAnimalKing();


        //generate enemies
        //no variable:generated randomly
        //has variable:switched from animal by enemy shaman, the variable is its born place
        void m_GenerateEnemyBarbarian();
        void m_GenerateEnemyBarbarian(const int place_x, const int place_y);
        void m_GenerateEnemyEater();
        void m_GenerateEnemyNativeWarrior();
        void m_GenerateEnemyNativeGunner();
        void m_GenerateEnemyNativeShaman();

        //generate armies
        void m_GenerateArmyInfantry();
        void m_GenerateArmyLight();
        void m_GenerateArmyCalvary();
        void m_GenerateArmyGrenadier();
        void m_GenerateArmySpecial();
        void m_GenerateSteward();

        //Generate Food at a certain place
        void m_GenerateFoodLand(const int place_x, const int place_y);
        void m_GenerateFoodSea(const int place_x, const int place_y);

        //Generate Bonus as a certain place
        //bonus_money and bonus_material is the level of the bonus
        void m_GenerateBonus(const int bonus_money, const int bonus_material, const int place_x, const int place_y);

        //Generate Ammo
        //type:1:army bullet   2:enemy bullet  3:bomb
        //place:start place of the ammo
        //final:final place of the ammo
        void m_GenerateAmmo
        (const int type, const int damage, const int place_x, const int place_y, const int final_x, const int final_y);


        //Upgrade Buildings
        void m_UpgradeFoodLand();       //upgrade food
        void m_UpgradeFoodSea();
        void m_UpgradeFoodMaxNumber();  //upgrade max food number
        void m_UpgradeFarm();
        void m_UpgradeFactory();
        void m_UpgradeMarket();
        void m_UpgradeHarbor();
        void m_UpgradeWall();
        void m_UpgradeBarrack();
        void m_UpgradeStable();
        void m_UpgradeArsenal();

        //handle ammo attack
        //place_x,place_y is the present place of the ammo
        void m_ExplodeAmmo(int type, int damage,int place_x, int place_y);
     protected:

        //generate enemies randomlu
        void m_GenerateEnemies();
     public:
        //build and destroy
        //start a new game
        GameCentralControl(const int country);

        //load a game from file
        GameCentralControl(const QString file);
        ~GameCentralControl();

        //output the information to a file to save the game
        void m_OutPut(QString file);
        friend class GameWindow;
};

#endif // GAMECENTRALCONTROL_H
