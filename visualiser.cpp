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

    // Fill Statistics Tab
    fillStatistics();

}




// Fills Overview Tab
void Visualiser::fillOverview(){

    // 1. Profile icon
    int profileIconId = summonerData["profileIconId"].toInt();
    QString iconPath = "include\\tftStuff\\profileicon\\718.png";
    //QString iconPath = "\\include\\tftStuff\\profileicon\\" + QString::number(profileIconId) + ".png";
    //QString iconPath = "D:\\Benutzer\\Yannik\\SynologyDrive\\HTW\\Module\\3 (5) WP1 - Vertiefung in die Programmierung\\Projekt\\QT\\TFTApp\\include\\tftStuff\\profileicon\\718.png";
    QPixmap profileIcon(iconPath);
    QUrl url("http://ddragon.leagueoflegends.com/cdn/6.3.1/img/profileicon/718.png");

    analyticsWindow->setLabel_ProfileIcon(profileIcon);

    // 1. Name
    QString summonerName = summonerData["name"].toString();
    analyticsWindow->setLabel_Name(summonerName);

    // 1. Region
    QJsonArray matchIDs = matchIDsData["matches"].toArray();
    QString region = matchIDs[0].toString().left(3);
    analyticsWindow->setLabel_Region(region);

    // 2. Tier and Rank
    QString tier = rankedData["tier"].toString();
    QString rank = rankedData["rank"].toString();
    analyticsWindow->setLabel_Tier(tier + " " + rank);

    // 2.Rank icon
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
    QString leaguePoints = QString::number(rankedData["leaguePoints"].toInt());
    analyticsWindow->setLabel_LP(leaguePoints);

    // Win Rate
    int wins = rankedData["wins"].toInt();
    int losses = rankedData["losses"].toInt();
    int gamesPlayed = wins + losses;
    double winrate = round(1000*(double)wins / gamesPlayed)/10;
    QString winrateString = QString::number(winrate);
    analyticsWindow->setLabel_WinRateDesc(winrateString);

    // Average Place
    QString placement = "3.7";
    analyticsWindow->setLabel_AveragePlacements(placement);

}



void Visualiser::fillStatistics(){

    // Ranked Box
    int wins = rankedData["wins"].toInt();
    int losses = rankedData["losses"].toInt();
    int gamesPlayed = wins + losses;
    double winrate = round(1000*(double)wins / gamesPlayed)/10;
    QString winrateString = QString::number(winrate) + "%";

    analyticsWindow->setLabel_Games(QString::number(gamesPlayed));
    analyticsWindow->setLabel_Wins(QString::number(wins));
    analyticsWindow->setLabel_Losses(QString::number(losses));
    analyticsWindow->setLabel_Winrate(winrateString);


}
