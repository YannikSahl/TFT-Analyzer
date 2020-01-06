#pragma once
#include <QtNetwork>

using namespace std;

class DataInquirer : QObject
{
    Q_OBJECT

private:
    QUrl url;

public:

    // Attribute
    QJsonObject jsonData;

    // Constructor
    DataInquirer(QUrl url_);

    // Method
    void queryRiotAPI();
    QByteArray manipulateMatchIds(QByteArray response);
    QByteArray manipulateRankedData(QByteArray response);

public slots:
    void handleResult(QNetworkReply* reply);

};
