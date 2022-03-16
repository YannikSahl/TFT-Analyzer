#pragma once
#include <QObject>
#include <QJsonObject>
#include <QUrl>
#include <QVector>
#include "datainquirer.h"
#include "analyticswindow.h"

/// Orcestrates what is when and how queried
class RequestHandler : public QObject
{
    Q_OBJECT


private:

    // Object of analyticsWindow to pass along to Visualiser
    AnalyticsWindow *analyticsWindow;

    // Information received from the MainWindow
    QString apiKey;
    QString summonerName;
    QString region;
    int matchCount;

    // Member variables used for internal logic
    QString queryString;
    QUrl queryUrl;
    DataInquirer *dataInq;

    // QVector that stores data about queried Matches for further Analysis
    QVector<QJsonObject> matchData;

public:

    RequestHandler(AnalyticsWindow *analyticsWindow, QString apiKey_, QString summonerName_, QString region_, int matchCount_);
    int handleRequest();

    QString determineRegion(bool regionFormat);

    // Functions to get Data for given Summoner
    QJsonObject querySummonerInfo(QString summonerName);
    QJsonObject queryRankedInfo(QString summonerId);
    QJsonObject queryMatchIDs(QString puuid, int matches);
    void queryMatchInfo(QString matchId);

    // Function to get Data for best Players
    QJsonObject queryChallengersInfo();


public slots:
    void handleTopRequest();

signals:
    void analysisStatusChanged(QString newStatus);
    void topTeamRequestStatusChanged(QString newStatus);

};

