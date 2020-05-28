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
    frontDet = frontDet << 1;
    frontDet |= ASample;

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
        phErr = phErrCount - lenOfBit/sign_moment;
        if( (abs(phErr) >= lenOfBit * 3.0 / 200.0) )
        {
            //Фазовая ошибка 1,5% и более
            if(abs(phErr) >= lenOfBit * 3.0 / 50.0)
            {
                if(receiveFlag)
                {
                    //Флаг приёма телеграммы есть
                    (phErr < 0) ? syncCount = lenOfBit + corr
                                : syncCount = lenOfBit - corr;
                }
                else
                {
                    //Флага приёма телеграммы нет
                    //-5 выполняется для исключения ложной
                    syncCount = lenOfBit - 5 - phErr * 1/8;
                }
            }
            else
            {
                //Фазовая ошибка более 1,5%, но менее 6%
                (phErr < 0) ? syncCount = lenOfBit + 2
                            : syncCount = lenOfBit - 2;
            }
        }
        else
        {
            syncCount = lenOfBit; //Фазовая ошибка менее 1,5%
        }

        syncro = 1;

        FResult.Sample = ASample;
        FResult.Syncro = syncro;
        FResult.PhError = phErr;
     }

    proc_cnt++;
}
