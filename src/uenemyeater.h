/*
Filename: UEnemyEater.h
Description: the father class of eaters
Version: 2.0
Date: 09/08/2018
*/

#ifndef UENEMYEATER_H
#define UENEMYEATER_H


#include <QObject>
#include <QPixmap>
#include "constant.hpp"
#include "resources.h"
#include "globalfunctions.h"
#include "uunit.h"
#include "uenemy.h"


class UEnemyEater: public UEnemy
{
    Q_OBJECT
public:
    //constants
    const int m_cHealthFull{100};
    const double m_cSpeedFull{4};
    const int m_cMoneyProduce{3};
    const int m_cMaterialProduce{0};
    QPixmap* m_cPicture{g_Resources -> EnemyEater};
public:

    //override father class function, only need to manage eating
    void m_UpdateStatus();

    /*the public interface in managing eating, decrease the enemy's health and hungry point according to food
     * use:when the enemy eats something
     * variables:health_add and hungry_point_add of an animal or food
     * the enemy's health will decrease by a formula of health_add and hungry_point_add
     * */
    void m_EatFood(const int health_add, const double hungry_point_add);

    //construct a new one
    UEnemyEater(const int place_x, const int place_y);

    //construct a old one from loaded file
    UEnemyEater(const int health, const double place_x, const double place_y );
    ~UEnemyEater(){}

    /* override father class function
     * function that outputs the species, health ,place into a file
     * use: when saving a game file
     * variable: the file the game will be saved on
     */
    virtual void m_OutPut(QString file);

};

#endif // UENEMYEATER_H
