#include "ChartsViewForm.h"
#include "ui_ChartsViewFform.h"

ChartsViewForm::ChartsViewForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartsViewForm)
{
    ui->setupUi(this);
}

ChartsViewForm::~ChartsViewForm()
{
    clear();
    delete ui;
}

int ChartsViewForm::addChart(const QString ATitle,
                             const double * ASamples,
                             const int ASamplesCount,
                             const int ASectionCount,
                             const QString AXTitle,
                             const QString AYTitle,
                             const double AXFactor,
                             const double AYFactor)
{
    ChartViewForm * TempForm = new ChartViewForm(ATitle,
                                                 ASamples,
                                                 ASamplesCount,
                                                 AXTitle,
                                                 AYTitle,
                                                 ASectionCount,
                                                 AXFactor,
                                                 AYFactor);
    ui->vlCharts->addWidget(TempForm);
    FForms.push_back(TempForm);
    return FForms.indexOf(TempForm);
}

void ChartsViewForm::removeByChartTitle(const QString AChartTitle)
{
    FForms.erase(
                std::remove_if(FForms.begin(),
                               FForms.end(),
                               [&](const ChartViewForm * a)
                               {
                                   if(a->Title() == AChartTitle)
                                    {
                                       delete a;
                                       return true;
                                    }
                                   else return false;
                               })
                ,FForms.end());
}

void ChartsViewForm::clear()
{
    foreach(auto FormItem, FForms)
    {
        FForms.remove(FForms.indexOf(FormItem));
        delete FormItem;
    }
}
