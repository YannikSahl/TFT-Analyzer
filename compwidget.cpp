#include "compwidget.h"

// Constructor
CompWidget::CompWidget(int place, QString teamComp, double playRate, double winRate, QWidget *parent) : QWidget(parent)
{

    initialize();
    customize(place, teamComp, playRate, winRate);

}

/// Sets up Basic Structure of the Widget
void CompWidget::initialize(){

    // Set size
    this->setFixedHeight(110);

    // Apply horizontal layout to CompWidget
    compWidget_layout = new QHBoxLayout(this);

    // Create labels
    label_ranking = new QLabel(this);
    label_compName = new QLabel(this);
    label_playRate = new QLabel(this);
    label_winRate = new QLabel(this);

    label_ranking->setStyleSheet("qproperty-alignment: 'AlignVCenter | AlignHCenter';");
    label_playRate->setStyleSheet("qproperty-alignment: 'AlignVCenter | AlignHCenter';");
    label_winRate->setStyleSheet("qproperty-alignment: 'AlignVCenter | AlignHCenter';");

    // Set size
    label_ranking->setFixedWidth(80);
    label_compName->setFixedWidth(635);
    label_playRate->setFixedWidth(130);
    label_winRate->setFixedWidth(130);

    // Add labels to layout
    compWidget_layout->addWidget(label_ranking);
    compWidget_layout->addWidget(label_compName);
    compWidget_layout->addWidget(label_playRate);
    compWidget_layout->addWidget(label_winRate);

}


/// Customizes Widget: Fills in data
void CompWidget::customize(int place, QString teamComp, double playRate, double winRate){

    label_ranking->setText(QString::number(place) + ".");
    label_compName->setText(teamComp);
    label_playRate->setText(QString::number((roundf(playRate * 10000))/100) + " %");
    label_winRate->setText(QString::number(roundf(winRate*100)/100));

}














