#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

    int matches;

private slots:

    void on_buttonBox_accepted();

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
