#ifndef COMPWIDGET_H
#define COMPWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

class CompWidget : public QWidget
{
    Q_OBJECT


private:
    QHBoxLayout *compWidget_layout;

    QLabel *label_ranking;
    QLabel *label_compName;
    QLabel *label_playRate;
    QLabel *label_winRate;


public:
    explicit CompWidget(int place, QString teamComp, double playRate, double winRate, QWidget *parent = nullptr);

    void initialize();

    void customize(int place, QString teamComp, double playRate, double winRate);


signals:

};

#endif // COMPWIDGET_H
