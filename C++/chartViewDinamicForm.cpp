#include "chartViewDinamicForm.h"
#include "ui_chartViewDinamicForm.h"

ChartViewDinamicForm::ChartViewDinamicForm(const QString ATitle,
                                           const QString AXTitle,
                                           const QString AYTitle,
                                           qreal RangeMaxX,
                                           qreal RangeMinX,
                                           qreal RangeMaxY,
                                           qreal RangeMinY,
                                           QWidget *parent)
    :QWidget(parent),
     ui(new Ui::ChartViewDinamicForm),
     FChart(new QChart),
     FView(new QChartView(FChart)),
     FSeries(new QLineSeries),
     FAxisX(new QValueAxis),
     FAxisY(new QValueAxis)
{
    ui->setupUi(this);

    FView->setMinimumSize(640, 400);

    FChart->setTitle(ATitle);
    FChart->addSeries(FSeries);
    FChart->legend()->hide();

    FAxisX->setTitleText(AXTitle);
    FAxisX->setRange(RangeMinX,RangeMaxX);
    FAxisX->setLabelFormat("%g");

    FAxisY->setTitleText(AYTitle);
    FAxisY->setRange(RangeMinY,RangeMaxY);
    FAxisY->setLabelFormat("%g");

    FChart->setAxisX(FAxisX,FSeries);
    FChart->setAxisY(FAxisY,FSeries);

    ui->vlMain->addWidget(FView);

}

ChartViewDinamicForm::~ChartViewDinamicForm()
{
    delete ui;
}

void ChartViewDinamicForm::ChartTitle(const QString ATitle)
{
    FChart->setTitle(ATitle);
}

void ChartViewDinamicForm::XTitle(const QString ATitle)
{
    FAxisX->setTitleText(ATitle);
}

void ChartViewDinamicForm::YTitle(const QString ATitle)
{
    FAxisY->setTitleText(ATitle);
}

void ChartViewDinamicForm::RangeX(const qreal AMin, const qreal AMax)
{
    FAxisX->setRange(AMin,AMax);
}

void ChartViewDinamicForm::RangeY(const qreal AMin, const qreal AMax)
{
    FAxisY->setRange(AMin,AMax);
}

void ChartViewDinamicForm::replace(QVector<QPointF> points)
{
    FSeries->replace(points);
}

QVector<QPointF> ChartViewDinamicForm::pointsVector() const
{
    return FSeries->pointsVector();
}
