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
    void setLabel_ProfileIcon(QPixmap profileIcon);
    void setLabel_RankedIcon(QPixmap profileIcon);

    void setLabel_Name(QString name);
    void setLabel_Region(QString region);
    void setLabel_Tier(QString tier);
    void setLabel_LP(QString lp);

    void setLabel_Games(QString games);
    void setLabel_Wins(QString wins);
    void setLabel_Losses(QString losses);
    void setLabel_Winrate(QString winrate);
    void setLabel_FavoriteComp(QString comp);


private:
    Ui::AnalyticsWindow *ui;
};
