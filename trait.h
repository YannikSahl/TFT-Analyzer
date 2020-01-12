#ifndef TRAIT_H
#define TRAIT_H

#include <QString>

class Trait
{
public:
    Trait(QString traitName, int numUnits, int tierCurrent, int tierTotal);

    QString traitName;
    int numUnits;
    int tierCurrent;
    int tierTotal;

    bool operator <(const Trait &traitObj) const;

};

#endif // TRAIT_H
