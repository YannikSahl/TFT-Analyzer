#include "mainwindow.h"
#include "analyticswindow.h"
#include "ui_mainwindow.h"
#include "requesthandler.h"
#include <QMessageBox>

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

    // If Summoner Name was found
    if(requestHandler->handleRequest() == true){

        // Show Analytics Window
        analyticsWindow->show();

    }
    // Else show Error
    else{
        showError();
    }


}

// Show error if Summoner Name could not be found
void MainWindow::showError(){

    QMessageBox msgBox;
    msgBox.setWindowTitle("Error");
    msgBox.setText("Failed to find summoner by provided input, please check again.");
    msgBox.setStyleSheet(""
                         "background-color: rgb(0, 0, 94);"
                         "color: rgb(255, 170, 0);"
                         "font-size: 24px;"
                         "QMessageBox QPushButton{"
                         "border: 10px solid;"
                         "}");
    msgBox.exec();

}


// Fire up Search on Enter Press
void MainWindow::on_summonerNameLine_returnPressed()
{
    on_searchButton_released();
}
