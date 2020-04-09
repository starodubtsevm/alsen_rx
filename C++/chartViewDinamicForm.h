#ifndef CHARTVIEWDINAMICFORM_H
#define CHARTVIEWDINAMICFORM_H

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>

using namespace QtCharts;

namespace Ui {
class ChartViewDinamicForm;
}

class ChartViewDinamicForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChartViewDinamicForm(const QString ATitle = "",
                                  const QString AXTitle = "",
                                  const QString AYTitle = "",
                                  qreal RangeMaxX = 4000.0,
                                  qreal RangeMinX = 0.0,
                                  qreal RangeMaxY = 1.0,
                                  qreal RangeMinY = -1.0,
                                  QWidget *parent = nullptr);
    ~ChartViewDinamicForm();

    void ChartTitle(const QString ATitle);
    void XTitle(const QString ATitle);
    void YTitle(const QString ATitle);
    void RangeX(const qreal AMin = 0.0, const qreal AMax = 4000.0);
    void RangeY(const qreal AMin = -1.0, const qreal AMax = 1.0);

    void replace(QVector<QPointF> points);
    QVector<QPointF> pointsVector() const;

private:
    Ui::ChartViewDinamicForm *ui;

    QChart *      FChart;
    QChartView *  FView;
    QLineSeries * FSeries;
    QValueAxis *  FAxisX;
    QValueAxis *  FAxisY;
};

#endif // CHARTVIEWDINAMICFORM_H
