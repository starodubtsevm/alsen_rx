#include "alsensignaldecoder.h"
#include "alsenconst.h"
#include <algorithm>

#include <iostream>

ALSENSignalDecoder::ALSENSignalDecoder
(
        const uint8_t ABaseCode0,
        const uint8_t ABaseCode90,
        const quint32 ADescrFreq,
        const uint   ADecimFactor,
        QObject *parent
)
:
    QObject(parent),
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
//    for( auto c : flt_iir1->COEFFS )
//    {
//        for( auto v : c )
//        {
//            //std::cout<<v<<std::endl;
//            printf( "%f\n", v );
//        }
//    }
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
        "%.2fc. кан%-2d:%s Code: 0x%x Byte: 0x%x; Base: 0x%x %s\n",
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
/*
# локальный генератор sin и cos
    gen0, gen90 = rx.local_gen(t)
# *--------------------------------------------------------------------------
*/
    FAlsenRX->local_gen();
    double gen0 = FAlsenRX->Result().first;
    double gen90 = FAlsenRX->Result().second;
    emit onAfterGen(gen0,gen90);
    //printf( "%.4f|%.4f\n", gen0, gen90 );

/*
# входные перемножители
    y0_aftermux1 = rx.mux1(gen0, sig[i])
    y90_aftermux1 = rx.mux1(gen90, sig[i])
# *--------------------------------------------------------------------------
*/
    double y0_aftermux1 = FAlsenRX->mux1(gen0,ASample);
    double y90_aftermux1 = FAlsenRX->mux1(gen90,ASample);
    emit onAfterMux(y0_aftermux1,y90_aftermux1);
    //printf( "%.4f|%.4f\n", y0_aftermux1, y90_aftermux1 );
/*
# фильтры - интеграторы
    y0_afterlpf1 = flt_iir1.filter(y0_aftermux1)
    y90_afterlpf1 = flt_iir2.filter(y90_aftermux1)
# *--------------------------------------------------------------------------
*/
    double y0_afterlpf1 = flt_iir1->filter(y0_aftermux1);
    double y90_afterlpf1 = flt_iir2->filter(y90_aftermux1);
    emit onAfterIIR(y0_afterlpf1,y90_afterlpf1);
    //printf( "%.1f|%.1f\n", y0_afterlpf1, y90_afterlpf1 );
/*
# дифференциальный декодер
    if i % D == 0:
        y7, y8 = rx.diff_decode(y0_afterlpf1, y90_afterlpf1)
# *--------------------------------------------------------------------------
*/
    if(!(FSampleCounter % FDecimFactor))
    {
        FAlsenRX->diff_decode(y0_afterlpf1, y90_afterlpf1);
        double y7 = FAlsenRX->Result().first;
        double y8 = FAlsenRX->Result().second;
        emit onY7_8(y7,y8);
        //printf( "%.0f\n", y7 );
        //printf( "%.0f\n", y8 );
/*
# функции sgn-(компараторы)
        y9 = rx.sgn(y7)
        y10 = rx.sgn(y8)
# *--------------------------------------------------------------------------
*/
        uint y9 = FAlsenRX->sgn(y7);
        uint y10 = FAlsenRX->sgn(y8);
        emit onY9_10(y9,y10);
//        printf( "%d\n", y9  );
//        printf( "%d\n", y10 );
/*
# ФАПЧ
        sync0, err0, bit0 = pll0.proc(y9)  # выходной сигнал ФАПЧ канал 0
        sync90, err90, bit90 = pll90.proc(y10)  # выходной сигнал ФАПЧ канал 90
# *--------------------------------------------------------------------------
*/
        pll0->proc(y9);
        uint sync0  = pll0->Result().Syncro;
        uint bit0   = pll0->Result().Sample;
        emit onPll0(sync0,bit0);
        //printf( "%d\n", sync0 );
        //printf( "%d\n", bit0 );

        pll90->proc(y10);
        uint sync90  = pll90->Result().Syncro;
        uint bit90   = pll90->Result().Sample;
        emit onPll90(sync90,bit90);
/*
# Декодеры (прием байтов)

        if sync0 == 1:
            counter_total += 1
            dec0, s0 = decoder0.proc(bit0)
            # выходной сигнал декодера канала 0
            if dec0 == 1:
                if first_suc_byte_flag == 0:
                    t_reaction = 1/fs * i
                    first_suc_byte_flag = 1
                counter_suc += 1
                # print_buff0.append("\x1b[32m  ok!  \x1b[0m")
            # else:
                # print_buff0.append("\x1b[31m not ok \x1b[0m")
*/

        double time = FSampleCounter / double(FDescrFreq);

        if(sync0 == 1)
        {
            if(decoder0->proc(bit0,FBaseCode0))
            {
                //TODO std::cout << "(" << FSampleCounter << ")" << "Decode byte 0: " << decoder0->toString() << " <-- " << std::hex << static_cast<int>(decoder0->Code())<< std::dec << std::endl;
                emit onCodeDetect0(decoder0->Code(),
                                   decoder0->BaseCode());
                print_res(time,0,decoder0,FBaseCode0,"ok!");
            }
            else
            {
                print_res(time,0,decoder0,FBaseCode0,"not ok");
            }
        }
/*
        if sync90 == 1:
            dec90, s90 = decoder90.proc(bit90)
            # выходной сигнал декодера канала 90
            # print_buff90.append(str('{:.2f}'.format(1.0/fs * i)))
            # print_buff90.append(str(s90))
            #if dec90 == 1:
            #    print_buff90.append("\x1b[32m  ok!  \x1b[0m")
            #else:
            #    print_buff90.append("\x1b[31m not ok \x1b[0m")
*/
        if(sync90 == 1)
        {
            if(decoder90->proc(bit90,FBaseCode90))
            {
                //TODO std::cout << "(" << FSampleCounter << ")" << "Decode byte 90: " << decoder90->toString() << " <-- " << std::hex << static_cast<int>(decoder90->Code())<< std::dec << std::endl;
                emit onCodeDetect90(decoder90->Code(),
                                    decoder90->BaseCode());
                print_res(time,90,decoder90,FBaseCode90,"ok!");
            }
            else
            {
                print_res(time,90,decoder90,FBaseCode90,"not ok");
            }
        }
/*
# *--------------------------------------------------------------------------
*/
    }
    FSampleCounter++;
}
