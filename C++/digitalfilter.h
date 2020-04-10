#ifndef DIGITALFILTER_H
#define DIGITALFILTER_H

#include "digitalfilterabstract.h"
#include "utility"
#include <QObject>

#include "filt.h"
#include "fft.h"
#include <vector>

class DigitalFilterNoFilter : public IDigitalFilter
{
public:
    virtual double filter(const double ASample) override;
};

class DigitalFilterAbs : public IDigitalFilter
{
public:
    virtual double filter(const double ASample) override;
};

class DigitalFilterLowHighPass : public IDigitalFilter
{
public:
    DigitalFilterLowHighPass(const int    APolesCount,
                             const double AGain,
                             const int    AXCoef[],
                             const double AYCoef[]);

    DigitalFilterLowHighPass(const DigitalFilterLowHighPass & AFilter);

    DigitalFilterLowHighPass & operator=(const DigitalFilterLowHighPass & AFilter);

    virtual ~DigitalFilterLowHighPass() override;

    void setNewParams(const int    APolesCount,
                      const double AGain,
                      const int    AXCoef[],
                      const double AYCoef[]);

    virtual double filter(const double ASample) override;
private:
    double   FGain;
    int      FPolesCount;
    int *    FXCoef;
    double * FYCoef;
    double * FXValue;
    double * FYValue;
};

class DigitalPhaseChangeFilter : public IDigitalFilter
{
public:
    /*!
     * \brief DigitalPhaseChangeFilter конструктор фильтра
     * \param ASampleFreq - частота дискретизации
     * \param ABitLen - длинна одного бита в секундах
     */
    DigitalPhaseChangeFilter(const unsigned ASampleFreq = 8000,
                             const double ABitLen = 0.091753641);
    /*!
     * \brief filter - сам фильтр
     * \param ASample - значение отсчета
     * \return - значение фазы пришедшего бита или -1.0
     */
    virtual double filter(const double ASample) override;
private:
    double FBitLen;
    double FdT {0.0};
    double FMax {0.001};
    double FMin {-0.001};
    quint64 FLastCounter {0};
    double FValues[8] {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};//,0.0,0.0,0.0,0.0};
    double FDerivative[2] {0.0,0.0};
    /*!
     * \brief determineComingPhase - определение фазы пришедшего бита
     * \param AValueBegin - значение начального отсчета
     * \param AValueEnd - значение конечного отсчета
     * \return - значение фазы
     */
    double determineComingPhase(const double & AValueBegin, const double & AValueEnd) const;
    /*!
     * \brief determineNextPhase - определение фазы нового - следующего бита
     * \param AValueBegin - значение начального отсчета
     * \param AValueEnd - значение конечного отсчета
     * \return - значение фазы
     */
    double determineNextPhase(const double & AValueBegin, const double & AValueEnd) const;

};

class DigitalBitChangeFilter : public IDigitalFilter
{
public:
    enum SignalFreq
    {
        SIG_FREQ_475 = 475,
        SIG_FREQ_525 = 525,
        SIG_FREQ_575 = 575,
        SIG_FREQ_625 = 625,
        SIG_FREQ_675 = 675,
        SIG_FREQ_725 = 725,
        SIG_FREQ_775 = 775,
        SIG_FREQ_825 = 825,
        SIG_FREQ_875 = 875,
        SIG_FREQ_925 = 925
    };

    /*!
     * \brief DigitalPhaseChangeFilter конструктор фильтра
     * \param ASampleFreq - частота дискретизации
     * \param ASignalFreq - несущая частота
     * \param AIsUpperLimit - фильтровать верхний предел частоты при частотной модуляции или нижний
     */
    DigitalBitChangeFilter(const SignalFreq ASignalFreq = SIG_FREQ_475,
                           const bool AIsUpperLimit = true,
                           const unsigned ASampleFreq = 8000);
    ~DigitalBitChangeFilter() override;
    /*!
     * \brief filter - сам фильтр
     * \param ASample - значение отсчета
     * \return - значение пришедшего бита
     */
    virtual double filter(const double ASample) override;

    void setNewSettings(const SignalFreq ASignalFreq = SIG_FREQ_475,
                        const unsigned ASampleFreq = 8000);

    static SignalFreq krlFreqCodeToFilterFreq(const quint8 AFreqCode);

private:
    bool             FIsUpperLimit;
    SignalFreq       FSignalFreq;
    unsigned         FDescrFreq;
    Filter *         FFilter;
    IDigitalFilter * FFilter2;
    double           FCurFreq[10] {0.0};
    double           FMax {0.0};
    double           FMin {0.0};

    void makeUpperLimitFilter(const SignalFreq ASignalFreq);
    void makeLowerLimitFilter(const SignalFreq ASignalFreq);
};

class DigitalBandBitChangeFilter : public IDigitalFilter
{
public:
    DigitalBandBitChangeFilter(const DigitalBitChangeFilter::SignalFreq ASignalFreq = DigitalBitChangeFilter::SignalFreq::SIG_FREQ_475,
                               const unsigned ASampleFreq = 8000);
    ~DigitalBandBitChangeFilter() override;
    /*!
     * \brief filter - сам фильтр
     * \param ASample - значение отсчета
     * \return - значение пришедшего бита
     */
    virtual double filter(const double ASample) override;

    void setNewSettings(const DigitalBitChangeFilter::SignalFreq ASignalFreq = DigitalBitChangeFilter::SignalFreq::SIG_FREQ_475,
                        const unsigned ASampleFreq = 8000);
private:
    DigitalBitChangeFilter * FUpperFilter;
    DigitalBitChangeFilter * FLowerFilter;
};

#endif // DIGITALFILTER_H
