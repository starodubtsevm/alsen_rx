#include <cmath>
#include "pll2.h"
#include <iostream>

pll2::pll2(const uint   ADeskrFreq,
           const uint   AScaleFs,
           const double ASignMoment,
           const double ABitRate,
           const uint   ADecimFactor)
    : lenOfBit((ADeskrFreq/ADecimFactor)/ABitRate),
      syncCount(lenOfBit),
      phErrCount(0),
      phErr(0),
      syncro(0),
      receiveFlag(true),
      frontDet(0),
      sample(0),
      Fs(ADeskrFreq/ADecimFactor),
      scale_fs(AScaleFs),
      corr(Fs/scale_fs),
      sign_moment(ASignMoment)
{
}

void pll2::proc(uint16 ASample, bool receiveFlag)
{
    //sample = ASample;
    frontDet = frontDet << 1;
    frontDet |= ASample;

//    printf( "------------------------\n" );
//    printf( "corr: %d\n", corr );
//    printf( "proc_cnt: %d\n", proc_cnt );
//    printf( "sample: %d\n", ASample );
//    printf( "syncCount: %d\n", syncCount );
//    printf( "phErrCount: %d\n", phErrCount );
//    printf( "phErr: %d\n", phErr );
//    printf( "frontDet: %d\n", frontDet );
//    printf( "lenOfBit: %d\n", lenOfBit );
//    printf( "syncro: %d\n", syncro );
//    printf( "\n" );

    --syncCount;

    if (syncCount != 0)
    {
        //Счётчик периода тактового сигнала не истёк
        ++phErrCount;

        if ((phErrCount >= lenOfBit) || ((frontDet & 0x0003) == 0x0001))
        {
            phErrCount = 0; //Фазовая ошибка стала равна длине бита или обнаружен фронт сигнала
        }

        syncro = 0;

        FResult.Sample = ASample;
        FResult.Syncro = syncro;
        FResult.PhError = phErr;
    }
    else
    {
        //Счётчик периода тактового сигнала истёк
//        printf( "phErrCount: %d\n", phErrCount );
//        printf( "lenOfBit: %d\n", lenOfBit );
//        printf( "sign_moment: %f\n", sign_moment );
        phErr = phErrCount - lenOfBit/sign_moment;
//        printf( "phErr: %d\n", phErr );
//        printf( "\n" );
        if( (abs(phErr) >= lenOfBit * 3.0 / 200.0) )
        {
            //Фазовая ошибка 1,5% и более
            if(abs(phErr) >= lenOfBit * 3.0 / 50.0)
            {
                if(receiveFlag)
                {
//                    printf( "br1\n" );
                    //Флаг приёма телеграммы есть
                    (phErr < 0) ? syncCount = lenOfBit + corr
                                : syncCount = lenOfBit - corr;
                }
                else
                {
//                    printf( "br2\n" );
                    //Флага приёма телеграммы нет
                    //-5 выполняется для исключения ложной
                    syncCount = lenOfBit - 5 - phErr * 1/8;
                }
            }
            else
            {
//                printf( "br3\n" );
                //Фазовая ошибка более 1,5%, но менее 6%
                (phErr < 0) ? syncCount = lenOfBit + 2
                            : syncCount = lenOfBit - 2;
            }
        }
        else
        {
//            printf( "br4\n" );
            syncCount = lenOfBit; //Фазовая ошибка менее 1,5%
        }

        syncro = 1;

        FResult.Sample = ASample;
        FResult.Syncro = syncro;
        FResult.PhError = phErr;
     }

//    printf( "proc_cnt: %d\n", proc_cnt );
//    printf( "sample: %d\n", ASample );
//    printf( "syncCount: %d\n", syncCount );
//    printf( "phErrCount: %d\n", phErrCount );
//    printf( "phErr: %d\n", phErr );
//    printf( "frontDet: %d\n", frontDet );
//    printf( "lenOfBit: %d\n", lenOfBit );
//    printf( "syncro: %d\n", syncro );

    proc_cnt++;
}
