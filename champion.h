#ifndef CHAMPION_H
#define CHAMPION_H

#include <QString>

class Champion
{
public:
    Champion(QString championName, int championTier, int championCost);

    QString championName;
    int championCost;
    int championTier;
};

#endif // CHAMPION_H
