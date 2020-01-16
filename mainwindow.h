#pragma once

#include <QMainWindow>
#include <QLabel>
#include "analyticswindow.h"
#include "requesthandler.h"
#include "settingsdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


/// Or rather: Search Window
class MainWindow : public QMainWindow
{
    Q_OBJECT



private:

    /// This dude
    Ui::MainWindow *ui;

    /// Instance of the analyticsWindow to invoke it: Main Result Window
    AnalyticsWindow *analyticsWindow;

    /// Instance of the settingsDialog to invoke it: Displays Errors to User
    SettingsDialog *settingsDialog;

    /// Instance of the requestHandler to invoke it: Queries RIOT's API
    RequestHandler *requestHandler;

    // Helper Methods to increase user experience
    void showLoadingSymbol(QLabel *lbl);
    void hideLoadingSymbol(QLabel *lbl);



private slots:

    // When the user clicks the Search Button
    void on_searchButton_released();

    // When the user presses Return
    void on_summonerNameLine_returnPressed();

    // When the invisible Settings Button is clicked
    void on_settingsButton_clicked();

public:

    // Constructor and Destructor
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Display Error Message
    void showError(QString errorMessage);

public slots:

    // Expose slot to receive Signals from other objects in order to reflect current Status
    void setAnalysisStatus(QString status);




};
