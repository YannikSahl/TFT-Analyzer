#pragma once

#include <QMainWindow>
#include <QLabel>
#include "analyticswindow.h"
#include "requesthandler.h"
#include "settingsdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT



private:
    Ui::MainWindow *ui;
    AnalyticsWindow *analyticsWindow;
    SettingsDialog *settingsDialog;
    RequestHandler *requestHandler;

    void showLoadingSymbol(QLabel *lbl);
    void hideLoadingSymbol(QLabel *lbl);



private slots:
    void on_searchButton_released();
    void on_summonerNameLine_returnPressed();

    void on_settingsButton_clicked();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showError(QString errorMessage);

public slots:
    void setAnalysisStatus(QString status);




};
