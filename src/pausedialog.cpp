#include <QPixmap>
#include <QPalette>
#include "pausedialog.h"
#include "ui_pausedialog.h"
#include "resources.h"

PauseDialog::PauseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PauseDialog)
{
    ui->setupUi(this);
    //background picture
        this->setAutoFillBackground(true);
        QPalette palette = this->palette();
        palette.setBrush(QPalette::Window,
                QBrush(g_Resources -> PausePicture -> scaled(
                    this->size(),
                    Qt::IgnoreAspectRatio,
                    Qt::SmoothTransformation)));
        this->setPalette(palette);
}

PauseDialog::~PauseDialog()
{
    delete ui;
}
