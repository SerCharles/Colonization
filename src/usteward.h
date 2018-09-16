/*
Filename: USteward.h
Description: the father class of stewards
Version: 2.0
Date: 09/10/2018
*/

#ifndef USTEWARD_H
#define USTEWARD_H
#include <QObject>
#include <QPixmap>
#include "uunit.h"
#include "constant.hpp"
#include "resources.h"
#include "globalfunctions.h"


class USteward: public UUnit
{
    Q_OBJECT
public:
    //constants
    const double m_cSpeed{2};
    const double m_cWanderSpeedRatio{0.2};                      //The ratio between wander speed and full speed
    QPixmap* m_cPictureOriginal{g_Resources -> StewardNormal};
    QPixmap* m_cPictureHide{g_Resources -> StewardHide};
    QPixmap* m_PictureHide;
    //state
    bool m_WhetherIsActive;                                     //1:can go and get bonus; 0:war, stand still and do nothing
public:


    //chase after the nearest bonus when active, variables are destinations
    void m_ChaseTarget(const int final_x, const int final_y);

    //go randomly when there's no bonus
    void m_Wander();


    //update whether it is active and its picture
    virtual void m_UpdateStatus();

    //output when saving files
    virtual void m_OutPut(QString file);

    USteward(const double place_x, const double place_y);
    ~USteward(){}
};

#endif // USTEWARD_H
