#ifndef ALSEN_RX_H
#define ALSEN_RX_H

#include <cmath>
#include <vector>
#include "alsenConst.h"

class alsen_rx
{
public:
    using uint = unsigned int;
    using AlsenRXRes = std::pair<double,double>;

    /*!
     * \brief alsen_rx - Приемник сигналов АЛСЕН
     * \param ADeskrFreq - частота дискретизации
     * \param ABitRate - скорость передачи Гц (Bod)
     * \param AFCar - несущая АЛС-ЕН
     * \param AAmplitude - амплитуда
     * \param ADecimFactor - фактор децимации
     */
    explicit alsen_rx(const uint   ADeskrFreq,
                      const double AAmplitude = 1.0,
                      const double ABitRate = BITRATE,
                      const double AFCar = CARFREQ,
                      const uint   ADecimFactor = 10);
    /*!
     * \brief sgn
     * \param sample - отсчет
     * \return 0 - если отсчет больше или равен 0 и 1 - если отсчет меньше 0
     */
    int sgn(const double sample) const;
    /*!
     * \brief local_gen - Локальный генератор cos и sin
     * \return - пару значений Y0 и Y90
     */
    void local_gen();
    /*!
     * \brief mux1 - Входные перемножители
     * \param gen - первый множитель
     * \param x - второй множитель
     * \return - результат перемножения
     */
    double mux1(const double gen,
                const double x) const;
    /*!
     * \brief diff_decode - Дифференциальный декодер
     * \param x0 - значение
     * \param x90 - значение
     * \return - пару декодированных значений Y7 и Y8
     */
    void diff_decode(const double x0,
                     const double x90);
    const alsen_rx::AlsenRXRes & Result() const { return FResult; }

private:
    double Fcar;
    double bit_rate;
    uint fs;

    double Ampl;
    double k;

    double X0_0;
    double X1_0;
    double X2_0;

    double X0_90;
    double X1_90;
    double X2_90;
    uint cycle_count;

    uint DecimFactor;
    uint buff_size;

    std::vector<double> data0;
    std::vector<double> data90;

    alsen_rx::AlsenRXRes FResult;

    /*!
     * \brief delay0 - Задержка сигнала на длительность посылки канала 0
     * \param x0 - значение
     * \return - значение с задержкой
     */
    double delay0(const double x0);
    /*!
     * \brief delay90 - Задержка сигнала на длительность посылки канала 90
     * \param x90 - значение
     * \return - значение с задержкой
     */
    double delay90(const double x90);
};

#endif // ALSEN_RX_H
