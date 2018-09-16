/*
Filename: PauseDialog.h
Description: the pause dialog of the game
Version: 2.0
Date: 09/10/2018
*/

#ifndef PAUSEDIALOG_H
#define PAUSEDIALOG_H

#include <QDialog>

namespace Ui {
class PauseDialog;
}
class GameMainClass;
class PauseDialog : public QDialog
{
friend class GameMainClass;
    Q_OBJECT

public:

    //set ui and background picture
    explicit PauseDialog(QWidget *parent = 0);
    ~PauseDialog();

private:
    Ui::PauseDialog *ui;
};

#endif // PAUSEDIALOG_H
