#include "mainwindow.h"
#include "analyticswindow.h"
#include "ui_mainwindow.h"
#include "requesthandler.h"
#include <QMessageBox>
#include <QPixmap>

// Constructor
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QPixmap(":/icons/include/tftStuff/tft_icon.png"));
}

// Destructor
MainWindow::~MainWindow()
{
    delete ui;
}

// Start Search Button Press
void MainWindow::on_searchButton_released()
{

    // Read User Input
    QString apiKey = "RGAPI-67b6bdfc-3bee-43a9-8731-c10c930d16d6";
    QString summonerName = ui->summonerNameLine->text();
    QString region = ui->regionChooserBox->currentText();

    // Create RequestHandler and AnalyticsWindow objects
    analyticsWindow = new AnalyticsWindow(this);
    RequestHandler *requestHandler = new RequestHandler(analyticsWindow, apiKey, summonerName, region);

    // If no Errors are returned
    if(requestHandler->handleRequest() == 1){

        // Show Analytics Window
        analyticsWindow->show();

    }
    // Else Show Error: Summoner not found
    else if(requestHandler->handleRequest() == 2){
        QString errorMessage = "Failed to find summoner '" + summonerName + "' in region '" + region + "'. \nCheck your input.";
        showError(errorMessage);
    }
    // Else Show Error: No Matches found
    else if(requestHandler->handleRequest() == 3){
        QString errorMessage = "Failed to find TFT Match Data for '" + summonerName + "' in region '" + region + "'.\nDid you play Ranked yet?";
        showError(errorMessage);
    }


}


// Display Error Message
void MainWindow::showError(QString errorMessage){

    QMessageBox msgBox;
    msgBox.setWindowTitle("Error");
    msgBox.setText(errorMessage);
    msgBox.setWindowIcon(QPixmap(":/icons/include/tftStuff/tft_icon.png"));
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.button(QMessageBox::Ok)->setText(" Try Again ");
    msgBox.button(QMessageBox::Ok)->setStyleSheet(""
                                                  "QPushButton{"
                                                  "padding: 4px;"
                                                  "background-color: rgb(255, 170, 0);"
                                                  "color: rgb(0, 0, 94);"
                                                  "border-radius: 16px;"
                                                  "}"
                                                  "QPushButton::hover{"
                                                  "background-color: rgb(218, 145, 0);"
                                                  "}"
                                                  "QPushButton::pressed{"
                                                  "background-color: rgb(138, 92, 0);"
                                                  "}"
                                                  );

    msgBox.setStyleSheet(""
                         "background-color: rgb(0, 0, 94);"
                         "color: rgb(255, 170, 0);"
                         "font: MS Sans Sarif;"
                         "font-weight: bold;"
                         "font-size: 20px;"
                         ""
                         );
    msgBox.exec();

}



// Fire up Search on Enter Press
void MainWindow::on_summonerNameLine_returnPressed()
{
    on_searchButton_released();
}
