/*
Filename: SaveMenu.cpp
Description: the window shown when you want to save a game
Version: 2.0
Date: 09/10/2018
*/


#include <QFileDialog>
#include <QFile>
#include <QPalette>
#include <QPixmap>
#include <QString>
#include "savemenu.h"
#include "ui_savemenu.h"
#include "resources.h"


SaveMenu::SaveMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SaveMenu)
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

SaveMenu::~SaveMenu()
{
    delete ui;
}


void SaveMenu::m_SaveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Open File"),"",tr("Save files (*.sav)"));
    if(fileName == ""){
            return;
        }
    emit m_FileSaved(fileName);
}
