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
    //QString iconPath = "/include/tftStuff/profileicon/" + QString::number(profileIconId);
    QString iconPath = "C:\\Users\\Yannik\\SynologyDrive\\HTW\\Module\\3 (5) WP1 - Vertiefung in die Programmierung\\Projekt\\QT Laptop\\TFTApp\\include\\tftStuff\\profileicon\\718.png";
    QPixmap profileIcon(iconPath);
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
    double winrate = round(1000*(double)wins / gamesPlayed)/10;
    QString winrateString = QString::number(winrate) + "%";

    analyticsWindow->setLabel_Games(QString::number(gamesPlayed));
    analyticsWindow->setLabel_Wins(QString::number(wins));
    analyticsWindow->setLabel_Losses(QString::number(losses));
    analyticsWindow->setLabel_Winrate(winrateString);

    // Favorite comp

}
