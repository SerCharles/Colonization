/*
Filename: UEnemy.h
Description: the father class of all enemies
Version: 2.0
Date: 09/07/2018
*/

#ifndef UENEMY_H
#define UENEMY_H

#include <QObject>
#include <QPixmap>
#include "uunit.h"
#include "constant.hpp"
#include "resources.h"
#include "globalfunctions.h"

class UEnemy: public UUnit
{
    Q_OBJECT
public:
    //constants
    const int m_cMeleeAttackSpan{50};                           //The time between each melee attack
    const int m_cRangedAttackSpan{300};                         //The time between each ranged attack
    const double m_cWanderSpeedRatio{0.2};                      //The ratio between wander speed and full speed

    //What do not change in a game
    int m_Species;                                              //1:barbarian 2:eater 3:warrior 4:gunner 5:shaman

    //What changes in a game
    bool m_WhetherCanAttack;
    
protected:
    //What do not change in a game
    int m_AttackDamage;                                         //The attack damage(including melee and ranged)
    int m_AttackThreshold;                                      //The attack point you need to perform an attack

    //What changes in a game
    int m_AttackPoint;                                          //the point you accumulate until next attack
    int m_MoneyProduce;                                         //money produce after death;
    int m_MaterialProduce;                                      //material produce after death;
signals:

    //shoot an ammo
    void m_AmmoShooted(int type, int damage, int place_x, int place_y, int final_x, int final_y);
    //produce bonus after death
    void m_BonusProduced(const int money_produce, const int material_produce, const int place_x,const int place_y);

protected:
    void m_UpdateHealth();                                      //Update health and death
    void m_UpdateAttack();                                      //Update whether you can attack
public:

    /*virtual function
     * returns your attack damage
     * public interface, used to give your attack point when shooting an ammo ormanaging an attack
     */
    virtual int m_PerformAttack(){return 0;}



    /*the public interface in managing being attack
     * use:when the enemy is attacked
     * variables:the damage the enemy taken
     * */
    void m_BeingAttack(const int damage);


    /*function: animal go fast to attack, or prepare to shoot
     * use:when there are targets in sight
     * variables:final_x, final_y is the place of the nearest target, the enemy will go fast to its target
     * public interface, used in the mainloop to update enemy movement
    */
    void m_ChaseTarget(const int final_x, const int final_y);



    /*function: generate a random direction, and the enemy will go slowly in the direction
     * use:when there is no target in sight
     * public interface, used in the mainloop to update enemy movement
    */
    void m_Wander();


    /*oveeride the function of uunit
     * used to update enemy's health, death and attack
     */
    virtual void m_UpdateStatus();

    /*
     * function that outputs the species, health ,attackvalue,place into a file
     * use: when saving a game file
     * variable: the file the game will be saved on
     */
    virtual void m_OutPut(QString file);

    /*the public interface in managing eating
     * use:when the enemy eater eats something
     * variables:health_add and hungry_point_add is the decrement of the enemy's health after eating something,
     * which is relevant to the animal/food's health_add and hungry_point_add
     * addon: uenemyeater do not need to output their attackpoint
     * */
    virtual void m_EatFood(const int health_add, const double hungry_point_add){}


    /*the public interface in managing ranged attack, an ammo will be shoot to the enemy
     * use:when the enemy gunner shoot an ammo
     * variables:the place of enemy
     * */
    virtual void m_ShootAmmo(const int final_x, const int final_y){}

public:
    UEnemy(){}
    ~UEnemy(){}
};

#endif // UENEMY_H
