#pragma once
#include <QString>

/// Container class for API-Data
class Champion
{

public:

    // Constructor
    Champion(QString championName, int championTier, int championCost);

    // Member variables
    QString championName;
    int championCost;
    int championTier;

    /// Define < operator to sort qlist
    bool operator <(const Champion &championObj) const;
};
