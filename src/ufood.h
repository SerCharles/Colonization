/*
Filename: UFood.h
Description: the father class of all food
Version: 1.1
Date: 09/02/2018
*/

#ifndef UFOOD_H
#define UFOOD_H
#include <QObject>
#include <QPixmap>
#include "uunit.h"
#include "resources.h"

class UFood:public UUnit
{
    Q_OBJECT
    protected:
        //What do not change in a game
        int m_Species;      //Type of food's species,1 is land, 2 is sea
        int m_HealthAdd;    //health increment after eatting it
        double m_HungryPointAdd; //HungryPoint after eatting it
        int m_Level;
    public:

        //the public interface, manage the food's goingdown
        void m_MoveDown();

        //after the food is eater, set it invalid
        void m_BeingEaten();

        //health_add and hungry_add will be the food's health_add and hungry_add
        //return the food's values
        //used when the food is eaten
        void m_GiveFood(int* health_add, double* hungry_add);

        //used to save file
        virtual void m_OutPut(QString file);
    public:
        UFood();
        ~UFood(){}

};


class UFoodLand:public UFood
{
    Q_OBJECT
    protected:
        //Constants by level
        const int m_cLevelMax{5};
        const int m_cHealthAddByLevel[6]{0,10,13,16,20,25};
        const double m_cHungryPointAddByLevel[6]{0,0.1,0.2,0.3,0.4,0.6};


        //Things do not change in a game
        QPixmap* m_PictureByLevel[6]
        {NULL, g_Resources->FoodLandLV1, g_Resources->FoodLandLV2, g_Resources->FoodLandLV3, g_Resources->FoodLandLV4, g_Resources->FoodLandLV5};
    public:
        UFoodLand(const int level, const int place_x, const int place_y);
        ~UFoodLand(){}

};

class UFoodSea:public UFood
{
    Q_OBJECT
    protected:
        //Constants by level
        const int m_cLevelMax{3};
        const int m_cHealthAddByLevel[4]{0,40,60,100};
        const double m_cHungryPointAddByLevel[4]{0,0.2,0.3,0.5};
        const double m_cSpeedByLevel[4]{0,0.5,0.25,1};


        //Things do not change in a game
        QPixmap* m_PictureByLevel[4]
        {NULL, g_Resources->FoodSeaLV1, g_Resources->FoodSeaLV2, g_Resources->FoodSeaLV3};
    public:
        UFoodSea(const int level, const int place_x, const int place_y);
        ~UFoodSea(){}

};


#endif // UFOOD_H
