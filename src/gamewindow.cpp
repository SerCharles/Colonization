/*
Filename: GameWindow.cpp
Description: the window of the game
Version: 1.1
Date: 09/04/2018
*/
#include <QDebug>
#include <QtDebug>
#include <QFile>
#include <QLabel>
#include <QTextStream>
#include <QObject>
#include <QTimer>
#include <QString>
#include <QPainter>
#include <QPixmap>
#include <QPalette>
#include "constant.hpp"
#include "resources.h"
#include "globalfunctions.h"
#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "gamecentralcontrol.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    m_GameControl = NULL;
    m_GameTimer = NULL;
    connect(this, SIGNAL(m_GameStarted()), this, SLOT(GamePlay()));

    //background picture
        this->setAutoFillBackground(true);
        QPalette palette = this->palette();
        palette.setBrush(QPalette::Window,
                QBrush(g_Resources -> GamePicture -> scaled(
                    this->size(),
                    Qt::IgnoreAspectRatio,
                    Qt::SmoothTransformation)));
        this->setPalette(palette);
}

GameWindow::~GameWindow()
{
    delete ui;
}


void GameWindow::m_StartGame(int country)
{
    if(m_GameControl != NULL)
    {
        delete m_GameControl;
        m_GameControl = NULL;
    }
    m_GameControl = new GameCentralControl(country);
    this -> show();
    emit m_GameStarted();
}

void GameWindow::m_StartGame(QString file)
{
    //delete previous game
    if(m_GameControl != NULL)
    {
        delete m_GameControl;
        m_GameControl = NULL;
    }
    
    m_GameControl = new GameCentralControl(file);
    //start game
    this -> show();
    emit m_GameStarted();
}

void GameWindow::m_ContinueGame()
{
    m_WhetherGameIsOn = 1;
    qDebug()<<m_WhetherGameIsOn;
    emit m_GameContinued();
    m_GameTimer -> start();
}

void GameWindow::m_StopGame()
{
    if(m_GameTimer == NULL) 
    {
        return;
    }
    m_GameTimer -> stop();
    m_WhetherGameIsOn = 0;
    qDebug()<<m_WhetherGameIsOn;
}

void GameWindow::m_OutPutFile(QString file)
{
    m_GameControl -> m_OutPut(file);
}

//main turn of the game
void GameWindow::GamePlay()
{
    m_InitializeWidgets();   //initialize buttons and their signal,slots
    m_WhetherGameIsOn = 1;
    qDebug()<<m_WhetherGameIsOn;
    m_GameTimer = new QTimer();
    connect(m_GameTimer, SIGNAL(timeout()), this, SLOT(MainTurn()));      //main turn connected
    m_GameTimer -> start(20);
}

void GameWindow::MainTurn()
{
    //judge victory
    if(m_GameControl -> m_WallLevel == 4)
    {
        emit m_Victory();
    }
    else if(m_GameControl -> m_AnimalList.length() == 0 && m_GameControl -> m_Money < 100)
    {
        emit m_Lose();
    }
    m_GameControl -> m_ClearDeath();
    m_GameControl -> m_UpdateStatus();
    m_GameControl -> m_UpdateEating();
    m_GameControl -> m_UpdateMovement();
    m_GameControl -> m_UpdateAttacking();
    m_RefreshWidgets();
    repaint();
    m_GameControl -> m_UpdatePeaceWar();
    m_GameControl -> m_UpdateBuilding();
}

void GameWindow::m_InitializeWidgets()
{
    //set button icons
   {
    QString temp_money_string;
    ui -> Animal_Grass_Button -> setIcon(*(g_Resources -> AnimalGrassLV1Normal));
    temp_money_string = QString::number(m_GameControl -> m_cAnimalGrassMoneyCost, 10);
    ui -> Animal_Grass_Button ->setText(temp_money_string);

    ui -> Animal_Material_Button -> setIcon(*(g_Resources -> AnimalMaterialLV1Normal));
    temp_money_string = QString::number(m_GameControl -> m_cAnimalMaterialMoneyCost, 10);
    ui -> Animal_Material_Button ->setText(temp_money_string);

    ui -> Animal_Meat_Small_Button -> setIcon(*(g_Resources -> AnimalMeatSmallNormal));
    temp_money_string = QString::number(m_GameControl -> m_cAnimalMeatSmallMoneyCost, 10);
    ui -> Animal_Meat_Small_Button ->setText(temp_money_string);

    ui -> Animal_Meat_Big_Button -> setIcon(*(g_Resources -> AnimalMeatBigNormal));
    temp_money_string = QString::number(m_GameControl -> m_cAnimalMeatBigMoneyCost, 10);
    ui -> Animal_Meat_Big_Button ->setText(temp_money_string);

    ui -> Animal_Mother_Button -> setIcon(*(g_Resources -> AnimalMotherLV1Normal));
    temp_money_string = QString::number(m_GameControl -> m_cAnimalMotherMoneyCost, 10);
    ui -> Animal_Mother_Button ->setText(temp_money_string);

    ui -> Animal_Material_Mother_Button -> setIcon(*(g_Resources -> AnimalMaterialMotherNormal));
    temp_money_string = QString::number(m_GameControl -> m_cAnimalMaterialMotherMoneyCost, 10);
    ui -> Animal_Material_Mother_Button ->setText(temp_money_string);

    ui -> Animal_King_Button -> setIcon(*(g_Resources -> AnimalKingNormal));
    temp_money_string = QString::number(m_GameControl -> m_cAnimalKingMoneyCost, 10);
    ui -> Animal_King_Button ->setText(temp_money_string);

    ui -> Steward_Button -> setIcon(*(g_Resources -> StewardNormal));
    temp_money_string = QString::number(m_GameControl -> m_cStewardMoneyCost, 10);
    ui -> Steward_Button ->setText(temp_money_string);

    if(m_GameControl -> m_Country == 1)
    {
        ui -> Army_Infantry_Button -> setIcon(*(g_Resources -> ArmyInfantryEngland));
        ui -> Army_Light_Button -> setIcon(*(g_Resources -> ArmyLightEngland));
        ui -> Army_Calvary_Button -> setIcon(*(g_Resources -> ArmyCalvaryEngland));
        ui -> Army_Grenadier_Button -> setIcon(*(g_Resources -> ArmyGrenadierEngland));
        ui -> Army_Special_Button -> setIcon(*(g_Resources -> ArmySpecialEngland));
    }

    if(m_GameControl -> m_Country == 2)
    {
        ui -> Army_Infantry_Button -> setIcon(*(g_Resources -> ArmyInfantryFrance));
        ui -> Army_Light_Button -> setIcon(*(g_Resources -> ArmyLightFrance));
        ui -> Army_Calvary_Button -> setIcon(*(g_Resources -> ArmyCalvaryFrance));
        ui -> Army_Grenadier_Button -> setIcon(*(g_Resources -> ArmyGrenadierFrance));
        ui -> Army_Special_Button -> setIcon(*(g_Resources -> ArmySpecialFrance));
    }

    if(m_GameControl -> m_Country == 3)
    {
        ui -> Army_Infantry_Button -> setIcon(*(g_Resources -> ArmyInfantrySpain));
        ui -> Army_Light_Button -> setIcon(*(g_Resources -> ArmyLightSpain));
        ui -> Army_Calvary_Button -> setIcon(*(g_Resources -> ArmyCalvarySpain));
        ui -> Army_Grenadier_Button -> setIcon(*(g_Resources -> ArmyGrenadierSpain));
        ui -> Army_Special_Button -> setIcon(*(g_Resources -> ArmySpecialSpain));
    }

    ui -> War_Warning_Sign ->setIcon(*(g_Resources -> WarWarningIcon));
    ui -> War_Warning_Sign ->setVisible(0);
    ui -> CityAdvanceHint ->setVisible(0);
   }

    //set information icons and labels
   {
    ui -> Food_Picture -> setIcon(*(g_Resources -> FoodIcon));
    ui -> Money_Picture -> setIcon(*(g_Resources -> MoneyIcon));
    ui -> Material_Picture -> setIcon(*(g_Resources -> MaterialIcon));
    ui -> FoodLevel_Picture -> setIcon(*g_Resources -> FoodMaxIcon);
    ui -> CityLevel_Picture -> setIcon(*g_Resources -> CityIcon);
    ui -> War_Warning_Sign -> setIcon(*(g_Resources -> WarWarningIcon));
    QString temp_food_string = QString::number(m_GameControl -> m_Food, 10);
    ui -> Food_Label ->setText(temp_food_string);
    QString temp_money_string = QString::number(m_GameControl -> m_Money, 10);
    ui -> Money_Label ->setText(temp_money_string);
    QString temp_material_string = QString::number(m_GameControl -> m_Material, 10);
    ui -> Material_Label ->setText(temp_material_string);
   }

    //produce
  {
    //produce animals
    connect(ui->Animal_Grass_Button, SIGNAL(clicked()), m_GameControl, SLOT(m_GenerateAnimalGrass()));
    connect(ui->Animal_Material_Button, SIGNAL(clicked()), m_GameControl, SLOT(m_GenerateAnimalMaterial()));
    connect(ui->Animal_Meat_Small_Button, SIGNAL(clicked()), m_GameControl, SLOT(m_GenerateAnimalMeatSmall()));
    connect(ui->Animal_Meat_Big_Button, SIGNAL(clicked()), m_GameControl, SLOT(m_GenerateAnimalMeatBig()));
    connect(ui->Animal_Mother_Button, SIGNAL(clicked()), m_GameControl, SLOT(m_GenerateAnimalMother()));
    connect(ui->Animal_Material_Mother_Button, SIGNAL(clicked()), m_GameControl, SLOT(m_GenerateAnimalMaterialMother()));
    connect(ui->Animal_King_Button, SIGNAL(clicked()), m_GameControl, SLOT(m_GenerateAnimalKing()));

    //produce armies
    connect(ui->Army_Infantry_Button, SIGNAL(clicked()), m_GameControl, SLOT(m_GenerateArmyInfantry()));
    connect(ui->Army_Light_Button, SIGNAL(clicked()), m_GameControl, SLOT(m_GenerateArmyLight()));
    connect(ui->Army_Calvary_Button, SIGNAL(clicked()), m_GameControl, SLOT(m_GenerateArmyCalvary()));
    connect(ui->Army_Grenadier_Button, SIGNAL(clicked()), m_GameControl, SLOT(m_GenerateArmyGrenadier()));
    connect(ui->Army_Special_Button, SIGNAL(clicked()), m_GameControl, SLOT(m_GenerateArmySpecial()));
    connect(ui->Steward_Button, SIGNAL(clicked()), m_GameControl, SLOT(m_GenerateSteward()));


    connect(m_GameControl, SIGNAL(m_ShowWarWarningSign(bool)), ui->War_Warning_Sign, SLOT(setVisible(bool)));
    connect(m_GameControl, SIGNAL(m_ShowUpgradeHintSign(int)), this, SLOT(m_ShowUpgradeSign(int)));
    connect(this, SIGNAL(m_InvisibleUpgradeSign(bool)), ui -> CityAdvanceHint, SLOT(setVisible(bool)));
  }
    //upgrade
    connect(ui->Food_Sea_Button, SIGNAL(clicked()), m_GameControl, SLOT(m_UpgradeFoodSea()));
    connect(ui->Food_Land_Button, SIGNAL(clicked()), m_GameControl, SLOT(m_UpgradeFoodLand()));
    connect(ui->Food_Level_Button, SIGNAL(clicked()), m_GameControl, SLOT(m_UpgradeFoodMaxNumber()));
    connect(ui->Wall_Button, SIGNAL(clicked()), m_GameControl, SLOT(m_UpgradeWall()));
    connect(ui->Farm_Button, SIGNAL(clicked()), m_GameControl, SLOT(m_UpgradeFarm()));
    connect(ui->Factory_Button, SIGNAL(clicked()), m_GameControl, SLOT(m_UpgradeFactory()));
    connect(ui->Market_Button, SIGNAL(clicked()), m_GameControl, SLOT(m_UpgradeMarket()));
    connect(ui->Harbor_Button, SIGNAL(clicked()), m_GameControl, SLOT(m_UpgradeHarbor()));
    connect(ui->Barrack_Button, SIGNAL(clicked()), m_GameControl, SLOT(m_UpgradeBarrack()));
    connect(ui->Stable_Button, SIGNAL(clicked()), m_GameControl, SLOT(m_UpgradeStable()));
    connect(ui->Arsenal_Button, SIGNAL(clicked()), m_GameControl, SLOT(m_UpgradeArsenal()));
}

//the 6 step of the main turn:refresh buttons and labels
void GameWindow::m_RefreshWidgets()
{
    //button's picture and labels
  {
    if(m_GameControl -> m_FoodLandLevel == 1)
    {
        ui -> Food_Land_Button ->setIcon(*(g_Resources -> FoodLandLV2));
        QString temp_money_string = QString::number(m_GameControl -> m_cFoodLandUpgradeMoneyCostByLevel[1], 10);
        ui -> Food_Land_Button ->setText(temp_money_string);
    }
    if(m_GameControl -> m_FoodLandLevel == 2)
    {
        ui -> Food_Land_Button ->setIcon(*(g_Resources -> FoodLandLV3));
        QString temp_money_string = QString::number(m_GameControl -> m_cFoodLandUpgradeMoneyCostByLevel[2], 10);
        ui -> Food_Land_Button ->setText(temp_money_string);
    }
    if(m_GameControl -> m_FoodLandLevel == 3)
    {
        ui -> Food_Land_Button ->setIcon(*(g_Resources -> FoodLandLV4));
        QString temp_money_string = QString::number(m_GameControl -> m_cFoodLandUpgradeMoneyCostByLevel[3], 10);
        ui -> Food_Land_Button ->setText(temp_money_string);
    }
    if(m_GameControl -> m_FoodLandLevel == 4)
    {
        ui -> Food_Land_Button ->setIcon(*(g_Resources -> FoodLandLV5));
        QString temp_money_string = QString::number(m_GameControl -> m_cFoodLandUpgradeMoneyCostByLevel[4], 10);
        ui -> Food_Land_Button ->setText(temp_money_string);
    }
    if(m_GameControl -> m_FoodLandLevel == 5)
    {
        ui -> Food_Land_Button ->setIcon(*(g_Resources -> LevelMaxIcon));
        QString temp_money_string;
        ui -> Food_Land_Button ->setText(temp_money_string);
    }
    if(m_GameControl -> m_FoodSeaLevel == 1)
    {
        ui -> Food_Sea_Button ->setIcon(*(g_Resources -> FoodSeaLV2));
        QString temp_money_string = QString::number(m_GameControl -> m_cFoodSeaUpgradeMoneyCostByLevel[1], 10);
        ui -> Food_Sea_Button ->setText(temp_money_string);
    }
    if(m_GameControl -> m_FoodSeaLevel == 2)
    {
        ui -> Food_Sea_Button ->setIcon(*(g_Resources -> FoodSeaLV3));
        QString temp_money_string = QString::number(m_GameControl -> m_cFoodSeaUpgradeMoneyCostByLevel[2], 10);
        ui -> Food_Sea_Button ->setText(temp_money_string);
    }
    if(m_GameControl -> m_FoodSeaLevel == 3)
    {
        ui -> Food_Sea_Button ->setIcon(*(g_Resources -> LevelMaxIcon));
        QString temp_money_string;
        ui -> Food_Sea_Button ->setText(temp_money_string);
    }
    if(m_GameControl -> m_FoodMaxNumberLevel == 1)
    {
        ui -> Food_Level_Button ->setIcon(*(g_Resources -> FoodMaxLV2));
        QString temp_money_string = QString::number(m_GameControl -> m_cFoodNumberUpgradeMoneyCostByLevel[1], 10);
        ui -> Food_Level_Button ->setText(temp_money_string);
    }
    if(m_GameControl -> m_FoodMaxNumberLevel == 2)
    {
        ui -> Food_Level_Button ->setIcon(*(g_Resources -> FoodMaxLV3));
        QString temp_money_string = QString::number(m_GameControl -> m_cFoodNumberUpgradeMoneyCostByLevel[2], 10);
        ui -> Food_Level_Button ->setText(temp_money_string);
    }
    if(m_GameControl -> m_FoodMaxNumberLevel == 3)
    {
        ui -> Food_Level_Button ->setIcon(*(g_Resources -> FoodMaxLV4));
        QString temp_money_string = QString::number(m_GameControl -> m_cFoodNumberUpgradeMoneyCostByLevel[3], 10);
        ui -> Food_Level_Button ->setText(temp_money_string);
    }
    if(m_GameControl -> m_FoodMaxNumberLevel == 4)
    {
        ui -> Food_Level_Button ->setIcon(*(g_Resources -> LevelMaxIcon));
        QString temp_money_string;
        ui -> Food_Level_Button ->setText(temp_money_string);
    }
    if(m_GameControl -> m_WallLevel == 0)
    {
        ui -> Wall_Button ->setIcon(*(g_Resources -> BuildingWallLV1));
        ui -> CityLevel_Label -> setText("Village");
    }
    if(m_GameControl -> m_WallLevel == 1)
    {
        ui -> Wall_Button ->setIcon(*(g_Resources -> BuildingWallLV2));
        ui -> CityLevel_Label -> setText("Town");
        ui -> CityAdvanceHint -> setIcon(*(g_Resources -> TownAdvanceHint));
    }
    if(m_GameControl -> m_WallLevel == 2)
    {
        ui -> Wall_Button ->setIcon(*(g_Resources -> BuildingWallLV3));
        ui -> CityLevel_Label -> setText("Large Town");
        ui -> CityAdvanceHint -> setIcon(*(g_Resources -> LargeTownAdvanceHint));

    }
    if(m_GameControl -> m_WallLevel == 3)
    {
        ui -> Wall_Button ->setIcon(*(g_Resources -> BuildingWallLV4));
        ui -> CityLevel_Label -> setText("City");
        ui -> CityAdvanceHint -> setIcon(*(g_Resources -> CityAdvanceHint));

    }
    if(m_GameControl -> m_WallLevel == 4)
    {
        ui -> Wall_Button ->setIcon(*(g_Resources -> LevelMaxIcon));
    }

    if(m_GameControl -> m_FarmLevel == 0)
    {
        ui -> Farm_Button ->setIcon(*(g_Resources -> BuildingFarmLV1));
    }
    if(m_GameControl -> m_FarmLevel == 1)
    {
        ui -> Farm_Button ->setIcon(*(g_Resources -> BuildingFarmLV2));
    }
    if(m_GameControl -> m_FarmLevel == 2)
    {
        ui -> Farm_Button ->setIcon(*(g_Resources -> BuildingFarmLV3));
    }
    if(m_GameControl -> m_FarmLevel == 3)
    {
        ui -> Farm_Button ->setIcon(*(g_Resources -> BuildingFarmLV4));
    }
    if(m_GameControl -> m_FarmLevel == 4)
    {
        ui -> Farm_Button ->setIcon(*(g_Resources -> LevelMaxIcon));
    }

    if(m_GameControl -> m_FactoryLevel == 0)
    {
        ui -> Factory_Button ->setIcon(*(g_Resources -> BuildingFactoryLV1));
    }
    if(m_GameControl -> m_FactoryLevel == 1)
    {
        ui -> Factory_Button ->setIcon(*(g_Resources -> BuildingFactoryLV2));
    }
    if(m_GameControl -> m_FactoryLevel == 2)
    {
        ui -> Factory_Button ->setIcon(*(g_Resources -> BuildingFactoryLV3));
    }
    if(m_GameControl -> m_FactoryLevel == 3)
    {
        ui -> Factory_Button ->setIcon(*(g_Resources -> LevelMaxIcon));
    }
    if(m_GameControl -> m_MarketLevel == 0)
    {
        ui -> Market_Button ->setIcon(*(g_Resources -> BuildingMarket));
    }
    else
    {
        ui -> Market_Button ->setIcon(*(g_Resources -> LevelMaxIcon));
    }
    if(m_GameControl -> m_HarborLevel == 0)
    {
        ui -> Harbor_Button ->setIcon(*(g_Resources -> BuildingHarbor));
    }
    else
    {
        ui -> Harbor_Button ->setIcon(*(g_Resources -> LevelMaxIcon));
    }
    if(m_GameControl -> m_BarrackLevel == 0)
    {
        ui -> Barrack_Button ->setIcon(*(g_Resources -> BuildingBarrack));
    }
    else
    {
        ui -> Barrack_Button ->setIcon(*(g_Resources -> LevelMaxIcon));
    }
    if(m_GameControl -> m_StableLevel == 0)
    {
        ui -> Stable_Button ->setIcon(*(g_Resources -> BuildingStable));
    }
    else
    {
        ui -> Stable_Button ->setIcon(*(g_Resources -> LevelMaxIcon));
    }
    if(m_GameControl -> m_ArsenalLevel == 0)
    {
        ui -> Arsenal_Button ->setIcon(*(g_Resources -> BuildingArsenal));
    }
    else
    {
        ui -> Arsenal_Button ->setIcon(*(g_Resources -> LevelMaxIcon));
    }
  }

    //information label
  {
    QString temp_food_string = QString::number(m_GameControl -> m_Food, 10);
    ui -> Food_Label ->setText(temp_food_string);
    QString temp_money_string = QString::number(m_GameControl -> m_Money, 10);
    ui -> Money_Label ->setText(temp_money_string);
    QString temp_material_string = QString::number(m_GameControl -> m_Material, 10);
    ui -> Material_Label ->setText(temp_material_string);
    QString temp_foodlevel_string = QString::number(m_GameControl -> m_FoodMaxNumber, 10);
    ui -> FoodLevel_Label ->setText(temp_foodlevel_string);
  }

    //disable and enable buttons
    {
        //animal
        if(m_GameControl -> m_Money < m_GameControl -> m_cAnimalGrassMoneyCost)
        {
            ui -> Animal_Grass_Button -> setDisabled(1);
        }
        else
        {
            ui -> Animal_Grass_Button -> setEnabled(1);
        }

        if(m_GameControl -> m_Money < m_GameControl -> m_cAnimalMaterialMoneyCost || m_GameControl -> m_WallLevel < 1)
        {
            ui -> Animal_Material_Button -> setDisabled(1);
        }
        else
        {
            ui -> Animal_Material_Button -> setEnabled(1);
        }

        if(m_GameControl -> m_Money < m_GameControl -> m_cAnimalMeatSmallMoneyCost || m_GameControl -> m_WallLevel < 1)
        {
            ui -> Animal_Meat_Small_Button -> setDisabled(1);
        }
        else
        {
            ui -> Animal_Meat_Small_Button -> setEnabled(1);
        }

        if(m_GameControl -> m_Money < m_GameControl -> m_cAnimalMeatBigMoneyCost || m_GameControl -> m_WallLevel < 2)
        {
            ui -> Animal_Meat_Big_Button -> setDisabled(1);
        }
        else
        {
            ui->Animal_Meat_Big_Button -> setEnabled(1);
        }

        if(m_GameControl -> m_Money < m_GameControl -> m_cAnimalMotherMoneyCost || m_GameControl -> m_WallLevel < 1)
        {
            ui -> Animal_Mother_Button -> setDisabled(1);
        }
        else
        {
            ui -> Animal_Mother_Button -> setEnabled(1);
        }

        if(m_GameControl -> m_Money < m_GameControl -> m_cAnimalMaterialMotherMoneyCost || m_GameControl -> m_WallLevel < 1)
        {
            ui -> Animal_Material_Mother_Button -> setDisabled(1);
        }
        else
        {
            ui -> Animal_Material_Mother_Button -> setEnabled(1);
        }

        if(m_GameControl -> m_Money < m_GameControl -> m_cAnimalKingMoneyCost ||
                m_GameControl -> m_AnimalKingNumbers >= m_GameControl -> m_cAnimalKingMaxNumber || m_GameControl -> m_WallLevel < 3)
        {
            ui -> Animal_King_Button -> setDisabled(1);
        }
        else
        {
            ui -> Animal_King_Button -> setEnabled(1);
        }

        if(m_GameControl -> m_Money < m_GameControl -> m_cArmyInfantryMoneyCost ||
                m_GameControl -> m_Material < m_GameControl -> m_cArmyInfantryMaterialCost ||
                m_GameControl -> m_BarrackLevel < 1)
        {
            ui -> Army_Infantry_Button -> setDisabled(1);
        }
        else
        {
            ui -> Army_Infantry_Button -> setEnabled(1);
        }

        if(m_GameControl -> m_Money < m_GameControl -> m_cArmyLightMoneyCost ||
                m_GameControl -> m_Material < m_GameControl -> m_cArmyLightMaterialCost ||
                m_GameControl -> m_BarrackLevel < 1)
        {
            ui -> Army_Light_Button -> setDisabled(1);
        }
        else
        {
            ui -> Army_Light_Button -> setEnabled(1);
        }

        if(m_GameControl -> m_Money < m_GameControl -> m_cArmyCalvaryMoneyCost ||
                m_GameControl -> m_Material < m_GameControl -> m_cArmyCalvaryMaterialCost ||
                m_GameControl -> m_StableLevel < 1)
        {
            ui -> Army_Calvary_Button -> setDisabled(1);
        }
        else
        {
            ui -> Army_Calvary_Button -> setEnabled(1);
        }

        if(m_GameControl -> m_Money < m_GameControl -> m_cArmyGrenadierMoneyCost ||
                m_GameControl -> m_Material < m_GameControl -> m_cArmyGrenadierMaterialCost ||
                m_GameControl -> m_ArsenalLevel < 1)
        {
            ui -> Army_Grenadier_Button -> setDisabled(1);
        }
        else
        {
            ui -> Army_Grenadier_Button -> setEnabled(1);
        }

        if(m_GameControl -> m_Money < m_GameControl -> m_cArmySpecialMoneyCost ||
                m_GameControl -> m_Material < m_GameControl -> m_cArmySpecialMaterialCost ||
                m_GameControl -> m_WallLevel < 3)
        {
            ui -> Army_Special_Button -> setDisabled(1);
        }
        else
        {
            ui -> Army_Special_Button -> setEnabled(1);
        }

        if(m_GameControl -> m_Money < m_GameControl -> m_cStewardMoneyCost || m_GameControl -> m_Steward != NULL
                || m_GameControl -> m_WallLevel < 1)
        {
            ui -> Steward_Button -> setDisabled(1);
        }
        else
        {
            ui -> Steward_Button -> setEnabled(1);
        }


        //buildings
        if(m_GameControl -> m_FoodLandLevel == m_GameControl -> m_cFoodLandLevelMax
                || m_GameControl -> m_Money < m_GameControl -> m_cFoodLandUpgradeMoneyCostByLevel[m_GameControl -> m_FoodLandLevel])

        {
            ui -> Food_Land_Button -> setDisabled(1);
        }
        else
        {
            ui -> Food_Land_Button -> setEnabled(1);
        }

        if(m_GameControl -> m_FoodSeaLevel == m_GameControl -> m_cFoodSeaLevelMax
                ||m_GameControl -> m_Money < m_GameControl -> m_cFoodSeaUpgradeMoneyCostByLevel[m_GameControl -> m_FoodSeaLevel])
        {
            ui -> Food_Sea_Button -> setDisabled(1);
        }
        else
        {
            ui -> Food_Sea_Button -> setEnabled(1);
        }

        if(m_GameControl -> m_FoodMaxNumberLevel == m_GameControl -> m_cFoodMaxNumberLevelMax ||
                m_GameControl -> m_Money < m_GameControl -> m_cFoodNumberUpgradeMoneyCostByLevel[m_GameControl -> m_FoodMaxNumberLevel])

        {
            ui -> Food_Level_Button -> setDisabled(1);
        }
        else
        {
            ui -> Food_Level_Button -> setEnabled(1);
        }

        if(m_GameControl -> m_WallLevel == m_GameControl -> m_cWallLevelMax ||
                m_GameControl -> m_Money < m_GameControl -> m_cWallMoneyCostByLevel[m_GameControl -> m_WallLevel + 1]
                || m_GameControl -> m_Material < m_GameControl -> m_cWallMaterialCostByLevel[m_GameControl -> m_WallLevel + 1]
                || m_GameControl -> m_Food < m_GameControl -> m_cWallFoodCostByLevel[m_GameControl -> m_WallLevel + 1])
        {
            ui -> Wall_Button -> setDisabled(1);
        }
        else
        {
            ui -> Wall_Button -> setEnabled(1);
        }

        if(m_GameControl -> m_FarmLevel == m_GameControl -> m_cFarmLevelMax ||
                m_GameControl -> m_Money < m_GameControl -> m_cFarmMoneyCostByLevel[m_GameControl -> m_FarmLevel + 1]
                || m_GameControl -> m_Material < m_GameControl -> m_cFarmMaterialCostByLevel[m_GameControl -> m_FarmLevel + 1]
                || m_GameControl -> m_WallLevel < m_GameControl -> m_cFarmBuildingRequirement[m_GameControl -> m_FarmLevel + 1])
        {
            ui -> Farm_Button -> setDisabled(1);
        }
        else
        {
            ui -> Farm_Button -> setEnabled(1);
        }

        if(m_GameControl -> m_FactoryLevel == m_GameControl -> m_cFactoryLevelMax ||
                m_GameControl -> m_Money < m_GameControl -> m_cFactoryMoneyCostByLevel[m_GameControl -> m_FactoryLevel + 1]
                || m_GameControl -> m_Material < m_GameControl -> m_cFactoryMaterialCostByLevel[m_GameControl -> m_FactoryLevel + 1]
                || m_GameControl -> m_WallLevel < m_GameControl -> m_cFactoryBuildingRequirement[m_GameControl -> m_FactoryLevel + 1])
        {
            ui -> Factory_Button -> setDisabled(1);
        }
        else
        {
            ui -> Factory_Button -> setEnabled(1);
        }

        if(m_GameControl -> m_MarketLevel == 1 ||
                m_GameControl -> m_Money < m_GameControl -> m_cMarketMoneyCost
                || m_GameControl -> m_Material < m_GameControl -> m_cMarketMaterialCost
                || m_GameControl -> m_WallLevel < m_GameControl -> m_cMarketBuildingRequirement)
        {
            ui -> Market_Button -> setDisabled(1);
        }
        else
        {
            ui -> Market_Button -> setEnabled(1);
        }

        if(m_GameControl -> m_HarborLevel == 1 ||
                m_GameControl -> m_Money < m_GameControl -> m_cHarborMoneyCost
                || m_GameControl -> m_Material < m_GameControl -> m_cHarborMaterialCost
                || m_GameControl -> m_WallLevel < m_GameControl -> m_cHarborBuildingRequirement)
        {
            ui -> Harbor_Button -> setDisabled(1);
        }
        else
        {
            ui -> Harbor_Button -> setEnabled(1);
        }

        if(m_GameControl -> m_BarrackLevel == 1 ||
                m_GameControl -> m_Money < m_GameControl -> m_cBarrackMoneyCost
                || m_GameControl -> m_Material < m_GameControl -> m_cBarrackMaterialCost
                || m_GameControl -> m_WallLevel < m_GameControl -> m_cBarrackBuildingRequirement)
        {
            ui -> Barrack_Button -> setDisabled(1);
        }
        else
        {
            ui -> Barrack_Button -> setEnabled(1);
        }

        if(m_GameControl -> m_StableLevel == 1 ||
                m_GameControl -> m_Money < m_GameControl -> m_cStableMoneyCost
                || m_GameControl -> m_Material < m_GameControl -> m_cStableMaterialCost
                || m_GameControl -> m_WallLevel < m_GameControl -> m_cStableBuildingRequirement)
        {
            ui -> Stable_Button -> setDisabled(1);
        }
        else
        {
            ui -> Stable_Button -> setEnabled(1);
        }

        if(m_GameControl -> m_ArsenalLevel == 1 ||
                m_GameControl -> m_Money < m_GameControl -> m_cArsenalMoneyCost
                || m_GameControl -> m_Material < m_GameControl -> m_cArsenalMaterialCost
                || m_GameControl -> m_WallLevel < m_GameControl -> m_cArsenalBuildingRequirement)
        {
            ui -> Arsenal_Button -> setDisabled(1);
        }
        else
        {
            ui -> Arsenal_Button -> setEnabled(1);
        }
    }
}

void GameWindow::m_ShowUpgradeSign(int level)
{
    if(level == 1)
    {
        ui -> CityAdvanceHint -> setIcon(*(g_Resources -> TownAdvanceHint));
    }
    if(level == 2)
    {
        ui -> CityAdvanceHint -> setIcon(*(g_Resources -> LargeTownAdvanceHint));      
    }
    if(level == 3)
    {
        ui -> CityAdvanceHint -> setIcon(*(g_Resources -> CityAdvanceHint));
    }
    ui -> CityAdvanceHint -> setVisible(1);
    m_UpgradeSignTimer = new QTimer();
    m_UpgradeSignTimer -> singleShot(m_GameControl -> m_cWarWarningTime * 20, this, SLOT(m_SetUpgradeSignInvisible()));
}

void GameWindow::m_SetUpgradeSignInvisible()
{
    emit m_InvisibleUpgradeSign(0);
}



//handle keyboard event in the game
void GameWindow::keyPressEvent(QKeyEvent *event)
{
    if(event -> key() == Qt::Key_Escape)
    {
        if(m_WhetherGameIsOn == 1)
        {
            m_GameTimer -> stop();
            m_WhetherGameIsOn = 0;
            qDebug()<<m_WhetherGameIsOn;

            emit m_GamePaused();
        }
    }
}

//handle mouse press in the game
void GameWindow::mousePressEvent(QMouseEvent *event)
{
    int place_x = event -> x();
    int place_y = event -> y();
    if(place_x < Constant::g_BorderMin_x - Constant::g_RadiusMediumObject || place_x > Constant::g_BorderMax_x + Constant::g_RadiusMediumObject ||
            place_y < Constant::g_BorderMin_x - Constant::g_RadiusMediumObject || place_y > Constant::g_BorderMax_y + Constant::g_RadiusMediumObject)
    {
        return;
    }

    bool whether_get_bonus = 0;
    for(int i = 0; i < m_GameControl -> m_BonusList.length(); i++)
    {
        double temp_distance = g_GetDistance(place_x, place_y, m_GameControl -> m_BonusList[i]);
        //get bonus
        if(temp_distance <= m_GameControl -> m_cMeleeInteractRange)
        {
            whether_get_bonus = 1;
            m_GameControl -> m_GetBonus(i);
        }
    }

    //bomb enemy
    bool whether_bomb_enemy = 0;
    for(int i = 0; i < m_GameControl -> m_EnemyList.length(); i++)
    {
        if(m_GameControl ->m_EnemyList[i] -> m_Species == 1) //bomb barbarian
        {
            double temp_distance = g_GetDistance(place_x, place_y, m_GameControl -> m_EnemyList[i]);
            if(temp_distance <= 2 * (m_GameControl -> m_cMeleeInteractRange))
            {
                whether_bomb_enemy = 1;
                m_GameControl -> m_GenerateAmmo(3,m_GameControl -> m_BombDamage, place_x, place_y, place_x, place_y);
            }
        }
    }

    //no bonus: put food, left:land ,right:sea
    if(whether_get_bonus == 0 && whether_bomb_enemy == 0)
    {
        if( event -> button() == Qt::LeftButton)
        {
            m_GameControl -> m_GenerateFoodLand(place_x, place_y);
        }
        else
        {
            m_GameControl -> m_GenerateFoodSea(place_x, place_y);
        }
    }
}


//painting
void GameWindow::paintEvent(QPaintEvent *event)
{
    //todo:background
    for(int i = 0; i < m_GameControl -> m_AnimalList.length(); i ++)
    {
        QPainter p(this);
        double place_x, place_y;
        m_GameControl -> m_AnimalList[i] ->m_GetPlace(&place_x, &place_y);

        p.drawPixmap(int(place_x - Constant::g_RadiusMediumObject), int(place_y - Constant::g_RadiusMediumObject),
                     *m_GameControl -> m_AnimalList[i] -> m_PictureShow);
    }

    for(int i = 0; i < m_GameControl -> m_ArmyList.length(); i ++)
    {
        QPainter p(this);
        double place_x, place_y;
        m_GameControl -> m_ArmyList[i] ->m_GetPlace(&place_x, &place_y);

        p.drawPixmap(int(place_x - Constant::g_RadiusMediumObject), int(place_y - Constant::g_RadiusMediumObject),
                     *m_GameControl -> m_ArmyList[i] -> m_PictureShow);
    }

    for(int i = 0; i < m_GameControl -> m_EnemyList.length(); i ++)
    {
        QPainter p(this);
        double place_x, place_y;
        m_GameControl -> m_EnemyList[i] ->m_GetPlace(&place_x, &place_y);

        p.drawPixmap(int(place_x - Constant::g_RadiusMediumObject), int(place_y - Constant::g_RadiusMediumObject),
                     *m_GameControl -> m_EnemyList[i] -> m_PictureShow);
    }

    for(int i = 0; i < m_GameControl -> m_FoodList.length(); i ++)
    {
        QPainter p(this);
        double place_x, place_y;
        m_GameControl -> m_FoodList[i] ->m_GetPlace(&place_x, &place_y);
        p.drawPixmap(int(place_x - Constant::g_RadiusSmallObject), int(place_y - Constant::g_RadiusSmallObject),
                     *m_GameControl -> m_FoodList[i] -> m_PictureShow);
    }
    for(int i = 0; i < m_GameControl -> m_BonusList.length(); i ++)
    {
        QPainter p(this);
        double place_x, place_y;
        m_GameControl -> m_BonusList[i] ->m_GetPlace(&place_x, &place_y);
        p.drawPixmap(int(place_x - Constant::g_RadiusMediumObject), int(place_y - Constant::g_RadiusMediumObject),
                     *m_GameControl -> m_BonusList[i] -> m_PictureShow);
    }

    for(int i = 0; i < m_GameControl -> m_AmmoList.length(); i ++)
    {
        QPainter p(this);
        double place_x, place_y;
        m_GameControl -> m_AmmoList[i] ->m_GetPlace(&place_x, &place_y);
        if(m_GameControl -> m_AmmoList[i] -> m_Species <= 2)
        {
            p.drawPixmap(int(place_x - Constant::g_RadiusVerySmallObject), int(place_y - Constant::g_RadiusVerySmallObject),
                     *m_GameControl -> m_AmmoList[i] -> m_PictureShow);
        }
        else
        {
            p.drawPixmap(int(place_x - Constant::g_RadiusSmallObject), int(place_y - Constant::g_RadiusSmallObject),
                     *m_GameControl -> m_AmmoList[i] -> m_PictureShow);
        }
    }
    if(m_GameControl -> m_Steward != NULL)
    {
        QPainter p(this);
        double place_x, place_y;
        m_GameControl -> m_Steward ->m_GetPlace(&place_x, &place_y);
            p.drawPixmap(int(place_x - Constant::g_RadiusMediumObject), int(place_y - Constant::g_RadiusMediumObject),
                     *m_GameControl -> m_Steward -> m_PictureShow);
    }
}
