#include "chartviewform.h"
#include <QDebug>
#include "ui_chartviewform.h"

ChartViewForm::ChartViewForm(const QString ATitle,
                             const double * ASamples,
                             const int ASamplesCount,
                             const QString AXTitle,
                             const QString AYTitle,
                             const int ASectionCount,
                             const double AXFactor,
                             const double AYFactor,
                             QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartViewForm),
    FSeriesVector(nullptr),
    FChart(new QChart()),
    FChartView(new QChartView(FChart)),
    FLeftButton(new QPushButton),
    FRightButton(new QPushButton),
    FCurrentSectionIndex(0),
    FCurrentSeries(new QLineSeries()),
    FCurrentXAxis(new QValueAxis),
    FCurrentYAxis(new QValueAxis),
    FXFactor(AXFactor),
    FYFactor(AYFactor),
    FTitle(ATitle)
{
    ui->setupUi(this);

    int SectionLenght = ASamplesCount/ASectionCount;
    int EndSectionLenght = ASamplesCount%ASectionCount;
    int Sectionscount = EndSectionLenght == 0 ? ASectionCount : ASectionCount + 1;

    auto AmplMax = std::max_element(ASamples,(ASamples+ASamplesCount));
    auto AmplMin = std::min_element(ASamples,(ASamples+ASamplesCount));

    FCurrentXAxis->setTitleText(AXTitle);
    FCurrentYAxis->setTitleText(AYTitle);

    FCurrentYAxis->setMin(*AmplMin * FYFactor);
    FCurrentYAxis->setMax(*AmplMax * FYFactor);

    // заполняем основные серии графика
    FSeriesVector = new QVector<SeriesStruct>(Sectionscount);
    for (int i = 0; i < ASectionCount; ++i)
    {
        (*FSeriesVector)[i].SeriesBoundaries.first = i * SectionLenght;
        (*FSeriesVector)[i].SeriesBoundaries.second = i * SectionLenght + (SectionLenght - 1);
        for (double index = (*FSeriesVector)[i].SeriesBoundaries.first; index < (*FSeriesVector)[i].SeriesBoundaries.second+1; ++index)
        {
            (*FSeriesVector)[i].Series->append(index * FXFactor, ASamples[static_cast<int>(index)] * FYFactor);
        }
        (*FSeriesVector)[i].SeriesBoundaries.first *= FXFactor;
        (*FSeriesVector)[i].SeriesBoundaries.second *= FXFactor;
    }
    // заполняем конечную серию
    if(EndSectionLenght)
    {
        int EndIndex = FSeriesVector->size()-1;
        (*FSeriesVector)[EndIndex].SeriesBoundaries.first = EndIndex * SectionLenght;
        (*FSeriesVector)[EndIndex].SeriesBoundaries.second = EndIndex * SectionLenght + (EndSectionLenght - 1);
        for (int index = (*FSeriesVector)[EndIndex].SeriesBoundaries.first ; index < (*FSeriesVector)[EndIndex].SeriesBoundaries.second+1; ++index)
        {
            (*FSeriesVector)[EndIndex].Series->append(index * FXFactor, ASamples[index] * FYFactor);
        }
        (*FSeriesVector)[EndIndex].SeriesBoundaries.first *= FXFactor;
        (*FSeriesVector)[EndIndex].SeriesBoundaries.second *= FXFactor;
    }

    // настраиваем график
    FChart->legend()->hide();
    FChart->addSeries(FCurrentSeries);
    FChart->addAxis(FCurrentYAxis,Qt::AlignLeft);
    FChart->addAxis(FCurrentXAxis,Qt::AlignBottom);
    FCurrentXAxis->setMin(FSeriesVector->at(FCurrentSectionIndex).SeriesBoundaries.first);
    FCurrentXAxis->setMax(FSeriesVector->at(FCurrentSectionIndex).SeriesBoundaries.second);
    FCurrentSeries->replace(FSeriesVector->at(FCurrentSectionIndex).Series->pointsVector());
    FCurrentSeries->attachAxis(FCurrentXAxis);
    FCurrentSeries->attachAxis(FCurrentYAxis);

    // настраиваем кнопки
    FLeftButton->setText("<");
    FLeftButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    FLeftButton->setMinimumSize(30,30);
    FLeftButton->setEnabled(false);
    connect(FLeftButton, &QPushButton::clicked,
            this, &ChartViewForm::leftClicked);

    FRightButton->setText(">");
    FRightButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    FRightButton->setMinimumSize(30,30);
    if(Sectionscount > 1) FRightButton->setEnabled(true);
     else FRightButton->setEnabled(false);
    connect(FRightButton, &QPushButton::clicked,
            this, &ChartViewForm::rightClicked);

    connect(this, &ChartViewForm::setCurrentSection,
            this, &ChartViewForm::setCurrentSectionSlot);

    // настраиваем интерфейс
    FChart->setTitle(FTitle);
    ui->hlChart->addWidget(FLeftButton);
    ui->hlChart->addWidget(FChartView);
    ui->hlChart->addWidget(FRightButton);
    QSize BSize = FRightButton->size();
    BSize.setWidth(30);
    FRightButton->setMaximumSize(BSize);
    FLeftButton->setMaximumSize(BSize);

}

ChartViewForm::~ChartViewForm()
{
    delete FChart;
    delete FChartView;
    delete FLeftButton;
    delete FRightButton;
    delete FSeriesVector;
    delete ui;
}

void ChartViewForm::leftClicked(bool checked)
{
    Q_UNUSED(checked)
    --FCurrentSectionIndex;
    if(FCurrentSectionIndex == 0)
    {
        FLeftButton->setEnabled(false);
        FRightButton->setEnabled(true);
    }
    else
    {
        FLeftButton->setEnabled(true);
        FRightButton->setEnabled(true);
    }

    emit setCurrentSection();
}

void ChartViewForm::rightClicked(bool checked)
{
    Q_UNUSED(checked)
    ++FCurrentSectionIndex;
    if(FCurrentSectionIndex == FSeriesVector->size()-1)
    {
        FRightButton->setEnabled(false);
        FLeftButton->setEnabled(true);
    }
    else
    {
        FLeftButton->setEnabled(true);
        FRightButton->setEnabled(true);
    }

    emit setCurrentSection();
}

void ChartViewForm::setCurrentSectionSlot()
{
    FCurrentSeries->replace(FSeriesVector->at(FCurrentSectionIndex).Series->pointsVector());
    FCurrentXAxis->setMin(FSeriesVector->at(FCurrentSectionIndex).SeriesBoundaries.first);
    FCurrentXAxis->setMax(FSeriesVector->at(FCurrentSectionIndex).SeriesBoundaries.second);
}

ChartViewForm::SeriesStruct::SeriesStruct()
{
    Series = new QLineSeries;
}

ChartViewForm::SeriesStruct::~SeriesStruct()
{
    delete Series;
}
