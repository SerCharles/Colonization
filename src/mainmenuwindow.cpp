/*
Filename: MainMenuWindow.cpp
Description: the main menu of the game
Version: 1.1
Date: 09/02/2018
*/
#include <QObject>
#include <QPalette>
#include <QPixmap>
#include "mainmenuwindow.h"
#include "ui_mainmenuwindow.h"
#include "resources.h"

MainMenuWindow::MainMenuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenuWindow)
{
    ui->setupUi(this);
    //background picture
        this->setAutoFillBackground(true);
        QPalette palette = this->palette();
        palette.setBrush(QPalette::Window,
                QBrush(g_Resources -> BackGroundPicture -> scaled(
                    this->size(),
                    Qt::IgnoreAspectRatio,
                    Qt::SmoothTransformation)));
        this->setPalette(palette);
}

MainMenuWindow::~MainMenuWindow()
{
    delete ui;
}


