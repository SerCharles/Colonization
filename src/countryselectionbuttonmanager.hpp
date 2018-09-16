/*
Filename: CountrySelectionButtonManager.hpp
Description: managing country selection buttons of the game
Version: 1.1
Date: 09/04/2018
*/

#pragma once
#ifndef COUNTRYSELECTIONBUTTONMANAGER_HPP
#define COUNTRYSELECTIONBUTTONMANAGER_HPP
#include <QObject>

class CountrySelectionButtonManager: public QObject
{
    Q_OBJECT
    private:
        int m_ButtonClicked;
    signals:
        void OpenGameWithCountry(int selection);
    public slots:
        void ClickedEngland()
        {
            m_ButtonClicked = 1;
            emit OpenGameWithCountry(m_ButtonClicked);
        }
        void ClickedFrance()
        {
            m_ButtonClicked = 2;
            emit OpenGameWithCountry(m_ButtonClicked);
        }
        void ClickedPrussia()
        {
            m_ButtonClicked = 3;
            emit OpenGameWithCountry(m_ButtonClicked);
        }
};

#endif // COUNTRYSELECTIONBUTTONMANAGER_HPP
