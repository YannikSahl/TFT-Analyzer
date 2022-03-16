#pragma once
#include <QString>

/// Container class for API-Data
class Trait
{
public:

    // Constructor
    Trait(QString traitName, int numUnits, int tierCurrent, int tierTotal);

    // Member variables
    QString traitName;
    int numUnits;
    int tierCurrent;
    int tierTotal;

    /// Define < operator to sort qlist
    bool operator <(const Trait &traitObj) const;

};
