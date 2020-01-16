#include "datainquirer.h"
#include <iostream>
#include <QDebug>
#include <string>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QEventLoop>

using namespace std;



// Constructor
DataInquirer::DataInquirer(QUrl url_)
{
    url = url_;

    qInfo().noquote() << "Created DataInquirer:' " + url.toString();
}



// Connect to API
void DataInquirer::queryRiotAPI(){

    // Loop to wait for finished api call
    QEventLoop loop;

    // Create object to query api
    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);

    // Wait for reply amd when the QNetWorkReply is finished, call handleResult
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleResult(QNetworkReply*)));
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));

    // Formulate the request
    QNetworkRequest request;
    request.setUrl(url);

    // Start asynchronous request
    networkManager->get(request);

    loop.exec();

}


// Do something with query reply
void DataInquirer::handleResult(QNetworkReply* reply){

    // Prepare variable
    QJsonObject jsonObject;

    // Check for error
    if (reply->error() == QNetworkReply::NoError){

        // Read reply
        QByteArray response = reply->readAll();

        // Manipulate Match IDs (god damnit riot, can you be concise for once)
        response = manipulateMatchIds(response);
        byteResponse = response;

        // Manipulate Ranked data
        response = manipulateRankedData(response); 

        // Convert to JSON
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
        jsonObject = jsonResponse.object();

        // Debug
        response.truncate(200);
        //qInfo() << "Response: " << response << "\n";

    } else{
        qInfo() << "Error with URL: " << url << "; " << reply->error();
    }

    // Store QJsonObject
    jsonData = jsonObject;

    // Delete reply
    reply->deleteLater();

}


// Helper methods to work with RIOTs inconsistent API
QByteArray DataInquirer::manipulateMatchIds(QByteArray response){

    if(response.at(0) == '[' && response.at(1) == '"'){

        // Prepend '{"matches":
        response.prepend("{\"matches\":");

        // Append '}
        response.append('}');
    }

    return response;

}

QByteArray DataInquirer::manipulateRankedData(QByteArray response){

    if(response.at(0) == '[' && response.at(1) == '{'){


        // Delete first
        response.remove(0, 1);

        // Append '}
        response = response.left(response.size()-1);

    }

    return response;

}
