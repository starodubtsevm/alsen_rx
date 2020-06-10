#include "alsensignaldecoder.h"
#include "alsenconst.h"
#include <algorithm>

#include <iostream>

ALSENSignalDecoder::ALSENSignalDecoder( const uint8_t ABaseCode0,
                                        const uint8_t ABaseCode90,
                                        const quint32 ADescrFreq,
                                        const uint   ADecimFactor,
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
    decoder0(new decode),
    decoder90(new decode)
{
}

ALSENSignalDecoder::~ALSENSignalDecoder()
{
    delete FAlsenRX;
    delete flt_iir1;
    delete flt_iir2;
    delete pll0;
    delete pll90;
    delete decoder0;
    delete decoder90;
}

static void print_res
(
        const double time,
        const uint8_t chan,
        const decode* decoder,
        const uint8_t FBaseCode,
        const char* result
)
{
    printf
    (
        "%.2fc. кан%-2d:%s Code: 0x%.2x Byte: 0x%.2x; Base: 0x%.2x %s\n",
        time,
        chan,
        decoder->toString().c_str(),
        FBaseCode,
        decoder->Code(),
        decoder->BaseCode(),
        result
    );
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

        double time = FSampleCounter / double(FDescrFreq);

        bool Detect0 = false;
        bool Detect90 = false;
        if(sync0 == 1)
        {
            if(decoder0->proc(bit0,FBaseCode0))
            {
                emit onCodeDetect0(time, decoder0->Code(),
                                   decoder0->BaseCode());
                Detect0 = true;
                print_res(time,0,decoder0,FBaseCode0,"ok!");
            }
            else
            {
                print_res(time,0,decoder0,FBaseCode0,"not ok");
            }
        }

        if(sync90 == 1)
        {
            if(decoder90->proc(bit90,FBaseCode90))
            {
                emit onCodeDetect90(time, decoder90->Code(),
                                    decoder90->BaseCode());
                Detect90 = true;
                print_res(time,90,decoder90,FBaseCode90,"ok!");
            }
            else
            {
                print_res(time,90,decoder90,FBaseCode90,"not ok");
            }
        }

//        if(Detect0 && Detect90)
//            emit onCodeDetect(decoder0->Code(),
//                              decoder0->BaseCode(),
//                              decoder90->Code(),
//                              decoder90->BaseCode());
    }
    FSampleCounter++;
}
