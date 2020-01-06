#pragma once

#include <QDialog>

namespace Ui {
class AnalyticsWindow;
}

class AnalyticsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AnalyticsWindow(QWidget *parent = nullptr);
    ~AnalyticsWindow();



public slots:
    void setLabel_Name(QString name);
    void setLabel_Region(QString region);
    void setLabel_Tier(QString tier);
    void setLabel_LP(QString lp);


private:
    Ui::AnalyticsWindow *ui;
};
