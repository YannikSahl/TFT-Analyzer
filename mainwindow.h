#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "analyticswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showError(QString errorMessage);

private slots:
    void on_searchButton_released();
    void on_summonerNameLine_returnPressed();

private:
    Ui::MainWindow *ui;
    AnalyticsWindow *analyticsWindow;
};
#endif // MAINWINDOW_H
