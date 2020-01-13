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

    // Set sizes main container
    frameGameInfo->setFixedWidth(220);
    frameCompInfo->setFixedWidth(170);
    frameTeamInfo->setFixedHeight(90);

    // Set sizes sub container
    frameTeamInfo_champions->setFixedHeight(50);
    frameTeamInfo_championsLevel->setFixedHeight(20);

    // Set alignment sub container layouts
    frameTeamInfo_champions_layout->setAlignment(Qt::AlignLeft);
    frameTeamInfo_championsLevel_layout->setAlignment(Qt::AlignLeft);

    // Set padding, margin for frameTeamInfo
    frameTeamInfo_layout->setContentsMargins(0, 0, 0, 0);
    frameTeamInfo_layout->setMargin(10);
    frameTeamInfo_champions_layout->setContentsMargins(0, 0, 0, 0);
    frameTeamInfo_championsLevel_layout->setContentsMargins(0, 0, 0, 0);

    frameGameInfo->setStyleSheet(".QFrame{"
                                 "border-right: 2px solid;"
                                 "border-color: rgb(219, 189, 128);"
                                 "}");

}



void MatchWidget::customize(QString placement, QString level, QString round, QString daysAgo, QList<Trait> traits, QList<Champion> champions){

    // Fill in frameGameInfo
    QString placementString = "#" + placement;
    QString levelString = "Level: " + level;
    QString roundString = "Round: " + round;
    QString daysAgoString = "";
    if(daysAgo == "1"){
        daysAgoString = daysAgo + " day ago";
    }else{
        daysAgoString = daysAgo + " days ago";
    }

    labelPlacement->setText(placementString);
    labelLevel->setText(levelString);
    labelRound->setText(roundString);
    labelDaysAgo->setText(daysAgoString);

    // Custome frameGameInfo
    labelPlacement->setStyleSheet("font-size: 30px;"
                                  "font-weight: bold;"
                                  );


    // Temp counter
    int counter = 0;

    // Create trait label
    for(int i = traits.size()-1; counter < 4 && i >= 0 ; i--){

        // Get trait data
        QLabel *labelTeamComp = new QLabel(frameCompInfo);
        Trait trait = traits[i];
        QString unitsTrait = QString::number(trait.numUnits);
        QString nameTrait = trait.traitName;
        int currentTierTrait = trait.tierCurrent;

        // Only if first buff is reached
        if(currentTierTrait>0){
            // Add to label
            labelTeamComp->setText(unitsTrait + "  " + nameTrait);
            frameCompInfo_layout->addWidget(labelTeamComp);
            counter++;
        }
    }

    // Add labels to frameTeamInfo
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
        if(championCost == "1"){labelChamp->setStyleSheet("border: 2px solid; border-color: grey;");}
        if(championCost == "2"){labelChamp->setStyleSheet("border: 2px solid; border-color: green;");}
        if(championCost == "3"){labelChamp->setStyleSheet("border: 2px solid; border-color: blue;");}
        if(championCost == "4"){labelChamp->setStyleSheet("border: 2px solid; border-color: purple;");}
        if(championCost == "5"){labelChamp->setStyleSheet("border: 2px solid; border-color: orange;");}
        if(championCost == "6"){labelChamp->setStyleSheet("border: 2px solid; border-color: white;");}

        // Add to layout
        frameTeamInfo_champions_layout->addWidget(labelChamp);
        frameTeamInfo_championsLevel_layout->addWidget(labelChamp_rank);

    }

}














