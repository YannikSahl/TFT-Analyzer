#include "visualiser.h"
#include "analyticswindow.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QPixmap>
#include <QUrl>


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
    QString iconPath = "include\\tftStuff\\profileicon\\718.png";
    //QString iconPath = "\\include\\tftStuff\\profileicon\\" + QString::number(profileIconId) + ".png";
    //QString iconPath = "D:\\Benutzer\\Yannik\\SynologyDrive\\HTW\\Module\\3 (5) WP1 - Vertiefung in die Programmierung\\Projekt\\QT\\TFTApp\\include\\tftStuff\\profileicon\\718.png";
    QPixmap profileIcon(iconPath);
    QUrl url("http://ddragon.leagueoflegends.com/cdn/6.3.1/img/profileicon/718.png");


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

    // Rank icon
    if(tier == "IRON"){analyticsWindow->setLabel_RankedIcon(QPixmap(":/icons/include/tftStuff/ranked-emblems/Emblem_Iron.png"));}
    if(tier == "BRONZE"){analyticsWindow->setLabel_RankedIcon(QPixmap(":/icons/include/tftStuff/ranked-emblems/Emblem_Bronze.png"));}
    if(tier == "SILVER"){analyticsWindow->setLabel_RankedIcon(QPixmap(":/icons/include/tftStuff/ranked-emblems/Emblem_Silver.png"));}
    if(tier == "GOLD"){analyticsWindow->setLabel_RankedIcon(QPixmap(":/icons/include/tftStuff/ranked-emblems/Emblem_Gold.png"));}
    if(tier == "PLATINUM"){analyticsWindow->setLabel_RankedIcon(QPixmap(":/icons/include/tftStuff/ranked-emblems/Emblem_Platinum.png"));}
    if(tier == "DIAMOND"){analyticsWindow->setLabel_RankedIcon(QPixmap(":/icons/include/tftStuff/ranked-emblems/Emblem_Diamond.png"));}
    if(tier == "MASTER"){analyticsWindow->setLabel_RankedIcon(QPixmap(":/icons/include/tftStuff/ranked-emblems/Emblem_Master.png"));}
    if(tier == "GRANDMASTER"){analyticsWindow->setLabel_RankedIcon(QPixmap(":/icons/include/tftStuff/ranked-emblems/Emblem_Grandmaster.png"));}
    if(tier == "CHALLENGER"){analyticsWindow->setLabel_RankedIcon(QPixmap(":/icons/include/tftStuff/ranked-emblems/Emblem_Challenger.png"));}


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
