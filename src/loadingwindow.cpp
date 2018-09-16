/*
Filename:LoadingWindow.cpp
Description: The Window Loading the game
Version: 2.0
Date: 09/10/2018
*/

#include <QTimer>
#include <QString>
#include <QPalette>
#include <QPixmap>
#include "loadingwindow.h"
#include "ui_loadingwindow.h"
#include "resources.h"

LoadingWindow::LoadingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoadingWindow)
{
    ui->setupUi(this);
    m_Progress = 0;
    m_Country = -1;
    m_SaveFile = "";

    //background picture
        this->setAutoFillBackground(true);
        QPalette palette = this->palette();
        palette.setBrush(QPalette::Window,
                QBrush(g_Resources -> LoadingPicture -> scaled(
                    this->size(),
                    Qt::IgnoreAspectRatio,
                    Qt::SmoothTransformation)));
        this->setPalette(palette);
}

LoadingWindow::~LoadingWindow()
{
    delete ui;
}



void LoadingWindow::m_Loading(const int country)
{
    m_Country = country;
    m_Progress = 0;
    m_Timer = new QTimer(this);
    connect(m_Timer, SIGNAL(timeout()), this, SLOT(m_UpdateLoadingNewGame()));
    m_Timer -> start(m_cLoadingTime/100);
}

void LoadingWindow::m_Loading(const QString file)
{
    m_SaveFile = file;
    m_Progress = 0;
    m_Timer = new QTimer(this);
    connect(m_Timer, SIGNAL(timeout()), this, SLOT(m_UpdateLoadingLoadedGame()));
    m_Timer -> start(m_cLoadingTime/100);
}


void LoadingWindow::m_UpdateLoadingNewGame()
{
    if(m_Progress == 100)
    {
        m_Timer -> stop();
        emit m_LoadingFinished(m_Country);
    }
    m_Progress ++;
    ui -> Progress_Bar ->setValue(m_Progress);
}

void LoadingWindow::m_UpdateLoadingLoadedGame()
{
    if(m_Progress == 100)
    {
        m_Timer -> stop();
        emit m_LoadingFinished(m_SaveFile);
    }
    m_Progress ++;
    ui -> Progress_Bar ->setValue(m_Progress);
}

