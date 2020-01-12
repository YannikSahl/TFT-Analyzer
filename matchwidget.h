#pragma once

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include "trait.h"
#include "champion.h"

class MatchWidget : public QWidget
{
    Q_OBJECT

private:

    // Main Containers
    QFrame *frameGameInfo;
    QFrame *frameCompInfo;
    QFrame *frameTeamInfo;

    // Sub Containers
    QFrame *frameTeamInfo_champions;
    QFrame *frameTeamInfo_championsLevel;

    // Layouts
    QHBoxLayout *matchWidget_layout;
    QGridLayout *frameGameInfo_layout;
    QVBoxLayout *frameCompInfo_layout;
    QVBoxLayout *frameTeamInfo_layout;

    QHBoxLayout *frameTeamInfo_champions_layout;
    QHBoxLayout *frameTeamInfo_championsLevel_layout;

    // Labels for frameGameInfo
    QLabel *labelPlacement;
    QLabel *labelLevel;
    QLabel *labelRound;
    QLabel *labelDaysAgo;

    // Labels for frameTeamInfo_champions, frameTeamInfo_championsLevel
    QLabel *labelChamp;
    QLabel *labelChamp_rank;

    // Methods
    void initialize();
    void customize(QString placement, QString level, QString round, QString daysAgo, QList<Trait> traits, QList<Champion> champions);


public:
    explicit MatchWidget(QString placement, QString level, QString round, QString daysAgo, QList<Trait> traits, QList<Champion> champions, QWidget *parent = nullptr);






signals:







};
