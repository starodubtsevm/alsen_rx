#include "alsenSignalGen.h"
#include <cmath>
#include <chrono>
#include <iostream>

alsenSignalGen::alsenSignalGen(const int    AAmplitude,
                               const uint   ASamplRate,
                               const double ACarrierFrequency,
                               const double ABitRate)
    : Fcar(ACarrierFrequency), // частота несущей
      FSamplRate(ASamplRate),   // частота дискретизации
      FBitRate(ABitRate),       // скорость передачи данных
      FAmplitude(AAmplitude),   // амплитуда
      imp_duty_count(static_cast<int>((1.0/FBitRate)/(1.0/FSamplRate))), // количество отсчетов
      count_bit(8),            // количество бит
      diBit(0),
      phase(0),
      d_phase(0),
      ConstDutyCount(static_cast<int>((1.0/FBitRate)/(1.0/FSamplRate))),
      FCode1(0),
      FCode2(0),
      Byte1(0),
      Byte2(0),
      FIsAddNoise(false),
      Iterator(0)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator = new std::default_random_engine(seed);
    distribution = new std::normal_distribution<double>(0.0,1.0);
}

alsenSignalGen::~alsenSignalGen()
{
    delete distribution;
    delete generator;
}

void alsenSignalGen::genSignal(alsenSignalGen::Samples & ADestSamples,
                               alsenSignalGen::uint ADuration,
                               alsenSignalGen::uint8 ACode1,
                               alsenSignalGen::uint8 ACode2,
                               bool isAddNoise)
{
    uint CountDuration = ADuration * FSamplRate;
    ADestSamples.reserve(CountDuration);
    Byte1 = ACode1;
    Byte2 = ACode2;
    for(uint i = 0; i < CountDuration; ++i)
    {
        if (imp_duty_count < ConstDutyCount)
            imp_duty_count++;
        else
        {
            imp_duty_count = 0;

            if (count_bit==0)
            {
                count_bit = 8;
                Byte1 = ACode1;
                Byte2 = ACode2;
            }

            diBit =((Byte1 & 0x80) >> 6)+((Byte2 & 0x80) >> 7);

            if(diBit == 0) d_phase = 0; // 0
            else
                if (diBit == 1) d_phase = 1; // 90
                else
                    if (diBit == 2) d_phase = 3; // 270
                    else
                        if (diBit == 3) d_phase = 2; // 180

            phase = phase + d_phase;

            if( phase > 4 ) phase -= 4;

            Byte1 <<= 1;
            Byte2 <<= 1;

            count_bit--;
        }

        double v = i * 2 * M_PI * Fcar/FSamplRate + (phase*M_PI)/2;
        double sample = FAmplitude * sin(v);

        if(isAddNoise) sample += normal_distribution_noise();

        ADestSamples.push_back(sample);
    }
}

double alsenSignalGen::genSample()
{
    if (imp_duty_count < ConstDutyCount)
        imp_duty_count++;
    else
    {
        imp_duty_count = 0;

        if (count_bit==0)
        {
            count_bit = 8;
            Byte1 = FCode1;
            Byte2 = FCode2;
        }

        diBit =((Byte1 & 0x80) >> 6)+((Byte2 & 0x80) >> 7);

        if(diBit == 0) d_phase = 0; // 0
        else
            if (diBit == 1) d_phase = 1; // 90
            else
                if (diBit == 2) d_phase = 3; // 270
                else
                    if (diBit == 3) d_phase = 2; // 180

        phase = phase + d_phase;

        if( phase > 4 ) phase -= 4;

        Byte1 <<= 1;
        Byte2 <<= 1;

        count_bit--;
    }

    double v = Iterator * 2 * M_PI * Fcar/FSamplRate + (phase*M_PI)/2;
    //printf( "%d,%d\n", imp_duty_count, count_bit );
    //printf( "%.10f\n", phase );
    //printf( "%.4f\n", v );
    double sample = FAmplitude * sin(v);
    //printf( "%.4f\n", sample );
    //TODO if(FIsAddNoise) sample += normal_distribution_noise();

    Iterator++;

    return sample;
}

void alsenSignalGen::Amplitude(const alsenSignalGen::uint AAmplitude)
{
    FAmplitude = AAmplitude;
}

void alsenSignalGen::SamplRate(const alsenSignalGen::uint ASamplRate)
{
    FSamplRate = ASamplRate;
    imp_duty_count = static_cast<int>((1.0/FBitRate)/(1.0/FSamplRate));
    ConstDutyCount = static_cast<int>((1.0/FBitRate)/(1.0/FSamplRate));
    initData();
}

void alsenSignalGen::CarrierFrequency(const double ACarrierFrequency)
{
    Fcar = ACarrierFrequency;
}

void alsenSignalGen::BitRate(const double ABitRate)
{
    FBitRate = ABitRate;
    imp_duty_count = static_cast<int>((1.0/FBitRate)/(1.0/FSamplRate));
    ConstDutyCount = static_cast<int>((1.0/FBitRate)/(1.0/FSamplRate));
    initData();
}

void alsenSignalGen::Code1(const alsenSignalGen::uint8 ACode1)
{
    FCode1 = ACode1;
    initData();
}

void alsenSignalGen::Code2(const alsenSignalGen::uint8 ACode2)
{
    FCode2 = ACode2;
    initData();
}

double alsenSignalGen::normal_distribution_noise()
{
    return (*distribution)(*generator) * FAmplitude;
}

void alsenSignalGen::initData()
{
    count_bit = 8;
    Byte1 = FCode1;
    Byte2 = FCode2;
    count_bit = 8;
    diBit = 0;
    phase = 0;
    d_phase = 0;
    Iterator = 0;
}
