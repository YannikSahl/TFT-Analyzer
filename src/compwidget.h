#pragma once
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

/*!
 * \brief The CompWidget class defines a widget that displays information about a certain Team, to be used in 'Your Team' and 'Top Team' Tab
 */
class CompWidget : public QWidget
{
    Q_OBJECT


private:

    /*!
     * \brief compWidget_layout is the Widget's layout.
     */
    QHBoxLayout *compWidget_layout;

    // Different labels to show information
    QLabel *label_ranking;
    QLabel *label_compName;
    QLabel *label_playRate;
    QLabel *label_winRate;


public:

    /*!
     * \brief CompWidget Constructor.
     */
    explicit CompWidget(int place, QString teamComp, double playRate, double winRate, QWidget *parent = nullptr);

    /*!
     * \brief initialize sets up Basic Structure of the Widget.
     */
    void initialize();

    /*!
     * \brief customize customizes Widget: Fills in data.
     */
    void customize(int place, QString teamComp, double playRate, double winRate);


signals:

};
