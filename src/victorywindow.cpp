/*
Filename: VictoryWindow.cpp
Description: the window shown when the game is win
Version: 2.0
Date: 09/10/2018
*/


#include <QPalette>
#include <QPixmap>
#include "victorywindow.h"
#include "ui_victorywindow.h"
#include "resources.h"

VictoryWindow::VictoryWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VictoryWindow)
{
    ui->setupUi(this);

    //background picture
        this->setAutoFillBackground(true);
        QPalette palette = this->palette();
        palette.setBrush(QPalette::Window,
                QBrush(g_Resources -> VictoryPicture -> scaled(
                    this->size(),
                    Qt::IgnoreAspectRatio,
                    Qt::SmoothTransformation)));
        this->setPalette(palette);
}

VictoryWindow::~VictoryWindow()
{
    delete ui;
}
