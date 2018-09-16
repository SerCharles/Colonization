/*
Filename: LoadMenu.h
Description: the window shown when you want to load a game save file
Version: 2.0
Date: 09/10/2018
*/



#ifndef LOADMENU_H
#define LOADMENU_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class LoadMenu;
}

class GameMainClass;
class LoadMenu : public QMainWindow
{
    friend class GameMainClass;
    Q_OBJECT

public:
    //construct ui and set background picture
    explicit LoadMenu(QWidget *parent = 0);
    ~LoadMenu();
signals:

    //the sign that the file is loaded, it will trigger the loading window, and then the game will start
    void m_SaveFileLoaded(QString file);
public slots:

    /*
      function: generate a qfiledialog for you to choose the load file
      if success, the game will be loaded
      warning: the load file must be .sav, must be valid
    */
    void m_LoadFile();
private:
    Ui::LoadMenu *ui;
};

#endif // LOADMENU_H
