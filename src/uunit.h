/*
Filename: UUnit.h
Description: the father class of all units, including animals, enemies and army.
Version: 1.1
Date: 09/02/2018
*/
#ifndef UUNIT_H
#define UUNIT_H
#include <QObject>
#include <QString>
#include <QPixmap>
#include <ctime>

class UUnit: public QObject
{
    Q_OBJECT
protected:
    //What do not change in the game
    int m_HealthFull;              //Full Health
    QPixmap* m_PictureOriginal;     //Normal Picture
    double m_SpeedFull;                 //Full Speed


    //What change in the game
    int m_HealthNow;                                //Health in the game
    double m_SpeedNow;                              //current speed
    double m_Place_x, m_Place_y;                    //Place in the game

public:
    QPixmap* m_PictureShow;                         //Picture show in the game
    bool m_WhetherIsValid;                          //whether the unit is valid, controls unit delete

public:
    /*function: the unit instantly move a distance after being bombed
     * variable: move_x,move_y: the x and y component of the instant movement of the unit
     */
    void m_InstantMove(const double move_x, const double move_y);


    /*function: judge whether the unit is over border. if so, let it stay in the border
     * variable: move_x,move_y: the x and y component of the instant movement of the unit
     * addon: the border of bonuses and other units are different, so the function is overrided by UBonus
     */
    virtual void m_RepairOverBorder();


    /*function: the public interface to get the present place of a unit
     * variable: place_x, place_y will be the present place of the unit after the function
     */
    void m_GetPlace(double* place_x, double* place_y);


    /*function: the virtual function used to save files, overrided by the real classes
     * variable: the file you want to save in
     */
    virtual void m_OutPut(QString file){}


    /*the public interface of an unit, overrided by real classes
     *function: update the status of the unit(which occurs on itself only), such as hungry, death, produce, upgrade
     */
    virtual void m_UpdateStatus(){}

protected: 
    /*
     * function: the basic moving function of all units, the unit will move towards its final for a small distance in a turn
     * variable:final_x, final_y
     */
    void m_SeekRoute(const double final_x, const double final_y);

public:
    //empty construction and destruction
    UUnit():m_WhetherIsValid(1){}
    ~UUnit(){}
};
#endif // UUNIT_H

