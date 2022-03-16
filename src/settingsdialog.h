#pragma once
#include <QDialog>
#include <QString>

namespace Ui {
class SettingsDialog;
}

/// Secret Settings Dialog
class SettingsDialog : public QDialog
{
    Q_OBJECT


public:

    // Constructor and Destructor
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

    // Two settings member variables
    int matches;
    QString apiKey;


private slots:

    // When the OK Button is pressed
    void on_buttonBox_accepted();

private:
    Ui::SettingsDialog *ui;
};
