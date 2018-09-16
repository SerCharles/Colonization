/*
Filename: LoadMenu.cpp
Description: the window shown when you want to load a game save file
Version: 2.0
Date: 09/10/2018
*/


#include <QDir>
#include <QDebug>
#include <QPalette>
#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include "loadmenu.h"
#include "ui_loadmenu.h"
#include "resources.h"


LoadMenu::LoadMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoadMenu)
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

LoadMenu::~LoadMenu()
{
    delete ui;
}



void LoadMenu::m_LoadFile()
{
    QString temp_file = QFileDialog::getOpenFileName(this,tr("Load Save Files"),"",tr("Save files (*.sav)"));
    if(temp_file == ""){
        return;
    }
    emit m_SaveFileLoaded(temp_file);
}
