#include "alsen_rx.h"
#include <iostream>

alsen_rx::alsen_rx(const uint   ADeskrFreq,
                   const double AAmplitude,
                   const double ABitRate,
                   const double AFCar,
                   const uint   ADecimFactor)
    : Fcar(AFCar),          // несущая АЛС-ЕН
      bit_rate(ABitRate),   // скорость передачи Гц (Bod)
      fs(ADeskrFreq),       // частота дискретизации
      Ampl(AAmplitude),
      k(2 * cos(2 * M_PI * Fcar / fs)),

      X0_0(0.0),
      X1_0(0.0),
      X2_0(Ampl * sin(2 * M_PI * Fcar / fs)),

      X0_90(0.0),
      X1_90(0.0),
      X2_90(Ampl * sin(2 * M_PI * Fcar / fs)),
      cycle_count(0),

      DecimFactor(ADecimFactor), // фактор децимации
      buff_size(static_cast<int>((1.0/bit_rate)/(1.0/fs)/DecimFactor)),
      data0(buff_size),
      data90(buff_size)
{
    //Q_UNUSED(AAmplitude)
}

int alsen_rx::sgn(const double sample) const
{
    return (sample < 0) ? 1 : 0;
}

void alsen_rx::local_gen()
{
    cycle_count++;

    X0_0 = k * X1_0 - X2_0;
    double y_0 = X0_0;
    X2_0 = X1_0;
    X1_0 = X0_0;

    double y_90 = 0.0;

    if (cycle_count > 13)
    {
       X0_90 = k * X1_90 - X2_90;
       y_90 = X0_90;
       X2_90 = X1_90;
       X1_90 = X0_90;
       cycle_count = 13;
    }

    FResult.first = y_0;
    FResult.second = y_90;
}

double alsen_rx::mux1(const double gen, const double x) const
{
    return gen * x;
}

void alsen_rx::diff_decode(const double x0, const double x90)
{
    double y1 = x0  * delay0(x0);
    double y2 = x90 * delay0(x0);
    double y3 = x0  * delay90(x90);
    double y4 = x90 * delay90(x90);

    FResult.first = (y2 - y3) + (y1 + y4); //# Окунев стр 171
    FResult.second = (y1 + y4) - (y2 - y3);
}

double alsen_rx::delay0(const double x0)
{
    data0.insert(data0.begin(),x0);
    data0.pop_back();
    return data0[data0.size()-1];
}

double alsen_rx::delay90(const double x90)
{
    data90.insert(data90.begin(),x90);
    data90.pop_back();
    return data90[data90.size()-1];
}
