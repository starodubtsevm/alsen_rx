#ifndef ALSENSIGNALGEN_H
#define ALSENSIGNALGEN_H

#include <vector>
#include <random>

class alsenSignalGen
{
public:
    using uint  = unsigned int;
    using uint8 = unsigned char;
    using Samples = std::vector<double>;

    alsenSignalGen(const int    AAmplitude = 10000,
                   const uint   ASamplRate = 8000,
                   const double ACarrierFrequency = 174.89,
                   const double ABitRate = 13.89);
    virtual ~alsenSignalGen();

    void genSignal(Samples & ADestSamples,
                   uint ADuration,
                   uint8 ACode1,
                   uint8 ACode2,
                   bool isAddNoise = false);
    double genSample();

    uint Amplitude() const { return FAmplitude; }
    void Amplitude(const uint AAmplitude);

    uint SamplRate() const { return FSamplRate; }
    void SamplRate(const uint ASamplRate);

    double CarrierFrequency() const { return Fcar; }
    void CarrierFrequency(const double ACarrierFrequency);

    double BitRate() const { return  FBitRate; }
    void BitRate(const double ABitRate);

    uint8 Code1() const { return FCode1; }
    void Code1(const uint8 ACode1);

    uint8 Code2() const { return FCode2; }
    void Code2(const uint8 ACode2);

    bool IsAddNoise() const { return FIsAddNoise; }
    void IsAddNoise(const bool AIsAddNoise) { FIsAddNoise = AIsAddNoise; }

private:
    double Fcar;
    uint   FSamplRate;
    double FBitRate;
    uint   FAmplitude;
    uint   imp_duty_count;
    uint   count_bit;
    uint8  diBit;
    double phase;
    double d_phase;
    uint   ConstDutyCount;
    uint8  FCode1;
    uint8  FCode2;
    uint8  Byte1;
    uint8  Byte2;
    bool   FIsAddNoise;
    uint64_t Iterator;

    std::default_random_engine * generator;
    std::normal_distribution<double> * distribution;

    /*!
     * \brief normal_distribution_noise - генерация шума нормального распределения
     * \return - возвращает случайное значение умноженное на амплитуду(Amplitude)
     */
    double normal_distribution_noise();
    void initData();
};

#endif // ALSENSIGNALGEN_H
