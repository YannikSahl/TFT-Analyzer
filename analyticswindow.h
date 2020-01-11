#pragma once

#include <QDialog>

namespace Ui {
class AnalyticsWindow;
}

class AnalyticsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AnalyticsWindow(QWidget *parent = nullptr);
    ~AnalyticsWindow();



public slots:

    // Overview
    void setLabel_ProfileIcon(QPixmap profileIcon);
    void setLabel_RankedIcon(QPixmap profileIcon);

    void setLabel_Name(QString name);
    void setLabel_Region(QString region);
    void setLabel_Tier(QString tier);
    void setLabel_LP(QString lp);
    void setLabel_WinRateDesc(QString winRate);
    void setLabel_AveragePlacements(QString averagePlacement);


    // Statistics: Ranked Box
    void setLabel_Games(QString games);
    void setLabel_Wins(QString wins);
    void setLabel_Losses(QString losses);
    void setLabel_Winrate(QString winrate);
    void setLabel_HotStreak(QString yesno);
    void setLabel_Placements(QString placements);

    // Statistics: Summoner Box
    void setLabel_summonerLevel(QString summonerLevel);
    void setLabel_activityStatus(QString active);

    // Statistics: Team Comp Box
    void setLabel_FavoriteComp(QString comp);
    void setLabel_FavoriteComp2(QString comp);

    // Match History
    void initializeMatchHistoryTab();
    void addMatch(QString placement, QString level, QString round, QString daysAgo, QHash<QString, int> traits, QHash<QString, int> champions);


private:
    Ui::AnalyticsWindow *ui;
};
