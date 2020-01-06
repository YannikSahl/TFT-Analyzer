#include "analyticswindow.h"
#include "ui_analyticswindow.h"


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
