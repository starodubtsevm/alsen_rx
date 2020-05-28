#include "DigitalFilterIIRr2.h"

#include <iostream>

DigitalFilterIIR2::DigitalFilterIIR2(const uint  AFs,
                                     const uint8 AOrder,
                                     const Cutoff ACutoff,
                                     const FilterType AFilterType,
                                     const FilterDesigns ADesigns,
                                     const uint8 ARp,
                                     const uint8 ARs)
    : IDigitalFilter()
{
    // заполнение коэффициентов и инициализация буферов
    createCoeffs(AOrder,ACutoff,AFilterType,ADesigns,ARp,ARs,AFs);
    acc_input.resize(COEFFS.size(),0.0);
    acc_output.resize(COEFFS.size(),0.0);
    buffer2.resize(COEFFS.size(),0.0);
    buffer1.resize(COEFFS.size(),0.0);
    input = 0.0;
    output = 0.0;
}

void DigitalFilterIIR2::createCoeffs(const DigitalFilterIIR2::uint8 AOrder,
                                     const DigitalFilterIIR2::Cutoff ACutoff,
                                     const DigitalFilterIIR2::FilterType AFilterType,
                                     const DigitalFilterIIR2::FilterDesigns ADesigns,
                                     const DigitalFilterIIR2::uint8 ARp,
                                     const DigitalFilterIIR2::uint8 ARs,
                                     const DigitalFilterIIR2::uint AFs)
{
    /*
     * Генерация коэффициентов пока не реализована
     * Значения получены при выполнении alsen_rx на Python от Стародубцева М.
     *
    Коэффициенты flt_iir1
    [[ 1.66045425e-10  3.32090849e-10  1.66045425e-10  1.00000000e+00 -1.99311554e+00  9.93144572e-01]
     [ 1.00000000e+00  2.00000000e+00  1.00000000e+00  1.00000000e+00 -1.99705203e+00  9.97154728e-01]]
     */
    //Q_UNUSED(AOrder);
    COEFFS.push_back(CoeffVector({1.66045425e-10,3.32090849e-10,1.66045425e-10,1.00000000e+00,-1.99311554e+00,9.93144572e-01}));
    COEFFS.push_back(CoeffVector({1.00000000e+00,2.00000000e+00,1.00000000e+00,1.00000000e+00,-1.99705203e+00,9.97154728e-01}));
}

double DigitalFilterIIR2::filter(const double ASample)
{
     if(COEFFS.size() > 1)
    {
        input = ASample;
        output = 0.0;

        decltype(COEFFS)::size_type i = 0;
        for(; i < COEFFS.size(); ++i)
        {
            for(auto ii = 0; ii < 3; ++ii) FIRCOEFFS.push_back(COEFFS[i][ii]);
            for(auto ii = 3; ii < 6; ++ii) IIRCOEFFS.push_back(COEFFS[i][ii]);

            acc_input[i] = (input + buffer1[i] * (-IIRCOEFFS[1]) + buffer2[i] * (-IIRCOEFFS[2]));
            acc_output[i] = (acc_input[i] * FIRCOEFFS[0] + buffer1[i] * FIRCOEFFS[1] + buffer2[i] * FIRCOEFFS[2]);

            buffer2[i] = buffer1[i];
            buffer1[i] = acc_input[i];
            input = acc_output[i];

            FIRCOEFFS.clear();
            IIRCOEFFS.clear();
        }
        output = acc_output[i-1];
    };

    return output;
}
