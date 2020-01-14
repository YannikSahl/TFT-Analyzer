#pragma once

#include <QObject>
#include <QJsonObject>
#include <QVector>
#include "analyticswindow.h"
#include "trait.h"
#include "champion.h"

class Visualiser : public QObject
{
    Q_OBJECT

private:

    struct TraitData{
        QList<Trait> traits;
        int placement;
    };
    struct TraitInfo{
        int occurences;
        int combinedRating;
    };

    AnalyticsWindow *analyticsWindow;

    QJsonObject summonerData;
    QJsonObject rankedData;
    QJsonObject matchIDsData;
    QVector<QJsonObject> matchData;

    QList< TraitData > allTraits;





public:
    Visualiser(AnalyticsWindow *analyticsWindow_, QJsonObject summonerData_, QJsonObject rankedData_, QJsonObject matchIDsData_, QVector<QJsonObject> matchData_);

    void fillGUI();

    void fillOverview();
    void fillStatistics();
    void fillMatchHistory();
    void fillLPHistory();
    void fillTeamComps();
    void fillTopTeams();

    QList<Trait> help_findTraitInfo(QJsonObject participantData);
    QList<Champion> help_findChampionInfo(QJsonObject participantData);


signals:

};

