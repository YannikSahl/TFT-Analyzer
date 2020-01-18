#pragma once
#include <QtNetwork>

using namespace std;

/*!
 * \brief The DataInquirer class is responsible for all things data.
 * It queries the API, returns the data and converts the result to the JSON format.
 */
class DataInquirer : QObject
{
    Q_OBJECT

private:
    QUrl url;

public:

    /*!
     * \brief jsonData is a member variable: it stores the (to JSON converted) returned data.
     */
    QJsonObject jsonData;


    /*!
     * \brief jsonData is a member variable: it stores the returned data.
     */
    QByteArray byteResponse;

    /*!
     * \brief Constructor for the DataInquirer class.
     * \param url_ The URL to be queried.
     */
    DataInquirer(QUrl url_);


    /*!
     * \brief queryRiotAPI queries the RIOT API using the parameters passed to the object.
     */
    void queryRiotAPI();


    /*!
     * \brief manipulateMatchIds is a helper method that unifies data returned by RIOTs inconsistent API
     * \param response is the initial response without any modifications.
     * \return the unified data.
     */
    QByteArray manipulateMatchIds(QByteArray response);


    /*!
     * \brief manipulateMatchIds is a helper method that unifies data returned by RIOTs inconsistent API
     * \param response is the initial response without any modifications.
     * \return the unified data.
     */
    QByteArray manipulateRankedData(QByteArray response);

public slots:

    /*!
     * \brief handleResult is a slot that is invoked whenever an API call is finished and orchestrates what happens with the returned data.
     * \param reply is the API return to be handled.
     */
    void handleResult(QNetworkReply* reply);

};
