#pragma once
#include <QObject>
#include <QJsonObject>
#include <QVector>
#include "analyticswindow.h"
#include "trait.h"
#include "champion.h"

/// Orchestrates how and what is displayed to the user
class Visualiser : public QObject
{
    Q_OBJECT

private:

    // Structs to reflect TFT Game objects
    struct TraitData{
        QList<Trait> traits;
        int placement;
    };
    struct TraitInfo{
        int occurences;
        int combinedRating;
    };

    /// Whom to pass the data to
    AnalyticsWindow *analyticsWindow;

    // API Data objects
    QJsonObject summonerData;
    QJsonObject rankedData;
    QJsonObject matchIDsData;
    QVector<QJsonObject> matchData;

    // Congegration of Trait Combinations from individual Matches
    QList< TraitData > allTraits;


public:

    // Constructor
    Visualiser(AnalyticsWindow *analyticsWindow_, QJsonObject summonerData_, QJsonObject rankedData_, QJsonObject matchIDsData_, QVector<QJsonObject> matchData_);

    /// Sets the Sequence of displaying Information
    void fillGUI();

    // Methods reflecting how individual Tabs are filled with data
    void fillOverview();
    void fillStatistics();
    void fillMatchHistory();
    void fillLPHistory();
    void fillTeamComps(QList< TraitData > traitsInfo, int choiceTab);
    void fillTopTeams();

    // Helper methods to extract desired Data
    QList<Trait> help_findTraitInfo(QJsonObject participantData);
    QList<Champion> help_findChampionInfo(QJsonObject participantData);

};

