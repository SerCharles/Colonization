/*
Filename:LoadingWindow.h
Description: The Window Loading the game
Version: 2.0
Date: 09/10/2018
*/

#ifndef LOADINGWINDOW_H
#define LOADINGWINDOW_H
#include <QMainWindow>
#include <QTimer>
#include <QString>

namespace Ui {
class LoadingWindow;
}

class GameMainClass;
class LoadingWindow : public QMainWindow
{
    friend class GameMainClass;
    Q_OBJECT

public:

    //set ui and background
    explicit LoadingWindow(QWidget *parent = 0);
    ~LoadingWindow();
    int m_Country;
    QString m_SaveFile;
private:
    Ui::LoadingWindow *ui;
    const int m_cLoadingTime{3000};
    int m_Progress;
    QTimer* m_Timer;
public slots:

    /*loading way 1:loading a new game
     * function:start the timer controlling the bar
     * variable:the country you choose
     * */
    void m_Loading(const int country);


    /*loading way 2:loading an old game
     * function:start the timer controlling the bar
     * variable:the save file
     * */
    void m_Loading(const QString file);


    /*loading way 1:loading a new game
     * function:update the bar, and when the bar goes to 100, the game will start
     * */
    void m_UpdateLoadingNewGame();


    /*loading way 2:loading an old game
     * function:update the bar, and when the bar goes to 100, the game will start
     * */
    void m_UpdateLoadingLoadedGame();

signals:

    //signal that starts the game
    //the first one is a new game, the variable is the country you choose
    //the second one is an old game, the variable is the save file
    void m_LoadingFinished(int country);
    void m_LoadingFinished(QString file);
};

#endif // LOADINGWINDOW_H
