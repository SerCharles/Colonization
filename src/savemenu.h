/*
Filename: SaveMenu.h
Description: the window shown when you want to save a game
Version: 2.0
Date: 09/10/2018
*/


#ifndef SAVEMENU_H
#define SAVEMENU_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QString>

namespace Ui {
class SaveMenu;
}

class GameMainClass;
class SaveMenu : public QMainWindow
{
    friend class GameMainClass;
    Q_OBJECT

public:
    //construct ui and set background picture
    explicit SaveMenu(QWidget *parent = 0);
    ~SaveMenu();
public slots:

    /*
      function: generate a qfiledialog for you to choose the the place and name of your saved file
      if success, the game will be saved
    */
    void m_SaveFile();
signals:


    //the signal that the file is saved, and close the save window
    void m_FileSaved(QString file);
private:
    Ui::SaveMenu *ui;
};

#endif // SAVEMENU_H
