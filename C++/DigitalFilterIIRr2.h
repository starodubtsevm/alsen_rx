#ifndef DIGITALFILTERIIR2_H
#define DIGITALFILTERIIR2_H

#include "digitalfilterabstract.h"
#include <utility>
#include <vector>

/*
 * Взято из IIR2Filter.py Стародубцева М.
 *
 * from IIR2Filter import IIR2Filter
 * MyFilter = IIR2Filter(order, cutoff, filterType, design = 'butter', rp = 1, rs = 1, fs = 0)
 *
 * При создании экземпляра фильтра обязательны следующие параметры:
 *     order: положительное целое число
 *          Он представляет порядок желаемого фильтра. Может быть нечетным или четным
 *          числом, фильтр создаст цепочку фильтров второго порядка и дополнительный
 *          фильтр первого порядка при необходимости.
 *     Cutoff: массив / положительное число с плавающей запятой
 *          В зависимости от желаемого фильтра 1 частота среза должна вводиться как
 *          положительное число с плавающей запятой для фильтров нижних/верхних частот
 *          или 2 частоты среза, которые должны вводиться в массив в качестве положительных
 *          значений с плавающей запятой для полосовых и полосовых фильтров.
 *          Эти частоты среза могут быть либо введены как нормализованные к частоте Найквиста
 *          (1 = частота Найквиста), либо как Гц (0 <f <Найквист), но в этом случае fs,
 *          частота дискретизации также должна быть пройдена.
 *     FilterType: строка
 *         Варианты: низкочастотный, высокочастотный, полосовой, полосовой(lowpass, highpass, bandpass, bandstop)
 *
 * Следующие параметры не являются обязательными:
 *     design: строка
 *          Различные типы поколений коэффициентов могут быть выбраны.
 *          Три доступных фильтра - Баттерворт, Чебышев, тип 1 или тип 2.
 *          Варианты: butter, cheby1, cheby2. Если не указано, значением
 *          по умолчанию является butter.
 *     rp: положительный результат
 *          Требуется только если выбран cheby1. Он определяет максимально допустимые
 *          колебания полосы пропускания в децибелах. Если не указано, по умолчанию 1.
 *     rs: положительный эффект
 *          Требуется только если выбран cheby2. Он определяет минимально необходимое
 *          затухание в полосе задерживания в децибелах. Если не указано, по умолчанию 1.
 *     fs: позитивный поплавок
 *          Частота дискретизации должна быть указана только в том случае, если
 *          предоставленная частота (частоты) отсечки уже не нормирована по Найквисту.
 *          В этом случае частота дискретизации в Гц будет использоваться для их
 *          нормализации.
 * Пример:
 *
 * from IIR2Filter import IIR2Filter
 * FilterMains = IIR2Filter (10, [45,55], 'bandtop', design = 'cheby1', rp = 2, fs = 1000)
 *
 * for i in range(len(mySignal)):
 *     mySignalFiltered [i] = FilterMains.filter(mySignal [i])
 *
 * # Он создает полосовой фильтр Чебышева 1-го порядка 10-го порядка, где частоты среза составляют 45 и 55 Гц для дискретных сигналов с частотой 1000 Гц. Фильтр допускает пульсации в полосе пропускания не более 2 дБ. Затем сигнал фильтруется выборка за выборкой и сохраняется в массиве mySignalFiltered.
*/

class DigitalFilterIIR2 : public IDigitalFilter
{
public:
    /*!
     * \brief FilterDesigns enum - тип фильтра
     */
    enum FilterDesigns
    {
        butter,     // Баттерворт
        cheby1,     // Чебышев, тип 1
        cheby2      // Чебышев, тип 2
    };
    /*!
     * \brief FilterType enum - тип фильтра
     */
    enum FilterType
    {
        lowpass,    // низкочастотный
        highpass,   // высокочастотный
        bandpass,   // полосовой
        bandstop    // режекторный
    };

    using Cutoff = std::pair<double,double>;
    using uint8 = unsigned char;
    using uint  = unsigned int;
    using CoeffVector = std::vector<double>;
    using Coefficients = std::vector<CoeffVector>;

    // запрещаем копирование и перемещение объекта
    DigitalFilterIIR2() = delete;
    DigitalFilterIIR2(const DigitalFilterIIR2 & AFilter) = delete;
    DigitalFilterIIR2(const DigitalFilterIIR2 && AFilter) = delete;
    DigitalFilterIIR2 & operator= (const DigitalFilterIIR2 & AFilter) = delete;
    DigitalFilterIIR2 & operator= (const DigitalFilterIIR2 && AFilter) = delete;
    /*!
     * \brief DigitalFilterIIR2 - конструктор фильтра
     * \param AOrder
     * \param ACutoff
     * \param AFilterType
     * \param ADesigns
     * \param ARp
     * \param ARs
     * \param AFs
     */
    explicit DigitalFilterIIR2(const uint  AFs,
                               const uint8 AOrder = 4,
                               const Cutoff ACutoff = Cutoff(13.0,0),
                               const FilterType AFilterType = lowpass,
                               const FilterDesigns ADesigns = cheby1,
                               const uint8 ARp = 1,
                               const uint8 ARs = 1);

    virtual double filter(const double ASample);

private:
    Coefficients COEFFS;
    std::vector<double> acc_input;
    std::vector<double> acc_output;
    std::vector<double> buffer1;
    std::vector<double> buffer2;
    CoeffVector FIRCOEFFS;
    CoeffVector IIRCOEFFS;
    double input;
    double output;

    void createCoeffs(const uint8 AOrder,
                              const Cutoff ACutoff,
                              const FilterType AFilterType,
                              const FilterDesigns ADesigns = cheby1,
                              const uint8 ARp = 1,
                              const uint8 ARs = 1,
                              const uint  AFs = 0);
};

#endif // DIGITALFILTERIIR2_H
