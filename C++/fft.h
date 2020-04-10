#ifndef FFT_H
#define FFT_H

#include <vector>

using namespace std;

/*!
 * \brief Класс fft - функтор. Вычисление Быстрого преобразования Фурье
 */
class fft
{
public:
    fft();
    ~fft();
    // запрещаем копирование и перенос
    fft(const fft & AFft) = delete;
    fft(const fft && AFft) = delete;
    fft & operator=(const fft & AFft) = delete;
    fft & operator=(const fft && AFft) = delete;

    /*!
     * \brief FFTValues - метод возвращает константную ссылку на массив значений рассчитанного Быстрого Преобразования Фурье(БПФ)
     * \return - константная ссылка на массив значений
     */
    const vector<double> & FFTValues() const { return * FFFTValues; }
    /*!
     * \brief maxHarmonicIndex - возвращает индекс максимальной гармоники спектра или -1 в случае если БПФ еще не расчитан
     * \return - индекс максимальной гармоники
     */
    int maxHarmonicIndex() const;
    /*!
     * \brief clear - очищает массив расчитанного БПФ
     */
    void clear();

    /*!
     * \brief operator()(const double * ASourceArray, const int ALen) - функция рассчета БПФ переданного массива отсчетов
     * \param ASourceArray - массив отсчетов
     * \param ALen - длинна масива отсчетов
     */
    void operator() (const double * ASourceArray, const int ALen);
    /*!
     * \brief operator()(const vector<double> & ASourceVector) - функция рассчета БПФ переданного вектора отсчетов
     * \param ASourceVector - вектор отсчетов
     */
    void operator() (const vector<double> & ASourceVector);

private:
    vector<double> * FFFTValues;
};

#endif // FFT_H
