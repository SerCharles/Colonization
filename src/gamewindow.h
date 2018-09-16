/*
Filename: GameWindow.h
Description: the window of the game
Version: 1.1
Date: 09/04/2018
*/

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QString>

#include "gamecentralcontrol.h"



class GameMainClass;
namespace Ui{
class GameWindow;
}

class GameWindow : public QMainWindow
{
    friend class GameMainClass;
    Q_OBJECT
public:
    //initialize ui and background
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

    //manage mousepress event to obtain bonus and attack enemies
    void mousePressEvent(QMouseEvent *event);

    //manage repaint event to paint units
    void paintEvent(QPaintEvent *event);

    //manage keypress event(only esc) to manage pause
    void keyPressEvent(QKeyEvent *event);
private:
    Ui::GameWindow *ui;
    GameCentralControl *m_GameControl;  //central control
    QTimer* m_GameTimer;                // the timer used for main loop
    QTimer* m_UpgradeSignTimer;         //the timer used to manage the stop of upgrade sign
    bool m_WhetherGameIsOn;             //1:game on  2:paused
public slots:

    //rebuild the central control
    //1:rebuild a new central control
    //2:rebuild a central control from loaded file
    void m_StartGame(int country);
    void m_StartGame(QString file);


    //start the main turn
    void GamePlay();


    //the mainturn. shutting down the qtimer to stop the game mainturn
    //refreshing the units, manage interactions between units
    void MainTurn();


    //after the pause menu shutted, restart the timer to restart the game
    void m_ContinueGame();

    //stop the timer to pause the game
    void m_StopGame();


    //output all the information of the central control and all the units, variable is the file you want to output
    void m_OutPutFile(QString file);


    //show the sign that the city has just upgraded. unshow it later.
    void m_ShowUpgradeSign(int level);
    void m_SetUpgradeSignInvisible();
signals:
    void m_GameStarted();
    void m_GamePaused();
    void m_GameContinued();
    void m_Victory();
    void m_Lose();
    void m_InvisibleUpgradeSign(bool whether);
private:

    //initialize the buttons and labels, connect signals and slots before the main loop
    void m_InitializeWidgets();


    //refresh widgets: update label show, button pictures and enable/disable buttons
    void m_RefreshWidgets();


};

#endif // GAMEWINDOW_H
