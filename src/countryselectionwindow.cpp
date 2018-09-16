/*
Filename: CountrySelectionWindow.cpp
Description: the window of country selection
Version: 1.1
Date: 09/02/2018
*/
#include <QPixmap>
#include <QPalette>
#include "countryselectionwindow.h"
#include "ui_countryselectionwindow.h"
#include "resources.h"

CountrySelectionWindow::CountrySelectionWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CountrySelectionWindow)
{
    ui->setupUi(this);
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

CountrySelectionWindow::~CountrySelectionWindow()
{
    delete ui;
}
