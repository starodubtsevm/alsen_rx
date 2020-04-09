#ifndef ALSENSIGNALIODEVICE_H
#define ALSENSIGNALIODEVICE_H

#include <QIODevice>
#include <QChartGlobal>

#include "chartViewDinamicForm.h"

class IDigitalFilter;
class ALSENSignalDecoder;

/*!
 * \brief Класс ALSENSignalIODevice обеспечивает получение данных из аудио устройства
 */
class ALSENSignalIODevice : public QIODevice
{
public:
    explicit ALSENSignalIODevice(IDigitalFilter & AViewFilter,
                                 IDigitalFilter & AWorkFilter,
                                 ALSENSignalDecoder & ADecoder,
                                 ChartViewDinamicForm * seriesFiltred = nullptr,
                                 ChartViewDinamicForm * seriesSource = nullptr,
                                 QObject *        parent = nullptr);

    /*!
     * \brief Stopped - флаг приостановки обработки
     * \return - значение флага
     */
    bool Stopped() const { return FStopped; }
    /*!
     * \brief Stopped - установка флага приостановки обработки
     * \param AStopped - значение флага
     */
    void Stopped(const bool AStopped);

    /*!
     * \brief Range - ширина "окна" для отображения графика в количестве отсчетов
     * \return - значение ширины
     */
    qint64 Range() const { return  FRange; }
    /*!
     * \brief Range  - установка ширины "окна" для отображения графика в количестве отсчетов
     * \param ARange - значение ширины
     */
    void Range(const qint64 ARange) { FRange = ARange; }

    /*!
     * \brief clearData - очистка "динамических" данных - не касается параметров порога, частоты дискретизации
     */
    void clearData();
    /*!
     * \brief writeRAWData - вызов декодера с необработанным отсчетом
     * \param ASample - значение отсчета
     */
    void writeRAWData(const double ASample);

protected:
    qint64 readData(char * data, qint64 maxSize);
    qint64 writeData(const char * data, qint64 maxSize);
private:
    ChartViewDinamicForm * FChartSeries;
    ChartViewDinamicForm * FChartSeries1;
    bool                   FStopped;
    qint64                 FRange;
    IDigitalFilter &       FViewFilter;
    IDigitalFilter &       FWorkFilter;
    ALSENSignalDecoder &   FDecoder;

    /*!
     * \brief showChart - метод отвечает за отрисовку обработанного сигнала
     * \param data - указатель на буфер отсчетов
     * \param maxSize - количество отсчетов в буфере
     */
    void showChart(const char * data, qint64 maxSize);
    /*!
     * \brief showSourceChart - метод отвечает за отрисовку исходного сигнала
     * \param data - указатель на буфер отсчетов
     * \param maxSize - количество отсчетов в буфере
     */
    void showSourceChart(const char * data, qint64 maxSize);
    /*!
     * \brief processSignal - метод производящий основную обработку сигнала
     * \param data - указатель на буфер отсчетов
     * \param maxSize - количество отсчетов в буфере
     */
    void processSignal(const char * data, qint64 maxSize);
};

#endif // ALSENSIGNALIODEVICE_H
