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

    QString determineRegion(bool regionFormat);

    QJsonObject querySummonerInfo(QString summonerName);
    QJsonObject queryRankedInfo(QString summonerId);
    QJsonObject queryMatchIDs(QString puuid);
    QJsonObject queryMatchInfo(QString matchId);

signals:
    void analysisStatusChanged(QString newStatus);

};

