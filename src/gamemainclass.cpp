#include <QObject>
#include <QMessageBox>
#include <QString>
#include <QtMultimedia/QSound>
#include "mainmenuwindow.h"
#include "ui_mainmenuwindow.h"
#include "countryselectionwindow.h"
#include "ui_countryselectionwindow.h"
#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "pausedialog.h"
#include "ui_pausedialog.h"
#include "loadmenu.h"
#include "ui_loadmenu.h"
#include "savemenu.h"
#include "ui_savemenu.h"
#include "loadingwindow.h"
#include "ui_loadingwindow.h"
#include "victorywindow.h"
#include "ui_victorywindow.h"
#include "losewindow.h"
#include "ui_losewindow.h"


#include "countryselectionbuttonmanager.hpp"

#include "gamemainclass.h"


GameMainClass::GameMainClass()
{
    //Construct Windows
    m_MainMenu = new MainMenuWindow();
    m_CountrySelection = new CountrySelectionWindow();
    m_Game = new GameWindow();
    m_PauseDialog = new PauseDialog();
    m_LoadMenu = new LoadMenu();
    m_SaveMenu = new SaveMenu();
    m_LoadingWindow = new LoadingWindow();
    m_Victory = new VictoryWindow();
    m_Lose = new LoseWindow();

    //managers
    m_CountrySelectionManager = new CountrySelectionButtonManager();

    //bgm
    m_MainTheme -> play();

    ConnectSignalSlot();
    m_MainMenu->show();
}

void GameMainClass::ConnectSignalSlot()
{
    // main menu buttons
    connect(m_MainMenu->ui->Quit_Button, SIGNAL(clicked()), this, SLOT(QuitGame()));
    connect(m_MainMenu->ui->Start_Button, SIGNAL(clicked()), m_MainMenu, SLOT(close()));
    connect(m_MainMenu->ui->Start_Button, SIGNAL(clicked()), m_CountrySelection, SLOT(show()));
    connect(m_MainMenu->ui->Load_Button, SIGNAL(clicked()), m_LoadMenu, SLOT(show()));

    //country selection and loading
    connect(m_CountrySelection->ui->England_Button, SIGNAL(clicked()), m_CountrySelectionManager, SLOT(ClickedEngland()));
    connect(m_CountrySelection->ui->France_Button, SIGNAL(clicked()), m_CountrySelectionManager, SLOT(ClickedFrance()));
    connect(m_CountrySelection->ui->Spain_Button, SIGNAL(clicked()), m_CountrySelectionManager, SLOT(ClickedPrussia()));

    connect(m_CountrySelectionManager, SIGNAL(OpenGameWithCountry(int)), m_LoadingWindow, SLOT(show()));
    connect(m_CountrySelectionManager, SIGNAL(OpenGameWithCountry(int)), m_LoadingWindow, SLOT(m_Loading(int)));
    connect(m_CountrySelectionManager, SIGNAL(OpenGameWithCountry(int)), m_MainTheme, SLOT(stop()));

    connect(m_LoadingWindow, SIGNAL(m_LoadingFinished(int)), m_Game, SLOT(m_StartGame(int)));
    connect(m_LoadingWindow, SIGNAL(m_LoadingFinished(int)), m_GameTheme, SLOT(play()));
    connect(m_LoadingWindow, SIGNAL(m_LoadingFinished(int)), m_LoadingWindow, SLOT(close()));
    connect(m_LoadingWindow, SIGNAL(m_LoadingFinished(QString)), m_Game, SLOT(m_StartGame(QString)));
    connect(m_LoadingWindow, SIGNAL(m_LoadingFinished(QString)), m_GameTheme, SLOT(play()));
    connect(m_LoadingWindow, SIGNAL(m_LoadingFinished(QString)), m_LoadingWindow, SLOT(close()));

    connect(m_CountrySelection->ui->England_Button, SIGNAL(clicked()), m_CountrySelection, SLOT(close()));
    connect(m_CountrySelection->ui->France_Button, SIGNAL(clicked()), m_CountrySelection, SLOT(close()));
    connect(m_CountrySelection->ui->Spain_Button, SIGNAL(clicked()), m_CountrySelection, SLOT(close()));
    
    //game and pause
    connect(m_Game, SIGNAL(m_GamePaused()), m_PauseDialog, SLOT(show()));
    connect(m_Game, SIGNAL(m_GameContinued()), m_PauseDialog, SLOT(close()));

    connect(m_PauseDialog->ui->Continue_Button, SIGNAL(clicked()), m_PauseDialog, SLOT(close()));
    connect(m_PauseDialog, SIGNAL(rejected()), m_Game, SLOT(m_ContinueGame()));
    connect(m_PauseDialog->ui->Quit_MainMenu_Button, SIGNAL(clicked()), this, SLOT(QuitToMainMenu()));
    connect(m_PauseDialog->ui->Quit_Button, SIGNAL(clicked()), this, SLOT(QuitGame()));
    connect(m_PauseDialog->ui->Load_Button, SIGNAL(clicked()), m_LoadMenu, SLOT(show()));
    connect(m_PauseDialog->ui->Save_Button, SIGNAL(clicked()), m_SaveMenu, SLOT(show()));

    //win and lose
    connect(m_Game, SIGNAL(m_Victory()), m_Victory, SLOT(show()));
    connect(m_Game, SIGNAL(m_Victory()), m_Game, SLOT(close()));
    connect(m_Game, SIGNAL(m_Victory()), m_Game, SLOT(m_StopGame()));
    connect(m_Game, SIGNAL(m_Victory()), m_GameTheme, SLOT(stop()));
    connect(m_Game, SIGNAL(m_Lose()), m_Lose, SLOT(show()));
    connect(m_Game, SIGNAL(m_Lose()), m_Game, SLOT(close()));
    connect(m_Game, SIGNAL(m_Lose()), m_Game, SLOT(m_StopGame()));
    connect(m_Game, SIGNAL(m_Lose()), m_GameTheme, SLOT(stop()));

    connect(m_Victory -> ui ->Back_Button, SIGNAL(clicked()), this, SLOT(QuitToMainMenu()));
    connect(m_Victory -> ui ->Restart_Button, SIGNAL(clicked()), m_Victory, SLOT(close()));
    connect(m_Victory -> ui ->Restart_Button, SIGNAL(clicked()), m_CountrySelection, SLOT(show()));

    connect(m_Lose -> ui ->Back_Button, SIGNAL(clicked()), this, SLOT(QuitToMainMenu()));
    connect(m_Lose -> ui ->Restart_Button, SIGNAL(clicked()), m_Lose, SLOT(close()));
    connect(m_Lose -> ui ->Restart_Button, SIGNAL(clicked()), m_CountrySelection, SLOT(show()));

    //save and load
    connect(m_LoadMenu -> ui -> Load_Button, SIGNAL(clicked()), m_LoadMenu, SLOT(m_LoadFile()));
    connect(m_LoadMenu, SIGNAL(m_SaveFileLoaded(QString)), this, SLOT(StartLoadedGame(QString)));
    connect(m_LoadMenu -> ui -> Back_Button, SIGNAL(clicked()), m_LoadMenu, SLOT(close()));
    connect(m_SaveMenu -> ui -> Back_Button, SIGNAL(clicked()), m_SaveMenu, SLOT(close()));
    connect(m_SaveMenu -> ui -> Save_Button, SIGNAL(clicked()), m_SaveMenu, SLOT(m_SaveFile()));
    connect(m_SaveMenu, SIGNAL(m_FileSaved(QString)), m_Game, SLOT(m_OutPutFile(QString)));



}

void GameMainClass::QuitGame()
{
    QMessageBox message(QMessageBox::NoIcon,"Quit Game","Do you really want to quit the game?", QMessageBox::Yes | QMessageBox::No, NULL);
    if(message.exec() == QMessageBox::Yes)
    {
        m_MainMenu -> close();
        m_Game -> m_StopGame();
        m_Game -> close();
        m_PauseDialog -> close();
        m_GameTheme -> stop();
    }
}

void GameMainClass::QuitToMainMenu()
{
    QMessageBox message(QMessageBox::NoIcon,"Quit to Main Menu","Do you really want to quit to Main Menu?", QMessageBox::Yes | QMessageBox::No, NULL);
    if(message.exec() == QMessageBox::Yes)
    {
        m_MainMenu -> show();
        m_Game -> close();
        m_Lose -> close();
        m_Victory -> close();
        m_PauseDialog -> close();
        m_Game -> m_StopGame();
        m_MainTheme ->play();
        m_GameTheme -> stop();
    }
}

void GameMainClass::StartLoadedGame(QString file)
{
    m_MainMenu -> close();
    m_MainTheme ->stop();
    m_LoadMenu -> close();
    m_PauseDialog -> close();
    m_Game -> m_StopGame();
    m_Game -> close();
    m_LoadingWindow -> show();
    m_LoadingWindow -> m_Loading(file);  
}
