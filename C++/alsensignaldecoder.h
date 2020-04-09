#ifndef ALSENSIGNALDECODER_H
#define ALSENSIGNALDECODER_H

#include <QObject>
#include "alsen_rx.h"
#include "pll2.h"
#include "decode.h"
#include "DigitalFilterIIRr2.h"

class ALSENSignalDecoder : public QObject
{
    Q_OBJECT
public:
    explicit ALSENSignalDecoder(const quint32 ADescrFreq = 8000,
                                const uint   ADecimFactor = 10,
                                QObject *parent = nullptr);

    quint8 Code0() const  { return decoder0->Code(); }
    quint8 Group0() const { return decoder0->BaseCode(); }

    quint8 Code90() const  { return decoder90->Code(); }
    quint8 Group90() const { return decoder90->BaseCode(); }

    void operator()(const double ASample);

signals:
    void onCodeDetect0(const quint8 ACode0,
                       const quint8 AGroup0);

    void onCodeDetect90(const quint8 ACode90,
                        const quint8 AGroup90);

    void onAfterGen(const double AValue0,
                    const double AValue90);

    void onAfterMux(const double AValue0,
                    const double AValue90);

    void onAfterIIR(const double AValue0,
                    const double AValue90);

    void onY7_8(const double AY7,
                const double AY8);

    void onY9_10(const double AY9,
                 const double AY10);

    void onPll0(const uint ASync,
                const uint ABit);

    void onPll90(const uint ASync,
                 const uint ABit);

private:
    uint                FDecimFactor;
    uint64_t            FSampleCounter;

    alsen_rx          * FAlsenRX;
    DigitalFilterIIR2 * flt_iir1;
    DigitalFilterIIR2 * flt_iir2;
    pll2              * pll0;
    pll2              * pll90;
    decode            * decoder0;
    decode            * decoder90;
};

#endif // ALSENSIGNALDECODER_H