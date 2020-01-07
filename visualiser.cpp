#include "visualiser.h"
#include "analyticswindow.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QPixmap>


Visualiser::Visualiser(AnalyticsWindow *analyticsWindow_, QJsonObject summonerData_, QJsonObject rankedData_, QJsonObject matchIDsData_, QVector<QJsonObject> matchData_)
{
    analyticsWindow = analyticsWindow_;

    summonerData = summonerData_;
    rankedData = rankedData_;
    matchIDsData = matchIDsData_;
    matchData = matchData_;
}


// Orchestrates Data Display
void Visualiser::fillGUI(){

    // Fill Overview Tab
    fillOverview();

}




// Fills Overview Tab
void Visualiser::fillOverview(){

    // Profile icon
    int profileIconId = summonerData["profileIconId"].toInt();
    QString iconPath = "include/profileicon/" + QString::number(profileIconId);
    QPixmap profileIcon;
    profileIcon.load(iconPath);
    analyticsWindow->setLabel_ProfileIcon(profileIcon);

    // Name
    QString summonerName = summonerData["name"].toString();
    analyticsWindow->setLabel_Name(summonerName);

    // Region
    QJsonArray matchIDs = matchIDsData["matches"].toArray();
    QString region = matchIDs[0].toString().left(3);
    analyticsWindow->setLabel_Region(region);

    // Tier and Rank
    QString tier = rankedData["tier"].toString();
    QString rank = rankedData["rank"].toString();
    analyticsWindow->setLabel_Tier(tier + " " + rank);

    // League Points
    QString leaguePoints = QString::number(rankedData["leaguePoints"].toInt()) + " LP";
    analyticsWindow->setLabel_LP(leaguePoints);

    // Games, Wins, Losses, Winrate
    int wins = rankedData["wins"].toInt();
    int losses = rankedData["losses"].toInt();
    int gamesPlayed = wins + losses;
    double winrate = wins / gamesPlayed;

    analyticsWindow->setLabel_Games(QString::number(gamesPlayed));
    analyticsWindow->setLabel_Wins(QString::number(wins));
    analyticsWindow->setLabel_Losses(QString::number(losses));
    analyticsWindow->setLabel_Winrate(QString::number(winrate));

    // Favorite comp

}
