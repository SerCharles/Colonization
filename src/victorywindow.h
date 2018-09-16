/*
Filename: VictoryWindow.h
Description: the window shown when the game is win
Version: 2.0
Date: 09/10/2018
*/


#ifndef VICTORYWINDOW_H
#define VICTORYWINDOW_H

#include <QMainWindow>

namespace Ui {
class VictoryWindow;
}

class GameMainClass;
class VictoryWindow : public QMainWindow
{
    friend class GameMainClass;
    Q_OBJECT

public:

    //construct ui and set background picture
    explicit VictoryWindow(QWidget *parent = 0);
    ~VictoryWindow();

private:
    Ui::VictoryWindow *ui;
};

#endif // VICTORYWINDOW_H
