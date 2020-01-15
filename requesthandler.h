#pragma once
#include <QObject>
#include <QJsonObject>
#include <QUrl>
#include <QVector>
#include "datainquirer.h"
#include "analyticswindow.h"


class RequestHandler : public QObject
{
    Q_OBJECT


private:

    AnalyticsWindow *analyticsWindow;

    QString apiKey;
    QString summonerName;
    QString region;
    int matchCount;

    QString queryString;
    QUrl queryUrl;
    DataInquirer *dataInq;

    QVector<QJsonObject> matchData;


public:

    RequestHandler(AnalyticsWindow *analyticsWindow, QString apiKey_, QString summonerName_, QString region_, int matchCount_);
    int handleRequest();
    int handleTopRequest();

    QString determineRegion(bool regionFormat);

    // Functions to get Data for given Summoner
    QJsonObject querySummonerInfo(QString summonerName);
    QJsonObject queryRankedInfo(QString summonerId);
    QJsonObject queryMatchIDs(QString puuid, int matches);
    QJsonObject queryMatchInfo(QString matchId);

    // Functions to get Data for best Players
    QJsonObject queryChallengersInfo();

signals:
    void analysisStatusChanged(QString newStatus);

};

