//#include <QTest>
#include "digitalfilter.h"
#include "alsensignaliodevice.h"
#include "alsensignaldecoder.h"
#include "alsenconst.h"

//#include "ALSENReceiver.h"

ALSENSignalIODevice::ALSENSignalIODevice(ALSENSignalDecoder & ADecoder,
                                         QObject * parent)
   :QIODevice (parent),
    FStopped(true),
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
    if (FStopped) return;
    FDecoder(ASample);
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
    return maxSize;
}

void ALSENSignalIODevice::processSignal(const char * data, qint64 maxSize)
{
    for(int i = 0; i < maxSize; ++i)
    {
        FDecoder(data[i] > 0 ? double(data[i]) - 128.0 : double(data[i]) + 128.0 );
    }
}
