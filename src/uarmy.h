/*
Filename: UArmy.h
Description: the father class of all armies
Version: 2.0
Date: 09/08/2018
*/
#ifndef UARMY_H
#define UARMY_H

#include <QObject>
#include <QPixmap>
#include "uunit.h"
#include "constant.hpp"
#include "resources.h"
#include "globalfunctions.h"

class UArmy: public UUnit
{
    Q_OBJECT
public:
    //constants
    const double m_cWanderSpeedRatio{0.2};                      //The ratio between wander speed and full speed
    //What do not change in a game
    int m_Species;                                              //1:infantry 2:light 3:calvery 4:grenadier 5:special unit
    int m_Country;
    //What changes in a game
    bool m_WhetherCanAttack;
    int m_AttackType;                                           //type 1:ranged 2:melee

protected:
    //What do not change in a game
    int m_AttackDamage;                                         //The attack damage(including melee and ranged)
    int m_AttackThreshold;                                      //The attack point you need to perform an attack
    //What changes in a game                                    //the point you accumulate until next attack
    int m_AttackPoint;
signals:
    //the signal that shoots an ammo
    void m_AmmoShooted(int type, int damage, int place_x, int place_y, int final_x, int final_y);

public:

    /*
     * returns your attack damage
     * public interface, used to give your attack point when shooting an ammo ormanaging an attack
     */
    int m_PerformAttack();


    /*the public interface in managing ranged attack, an ammo will be shoot to the enemy
     * use:when the gunner shoot an ammo
     * variables:the place of enemy
     * */
    virtual void m_ShootAmmo(const int final_x, const int final_y){}


    /*the public interface in managing being attack
     * use:when the enemy is attacked
     * variables:the damage the enemy taken
     * */
    void m_BeingAttack(const int damage);


    /*function: animal go fast to attack, or prepare to shoot
     * use:when there are targets in sight
     * variables:final_x, final_y is the place of the nearest target, the army will go fast to its target
     * public interface, used in the mainloop to update army movement
    */
    void m_ChaseTarget(const int final_x, const int final_y);


    /*function: generate a random direction, and the army will go slowly in the direction
     * use:when there is no target in sight
     * public interface, used in the mainloop to update enemy movement
    */
    void m_Wander();


    /*oveeride the function of uunit
     * used to update army's health, death and attack
     * addon:some army need to update attack mode(melee or ranged)
     */
    virtual void m_UpdateStatus();


    /*
     * function that outputs the species, health ,attackvalue,place into a file
     * use: when saving a game file
     * variable: the file the game will be saved on
     * addon:some armies need to output ammo left
     */
    virtual void m_OutPut(QString file);
protected:
    void m_UpdateHealth();          //update health and death
    void m_UpdateAttack();          //update whether can attack
public:
    UArmy(){}
    ~UArmy(){}
};

#endif // UARMY_H
