#pragma once
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QLineSeries>

using namespace QtCharts;


/// Chart that shows the recent Ranking
class PlacementChart : public QWidget
{
    Q_OBJECT



public:

    // Constructor
    explicit PlacementChart(QScatterSeries *series, QLineSeries *averagePlacements, int minDaysAgo, int maxDaysAgo, QWidget *parent = nullptr);

    // Chart View shown to the user
    QChartView *chartView;

};
