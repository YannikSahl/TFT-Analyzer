#include "analyticswindow.h"
#include "ui_analyticswindow.h"
#include "compwidget.h"
#include <QPixmap>
#include <QVBoxLayout>
#include <QDebug>
#include <QScrollBar>
#include "placementchart.h"

// Constructor
AnalyticsWindow::AnalyticsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnalyticsWindow)
{
    ui->setupUi(this);

    // Hide "?"
    this->setWindowFlag(Qt::WindowContextHelpButtonHint,false);

    // Set Icon
    this->setWindowIcon(QPixmap(":/include/tft_icon.png"));

    // Set Fixed Size
    this->setFixedSize(this->size());

    // Set Window Title
    this->setWindowTitle("TFT Analysis: " + ui->label_overview_summonerName->text());

    // Initialize Match History Tab
    initializeMatchHistoryTab();

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
    ui->label_overview_tier->setText("Rank is " + tier);
}

void AnalyticsWindow::setLabel_LP(QString lp){
    ui->label_overview_lp->setText("Currently " + lp + " LP");
}

void AnalyticsWindow::setLabel_WinRateDesc(QString winRate){
    ui->label_overview_winRate->setText("Win Rate of " + winRate + "%");
}

void AnalyticsWindow::setLabel_AveragePlacements(QString averagePlacement){
    ui->label_overview_averagePlace->setText("Average Place: " + averagePlacement);
}




// Slots Statistics Tab: Ranked Box
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


// Slots Placement History Tab: Initialize Tab
void AnalyticsWindow::fillPlacementHistoryTab(QVector< QVector<int> > placements, int maxDaysAgo, int minDaysAgo){

    // Add layout to tab
    tabVLayout2 = new QVBoxLayout(ui->tab_rankings);
    ui->tab_rankings->setLayout(tabVLayout2);

    // Make series
    QScatterSeries *placementsSeries = new QScatterSeries();
    QLineSeries *placementAveragesSeries = new QSplineSeries();

    // Add to average series for Placement History tab
    int counter = 0, lastDaysAgo = 0;
    double placementSum = 0, averagePlacement = 0;
    for(int i = placements.size()-1; i >=0; i--){

        // Single placement
        QVector<int> placement = placements[i];
        int daysAgo = -placement[0];
        int place = placement[1];

        // Mirror place
        place = place + 2 * (4.5-place);

        // Store single placement (days ago, place)
        placementsSeries->append(daysAgo, place);

        // On every change store last (never on first)
        if((!(lastDaysAgo == daysAgo) && lastDaysAgo != 0)){

            // Store placement average
            averagePlacement = placementSum/counter;
            placementAveragesSeries->append(lastDaysAgo, placementSum/counter);

        }
        // Always on last
        if(i == 0){
            // Store placement average
            averagePlacement = (placementSum+place)/(counter+1);
            placementAveragesSeries->append(daysAgo, (placementSum+place)/(counter+1));
        }

        // Placement average
        placementSum += place;

        // Next i
        lastDaysAgo = daysAgo;
        counter++;
    }

    // Create graph
    PlacementChart *pChart = new PlacementChart(placementsSeries, placementAveragesSeries, maxDaysAgo, minDaysAgo);

    // Add to layout
    tabVLayout2->addWidget(pChart->chartView);

}


// Slots Match History Tab: Initialize Tab
void AnalyticsWindow::initializeMatchHistoryTab(){

    // Add layout to tab
    tabVLayout = new QVBoxLayout(ui->tab_matchHistory);
    ui->tab_matchHistory->setLayout(tabVLayout);

    // Add scroll area
    scrollArea = new QScrollArea(ui->tab_matchHistory);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tabVLayout->addWidget(scrollArea);

    // Custom scroll area layout
    scrollVLayout = new QVBoxLayout(scrollArea);
    scrollArea->setLayout(scrollVLayout);
    scrollArea->setWidgetResizable( true );

    // Add wiget
    scrollContents = new QWidget(scrollArea);
    scrollArea->setWidget(scrollContents);

    // Customize widget layout
    layout = new QVBoxLayout();

    scrollContents->setLayout( layout );
    // Set margin, padding
    scrollArea->setStyleSheet("QScrollArea > QWidget{margin: 0px;}"
                              "QScrollArea{border: 0;}");

}

// Slots Match History Tab: Add Match
void AnalyticsWindow::addMatch(QString placement, QString level, QString round, QString daysAgo, QList<Trait> traits, QList<Champion> champions){

    // Add match
    MatchWidget *match = new MatchWidget(placement, level, round, daysAgo, traits, champions, this);
    layout->addWidget(match);

    // Spacer
    QWidget *spacer = new QWidget(scrollContents);
    spacer->setStyleSheet(""
                          "border: 1px solid rgb(219, 189, 128);"
                          "margin: 10px;"
                          );
    spacer->setFixedHeight(20);
    spacer->setFixedWidth(780);
    layout->addWidget(spacer);
    layout->setAlignment(spacer, Qt::AlignHCenter);

}

// Slots Comp Tab: Add Team Comp
void AnalyticsWindow::addComp(int place, QString teamComp, double playRate, double winRate){


    // Create object
    CompWidget *cWidget = new CompWidget(place, teamComp, playRate, winRate, this);

    // Add to layout
    ui->tab_teamComps->layout()->addWidget(cWidget);

}


// Scroll to top on click
void AnalyticsWindow::on_tabWidget_tabBarClicked(int index)
{

    // If Top Teams is chosen
    if(index == 5){

        // Emit signal
        emit topTeamsRequested();

    }

}

void AnalyticsWindow::on_tabWidget_tabBarDoubleClicked(int index)
{
    // If Match History is double clicked
    if(index == 2){
        QScrollBar *vScrollBar = scrollArea->verticalScrollBar();
        vScrollBar->triggerAction(QScrollBar::SliderToMinimum);
    }
}
