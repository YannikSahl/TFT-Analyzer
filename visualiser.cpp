#include "visualiser.h"
#include "analyticswindow.h"
#include "datainquirer.h"
#include "compwidget.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QPixmap>
#include <QUrl>
#include <chrono>

using namespace std::chrono;


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

    // Fills Team Comps Tab
    fillTeamComps();

    // Fills Top 10 Tab
    fillTop10();

}




// Fills Overview Tab
void Visualiser::fillOverview(){

    // 1. Profile icon
    int profileIconId = summonerData["profileIconId"].toInt();
    QString queryUrl = "http://ddragon.leagueoflegends.com/cdn/10.1.1/img/profileicon/" + QString::number(profileIconId )+ ".png";
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

    // Average Place: Handled by fillMatchHistory

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

    // Calculate average placement
    double placementAverage = 0, placementAverageMirror = 0;
    int minDaysAgo = 80000, maxDaysAgo = 0;

    // Prepare statistics recent placement string
    QString recentPlacements;
    QVector< QVector <int> > placements;

    // Iterate over Matches
    for(int i = 0; i < matchData.size(); i++){

        QJsonObject match = matchData[i];

        // Get "info" data
        QJsonObject infoData = match["info"].toObject();
        uint64_t gameTime = (uint64_t)infoData["game_datetime"].toDouble();
        uint64_t now = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        int diffInDays = round((double)(now - gameTime)/1000/60/60/24);
        QString daysAgo = QString::number(diffInDays);

        // Calculate max, min diffInDays
        if(diffInDays > maxDaysAgo) { maxDaysAgo = diffInDays; }
        if(diffInDays < minDaysAgo) { minDaysAgo = diffInDays; }

        // Get metadata to print match_id
        QJsonObject metaData = match["metadata"].toObject();
        QString matchId = metaData["match_id"].toString();
        qDebug().noquote() << "Match: " << matchId;

        // Get "participants" from "info"
        QJsonArray participantsArray = infoData["participants"].toArray();

        // Iterate over participantsArray
        for(int j = 0; j < participantsArray.size(); j++){

            // Get single participant info
            QJsonObject participantData = participantsArray[j].toObject();

            // Get Info belonging to PUUID
            if (participantData["puuid"] == summonerData["puuid"]){

                // Get meta data
                int placement = participantData["placement"].toInt();
                int level = participantData["level"].toInt();
                int round = participantData["last_round"].toInt(); 

                // Add to recentPlacements
                if(recentPlacements.length() < 15){
                    recentPlacements += QString::number(placement) + ", ";
                }

                // Add to average
                placementAverage += placement;

                // Store for later use in placement history
                QVector<int> singlePlacement;
                singlePlacement.append(diffInDays);
                singlePlacement.append(placement);
                placements.append(singlePlacement);

                // Get traits with num units, sort and append to list
                QList<Trait> traits = help_findTraitInfo(participantData);
                qSort(traits.begin(), traits.end());

                // Store
                struct TraitData singletrait{traits, placement};
                allTraits.append(singletrait);

                // Get champions with star
                QList<Champion> champions = help_findChampionInfo(participantData);

                // Sort champions by cost
                qSort(champions.begin(), champions.end());

                // Display values
                analyticsWindow->addMatch(QString::number(placement), QString::number(level), QString::number(round), daysAgo, traits, champions);

            }
        }
    }

    // Overview Tab: Display average
    placementAverage = roundf(100*(placementAverage / (double) matchData.length()))/100;
    analyticsWindow->setLabel_AveragePlacements(QString::number(placementAverage));

    // Statistics Tab: Display Recent placements
    qInfo() << "Davor: " << recentPlacements;
    recentPlacements = recentPlacements.left(recentPlacements.size()-2);
    qInfo() << "Danach: " << recentPlacements;
    analyticsWindow->setLabel_Placements(recentPlacements);

    // Placement History Tab: Display chart
    analyticsWindow->fillPlacementHistoryTab(placements, maxDaysAgo, minDaysAgo);

}



// Fills Team Comps Tab
void Visualiser::fillTeamComps(){

    // Prepare hash
    QHash<QString, TraitInfo> compCounts;

    // Find most common team comps
    for(TraitData traitData : allTraits){

        // Extract info
        QList<Trait> traits = traitData.traits;
        int placement = traitData.placement;

        // Add two most played traits
        QString trait1 = traits[traits.size()-1].traitName;
        QString trait2 = traits[traits.size()-2].traitName;

        // Form QString
        QString traitComb = trait1 + " + " + trait2;
        QString traitComb2 = trait2 + " + " + trait1;

        // Add to hash
        if(compCounts.contains(traitComb)){
            TraitInfo t = compCounts[traitComb];
            t.occurences += 1;
            t.combinedRating += placement;
            compCounts[traitComb] = t;
        }
        else if (compCounts.contains(traitComb2)){
            TraitInfo t = compCounts[traitComb2];
            t.occurences += 1;
            t.combinedRating += placement;
            compCounts[traitComb2] = t;
        }
        else{
            struct TraitInfo t{1, placement};
            compCounts.insert(traitComb, t);
        }
    }

    // Forward top 5
    int compsSize = compCounts.size();
    int allPlays = 0;
    for(int i = 0; i < 5 && i < compsSize; i++){

        QHashIterator<QString, TraitInfo> iter(compCounts);

        // Comp values
        int compPlays = 0;
        QString compName = "";
        int compRating = 0;

        // Iterate over all traits
        while(iter.hasNext())
        {
            iter.next();

            // Find highest comp
            QString name = iter.key();
            int plays = iter.value().occurences;
            int rating = iter.value().combinedRating;

            if(i == 0) allPlays += plays;

            if(plays > compPlays){
                compPlays = plays;
                compName = name;
                compRating = rating;
            }
        }

        // Show comp and remove
        analyticsWindow->addComp(i+1, compName, (double)compPlays/allPlays, (double)compRating/compPlays);
        compCounts.remove(compName);

        // Fill overview tab
        if(i == 0) analyticsWindow->setLabel_FavoriteComp(compName);
        if(i == 1) analyticsWindow->setLabel_FavoriteComp2(compName);

        // Reset iterator
        iter.toFront();
    }


}



// Fills Top 10 Tab
void Visualiser::fillTop10(){

}







// Helper methods
QList<Trait> Visualiser::help_findTraitInfo(QJsonObject participantData){

    // Prepare return variable
    QList<Trait> traits;

    // Extract traits
    QJsonArray traitArray = participantData["traits"].toArray();

    // Iterate over traits
    for(int i = 0; i < traitArray.size(); i++){

        // Get single trait info
        QJsonObject traitData = traitArray[i].toObject();

        // Add to hash
        QString traitName = traitData["name"].toString();
        int numUnits  = traitData["num_units"].toInt();
        int tierCurrent = traitData["tier_current"].toInt();
        int tierTotal = traitData["tier_total"].toInt();

        // Fix name "SET2_"
        if(traitName.contains("_")){ traitName = traitName.mid(5);}

        Trait traitino(traitName, numUnits, tierCurrent, tierTotal);
        traits.append(traitino);
    }

    // Return stuff
    return traits;

}



QList<Champion> Visualiser::help_findChampionInfo(QJsonObject participantData){

    // Prepare return variable
    QList<Champion> championInfo;

    // Extract traits
    QJsonArray championsArray = participantData["units"].toArray();

    // Iterate over traits
    for(int i = 0; i < championsArray.size(); i++){

        // Get single trait info
        QJsonObject championData = championsArray[i].toObject();

        // Add to hash
        QString championName = championData["character_id"].toString();
        int championTier = championData["tier"].toInt();
        int championCost = championData["rarity"].toInt() + 1;

        // Remove "TFT_2" and "Ocean/..." in LuxOcean
        if(championName[4] == "_"){
            championName = championName.mid(5);
        }
        if(championName.contains("Lux")){
            championName = "Lux";
        }
        if(championName.contains("Qiyana")){
            championName = "Qiyana";
        }

        // Create champion object
        Champion champ(championName, championTier, championCost);
        championInfo.append(champ);

    }

    // Return stuff
    return championInfo;

}

