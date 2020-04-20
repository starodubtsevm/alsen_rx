#ifndef PLL2_H
#define PLL2_H

#include <stdint.h>

/*!
 * \brief Класс pll2 - ФАПЧ
 */
class pll2
{
public:
    using uint = unsigned int;
    using uint16 = unsigned short;

    typedef struct FAPCHResultStruct
    {
        uint Syncro {0};
        int  PhError {0};
        uint Sample {0};
    } FAPCHResult;

    pll2(const uint   ADeskrFreq,
         const uint   AScaleFs = 80,
         const double ASignMoment = 4.5, // из main.py вылазит
         const double ABitRate = 12.89,
         const uint   ADecimFactor = 10);

    void proc(uint16 ASample, bool receiveFlag = true);

    const FAPCHResult & Result() const { return FResult; }

private:
    int     lenOfBit;
    int     syncCount;
    int     phErrCount;
    int     phErr;
    int     syncro;
    bool    receiveFlag;
    uint16  frontDet;
    uint    sample;
    double  Fs;
    uint    scale_fs;
    int     corr;
    double  sign_moment;
    uint32_t  proc_cnt = 0;

    FAPCHResult FResult;

};

#endif // PLL2_H
