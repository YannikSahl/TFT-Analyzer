#pragma once
#include <QtNetwork>

using namespace std;

class DataInquirer : QObject
{
    Q_OBJECT

private:
    QUrl url;

public:

    // Member Variables
    QJsonObject jsonData;
    QByteArray byteResponse;

    // Constructor
    DataInquirer(QUrl url_);

    /// Basic Query to RIOT's API
    void queryRiotAPI();

    /// Helper method that unifies data returned by RIOTs inconsistent API
    QByteArray manipulateMatchIds(QByteArray response);


    /// Helper method that unifies data returned by RIOTs inconsistent API
    QByteArray manipulateRankedData(QByteArray response);

public slots:

    /// Slot that is invoked whenever an API call is finished
    void handleResult(QNetworkReply* reply);

};
