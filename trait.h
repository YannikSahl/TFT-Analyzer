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

};

#endif // TRAIT_H
