#ifndef CHARTSVIEWFORM_H
#define CHARTSVIEWFORM_H

#include <QWidget>
#include <QVector>
#include "chartviewform.h"

namespace Ui {
class ChartsViewForm;
}

class ChartsViewForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChartsViewForm(QWidget *parent = nullptr);
    ~ChartsViewForm();

    int addChart(const QString ATitle,
                 const double * ASamples,
                 const int ASamplesCount,
                 const int ASectionCount = 1,
                 const QString AXTitle = "",
                 const QString AYTitle = "",
                 const double AXFactor = 1.0,
                 const double AYFactor = 1.0);

    int count() const { return  FForms.size(); }
    const ChartViewForm & operator[](const int AIndex) const {return *FForms.at(AIndex);}

    void removeByChartTitle(const QString AChartTitle);
    void clear();

private:
    Ui::ChartsViewForm *      ui;
    QVector<ChartViewForm  *> FForms;
};

#endif // CHARTSVIEWFORM_H
