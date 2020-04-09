#ifndef CHARTVIEWFORM_H
#define CHARTVIEWFORM_H

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QPushButton>
#include <QLineSeries>
#include <QValueAxis>

using namespace QtCharts;

namespace Ui {
class ChartViewForm;
}

class ChartViewForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChartViewForm(const QString ATitle,
                           const double * ASamples,
                           const int ASamplesCount,
                           const QString AXTitle,
                           const QString AYTitle,
                           const int ASectionCount = 1,
                           const double AXFactor = 1.0,
                           const double AYFactor = 1.0,
                           QWidget *parent = nullptr);
    ~ChartViewForm();

    QString Title() const { return FTitle; }

private:
    struct SeriesStruct
    {
        QLineSeries *         Series;
        // границы серии
        QPair<double,double>  SeriesBoundaries;
        SeriesStruct();
        ~SeriesStruct();
    };

    Ui::ChartViewForm * ui;

    QVector<SeriesStruct> * FSeriesVector;
    QChart *                FChart;
    QChartView *            FChartView;
    QPushButton *           FLeftButton;
    QPushButton *           FRightButton;

    int                     FCurrentSectionIndex;
    QLineSeries *           FCurrentSeries;
    QValueAxis *            FCurrentXAxis;
    QValueAxis *            FCurrentYAxis;
    double                  FXFactor;
    double                  FYFactor;

    QString                 FTitle;

signals:
    void setCurrentSection();

private slots:

    void leftClicked(bool checked = false);
    void rightClicked(bool checked = false);
    void setCurrentSectionSlot();
};

#endif // CHARTVIEWFORM_H
