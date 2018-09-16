/*
Filename: GameMainClass.h
Description: the main controller of the all the windows
Version: 1.0
Date: 09/02/2018
*/

#ifndef GAMEMAINCLASS_H
#define GAMEMAINCLASS_H


#include <QObject>
#include <QString>
#include <QtMultimedia/QSound>
#include "mainmenuwindow.h"
#include "countryselectionwindow.h"
#include "gamewindow.h"
#include "pausedialog.h"
#include "loadmenu.h"
#include "savemenu.h"
#include "loadingwindow.h"
#include "victorywindow.h"
#include "losewindow.h"
#include "resources.h"
#include "countryselectionbuttonmanager.hpp"



class GameMainClass:public QObject
{
    Q_OBJECT
public:
    //Game Windows
    MainMenuWindow* m_MainMenu;
    CountrySelectionWindow* m_CountrySelection;
    GameWindow* m_Game;
    PauseDialog* m_PauseDialog;
    LoadMenu* m_LoadMenu;
    SaveMenu* m_SaveMenu;
    LoadingWindow* m_LoadingWindow;
    VictoryWindow* m_Victory;
    LoseWindow* m_Lose;
    //bgm
    QSound* m_MainTheme{g_Resources -> MainTheme};
    QSound* m_GameTheme{g_Resources -> GameTheme};
    //Button managers
    CountrySelectionButtonManager* m_CountrySelectionManager;

    //construction and destruction
    GameMainClass();
    ~GameMainClass(){}
public slots:

    /*
        function:control game quitting
        if using the function, a messagebox will appear
      */
    void QuitGame();


    /*
        function:control game quitting to the main menu
        if using the function, a messagebox will appear
      */
    void QuitToMainMenu();



    /*
     function: start a game from loading file
     variable: loading file
     warning:the file must be valid, or the game will be crash
     valid file is what you save in the game, please do not change the file
     */
    void StartLoadedGame(QString file);
private:


    /*function: connect the signals and slots, to control all the windows's open, close, as well as bgm
     */
    void ConnectSignalSlot();
};



#endif // GAMEMAINCLASS_H
