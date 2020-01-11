#include "visualiser.h"
#include "analyticswindow.h"
#include "datainquirer.h"
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

    // Fill Match History Tab
    fillMatchHistory();

    // Fills LP History Tab
    fillLPHistory();

    // Fills Team Comps Tab
    fillTeamComps();

    // Fills Top 10 Tab
    fillTop10();

}




// Fills Overview Tab
void Visualiser::fillOverview(){

    // 1. Profile icon
    int profileIconId = summonerData["profileIconId"].toInt();
    QString queryUrl = "http://ddragon.leagueoflegends.com/cdn/6.3.1/img/profileicon/" + QString::number(profileIconId )+ ".png";
    DataInquirer *dataInq = new DataInquirer(queryUrl);
    dataInq->queryRiotAPI();
    QPixmap profileIcon;
    profileIcon.loadFromData(dataInq->byteResponse);
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
    if(tier == "IRON"){analyticsWindow->setLabel_RankedIcon(QPixmap(":/include/ranked-emblems/Emblem_Iron.png"));}
    if(tier == "BRONZE"){analyticsWindow->setLabel_RankedIcon(QPixmap(":/include/ranked-emblems/Emblem_Bronze.png"));}
    if(tier == "SILVER"){analyticsWindow->setLabel_RankedIcon(QPixmap(":/include/ranked-emblems/Emblem_Silver.png"));}
    if(tier == "GOLD"){analyticsWindow->setLabel_RankedIcon(QPixmap(":/include/ranked-emblems/Emblem_Gold.png"));}
    if(tier == "PLATINUM"){analyticsWindow->setLabel_RankedIcon(QPixmap(":/include/ranked-emblems/Emblem_Platinum.png"));}
    if(tier == "DIAMOND"){analyticsWindow->setLabel_RankedIcon(QPixmap(":/include/ranked-emblems/Emblem_Diamond.png"));}
    if(tier == "MASTER"){analyticsWindow->setLabel_RankedIcon(QPixmap(":/include/ranked-emblems/Emblem_Master.png"));}
    if(tier == "GRANDMASTER"){analyticsWindow->setLabel_RankedIcon(QPixmap(":/include/ranked-emblems/Emblem_Grandmaster.png"));}
    if(tier == "CHALLENGER"){analyticsWindow->setLabel_RankedIcon(QPixmap(":/include/ranked-emblems/Emblem_Challenger.png"));}

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


// Fills Statistics Tab
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

    bool hotStreak = rankedData["hotStreak"].toBool();
    analyticsWindow->setLabel_HotStreak(hotStreak ? "Yes" : "No");

    // Summoner Box
    int summonerLevel = summonerData["summonerLevel"].toInt();
    analyticsWindow->setLabel_summonerLevel(QString::number(summonerLevel));
    bool activity = rankedData["inactive"].toBool();
    analyticsWindow->setLabel_activityStatus(!activity ? "Active" : "Inactive");

    // Team Comp Box



}

// Fills Match History Tab
void Visualiser::fillMatchHistory(){

    // Iterate over Matches
    for(QJsonObject match : matchData){

        // Get "info" data
        QJsonObject infoData = match["info"].toObject();

        // Get "participants" from "info"
        QJsonArray participantsArray = infoData["participants"].toArray();

        // Iterate over participantsArray
        for(int i = 0; i < participantsArray.size(); i++){

            // Get single participant info
            QJsonObject participantData = participantsArray[i].toObject();

            // Get Info belonging to PUUID
            if (participantData["puuid"] == summonerData["puuid"]){

                // Get meta data
                int placement = participantData["placement"].toInt();
                int gold = participantData["gold_left"].toInt();
                int level = participantData["level"].toInt();
                int round = participantData["last_round"].toInt();

                // Get traits with num units
                QHash<QString, int> traits = help_findTraitInfo(participantData);
                qInfo() << "Traits: " << traits;

                // Get champions with star
                QHash<QString, int> champions = help_findChampionInfo(participantData);
                qInfo() << "Champions: " << champions;

                // Display values

            }
        }
    }
}



// Fills LP History Tab
void Visualiser::fillLPHistory(){

}



// Fills Team Comps Tab
void Visualiser::fillTeamComps(){

}



// Fills Top 10 Tab
void Visualiser::fillTop10(){

}







// Helper methods
QHash<QString, int> Visualiser::help_findTraitInfo(QJsonObject participantData){

    // Prepare return variable
    QHash<QString, int> traits;

    // Extract traits
    QJsonArray traitArray = participantData["traits"].toArray();

    // Iterate over traits
    for(int i = 0; i < traitArray.size(); i++){

        // Get single trait info
        QJsonObject traitData = traitArray[i].toObject();

        // Add to hash
        traits[traitData["name"].toString()] = traitData["num_units"].toInt();

    }

    // Return stuff
    return traits;

}



QHash<QString, int> Visualiser::help_findChampionInfo(QJsonObject participantData){

    // Prepare return variable
    QHash<QString, int> champions;

    // Extract traits
    QJsonArray championsArray = participantData["units"].toArray();

    // Iterate over traits
    for(int i = 0; i < championsArray.size(); i++){

        // Get single trait info
        QJsonObject championData = championsArray[i].toObject();

        // Add to hash
        champions[championData["name"].toString()] = championData["tier"].toInt();

    }

    // Return stuff
    return champions;

}

