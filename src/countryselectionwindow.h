/*
Filename: CountrySelectionWindow.h
Description: the window of country selection
Version: 1.1
Date: 09/02/2018
*/


#ifndef COUNTRYSELECTIONWINDOW_H
#define COUNTRYSELECTIONWINDOW_H

#include <QMainWindow>
class GameMainClass;
namespace Ui {
class CountrySelectionWindow;
}

class CountrySelectionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CountrySelectionWindow(QWidget *parent = 0);
    ~CountrySelectionWindow();

private:
    Ui::CountrySelectionWindow *ui;
    friend class GameMainClass;
};

#endif // COUNTRYSELECTIONWINDOW_H
