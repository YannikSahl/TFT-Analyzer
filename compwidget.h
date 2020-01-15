#pragma once
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

/// Widget that displays information about a certain Team, to be used in 'Your Team' and 'Top Team' Tab
class CompWidget : public QWidget
{
    Q_OBJECT


private:

    // Layout of the widget
    QHBoxLayout *compWidget_layout;

    // Different labels to show information
    QLabel *label_ranking;
    QLabel *label_compName;
    QLabel *label_playRate;
    QLabel *label_winRate;


public:

    // Constructor
    explicit CompWidget(int place, QString teamComp, double playRate, double winRate, QWidget *parent = nullptr);

    /// Sets up Basic Structure of the Widget
    void initialize();

    /// Customizes Widget: Fills in data
    void customize(int place, QString teamComp, double playRate, double winRate);


signals:

};
