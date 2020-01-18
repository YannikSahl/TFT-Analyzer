#pragma once
#include <QString>

/*!
 * \brief The Champion class is a container class for API-Data.
 */
class Champion
{

public:

    /// Constructor
    /*!
     * \brief Champion Constructor.
     */
    Champion(QString championName, int championTier, int championCost);

    // Member variables
    QString championName;
    int championCost;
    int championTier;

    /*!
     * \brief operator < define < operator to sort QList.
     */
    bool operator <(const Champion &championObj) const;
};
