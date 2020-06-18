#ifndef ALSENSIGNALDECODER_H
#define ALSENSIGNALDECODER_H

#include <QObject>
#include "alsen_rx.h"
#include "pll2.h"
#include "decode.h"
#include "DigitalFilterIIRr2.h"
#include "alsenConst.h"

class ALSENSignalDecoder : public QObject
{
    Q_OBJECT
public:
    explicit ALSENSignalDecoder(const uint8_t ABaseCode0,
                                const uint8_t ABaseCode90,
                                const quint32 ADescrFreq = SAMPLERATE,
                                const uint    ADecimFactor = 10,
                                const bool    AOnlyDvuBit = true,
                                QObject *parent = nullptr);
    ~ALSENSignalDecoder();

    quint8 Code0() const;
    quint8 Group0() const;

    quint8 Code90() const;
    quint8 Group90() const;

    bool OnlyDvubit() const { return FOnlyDvubit; }
    void OnlyDvubit(const bool AOnlyDvubit);

    void operator()(const double ASample );

signals:
    void onEnterSample(const double ASample);

    void onCodeDetect0(const double time,
                       const quint8 ACode0,
                       const quint8 ABaseCode0);

    void onCodeDetect90(const double time,
                        const quint8 ACode90,
                        const quint8 ABaseCode90);

    void onCodeDetectBits( const uint64_t sample_count,
                           const bool bit0,
                           const bool bit90 );

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
    uint8_t             FBaseCode0;
    uint8_t             FBaseCode90;
    uint32_t            FDescrFreq;

    uint                FDecimFactor;
    uint64_t            FSampleCounter;
    uint64_t            FSampleCounterLast = 0;


    alsen_rx          * FAlsenRX;
    DigitalFilterIIR2 * flt_iir1;
    DigitalFilterIIR2 * flt_iir2;
    pll2              * pll0;
    pll2              * pll90;
    decode            * decoder0;
    decode            * decoder90;

    bool                FOnlyDvubit;
};

#endif // ALSENSIGNALDECODER_H
