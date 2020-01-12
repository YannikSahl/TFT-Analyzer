#include "trait.h"

Trait::Trait(QString traitName_, int numUnits_, int tierCurrent_, int tierTotal_)
{

    traitName = traitName_;
    numUnits = numUnits_;
    tierCurrent = tierCurrent_;
    tierTotal = tierTotal_;

}


// Define < operator to sort qlist
bool Trait::operator <(const Trait &traitObj) const{
    return numUnits < traitObj.numUnits;
}
