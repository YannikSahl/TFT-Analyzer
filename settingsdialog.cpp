#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QString>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    matches = ui->matchesLine->text().toInt();
    apiKey = ui->apiKeyLine->text();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

// Store any changes that were made
void SettingsDialog::on_buttonBox_accepted()
{
    matches = ui->matchesLine->text().toInt();
    apiKey = ui->apiKeyLine->text();
}
