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

    // Set Icon
    this->setWindowIcon(QPixmap(":/icons/include/tftStuff/tft_icon.png"));

    // Set Fixed Size
    this->setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
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
    QString apiKey = "RGAPI-034abf14-034c-445c-9297-490c06534379";
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
                                                  "background-color: rgb(207, 168, 85);"
                                                  "color: black;"
                                                  "border-radius: 16px;"
                                                  "margin: 15px;"
                                                  "}"
                                                  "QPushButton::hover{"
                                                  "background-color: rgb(166, 133, 68);"
                                                  "}"
                                                  "QPushButton::pressed{"
                                                  "background-color: rgb(99, 79, 40);"
                                                  "}"
                                                  );
    msgBox.textFormat();

    msgBox.setStyleSheet(""
                         "QMessageBox QLabel{"
                         "background: transparent;"
                         "margin: 10px;"
                         "margin-right: 30px;"
                         "}"
                         "*{"
                         "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(7, 25, 43, 255), stop:1 rgba(19, 171, 194, 255));"
                         "color: rgb(219, 189, 128);"
                         "font: MS Sans Sarif;"
                         "font-size: 20px;"
                         "}"
                         );
    msgBox.exec();

}



// Fire up Search on Enter Press
void MainWindow::on_summonerNameLine_returnPressed()
{
    on_searchButton_released();
}
