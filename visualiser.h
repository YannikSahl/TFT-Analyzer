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
    void fillStatistics();
    void fillMatchHistory();
    void fillLPHistory();
    void fillTeamComps();
    void fillTop10();

    QHash<QString, int> help_findTraitInfo(QJsonObject participantData);
    QHash<QString, int> help_findChampionInfo(QJsonObject participantData);


signals:

};

