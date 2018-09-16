/*
Filename: LoseWindow.h
Description: the window shown when the game is lost
Version: 2.0
Date: 09/10/2018
*/
#ifndef LOSEWINDOW_H
#define LOSEWINDOW_H

#include <QMainWindow>

namespace Ui {
class LoseWindow;
}

class GameMainClass;
class LoseWindow : public QMainWindow
{
    friend class GameMainClass;
    Q_OBJECT

public:

    //set ui and background picture
    explicit LoseWindow(QWidget *parent = 0);
    ~LoseWindow();

private:
    Ui::LoseWindow *ui;
};

#endif // LOSEWINDOW_H
