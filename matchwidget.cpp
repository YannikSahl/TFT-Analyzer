#include "matchwidget.h"
#include <QVBoxLayout>


// Constructor
MatchWidget::MatchWidget(QString placement, QString level, QString round, QString daysAgo, QList<Trait> traits, QList<Champion> champions, QWidget *parent) : QWidget(parent)
{

    initialize();
    customize(placement, level, round, daysAgo, traits, champions);

}


void MatchWidget::initialize(){

    // Set size
    this->setFixedHeight(160);
    this->setStyleSheet("border: 2px solid;");

    // Apply horizontal layout to MatchWidget
    matchWidget_layout = new QHBoxLayout(this);

    // Add Main Container
    frameGameInfo = new QFrame(this);
    frameCompInfo = new QFrame(this);
    frameTeamInfo = new QFrame(this);
    matchWidget_layout->addWidget(frameGameInfo);
    matchWidget_layout->addWidget(frameCompInfo);
    matchWidget_layout->addWidget(frameTeamInfo);

    // Set Layout Main Container
    frameGameInfo_layout = new QGridLayout(frameGameInfo);
    frameCompInfo_layout = new QVBoxLayout(frameCompInfo);
    frameTeamInfo_layout = new QVBoxLayout(frameTeamInfo);
    frameGameInfo->setLayout(frameGameInfo_layout);
    frameCompInfo->setLayout(frameCompInfo_layout);
    frameTeamInfo->setLayout(frameTeamInfo_layout);

    // Add Sub Container
    frameTeamInfo_champions = new QFrame(frameTeamInfo);
    frameTeamInfo_championsLevel = new QFrame(frameTeamInfo);
    frameTeamInfo_layout->addWidget(frameTeamInfo_championsLevel);
    frameTeamInfo_layout->addWidget(frameTeamInfo_champions);

    // Set Layout Sub Container
    frameTeamInfo_champions_layout = new QHBoxLayout(frameTeamInfo_champions);
    frameTeamInfo_championsLevel_layout = new QHBoxLayout(frameTeamInfo_championsLevel);
    frameTeamInfo_champions->setLayout(frameTeamInfo_champions_layout);
    frameTeamInfo_championsLevel->setLayout(frameTeamInfo_championsLevel_layout);

    // Add label to frameGameInfo
    labelPlacement = new QLabel(frameGameInfo);
    labelLevel = new QLabel(frameGameInfo);
    labelRound = new QLabel(frameGameInfo);
    labelDaysAgo = new QLabel(frameGameInfo);
    frameGameInfo_layout->addWidget(labelPlacement, 0, 0, 3, 1);
    frameGameInfo_layout->addWidget(labelLevel, 0, 1);
    frameGameInfo_layout->addWidget(labelRound, 1, 1);
    frameGameInfo_layout->addWidget(labelDaysAgo, 2, 1);

    // Add label to frameCompInfo
    labelTeamComp1 = new QLabel(frameCompInfo);
    labelTeamComp2 = new QLabel(frameCompInfo);
    labelTeamComp3 = new QLabel(frameCompInfo);
    frameCompInfo_layout->addWidget(labelTeamComp1);
    frameCompInfo_layout->addWidget(labelTeamComp2);
    frameCompInfo_layout->addWidget(labelTeamComp3);

}



void MatchWidget::customize(QString placement, QString level, QString round, QString daysAgo, QList<Trait> traits, QList<Champion> champions){

    // Fill in frameGameInfo
    labelPlacement->setText(placement);
    labelLevel->setText(level);
    labelRound->setText(round);
    labelDaysAgo->setText(daysAgo);

    // Fill in frameCompInfo


    // Add label to frameTeamInfo
    for(int i = 0; i < 9; i++){

        // Create label
        labelChamp = new QLabel(frameTeamInfo_champions);
        labelChamp_rank = new QLabel(frameTeamInfo_championsLevel);

        // Set text
        Champion champion = champions[i];
        QString championName = champion.championName;
        QString championTier = QString::number(champion.championTier);
        labelChamp->setText(championName);
        labelChamp_rank->setText(championTier);

        // Add to layout
        frameTeamInfo_champions_layout->addWidget(labelChamp);
        frameTeamInfo_championsLevel_layout->addWidget(labelChamp_rank);

    }

}














