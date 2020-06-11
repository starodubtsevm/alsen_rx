#ifndef DECODERTESTMAIN_H
#define DECODERTESTMAIN_H

#include <QMainWindow>
#include <QVector>
#include "ChartsViewForm.h"
#include <QAudioInput>

QT_BEGIN_NAMESPACE
namespace Ui { class DecoderTestMain; }
QT_END_NAMESPACE

class DecoderTestMain : public QMainWindow
{
    Q_OBJECT

public:
    DecoderTestMain(QWidget *parent = nullptr);
    ~DecoderTestMain();

    void addMessageToLog(const QString AMessage);

public slots:
    void onEnterSampleProc(const double ASample);

    void onCodeDetect0proc(const double time, const quint8 ACode0, const quint8 ABaseCode0);
    void onCodeDetect90proc(const double time, const quint8 ACode90, const quint8 ABaseCode90);

//    void onCodeDetect(const quint8 ACode0, const quint8 AGroup0,
//                      const quint8 ACode90, const quint8 AGroup90);

    void onCodeDetectBits( const uint64_t sample_count,
                           const bool bit0,
                           const bool bit90 );

    void onAfterGenProc(const double AValue0,
                        const double AValue90);

    void onAfterMuxProc(const double AValue0,
                        const double AValue90);

    void onAfterIIRProc(const double AValue0,
                        const double AValue90);

    void onY7_8Proc(const double AY7,
                    const double AY8);

    void onY9_10Proc(const double AY9,
                     const double AY10);

    void onPll0Proc(const uint ASync,
                    const uint ABit);

    void onPll90Proc(const uint ASync,
                     const uint ABit);

private slots:
    void on_pbLogClear_clicked();
    void on_pbStart_clicked();

    void on_cmbAudioInputList_currentIndexChanged(int index);

    void on_pbStopRecord_clicked();

private:
    Ui::DecoderTestMain *ui;

    QList<QAudioDeviceInfo>  FAudioDeviceList;
    QAudioDeviceInfo         FAudioInfoCurrent;
    QAudioFormat *           FAudioFormat;
    bool                     FRecordRun;

    ChartsViewForm  FViewForm;

    QVector<double> FSamplesVec;
    QVector<double> FGen0Vec;
    QVector<double> FGen90Vec;
    QVector<double> FMux0Vec;
    QVector<double> FMux90Vec;
    QVector<double> FIRR0Vec;
    QVector<double> FIRR90Vec;
    QVector<double> FY7Vec;
    QVector<double> FY8Vec;
    QVector<double> FY9Vec;
    QVector<double> FY10Vec;
    QVector<double> FSync0Vec;
    QVector<double> FBit0Vec;
    QVector<double> FSync90Vec;
    QVector<double> FBit90Vec;

    void clearData();
    void makeAndShowCharts();
};
#endif // DECODERTESTMAIN_H
