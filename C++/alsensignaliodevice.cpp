//#include <QTest>
#include "digitalfilter.h"
#include "alsensignaliodevice.h"
#include "alsensignaldecoder.h"
#include "alsenconst.h"

#include "ALSENReceiver.h"

ALSENSignalIODevice::ALSENSignalIODevice(IDigitalFilter &AViewFilter,
                                         IDigitalFilter &AWorkFilter,
                                         ALSENSignalDecoder &ADecoder,
                                         ChartViewDinamicForm * seriesFiltred,
                                         ChartViewDinamicForm * seriesSource,
                                         QObject * parent)
   :QIODevice (parent),
    FChartSeries(seriesFiltred),
    FChartSeries1(seriesSource),
    FStopped(true),
    FRange(4000),
    FViewFilter(AViewFilter),
    FWorkFilter(AWorkFilter),
    FDecoder(ADecoder)
{

}

void ALSENSignalIODevice::Stopped(const bool AStopped)
{
    if(FStopped == AStopped) return;
    FStopped = AStopped;
    if(!FStopped) clearData(); // запуск
}

void ALSENSignalIODevice::clearData()
{

}

void ALSENSignalIODevice::writeRAWData(const double ASample)
{
    //static ALSENReceiver reciewer;

    if (FStopped) return;
    FDecoder(ASample);
    //reciewer(ASample);
}

qint64 ALSENSignalIODevice::readData(char *data, qint64 maxSize)
{
    Q_UNUSED(data)
    Q_UNUSED(maxSize)
    return -1;
}

qint64 ALSENSignalIODevice::writeData(const char *data, qint64 maxSize)
{
    if (FStopped) return maxSize;
    processSignal(data,maxSize);
    showChart(data,maxSize);
    showSourceChart(data,maxSize);
    return maxSize;
}

void ALSENSignalIODevice::showChart(const char *data, qint64 maxSize)
{
    if(!FChartSeries) return;

    // максимальное количество точек графика
    qint64 range = FRange;
    // текущий набор точек
    QVector<QPointF> oldPoints = FChartSeries->pointsVector();
    // новый набор точек
    QVector<QPointF> points;

    if (oldPoints.count() < range) points = FChartSeries->pointsVector();
    else
      for (int i = static_cast<int>(maxSize); i < oldPoints.count(); i++)
        points.append(QPointF(i - maxSize, oldPoints.at(i).y()));

    qint64 size = points.count();
    for (int k = 0; k < maxSize; k++)
    {
        double Val = FViewFilter.filter((static_cast<quint8>(data[k]) - 128)/128.0);//data[k] > 0 ? data[k]-128 : data[k]+128);//(static_cast<quint8>(data[k]) - 128)/128.0);
        points.append(QPointF(k + size, Val));
    }

    FChartSeries->replace(points);
}

void ALSENSignalIODevice::showSourceChart(const char *data, qint64 maxSize)
{
    if(!FChartSeries) return;

    // максимальное количество точек графика
    qint64 range = FRange;
    // текущий набор точек
    QVector<QPointF> oldPoints = FChartSeries1->pointsVector();
    // новый набор точек
    QVector<QPointF> points;

    if (oldPoints.count() < range) points = FChartSeries1->pointsVector();
    else
      for (int i = static_cast<int>(maxSize); i < oldPoints.count(); i++)
        points.append(QPointF(i - maxSize, oldPoints.at(i).y()));

    qint64 size = points.count();
    for (int k = 0; k < maxSize; k++)
    {
        double Val = (static_cast<quint8>(data[k]) - 128)/128.0;//data[k] > 0 ? data[k]-127 : data[k]+128;//(static_cast<quint8>(data[k]) - 128)/128.0;
        points.append(QPointF(k + size, Val));
    }

    FChartSeries1->replace(points);
}

void ALSENSignalIODevice::processSignal(const char * data, qint64 maxSize)
{
    for(int i = 0; i < maxSize; ++i)
    {
       FDecoder((static_cast<quint8>(data[i]) - 128)/128.0);
       //qreal angle = FWorkFilter.filter((static_cast<quint8>(data[i]) - 128)/128.0);
       //switch (static_cast<int>(angle))
       //{
       //case   0: FDecoder(VAL_FI_0); break;
       //case  90: FDecoder(VAL_FI_90); break;
       //case 270: FDecoder(VAL_FI_270); break;
       //case 180: FDecoder(VAL_FI_180); break;
       //default: continue;
       //}
    }
}
