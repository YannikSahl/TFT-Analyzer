#include "mainwindow.h"
#include "analyticswindow.h"
#include "ui_mainwindow.h"
#include "requesthandler.h"

// Constructor
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

// Destructor
MainWindow::~MainWindow()
{
    delete ui;
}

// Start Search on Enter Press
void MainWindow::on_searchButton_released()
{

    // Read User Input
    QString apiKey = "RGAPI-eaa7cde0-4769-4b70-9141-400f9cb4802a";
    QString summonerName = ui->summonerNameLine->text();
    QString region = ui->regionChooserBox->currentText();

    // Create RequestHandler and AnalyticsWindow objects
    analyticsWindow = new AnalyticsWindow(this);
    RequestHandler *requestHandler = new RequestHandler(analyticsWindow, apiKey, summonerName, region);

    // Show Analytics Window
    requestHandler->handleRequest();
    analyticsWindow->show();

}

// Fire up Search on Enter Press
void MainWindow::on_summonerNameLine_returnPressed()
{
    on_searchButton_released();
}
