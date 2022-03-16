#pragma once

#include <QDialog>
#include <QVBoxLayout>
#include <QScrollArea>
#include <matchwidget.h>
#include "trait.h"
#include "champion.h"
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLineSeries>

namespace Ui {
class AnalyticsWindow;
}

/*!
 * \brief The AnalyticsWindow class displays information to the user.
 */
class AnalyticsWindow : public QDialog
{
    Q_OBJECT

public:

    /*!
     * \brief AnalyticsWindow Constructor.
     */
    explicit AnalyticsWindow(QWidget *parent = nullptr);

    /*!
     * \brief ~AnalyticsWindow Destructor.
     */
    ~AnalyticsWindow();


public slots:

    // Overview Tab: Interface to set labels
    void setLabel_ProfileIcon(QPixmap profileIcon);
    void setLabel_RankedIcon(QPixmap profileIcon);
    void setLabel_Name(QString name);
    void setLabel_Region(QString region);
    void setLabel_Tier(QString tier);
    void setLabel_LP(QString lp);
    void setLabel_WinRateDesc(QString winRate);
    void setLabel_AveragePlacements(QString averagePlacement);

    // Statistics: Ranked Box: Interface to set labels
    void setLabel_Games(QString games);
    void setLabel_Wins(QString wins);
    void setLabel_Losses(QString losses);
    void setLabel_Winrate(QString winrate);
    void setLabel_HotStreak(QString yesno);
    void setLabel_Placements(QString placements);

    // Statistics: Summoner Box: Interface to set labels
    void setLabel_summonerLevel(QString summonerLevel);
    void setLabel_activityStatus(QString active);

    // Statistics: Team Comp Box: Interface to set labels
    void setLabel_FavoriteComp(QString comp);
    void setLabel_FavoriteComp2(QString comp);

    /*!
     * \brief initializeMatchHistoryTab initializes the Match History Tab by configuring the layout.
     */
    void initializeMatchHistoryTab();


    /*!
     * \brief addMatch adds a MatchWidget that was constructed using the passed parameters.
     */
    void addMatch(QString placement, QString level, QString round, QString daysAgo, QList<Trait> traits, QList<Champion> champions);


    /*!
     * \brief fillPlacementHistoryTab uses the passed data to configure the graph shown in the "Rankings" Tab.
     */
    void fillPlacementHistoryTab(QVector< QVector<int> > placements, int maxDaysAgo, int minDaysAgo);

    /*!
     * \brief addComp adds a CompWidget that was constructed using the passed parameters.
     */
    void addComp(int place, QString teamComp, double playRate, double winRate, int choiceTab);


    /*!
     * \brief setTopTeamsStatus sets the Label on the "Ranking" Tab to inform the user about the current status.
     */
    void setTopTeamsStatus(QString status);

private:
    Ui::AnalyticsWindow *ui;

    // Match History Elements
    QVBoxLayout *tabVLayout;
    QScrollArea *scrollArea;
    QVBoxLayout *scrollVLayout;
    QWidget *scrollContents;
    QVBoxLayout *layout;

    // Placement History Elements
    QVBoxLayout *tabVLayout2;

private slots:

    /*!
     * \brief on_tabWidget_tabBarClicked is called whenever the Tab Bar is single-clicked.
     * \param index is the tab being clicked.
     */
    void on_tabWidget_tabBarClicked(int index);

    // Tab Bar: Double Click
    /*!
     * \brief on_tabWidget_tabBarDoubleClicked is called whenever the Tab Bar is double-clicked.
     * \param index is the tab being clicked.
     */
    void on_tabWidget_tabBarDoubleClicked(int index);


signals:

    /*!
     * \brief topTeamsRequested is a signal emitted to fill the "Top Teams" Tab.
     */
    void topTeamsRequested();

};
