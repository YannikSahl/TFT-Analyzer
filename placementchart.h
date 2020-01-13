#ifndef PLACEMENTCHART_H
#define PLACEMENTCHART_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QLineSeries>

using namespace QtCharts;

class PlacementChart : public QWidget
{
    Q_OBJECT



public:
    explicit PlacementChart(QScatterSeries *series, QLineSeries *averagePlacements, int minDaysAgo, int maxDaysAgo, QWidget *parent = nullptr);

    QChartView *chartView;





signals:



};

#endif // PLACEMENTCHART_H
