#include <algorithm>
#include <math.h>
#include "digitalfilter.h"
#include "digitalfltersettings.h"
#include <iostream>

DigitalFilterLowHighPass::DigitalFilterLowHighPass(const int    APolesCount,
                                                   const double AGain,
                                                   const int    AXCoef[],
                                                   const double AYCoef[]) :
    IDigitalFilter(),
    FGain(AGain),
    FPolesCount(APolesCount),
    FXCoef(new int [APolesCount+1] ()),
    FYCoef(new double [APolesCount] ()),
    FXValue(new double [APolesCount+1] ()),
    FYValue(new double [APolesCount+1] ())
{
    std::copy(AXCoef,(AXCoef+APolesCount+1),FXCoef);
    std::copy(AYCoef,(AYCoef+APolesCount),FYCoef);
}

DigitalFilterLowHighPass::DigitalFilterLowHighPass(const DigitalFilterLowHighPass &AFilter) :
    IDigitalFilter(),
    FGain(AFilter.FGain),
    FPolesCount(AFilter.FPolesCount),
    FXCoef(new int [FPolesCount+1] ()),
    FYCoef(new double [FPolesCount] ()),
    FXValue(new double [FPolesCount+1] ()),
    FYValue(new double [FPolesCount+1] ())
{
    std::copy(AFilter.FXCoef,(AFilter.FXCoef+AFilter.FPolesCount+1),FXCoef);
    std::copy(AFilter.FYCoef,(AFilter.FYCoef+AFilter.FPolesCount),FYCoef);
    std::copy(AFilter.FXValue,(AFilter.FXValue+AFilter.FPolesCount+1),FXValue);
    std::copy(AFilter.FYValue,(AFilter.FYValue+AFilter.FPolesCount+1),FYValue);
}

DigitalFilterLowHighPass &DigitalFilterLowHighPass::operator=(const DigitalFilterLowHighPass &AFilter)
{
    if(this != &AFilter)
    {
        FGain = AFilter.FGain;
        if(FPolesCount != AFilter.FPolesCount)
        {
            delete [] FXCoef;
            delete [] FYCoef;
            delete [] FXValue;
            delete [] FYValue;
            FPolesCount = AFilter.FPolesCount;
            FXCoef = new int [FPolesCount+1] ();
            FYCoef = new double [FPolesCount] ();
            FXValue = new double [FPolesCount+1] ();
            FYValue = new double [FPolesCount+1] ();
        }
        std::copy(AFilter.FXCoef,(AFilter.FXCoef+AFilter.FPolesCount+1),FXCoef);
        std::copy(AFilter.FYCoef,(AFilter.FYCoef+AFilter.FPolesCount),FYCoef);
        std::copy(AFilter.FXValue,(AFilter.FXValue+AFilter.FPolesCount+1),FXValue);
        std::copy(AFilter.FYValue,(AFilter.FYValue+AFilter.FPolesCount+1),FYValue);
    }
    return *this;
}

DigitalFilterLowHighPass::~DigitalFilterLowHighPass()
{
    delete [] FXCoef;
    delete [] FYCoef;
    delete [] FXValue;
    delete [] FYValue;
}

void DigitalFilterLowHighPass::setNewParams(const int APolesCount, const double AGain, const int AXCoef[], const double AYCoef[])
{
    FGain = AGain;
    FPolesCount = APolesCount;
    delete [] FXCoef;
    FXCoef = new int [FPolesCount + 1] ();
    delete [] FYCoef;
    FYCoef = new double [FPolesCount] ();
    delete [] FXValue;
    FXValue = new double [FPolesCount+1] ();
    delete [] FYValue;
    FYValue = new double [FPolesCount+1] ();
    std::copy(AXCoef,(AXCoef+APolesCount+1),FXCoef);
    std::copy(AYCoef,(AYCoef+APolesCount),FYCoef);
}

double DigitalFilterLowHighPass::filter(const double ASample)
{
    double Value = ASample;
    if(FPrefilter) Value = FPrefilter->filter(Value);

    // алгоритм получен после переработки кода фильтра полученного с сайта http://www-users.cs.york.ac.uk/~fisher/mkfilter
    std::copy(FXValue+1,(FXValue + FPolesCount + 1),FXValue);
    FXValue[FPolesCount] = Value / FGain;
    std::copy(FYValue+1,(FYValue + FPolesCount + 1),FYValue);
    double XValue {0.0};
    double YValue {0.0};
    for (int i = 0; i < (FPolesCount+1); ++i) XValue += FXValue[i]*FXCoef[i];
    for (int i = 0; i < (FPolesCount); ++i)   YValue += FYValue[i]*FYCoef[i];
    FYValue[FPolesCount] = XValue + YValue;
    return FYValue[FPolesCount];
}

double DigitalFilterNoFilter::filter(const double ASample)
{
    double Value = ASample;
    if(FPrefilter) Value = FPrefilter->filter(Value);
    return Value;
}

double DigitalFilterAbs::filter(const double ASample)
{
    double Value = ASample;
    if(FPrefilter) Value = FPrefilter->filter(Value);
    return std::abs(Value);
}

DigitalPhaseChangeFilter::DigitalPhaseChangeFilter(const unsigned ASampleFreq,
                                                   const double ABitLen):
    IDigitalFilter(),
    FBitLen(ABitLen),
    FdT(1.0/ASampleFreq)
{
}

double DigitalPhaseChangeFilter::filter(const double ASample)
{
    if(FMax < abs(ASample)) FMax = abs(ASample);
    if(FMin > ASample)      FMin = ASample;

    static int index = 0;
    static int counter = 0;

    //std::copy((FValues+1),(FValues+12),FValues);
    //FValues[11] = ASample;

    FLastCounter++;

    double derivative2 = 0.0;

    //int temp = (index-1) < 0 ? 0 : (index-1);
    //derivative2 = 150 + FValues[temp] * 150;

    FValues[index++] = ASample;
    if(index > 7) // получено 12 отсчетов
{
    index = 0;

    //FDerivative[0] = FDerivative[1];
    // первая центральная производная
    //FDerivative[1] = ((FValues[9]/((FMax - FMin)/2) - FValues[11]/((FMax - FMin)/2))/(2*FdT))/1000;

    derivative2 = 150 + FValues[7]*150;//determineComingPhase(FValues[0],FValues[6]);
    if(derivative2 < 70) derivative2 = 0.0;

    if(derivative2 > 0)
    {
        counter++;
        if (counter <= 5) derivative2 = 0;
    }
    else
    {
        if(counter > 5) std::cout << counter << "\t\t" << FLastCounter << std::endl;
        FLastCounter = 0;
        counter = 0;
    }
}
    //FDerivative[0] = FDerivative[1];
    // первая центральная производная
    //FDerivative[1] = ((FValues[9]/((FMax - FMin)/2) - FValues[11]/((FMax - FMin)/2))/(2*FdT))/1000;
    // вторая производная
    //double derivative2 = ((FDerivative[1] - FDerivative[0])/(FdT))/1000;
    // фильтр "всплесков" - изменения фазы - порог 7 - выбран эксперементально
    //derivative2 = abs(derivative2) < 7 ? 0.0 : abs(derivative2);
    //
    //if (derivative2 > 0.0)
    //{ // фиксируем "всплеск"
    //    if(FLastCounter > 3) //если прошло больше половины полуволны
    //    {
    //        derivative2 = determineComingPhase(FValues[3],FValues[8]);
    //
    //        std::cout << "1  "
    //                  << FLastCounter
    //                  << "\t\t"
    //                  << derivative2
    //                  << std::endl;
    //
    //    }
    //    else derivative2 = -1.0;
    //    FLastCounter = 0;
    //}
    //else
    //{   // определение бита или сразу после "всплеска"
    //    if(FLastCounter == round(FBitLen/FdT))
    //    {
    //        derivative2 = determineComingPhase(FValues[3],FValues[8]);
    //
    //        std::cout << "2  "
    //                  << FLastCounter
    //                  << "\t\t"
    //                  << derivative2
    //                  << std::endl;
    //
    //        FLastCounter = 0;
    //    }
    //    else
    //    derivative2 = -1.0;
    //}

    return derivative2;
}

double DigitalPhaseChangeFilter::determineComingPhase(const double &AValueBegin,
                                                      const double &AValueEnd) const
{
    double difference = AValueEnd - AValueBegin;
    bool plus = AValueBegin > 0;
    bool up;

    if(plus) up = difference > 0.0;
     else up = difference < 0.0;

    // для прошедшего сигнала
    if(plus && up)   return 90.0;
    if(plus && !up)  return 180.0;
    if(!plus && up)  return 270.0;
    if(!plus && !up) return 0.0;

    return -20.0;
}

double DigitalPhaseChangeFilter::determineNextPhase(const double &AValueBegin,
                                                    const double &AValueEnd) const
{
    double difference = AValueEnd - AValueBegin;
    bool plus = AValueBegin > 0;
    bool up;

    if(plus) up = difference > 0.0;
     else up = difference < 0.0;

    // для нового сигнала
    if(plus && up)   return 0.0;
    if(plus && !up)  return 90.0;
    if(!plus && up)  return 180.0;
    if(!plus && !up) return 270.0;

    return -1.0;
}

DigitalBitChangeFilter::DigitalBitChangeFilter(const SignalFreq ASignalFreq,
                                               const bool AIsUpperLimit,
                                               const unsigned ASampleFreq):
    IDigitalFilter(),
    FIsUpperLimit(AIsUpperLimit),
    FSignalFreq(ASignalFreq),
    FDescrFreq(ASampleFreq),
    FFilter(nullptr),
    FFilter2(nullptr)
{
    if(FIsUpperLimit) makeUpperLimitFilter(FSignalFreq);
     else makeLowerLimitFilter(FSignalFreq);
}

DigitalBitChangeFilter::~DigitalBitChangeFilter()
{
    delete FFilter;
    delete FFilter2;
}

double DigitalBitChangeFilter::filter(const double ASample)
{
    std::copy(FCurFreq+1,FCurFreq+10,FCurFreq);
    FCurFreq[9]= /*FFilter->do_sample(ASample);//*/FFilter2->filter(abs(FFilter->do_sample(ASample)));

    if(FCurFreq[9] > FMax) FMax = FCurFreq[9];
    if(FCurFreq[9] < FMin) FMin = FCurFreq[9];

    if(FCurFreq[9] < (FMax - FMin)/2) FCurFreq[9] = 0.0;
     else FCurFreq[9] = 1.0;
    // "убиваем" короткие провалы
    if(((FCurFreq[0] == 1.0) && (FCurFreq[9] == 1.0))||
       ((FCurFreq[0] == 0.0) && (FCurFreq[9] == 0.0)))
    {
        auto Iter = std::find(FCurFreq,FCurFreq+10,FCurFreq[0] == 1.0 ? 1.0 : 0.0);
        if(Iter != FCurFreq + 10)
        {
            if (FCurFreq[0] == 1.0) std::generate(FCurFreq,FCurFreq+10,[](){return 1.0;});
             else std::generate(FCurFreq,FCurFreq+10,[](){return 0.0;});
        }
    }


    //std::cout << FCurFreq[0] << std::endl;
    return FCurFreq[0];
}

void DigitalBitChangeFilter::setNewSettings(const SignalFreq ASignalFreq,
                                            const unsigned ASampleFreq)
{
    FSignalFreq = ASignalFreq;
    FDescrFreq   = ASampleFreq;
    if(FIsUpperLimit) makeUpperLimitFilter(FSignalFreq);
    else makeLowerLimitFilter(FSignalFreq);
}

DigitalBitChangeFilter::SignalFreq DigitalBitChangeFilter::krlFreqCodeToFilterFreq(const quint8 AFreqCode)
{
    switch (AFreqCode)
    {
        case 0: return DigitalBitChangeFilter::SIG_FREQ_475;
        case 1: return DigitalBitChangeFilter::SIG_FREQ_525;
        case 2: return DigitalBitChangeFilter::SIG_FREQ_575;
        case 3: return DigitalBitChangeFilter::SIG_FREQ_625;
        case 4: return DigitalBitChangeFilter::SIG_FREQ_675;
        case 5: return DigitalBitChangeFilter::SIG_FREQ_725;
        case 6: return DigitalBitChangeFilter::SIG_FREQ_775;
        case 7: return DigitalBitChangeFilter::SIG_FREQ_825;
        case 8: return DigitalBitChangeFilter::SIG_FREQ_875;
        case 9: return DigitalBitChangeFilter::SIG_FREQ_925;
        default: return DigitalBitChangeFilter::SIG_FREQ_475;
    }
}

void DigitalBitChangeFilter::makeUpperLimitFilter(const DigitalBitChangeFilter::SignalFreq ASignalFreq)
{
    if(FFilter) delete FFilter;
    FFilter = new Filter(BPF,1000,FDescrFreq,FSignalFreq+6,FSignalFreq+16);

    if(FFilter2) delete FFilter2;
    switch (ASignalFreq)
    {
    case SIG_FREQ_475 :
    {
        FFilter2 = new DigitalFilterLowHighPass(Butt_LP_5_8000_486_PolesCount,
                                                Butt_LP_5_8000_486_GAIN,
                                                Butt_LP_5_8000_486_XCoef,
                                                Butt_LP_5_8000_486_YCoef);
    } break;
    case SIG_FREQ_525 :
    {
        FFilter2 = new DigitalFilterLowHighPass(Butt_LP_5_8000_536_PolesCount,
                                                Butt_LP_5_8000_536_GAIN,
                                                Butt_LP_5_8000_536_XCoef,
                                                Butt_LP_5_8000_536_YCoef);
    } break;
    case SIG_FREQ_575 :
    {
        FFilter2 = new DigitalFilterLowHighPass(Butt_LP_5_8000_586_PolesCount,
                                                Butt_LP_5_8000_586_GAIN,
                                                Butt_LP_5_8000_586_XCoef,
                                                Butt_LP_5_8000_586_YCoef);
    } break;
    case SIG_FREQ_625 :
    {
        FFilter2 = new DigitalFilterLowHighPass(Butt_LP_5_8000_636_PolesCount,
                                                Butt_LP_5_8000_636_GAIN,
                                                Butt_LP_5_8000_636_XCoef,
                                                Butt_LP_5_8000_636_YCoef);
    } break;
    case SIG_FREQ_675 :
    {
        FFilter2 = new DigitalFilterLowHighPass(Butt_LP_5_8000_686_PolesCount,
                                                Butt_LP_5_8000_686_GAIN,
                                                Butt_LP_5_8000_686_XCoef,
                                                Butt_LP_5_8000_686_YCoef);
    } break;
    case SIG_FREQ_725 :
    {
        FFilter2 = new DigitalFilterLowHighPass(Butt_LP_5_8000_736_PolesCount,
                                                Butt_LP_5_8000_736_GAIN,
                                                Butt_LP_5_8000_736_XCoef,
                                                Butt_LP_5_8000_736_YCoef);
    } break;
    case SIG_FREQ_775 :
    {
        FFilter2 = new DigitalFilterLowHighPass(Butt_LP_5_8000_786_PolesCount,
                                                Butt_LP_5_8000_786_GAIN,
                                                Butt_LP_5_8000_786_XCoef,
                                                Butt_LP_5_8000_786_YCoef);
    } break;
    case SIG_FREQ_825 :
    {
        FFilter2 = new DigitalFilterLowHighPass(Butt_LP_5_8000_836_PolesCount,
                                                Butt_LP_5_8000_836_GAIN,
                                                Butt_LP_5_8000_836_XCoef,
                                                Butt_LP_5_8000_836_YCoef);
    } break;
    case SIG_FREQ_875 :
    {
        FFilter2 = new DigitalFilterLowHighPass(Butt_LP_5_8000_886_PolesCount,
                                                Butt_LP_5_8000_886_GAIN,
                                                Butt_LP_5_8000_886_XCoef,
                                                Butt_LP_5_8000_886_YCoef);
    } break;
    case SIG_FREQ_925 :
    {
        FFilter2 = new DigitalFilterLowHighPass(Butt_LP_5_8000_936_PolesCount,
                                                Butt_LP_5_8000_936_GAIN,
                                                Butt_LP_5_8000_936_XCoef,
                                                Butt_LP_5_8000_936_YCoef);
    } break;
    }
}

void DigitalBitChangeFilter::makeLowerLimitFilter(const DigitalBitChangeFilter::SignalFreq ASignalFreq)
{
    if(FFilter) delete FFilter;
    FFilter = new Filter(BPF,1000,FDescrFreq,FSignalFreq-16,FSignalFreq-6);

    if(FFilter2) delete FFilter2;
    switch (ASignalFreq)
    {
    case SIG_FREQ_475 :
    {
        FFilter2 = new DigitalFilterLowHighPass(Butt_LP_5_8000_464_PolesCount,
                                                Butt_LP_5_8000_464_GAIN,
                                                Butt_LP_5_8000_464_XCoef,
                                                Butt_LP_5_8000_464_YCoef);
    } break;
    case SIG_FREQ_525 :
    {
        FFilter2 = new DigitalFilterLowHighPass(Butt_LP_5_8000_514_PolesCount,
                                                Butt_LP_5_8000_514_GAIN,
                                                Butt_LP_5_8000_514_XCoef,
                                                Butt_LP_5_8000_514_YCoef);
    } break;
    case SIG_FREQ_575 :
    {
        FFilter2 = new DigitalFilterLowHighPass(Butt_LP_5_8000_564_PolesCount,
                                                Butt_LP_5_8000_564_GAIN,
                                                Butt_LP_5_8000_564_XCoef,
                                                Butt_LP_5_8000_564_YCoef);
    } break;
    case SIG_FREQ_625 :
    {
        FFilter2 = new DigitalFilterLowHighPass(Butt_LP_5_8000_614_PolesCount,
                                                Butt_LP_5_8000_614_GAIN,
                                                Butt_LP_5_8000_614_XCoef,
                                                Butt_LP_5_8000_614_YCoef);
    } break;
    case SIG_FREQ_675 :
    {
        FFilter2 = new DigitalFilterLowHighPass(Butt_LP_5_8000_664_PolesCount,
                                                Butt_LP_5_8000_664_GAIN,
                                                Butt_LP_5_8000_664_XCoef,
                                                Butt_LP_5_8000_664_YCoef);
    } break;
    case SIG_FREQ_725 :
    {
        FFilter2 = new DigitalFilterLowHighPass(Butt_LP_5_8000_714_PolesCount,
                                                Butt_LP_5_8000_714_GAIN,
                                                Butt_LP_5_8000_714_XCoef,
                                                Butt_LP_5_8000_714_YCoef);
    } break;
    case SIG_FREQ_775 :
    {
        FFilter2 = new DigitalFilterLowHighPass(Butt_LP_5_8000_764_PolesCount,
                                                Butt_LP_5_8000_764_GAIN,
                                                Butt_LP_5_8000_764_XCoef,
                                                Butt_LP_5_8000_764_YCoef);
    } break;
    case SIG_FREQ_825 :
    {
        FFilter2 = new DigitalFilterLowHighPass(Butt_LP_5_8000_814_PolesCount,
                                                Butt_LP_5_8000_814_GAIN,
                                                Butt_LP_5_8000_814_XCoef,
                                                Butt_LP_5_8000_814_YCoef);
    } break;
    case SIG_FREQ_875 :
    {
        FFilter2 = new DigitalFilterLowHighPass(Butt_LP_5_8000_864_PolesCount,
                                                Butt_LP_5_8000_864_GAIN,
                                                Butt_LP_5_8000_864_XCoef,
                                                Butt_LP_5_8000_864_YCoef);
    } break;
    case SIG_FREQ_925 :
    {
        FFilter2 = new DigitalFilterLowHighPass(Butt_LP_5_8000_914_PolesCount,
                                                Butt_LP_5_8000_914_GAIN,
                                                Butt_LP_5_8000_914_XCoef,
                                                Butt_LP_5_8000_914_YCoef);
    } break;
    }
}

DigitalBandBitChangeFilter::DigitalBandBitChangeFilter(const DigitalBitChangeFilter::SignalFreq ASignalFreq,
                                                       const unsigned ASampleFreq):
    IDigitalFilter(),
    FUpperFilter(new DigitalBitChangeFilter(ASignalFreq,true,ASampleFreq)),
    FLowerFilter(new DigitalBitChangeFilter(ASignalFreq,false,ASampleFreq))
{
}

DigitalBandBitChangeFilter::~DigitalBandBitChangeFilter()
{
    delete FUpperFilter;
    delete FLowerFilter;
}

double DigitalBandBitChangeFilter::filter(const double ASample)
{
    int UpperValue = static_cast<int>(FUpperFilter->filter(ASample));
    int LowerValue = static_cast<int>(FLowerFilter->filter(ASample));
    double ResultValue = 0.0;
    if(UpperValue == LowerValue) ResultValue = 0.0;
     else if((UpperValue == 1)&&(LowerValue == 0)) ResultValue = 1.0;
      else if((UpperValue == 0)&&(LowerValue == 1)) ResultValue = 0.0;
        else ResultValue = -1.0;
    return ResultValue;
}

void DigitalBandBitChangeFilter::setNewSettings(const DigitalBitChangeFilter::SignalFreq ASignalFreq, const unsigned ASampleFreq)
{
    FUpperFilter->setNewSettings(ASignalFreq,ASampleFreq);
    FLowerFilter->setNewSettings(ASignalFreq,ASampleFreq);
}
