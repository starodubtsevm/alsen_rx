#include "alsensignaldecoder.h"
#include "alsenconst.h"
#include <algorithm>

#include <iostream>

#include <limits>

ALSENSignalDecoder::ALSENSignalDecoder(const uint8_t  ABaseCode0,
                                        const uint8_t ABaseCode90,
                                        const quint32 ADescrFreq,
                                        const uint    ADecimFactor,
                                        const bool    AOnlyDvuBit,
                                        QObject *parent)
   :QObject(parent),
    FBaseCode0(ABaseCode0),
    FBaseCode90(ABaseCode90),
    FDescrFreq(ADescrFreq),
    FDecimFactor(ADecimFactor),
    FSampleCounter(0),
    FAlsenRX(new alsen_rx(ADescrFreq)),
    flt_iir1(new DigitalFilterIIR2(ADescrFreq)),
    flt_iir2(new DigitalFilterIIR2(ADescrFreq)),
    pll0(new pll2(ADescrFreq)),
    pll90(new pll2(ADescrFreq)),
    FOnlyDvubit(AOnlyDvuBit)
{
    if(!FOnlyDvubit)
    {
        decoder0 = new decode;
        decoder90 = new decode;
    }
}

ALSENSignalDecoder::~ALSENSignalDecoder()
{
    delete FAlsenRX;
    delete flt_iir1;
    delete flt_iir2;
    delete pll0;
    delete pll90;
    if(decoder0) delete decoder0;
    if(decoder90) delete decoder90;
}

quint8 ALSENSignalDecoder::Code0() const
{
    if(FOnlyDvubit) return 0;
    return decoder0->Code();
}

quint8 ALSENSignalDecoder::Group0() const
{
    if(FOnlyDvubit) return 0;
    return decoder0->BaseCode();
}

quint8 ALSENSignalDecoder::Code90() const
{
    if(FOnlyDvubit) return 0;
    return decoder90->Code();
}

quint8 ALSENSignalDecoder::Group90() const
{
    if(FOnlyDvubit) return 0;
    return decoder90->BaseCode();
}

void ALSENSignalDecoder::OnlyDvubit(const bool AOnlyDvubit)
{
    if(FOnlyDvubit == AOnlyDvubit) return;
    FOnlyDvubit = AOnlyDvubit;
    if(FOnlyDvubit)
    {
        if(decoder0) delete decoder0;
        decoder0 = nullptr;
        if(decoder90) delete decoder90;
        decoder90 = nullptr;
    }
    else
    {
        decoder0 = new decode;
        decoder90 = new decode;
    }
}

void ALSENSignalDecoder::operator()(const double ASample )
{
    emit onEnterSample(ASample);

    FAlsenRX->local_gen();
    double gen0 = FAlsenRX->Result().first;
    double gen90 = FAlsenRX->Result().second;
    emit onAfterGen(gen0,gen90);

    double y0_aftermux1 = FAlsenRX->mux1(gen0,ASample);
    double y90_aftermux1 = FAlsenRX->mux1(gen90,ASample);
    emit onAfterMux(y0_aftermux1,y90_aftermux1);

    double y0_afterlpf1 = flt_iir1->filter(y0_aftermux1);
    double y90_afterlpf1 = flt_iir2->filter(y90_aftermux1);
    emit onAfterIIR(y0_afterlpf1,y90_afterlpf1);

    if(!(FSampleCounter % FDecimFactor))
    {
        FAlsenRX->diff_decode(y0_afterlpf1, y90_afterlpf1);
        double y7 = FAlsenRX->Result().first;
        double y8 = FAlsenRX->Result().second;
        emit onY7_8(y7,y8);

        uint y9 = FAlsenRX->sgn(y7);
        uint y10 = FAlsenRX->sgn(y8);
        emit onY9_10(y9,y10);

        pll0->proc(y9);
        uint sync0  = pll0->Result().Syncro;
        uint bit0   = pll0->Result().Sample;
        emit onPll0(sync0,bit0);

        pll90->proc(y10);
        uint sync90  = pll90->Result().Syncro;
        uint bit90   = pll90->Result().Sample;
        emit onPll90(sync90,bit90);

        double time = FSampleCounter/double(FDescrFreq);

        if(sync0 == 1)
        {
            // выводим полученный двубит (антидребезг и првоерка уровня сигнала - вне декодера)
            // расчет длительности двубита с учётом переполнения
            auto SampleCount = 0;
            if( FSampleCounter >= FSampleCounterLast )
            {
                SampleCount = FSampleCounter - FSampleCounterLast;
            }
            else
            {
                SampleCount = FSampleCounter + (std::numeric_limits<uint64_t>::max() - FSampleCounterLast);
            }

            emit onCodeDetectBits(SampleCount, bit0, bit90 );

            FSampleCounterLast = FSampleCounter;

            if(!FOnlyDvubit)
            {
                if(decoder0->proc(bit0,FBaseCode0))
                {
                    emit onCodeDetect0(time,
                                       decoder0->Code(),
                                       decoder0->BaseCode());
                }
            }
        }

        if(!FOnlyDvubit)
        {
            if(sync90 == 1)
            {
                if(decoder90->proc(bit90,FBaseCode90))
                {
                    emit onCodeDetect90(time,
                                        decoder90->Code(),
                                        decoder90->BaseCode());
                }
            }
        }
    }
    FSampleCounter++;
}
