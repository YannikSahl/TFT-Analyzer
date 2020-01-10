#include "analyticswindow.h"
#include "ui_analyticswindow.h"
#include <QPixmap>


// Constructor
AnalyticsWindow::AnalyticsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnalyticsWindow)
{
    ui->setupUi(this);

    // Hide "?"
    this->setWindowFlag(Qt::WindowContextHelpButtonHint,false);

    // Set Icon
    this->setWindowIcon(QPixmap(":/icons/include/tftStuff/tft_icon.png"));

    // Set Fixed Size
    this->setSizeGripEnabled(false);
}

// Destructor
AnalyticsWindow::~AnalyticsWindow()
{
    delete ui;
}


// Slots Overview Tab
void AnalyticsWindow::setLabel_ProfileIcon(QPixmap profileIcon){
    ui->label_overview_picture_profileIcon->setPixmap(profileIcon);
    ui->label_overview_picture_profileIcon->setScaledContents(true);
}

void AnalyticsWindow::setLabel_RankedIcon(QPixmap profileIcon){
    ui->label_overview_picture_ranked->setPixmap(profileIcon);
    ui->label_overview_picture_ranked->setScaledContents(true);
}

void AnalyticsWindow::setLabel_Name(QString name){
    ui->label_overview_summonerName->setText(name);
}

void AnalyticsWindow::setLabel_Region(QString region){
    ui->label_overview_region->setText(region);
}

void AnalyticsWindow::setLabel_Tier(QString tier){
    ui->label_overview_tier->setText("Ranked Tier is " + tier);
}

void AnalyticsWindow::setLabel_LP(QString lp){
    ui->label_overview_lp->setText("With currently " + lp + " LP");
}

void AnalyticsWindow::setLabel_WinRateDesc(QString winRate){
    ui->label_overview_winRate->setText("Win Rate of " + winRate + "%");
}

void AnalyticsWindow::setLabel_AveragePlacements(QString averagePlacement){
    ui->label_overview_averagePlace->setText("Average Place: " + averagePlacement);
}




// Slots Overview Tab: Ranked Box
void AnalyticsWindow::setLabel_Games(QString games){
    ui->label_gamesPlayed_data->setText(games);
}

void AnalyticsWindow::setLabel_Wins(QString wins){
    ui->label_wins_data->setText(wins);
}

void AnalyticsWindow::setLabel_Losses(QString losses){
    ui->label_losses_data->setText(losses);
}

void AnalyticsWindow::setLabel_Winrate(QString winrate){
    ui->label_winRate_data->setText(winrate);
}

void AnalyticsWindow::setLabel_HotStreak(QString yesno){
    ui->label_hotStreak_data->setText(yesno);
}

void AnalyticsWindow::setLabel_Placements(QString placements){
    ui->label_placementHistory_data->setText(placements);
}

// Slots Overview Tab: Summoner Box
void AnalyticsWindow::setLabel_summonerLevel(QString summonerLevel){
    ui->label_summonerLevel_data->setText(summonerLevel);
}

void AnalyticsWindow::setLabel_activityStatus(QString active){
    ui->label_activity_data->setText(active);
}


// Slots Overview Tab: Team Comp Box
void AnalyticsWindow::setLabel_FavoriteComp(QString comp){
    ui->label_favorite_data->setText(comp);
}

void AnalyticsWindow::setLabel_FavoriteComp2(QString comp){
    ui->label_favorite2_data->setText(comp);
}

