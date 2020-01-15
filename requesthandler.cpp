#include "requesthandler.h"
#include "datainquirer.h"
#include "visualiser.h"
#include <QDebug>
#include <QtConcurrent/QtConcurrent>
#include <QThread>



// Constructor
RequestHandler::RequestHandler(AnalyticsWindow *analyticsWindow_, QString apiKey_, QString summonerName_, QString region_, int matchCount_)
{
    // Parameter
    analyticsWindow = analyticsWindow_;
    apiKey = apiKey_;
    summonerName = summonerName_;
    region = region_;
    matchCount = matchCount_;

    // Connect analyticswindow and requesthandler: analyticsWindow sends signal request for topTeams, requesthandler starts new request
    connect(analyticsWindow, SIGNAL(topTeamsRequested()), this, SLOT(handleTopRequest()));

    // Connect requesthandler and analyticswindow: requesthandler sends signal status update, analyticswindow shows status
    connect(this, SIGNAL(topTeamRequestStatusChanged(QString)), analyticsWindow, SLOT(setTopTeamsStatus(QString)));

    // Status
    qInfo().noquote() << "Created RequestHandler object with apiKey:'" + apiKey_ + "' and summonerName:'" + summonerName;
}




// Orchestrate Process Procedure
int RequestHandler::handleRequest(){

    // Get Summoner Info
    QJsonObject summonerData = querySummonerInfo(this->summonerName);
    if(summonerData.isEmpty()){
        return 2;
    }

    // Get Ranked Info
    QString summonerId = summonerData["id"].toString();
    QJsonObject rankedData = queryRankedInfo(summonerId);

    // Get Match IDs
    QString puuid = summonerData["puuid"].toString();
    QJsonObject matchIDsData = queryMatchIDs(puuid, matchCount);

    // Get Match Info
    if(matchIDsData["matches"].isNull()){
        return 3;
    }
    QJsonArray matchIds = matchIDsData["matches"].toArray();
    int maxMatches = matchIds.size() < matchCount ? matchIds.size() : matchCount;

    for(int i = 0; i < maxMatches; i++){

        // Get Single Match Id
        QString matchIdString = matchIds[i].toString();

        // Emit signal current status
        emit analysisStatusChanged("Querying Match " + QString::number(i+1) + " of " + QString::number(maxMatches));

        // Query Match Info for That Match (in separate Thread)
        queryMatchInfo(matchIdString);
        /*
        QFuture<QJsonObject> matData = QtConcurrent::run(this, &RequestHandler::queryMatchInfo, matchIdString);

        // Try to not get blocked from API access
        if((i+1)%5 == 0){
            matData.waitForFinished();
        }
        */
    }

    // Wait for all responses
    //while(matchData.size() != maxMatches){}

    // Update status
    emit analysisStatusChanged("Processing Matches");

    // Forward Data for Visualisation
    Visualiser *visual = new Visualiser(analyticsWindow, summonerData, rankedData, matchIDsData, matchData);
    visual->fillGUI();

    // Return value
    return 1;

}


// Gets currently best players
QJsonObject RequestHandler::queryChallengersInfo(){

    QList<QString> challengerPuuids;

    // Status
    emit analysisStatusChanged("Querying Challenger Names");

    // Build URL
    QString regionFormat = determineRegion(0);
    queryString = "https://euw1.api.riotgames.com/tft/league/v1/grandmaster?api_key=" + apiKey;
    queryUrl.setUrl(queryString);

    // Inquire Data
    dataInq = new DataInquirer(queryUrl);
    dataInq->queryRiotAPI();

    // Get Response Data
    return dataInq->jsonData;

}

// Gets Information about the Summoner Name
QJsonObject RequestHandler::querySummonerInfo(QString summonerName){

    // Status
    emit analysisStatusChanged("Querying Summoner Data");

    // Build URL
    QString regionFormat = determineRegion(0);
    queryString = "https://" + regionFormat + ".api.riotgames.com/tft/summoner/v1/summoners/by-name/" + summonerName + "?api_key=" + apiKey;
    queryUrl.setUrl(queryString);

    // Inquire Data
    dataInq = new DataInquirer(queryUrl);
    dataInq->queryRiotAPI();

    // Get Response Data
    return dataInq->jsonData;

}

// Gets Information about the Ranked Status
QJsonObject RequestHandler::queryRankedInfo(QString summonerId){

    // Status
    emit analysisStatusChanged("Querying Ranked Data");

    // Build URL
    QString regionFormat = determineRegion(0);
    queryString = "https://" + regionFormat + ".api.riotgames.com/tft/league/v1/entries/by-summoner/" + summonerId + "?api_key=" + apiKey;
    queryUrl.setUrl(queryString);

    // Inquire Data
    dataInq = new DataInquirer(queryUrl);
    dataInq->queryRiotAPI();

    // Get Response Data
    return dataInq->jsonData;


}

// Gets all the Match IDs belonging to a specific PUUID
QJsonObject RequestHandler::queryMatchIDs(QString puuId, int matches = 100){

    // Status
    emit analysisStatusChanged("Querying Match Data");

    // Build URL
    QString regionFormat = determineRegion(1);
    queryString = "https://" + regionFormat + ".api.riotgames.com/tft/match/v1/matches/by-puuid/" + puuId + "/ids?count=" + QString::number(matches) + "&api_key=" + apiKey;
    queryUrl.setUrl(queryString);

    // Inquire Data
    dataInq = new DataInquirer(queryUrl);
    dataInq->queryRiotAPI();

    // Get Response Data
    return dataInq->jsonData;

}

// Gets Info for a specific Match
void RequestHandler::queryMatchInfo(QString matchId){

    // Build URL
    QString regionFormat = determineRegion(1);
    queryString = "https://" + regionFormat + ".api.riotgames.com/tft/match/v1/matches/" + matchId + "?api_key=" + apiKey;
    queryUrl.setUrl(queryString);

    // Inquire Data
    dataInq = new DataInquirer(queryUrl);
    dataInq->queryRiotAPI();

    // Get Response Data
    QJsonObject singleMatch = dataInq->jsonData;

    // Inspect on completeness
    QJsonObject infoData = singleMatch["info"].toObject();
    QString gamelength = QString::number(infoData["game_length"].toDouble());

    // Data complete: gameLength = 0?
    if(gamelength == "0"){
        qInfo() << "Error: Match '" << matchId << "' lacks data, has gamelength" << gamelength << " -> Skipped";
    } else{

        // Append to other matches
        matchData.append(singleMatch);

    }

}

// Helper method to work out RIOT's region formatting
QString RequestHandler::determineRegion(bool regionFormat){

    // Prepare Return Variable
    QString regionString;

    // EUROPE, ASIA, AMERICAS
    if(regionFormat == true){

        if(region == "EUN" || region == "EUW" || region == "RU" || region == "TR"){
            regionString = "EUROPE";
        }
        else if(region == "BR" || region == "LA" || region == "NA" || region == "OC"){
            regionString = "AMERICAS";
        }
        else if(region == "JP" || region == "KR"){
            regionString = "ASIA";
        }

    }
    // BR1, EUN1, EUW1, JP1, KR, LA1, LA2, NA1, RU, OC1, TR1
    else{

        // Append a 1 (if not KR or RU)
        if(!(region == "KR" || region == "RU")){
            regionString = region + "1";
        }
    }

    // Return QString
    return regionString;

}



// Slots: Start request for TopTeams
void RequestHandler::handleTopRequest(){

    matchData.erase(matchData.begin(), matchData.end());

    // Get challenger puuids
    QJsonObject challengerInfo = queryChallengersInfo();

    // Get "entries"
    QJsonArray entriesArray = challengerInfo["entries"].toArray();

    // Get top 10
    int challengerCount = 10;
    for(int i = 0; i < challengerCount; i++){

        // Get entry
        QJsonObject entry = entriesArray[i].toObject();

        // Get name
        QString name = entry["summonerName"].toString();

        // Status
        emit topTeamRequestStatusChanged("\t\tQuerying Data for Challenger " + QString::number(i+1) + " of " + QString::number(challengerCount) + ": Summoner Data");

        // Use name to get summmoner info (to get puuid)
        QJsonObject entrySummonerInfo = querySummonerInfo(name);

        // Extract puuid
        QString puuid = entrySummonerInfo["puuid"].toString();

        // Use puuid to query matches
        int matchCounter = 5;
        QJsonObject matchIDsData = queryMatchIDs(puuid, matchCounter);
        QJsonArray matchIds = matchIDsData["matches"].toArray();

        // Get most recent matches
        for(int j = 0; j < matchIds.size(); j++){

            // Status
            emit topTeamRequestStatusChanged("\t\tQuerying Data for Challenger " + QString::number(i+1) + " of " + QString::number(challengerCount) + ": Match " + QString::number(j+1) + " of " + QString::number(matchCounter));

            // Get single match ID
            QString matchIdString = matchIds[j].toString();

            // Add match to
            queryMatchInfo(matchIdString);

        }
    }

    // Update status
    emit topTeamRequestStatusChanged("\t\tProcessing Matches");

    // Forward Data for Visualisation
    Visualiser *visualTop = new Visualiser(analyticsWindow, *new QJsonObject(), *new QJsonObject(), *new QJsonObject(), matchData);
    visualTop->fillTopTeams();

    // Clear status label
    emit analysisStatusChanged("");

}
