#include "placementchart.h"
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QCategoryAxis>
#include <QDebug>

using namespace QtCharts;


PlacementChart::PlacementChart(QScatterSeries *placements, QLineSeries *averagePlacements, int maxDaysAgo, int minDaysAgo, QWidget *parent) : QWidget(parent)
{

    // Create chart
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(placements);
    chart->addSeries(averagePlacements);

    // Customize graphs
    placements->setMarkerSize(10);
    QPen pen(QRgb(qRgb(219, 189, 128)));
    pen.setWidth(5);
    placements->setPen(pen);
    pen.setWidth(3);
    averagePlacements->setPen(pen);

    // Customize chart background
    chart->setBackgroundVisible(false);

    // Customize plot area background
    chart->setPlotAreaBackgroundVisible(false);

    // Create axis
    QCategoryAxis *axisX = new QCategoryAxis();
    QCategoryAxis *axisY = new QCategoryAxis();

    // Customize starting point
    axisY->setStartValue(1);

    // Customize axis label font
    QFont labelsFont;
    labelsFont.setPixelSize(20);
    labelsFont.setItalic(true);
    axisX->setLabelsFont(labelsFont);
    axisY->setLabelsFont(labelsFont);

    // Customize axis colors
    QPen axisPen(QRgb(qRgb(219, 189, 128)));
    axisPen.setWidth(2);
    axisX->setLinePen(axisPen);
    axisY->setLinePen(axisPen);

    // Customize axis label colors
    QBrush axisBrush(QColor(153, 204, 204, 150));
    axisX->setLabelsBrush(axisBrush);
    axisY->setLabelsBrush(axisBrush);

    // Customize grid lines and shades
    axisX->setGridLineVisible(false);
    axisY->setGridLineVisible(false);

    // Append segments
    axisX->append("Today", 0);
    axisX->setRange(-maxDaysAgo-1, 1);

    axisY->setRange(0, 9);
    axisY->append("5th to 8th  ", 4);
    axisY->append("4th and 5th  ", 5);
    axisY->append("1st to 4th  ", 9);

    // Append axis
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    placements->attachAxis(axisX);
    placements->attachAxis(axisY);
    averagePlacements->attachAxis(axisX);
    averagePlacements->attachAxis(axisY);

    // Set chart title
    QFont font;
    font.setPixelSize(30);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(QRgb(qRgb(219, 189, 128))));
    chart->setTitle("Single Rankings (Dots) and Average Ranking (Spline)");


    // Create view
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setChart(chart);

}
