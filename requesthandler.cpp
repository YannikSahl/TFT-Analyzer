#include "requesthandler.h"
#include "datainquirer.h"
#include "visualiser.h"
#include <QDebug>
#include <QtConcurrent/QtConcurrent>
#include <QThread>



// Constructor
RequestHandler::RequestHandler(AnalyticsWindow *analyticsWindow_, QString apiKey_, QString summonerName_, QString region_, int matchCount_)
{
    analyticsWindow = analyticsWindow_;
    apiKey = apiKey_;
    summonerName = summonerName_;
    region = region_;
    matchCount = matchCount_;

    emit analysisStatusChanged("test");
    qInfo() << "Created RequestHandler object with apiKey:'" + apiKey_ + "' and summonerName:'" + summonerName;
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
    QJsonObject matchIDsData = queryMatchIDs(puuid);

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
        qInfo() << "i: " << i << " with matchId " << matchIdString;
        emit analysisStatusChanged("Status: " + QString::number(i+1) + " of " + QString::number(maxMatches) + " Matches");

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
    while(matchData.size() != maxMatches){}

    // Forward Data for Visualisation
    Visualiser *visual = new Visualiser(analyticsWindow, summonerData, rankedData, matchIDsData, matchData);
    visual->fillGUI();
    return 1;

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
QJsonObject RequestHandler::queryMatchIDs(QString puuId){

    // Status
    emit analysisStatusChanged("Querying Match Data");

    // Build URL
    QString regionFormat = determineRegion(1);
    queryString = "https://" + regionFormat + ".api.riotgames.com/tft/match/v1/matches/by-puuid/" + puuId + "/ids?count=1000&api_key=" + apiKey;
    queryUrl.setUrl(queryString);

    // Inquire Data
    dataInq = new DataInquirer(queryUrl);
    dataInq->queryRiotAPI();

    // Get Response Data
    return dataInq->jsonData;

}

// Gets Info for a specific Match
QJsonObject RequestHandler::queryMatchInfo(QString matchId){

    // Build URL
    QString regionFormat = determineRegion(1);
    queryString = "https://" + regionFormat + ".api.riotgames.com/tft/match/v1/matches/" + matchId + "?api_key=" + apiKey;
    queryUrl.setUrl(queryString);


    // Inquire Data
    dataInq = new DataInquirer(queryUrl);
    dataInq->queryRiotAPI();

    // Get Response Data
    QJsonObject singleMatch = dataInq->jsonData;
    matchData.append(singleMatch);
    qInfo() << "match id: " << matchId << ", this match:" << singleMatch.size() << ", list size:" << matchData.size();
    return dataInq->jsonData;

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
