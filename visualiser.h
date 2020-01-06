#pragma once

#include <QObject>
#include <QJsonObject>
#include <QVector>
#include "analyticswindow.h"

class Visualiser : public QObject
{
    Q_OBJECT

private:

    AnalyticsWindow *analyticsWindow;

    QJsonObject summonerData;
    QJsonObject rankedData;
    QJsonObject matchIDsData;
    QVector<QJsonObject> matchData;

public:
    Visualiser(AnalyticsWindow *analyticsWindow_, QJsonObject summonerData_, QJsonObject rankedData_, QJsonObject matchIDsData_, QVector<QJsonObject> matchData_);

    void fillGUI();
    void fillOverview();


signals:

};

