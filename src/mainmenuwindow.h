/*
Filename: MainMenuWindow.h
Description: the main menu of the game
Version: 1.0
Date: 09/02/2018
*/

#ifndef MAINMENUWINDOW_H
#define MAINMENUWINDOW_H

#include <QMainWindow>



class GameMainClass;
namespace Ui {
class MainMenuWindow;
}

class MainMenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    //construction:construct ui and set background
    explicit MainMenuWindow(QWidget *parent = 0);
    ~MainMenuWindow();
private:
    Ui::MainMenuWindow *ui;
    friend class GameMainClass;

};

#endif // MAINMENUWINDOW_H
