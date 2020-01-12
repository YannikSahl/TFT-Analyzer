#include "matchwidget.h"
#include <QVBoxLayout>
#include <QDebug>


// Constructor
MatchWidget::MatchWidget(QString placement, QString level, QString round, QString daysAgo, QList<Trait> traits, QList<Champion> champions, QWidget *parent) : QWidget(parent)
{

    initialize();
    customize(placement, level, round, daysAgo, traits, champions);

}


void MatchWidget::initialize(){

    // Set size
    this->setFixedHeight(160);
    this->setStyleSheet("border: 0.5px solid;");

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

    // Set sizes main container
    frameGameInfo->setFixedWidth(220);
    frameCompInfo->setFixedWidth(170);

    // Set sizes sub container
    frameTeamInfo_champions->setFixedHeight(80);
    frameTeamInfo_championsLevel->setFixedHeight(30);

    // Set alignment sub container layouts
    frameTeamInfo_champions_layout->setAlignment(Qt::AlignLeft);
    frameTeamInfo_championsLevel_layout->setAlignment(Qt::AlignLeft);

    // Set padding, margin for frameTeamInfo
    frameTeamInfo->setStyleSheet("*{"
                                 "margin: 0px;"
                                 "padding: 0px;"
                                 "}"
                                 );

}



void MatchWidget::customize(QString placement, QString level, QString round, QString daysAgo, QList<Trait> traits, QList<Champion> champions){

    // Fill in frameGameInfo
    QString placementString = "#" + placement;
    QString levelString = "Level: " + level;
    QString roundString = "Round: " + round;
    QString daysAgoString = daysAgo + " days ago";
    labelPlacement->setText(placementString);
    labelLevel->setText(levelString);
    labelRound->setText(roundString);
    labelDaysAgo->setText(daysAgoString);

    // Custome frameGameInfo
    labelPlacement->setStyleSheet("font-size: 30px;"
                                  "font-weight: bold;"
                                  );

    // Iterate over Traits
    for(Trait trait : traits){

        // Add to label if played
        if(trait.numUnits > labelTeamComp1->text().toInt()){
            labelTeamComp2->setText(labelTeamComp1->text());
            labelTeamComp1->setText(QString::number(trait.numUnits) + " " + trait.traitName);
        }
        else if(trait.numUnits > labelTeamComp2->text().toInt()){
            labelTeamComp3->setText(labelTeamComp2->text());
            labelTeamComp1->setText(QString::number(trait.numUnits) + " " + trait.traitName);
        }
        else if(trait.numUnits > labelTeamComp3->text().toInt()){
            labelTeamComp1->setText(QString::number(trait.numUnits) + " " + trait.traitName);
        }

    }
    labelTeamComp1->setText("6 Blademaster");
    labelTeamComp2->setText("6 Blademaster");
    labelTeamComp3->setText("6 Blademaster");

    // Add label to frameTeamInfo
    for(int i = 0; i < champions.size(); i++){

        // Create label
        labelChamp = new QLabel(frameTeamInfo_champions);
        labelChamp_rank = new QLabel(frameTeamInfo_championsLevel);

        // Set sizes
        labelChamp->setFixedSize(50, 50);
        labelChamp_rank->setFixedSize(50, 20);
        labelChamp_rank->setAlignment(Qt::AlignHCenter);


        // Champion data
        Champion champion = champions[i];
        QString championName = champion.championName;
        QString championTier = QString::number(champion.championTier);
        QString championCost = QString::number(champion.championCost);

        // Fill champion icon and tier
        QPixmap championIcon(":/include/champions/" + championName + ".jpg");
        labelChamp->setPixmap(championIcon);
        labelChamp->setScaledContents(true);
        qInfo() << "Champ name: " << championName << "; Pixmap: " << championIcon.size();

        if(championTier == "1"){labelChamp_rank->setText("*");}
        if(championTier == "2"){labelChamp_rank->setText("**");}
        if(championTier == "3"){labelChamp_rank->setText("***");}

        // Set border according to cost
        if(championCost == "1"){labelChamp->setStyleSheet("border-color: grey;");}
        if(championCost == "2"){labelChamp->setStyleSheet("border-color: green;");}
        if(championCost == "3"){labelChamp->setStyleSheet("border-color: blue;");}
        if(championCost == "4"){labelChamp->setStyleSheet("border-color: purple;");}
        if(championCost == "5"){labelChamp->setStyleSheet("border-color: orange;");}
        if(championCost == "7"){labelChamp->setStyleSheet("border-color: white;");}
        labelChamp->setStyleSheet("border: 2px solid;");

        // Add to layout
        frameTeamInfo_champions_layout->addWidget(labelChamp);
        frameTeamInfo_championsLevel_layout->addWidget(labelChamp_rank);

    }

}














