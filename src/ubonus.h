/*
Filename: UBonus.h
Description: the father class of bonuses, including two types
Version: 1.1
Date: 09/04/2018
*/
#ifndef UBONUS_H
#define UBONUS_H

#include <QObject>
#include "uunit.h"
#include "resources.h"

class UBonus: public UUnit
{
protected:
    //What do not change
    int m_Type;   //The type of bonus, including money(1) and material(2)
    int m_Level;  //The Level of bonus
    int m_BonusQuantity; //The Quantity of bonus
public:
    UBonus();
    ~UBonus(){}
public:

    /*
     *function:return the type and quantity of the bonus
     * public interface, used when the player or the steward get the bonus
     * variable: type and quantity will be the type and quantity of the bonus
     */
    void m_GiveBonus(int* type, int* quantity);

    //after the bonus is taken, it will be set invalid and be destroyed
    void m_BeingTaken();

    //override uunit function, output the information to save files
    virtual void m_OutPut(QString file);



    //override uunit function, different borders
    virtual void m_RepairOverBorder();

};

class UBonusMoney: public UBonus
{
protected:
    //Constants
    const int m_cLevelMax{4};     //4 levels, including bronze, silver, gold ,diamond
    const int m_cBonusQuantityByLevel[5]{0, 15, 35, 200 ,1000};

    //What do not change in a game
    QPixmap* m_PictureByLevel[5]
    {NULL, g_Resources->BonusMoneyLV1, g_Resources->BonusMoneyLV2, g_Resources->BonusMoneyLV3, g_Resources->BonusMoneyLV4};
public:
    UBonusMoney(const int level, const int place_x, const int place_y);
    ~UBonusMoney(){}

};

class UBonusMaterial: public UBonus
{
protected:
    //Constants
    const int m_cLevelMax{3};     //3 levels, including ore, ingot, plate
    const int m_cBonusQuantityByLevel[4]{0, 20, 40, 60};

    //what do not change in a game
    QPixmap* m_PictureByLevel[4]
    {NULL, g_Resources->BonusMaterialLV1, g_Resources->BonusMaterialLV2, g_Resources->BonusMaterialLV3};
public:
    UBonusMaterial(const int level, const int place_x, const int place_y);
    ~UBonusMaterial(){}

};

#endif // UBONUS_H
