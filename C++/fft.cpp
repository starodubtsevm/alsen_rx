#include "fft.h"
#include <math.h>
#include <algorithm>

fft::fft():
    FFFTValues(new vector<double>())
{
}

fft::~fft()
{
    clear();
    delete FFFTValues;
}

int fft::maxHarmonicIndex() const
{
    if(!FFFTValues->size()) return -1;
    auto MaxValue = max_element(FFFTValues->begin(),FFFTValues->end());
    if(MaxValue == FFFTValues->end()) return -1;
    return static_cast<int>(distance(FFFTValues->begin(), MaxValue));
}

void fft::clear()
{
    FFFTValues->clear();
}

void fft::operator()(const vector<double> & ASourceVector)
{
    this->operator()(ASourceVector.data(),static_cast<int>(ASourceVector.size()));
}

void fft::operator()(const double * ASourceArray, const int ALen)
{
    if(!ALen) return;
    clear();
    FFFTValues->reserve(static_cast<size_t>(ALen));

    // https://ru.wikibooks.org/wiki/Реализации_алгоритмов/Быстрое_преобразование_Фурье
    int i, j, n, m, Mmax, Istp;
    double Tmpr, Tmpi, Wtmp, Theta;
    double Wpr, Wpi, Wr, Wi;
    double * Tmvl;

    n = ALen * 2;
    Tmvl = new double[n];

    for (i = 0; i < n; i+=2)
    {
     Tmvl[i] = 0;
     Tmvl[i+1] = ASourceArray[i/2];
    }

    i = 1; j = 1;
    while (i < n)
    {
      if (j > i)
      {
        Tmpr = Tmvl[i];
        Tmvl[i] = Tmvl[j];
        Tmvl[j] = Tmpr;
        Tmpr = Tmvl[i+1];
        Tmvl[i+1] = Tmvl[j+1];
        Tmvl[j+1] = Tmpr;
      }
      i = i + 2;
      m = ALen;
      while ((m >= 2) && (j > m))
      {
        j = j - m;
        m = m >> 1;
      }
      j = j + m;
    }

    Mmax = 2;
    while (n > Mmax)
    {
      Theta = -(M_PI * 2) / Mmax;
      Wpi = sin(Theta);
      Wtmp = sin(Theta / 2);
      Wpr = Wtmp * Wtmp * 2;
      Istp = Mmax * 2;
      Wr = 1;
      Wi = 0;
      m = 1;

      while (m < Mmax)
      {
        i = m; m = m + 2;
        Tmpr = Wr;
        Tmpi = Wi;
        Wr = Wr - Tmpr * Wpr - Tmpi * Wpi;
        Wi = Wi + Tmpr * Wpi - Tmpi * Wpr;

        while (i < n)
        {
          j = i + Mmax;
          Tmpr = Wr * Tmvl[j] - Wi * Tmvl[j-1];
          Tmpi = Wi * Tmvl[j] + Wr * Tmvl[j-1];

          Tmvl[j] = Tmvl[i] - Tmpr;
          Tmvl[j-1] = Tmvl[i-1] - Tmpi;
          Tmvl[i] = Tmvl[i] + Tmpr;
          Tmvl[i-1] = Tmvl[i-1] + Tmpi;
          i = i + Istp;
        }
      }

      Mmax = Istp;
    }

    for (i = 0; i < ALen; i++)
    {
      j = i * 2;
      FFFTValues->push_back(2 * sqrt(pow(Tmvl[j],2) + pow(Tmvl[j+1],2))/ALen);
      //FTvl[i] = 2 * sqrt(pow(Tmvl[j],2) + pow(Tmvl[j+1],2))/ALen;
    }

    delete [] Tmvl;
}
