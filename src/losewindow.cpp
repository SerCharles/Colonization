/*
Filename: LoseWindow.cpp
Description: the window shown when the game is lost
Version: 2.0
Date: 09/10/2018
*/

#include <QPalette>
#include <QPixmap>
#include "losewindow.h"
#include "ui_losewindow.h"
#include "resources.h"




LoseWindow::LoseWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoseWindow)
{
    ui->setupUi(this);
    //background picture
        this->setAutoFillBackground(true);
        QPalette palette = this->palette();
        palette.setBrush(QPalette::Window,
                QBrush(g_Resources -> LosePicture -> scaled(
                    this->size(),
                    Qt::IgnoreAspectRatio,
                    Qt::SmoothTransformation)));
        this->setPalette(palette);
}

LoseWindow::~LoseWindow()
{
    delete ui;
}
