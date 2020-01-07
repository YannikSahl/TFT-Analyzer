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
}

// Destructor
AnalyticsWindow::~AnalyticsWindow()
{
    delete ui;
}


///// SLOTS
void AnalyticsWindow::setLabel_ProfileIcon(QPixmap profileIcon){
    ui->label_profileIcon->setPixmap(profileIcon);
    ui->label_profileIcon->setScaledContents(true);
}

void AnalyticsWindow::setLabel_Name(QString name){
    ui->label_data_summonerName->setText(name);
}

void AnalyticsWindow::setLabel_Region(QString region){
    ui->label_data_region->setText(region);
}

void AnalyticsWindow::setLabel_Tier(QString tier){
    ui->label_data_tier->setText(tier);
}

void AnalyticsWindow::setLabel_LP(QString lp){
    ui->label_data_leaguePoints->setText(lp);
}

void AnalyticsWindow::setLabel_Games(QString games){
    ui->label_data_gamesPlayed->setText(games);
}

void AnalyticsWindow::setLabel_Wins(QString wins){
    ui->label_data_wins->setText(wins);
}

void AnalyticsWindow::setLabel_Losses(QString losses){
    ui->label_data_losses->setText(losses);
}

void AnalyticsWindow::setLabel_Winrate(QString winrate){
    ui->label_data_winRate->setText(winrate);
}

void AnalyticsWindow::setLabel_FavoriteComp(QString comp){
    ui->labeL_data_favoriteComp->setText(comp);
}

