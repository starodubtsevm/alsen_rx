#include "DigitalFilterIIRr2.h"

DigitalFilterIIR2::DigitalFilterIIR2(const uint  AFs,
                                     const uint8 AOrder,
                                     const Cutoff ACutoff,
                                     const FilterType AFilterType,
                                     const FilterDesigns ADesigns,
                                     const uint8 ARp,
                                     const uint8 ARs)
    : IDigitalFilter()
{
    createCoeffs(AOrder,ACutoff,AFilterType,ADesigns,ARp,ARs,AFs);
    // заполнение коэффициентов и инициализация буферов

    //for(size_t i = 0; i < COEFFS.size(); ++i)
    //{
    //    for(size_t ii = 0; ii < 3; ++ii) FIRCOEFFS.push_back(COEFFS[i][ii]);
    //    for(size_t ii = 3; ii < 6; ++ii) IIRCOEFFS.push_back(COEFFS[i][ii]);
    //}

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
    COEFFS.push_back(CoeffVector({1.66045425e-10,3.32090849e-10,1.66045425e-10,1.00000000e+00,-1.99311554e+00,9.93144572e-01}));
    COEFFS.push_back(CoeffVector({1.00000000e+00,2.00000000e+00,1.00000000e+00,1.00000000e+00,-1.99705203e+00,9.97154728e-01}));
}

double DigitalFilterIIR2::filter(const double ASample)
{
 /*
 * len (COEFFS [0 ,:] == 1 означает, что произошла ошибка при генерации
 * коэффициентов, и фильтрация не должна использоваться
 *
 * if len(self.COEFFS[0,:]) > 1:
 *
 *     self.input = input
 *     self.output = 0
 *
 *     Цикл for создает цепочку фильтров второго порядка в соответствии
 *     с желаемым порядком. Если должен быть создан фильтр 10-го порядка,
 *     цикл будет повторяться 5 раз, чтобы создать цепочку из фильтров
 *     5-го порядка.
 *
 *     for i in range(len(self.COEFFS)):
 *         self.FIRCOEFFS = self.COEFFS[i][0:3]
 *         self.IIRCOEFFS = self.COEFFS[i][3:6]
 *
 *         Вычисление накопленного ввода, состоящего из ввода и значений,
 *         поступающих из контуров обратной связи (буферы задержки,
 *         взвешенные по коэффициентам БИХ).
 *         self.acc_input[i] = (self.input + self.buffer1[i] * -self.IIRCOEFFS[1] + self.buffer2[i] * -self.IIRCOEFFS[2])
 *
 *         Вычисление накопленного выхода, полученного из накопленного ввода,
 *         и значений из буферов задержки, взвешенных по коэффициентам КИХ.
 *         self.acc_output[i] = (self.acc_input[i] * self.FIRCOEFFS[0] + self.buffer1[i] * self.FIRCOEFFS[1] + self.buffer2[i] * self.FIRCOEFFS[2])
 *
 *         Сдвиг значений на линии задержки: acc_input-> buffer1-> buffer2
 *         self.buffer2[i] = self.buffer1[i]
 *         self.buffer1[i] = self.acc_input[i]
 *
 *         self.input = self.acc_output[i]
 *
 *     self.output = self.acc_output[i]
 *
 * return self.output
 */
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
