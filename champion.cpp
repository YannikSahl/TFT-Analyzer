#include "champion.h"

Champion::Champion(QString championName_, int championTier_, int championCost_)
{

    championName = championName_;
    championTier = championTier_;
    championCost = championCost_;

}

// Define < operator to sort qlist
bool Champion::operator <(const Champion &championObj) const{
    return championCost < championObj.championCost;
}
