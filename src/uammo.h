/*
Filename: UAmmo.h
Description: the father class of all Ammos
Version: 2.0
Date: 09/08/2018
*/
#ifndef UAMMO_H
#define UAMMO_H

#include <QObject>
#include <QPixmap>
#include "uunit.h"
#include "resources.h"

class UAmmo:public UUnit
{
    Q_OBJECT
public:
    //constants
    const double m_cSpeedBySpecies[4]{0,30,30,15};
    const double m_cWorkRange{30};
    const double m_cBombRangeBySpecies[4]{0,50,50,100};
    QPixmap* m_cPictureBySpecies[4]{NULL,g_Resources->AmmoBullet,g_Resources->AmmoBullet,g_Resources->AmmoBomb};
    int m_Species;                                                      //type: 1:friendly 2:enemy 3:cannon
protected:
    double m_Final_x, m_Final_y;                                        //destination
    int m_Damage;                                                       //damage
public:
    void m_UpdateStatus();   //move
    virtual void m_OutPut(QString file);                        //save file
signals:
    void m_AmmoExploded(int type, int damage,int place_x, int place_y);
public:
    UAmmo(const int type, const int damage, const int place_x, const int place_y, const int final_x, const int final_y);
    ~UAmmo(){}
};













#endif // UAMMO_H
