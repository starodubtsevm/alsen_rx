#include "decodertestmain.h"
#include "ui_decodertestmain.h"

#include "alsenSignalGen.h"
#include "alsensignaldecoder.h"
#include "alsensignaliodevice.h"
#include <vector>
#include <iostream>
#include <iomanip>

#include <QSignalSpy>
#include <QTest>

#include <QTimer>

//#include "alsen_sig_const.h"

#include <QTime>

const quint8 bauerCode[16] = { 0x01, 0x1F, 0x2C, 0x32, 0x4A, 0x54, 0x67, 0x79, 0x86, 0x98, 0xAB, 0xB5, 0xCD, 0xD3, 0xE0, 0xFE };

DecoderTestMain::DecoderTestMain(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::DecoderTestMain),
      FAudioFormat(new QAudioFormat)
{
    ui->setupUi(this);

    // перечень устройств ввода звука
    FAudioDeviceList = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    foreach (const QAudioDeviceInfo & deviceInfo, FAudioDeviceList)
    {
        if(!deviceInfo.isNull())
            ui->cmbAudioInputList->addItem(deviceInfo.deviceName());
    }
    ui->cmbAudioInputList->setCurrentIndex(0);
    FAudioInfoCurrent = FAudioDeviceList.at(0);

    FAudioFormat->setSampleRate(SAMPLERATE);
    FAudioFormat->setChannelCount(1);
    FAudioFormat->setSampleSize(8);
    FAudioFormat->setCodec("audio/pcm");
    FAudioFormat->setByteOrder(QAudioFormat::LittleEndian);
    FAudioFormat->setSampleType(QAudioFormat::UnSignedInt);
}

DecoderTestMain::~DecoderTestMain()
{
    delete FAudioFormat;
    delete ui;
}

void DecoderTestMain::onEnterSampleProc(const double ASample)
{
    FSamplesVec.push_back(ASample);
}

void DecoderTestMain::on_pbLogClear_clicked()
{
    ui->teLog->clear();
}

void DecoderTestMain::on_pbStart_clicked()
{
    ui->pbStart->setEnabled(false);

    addMessageToLog("Запуск измерения.");

    ALSENSignalDecoder decoder(bauerCode[ui->cmbCode0->currentIndex()],    //Code0
                               bauerCode[ui->cmbCode90->currentIndex()]);  //Code90
                               //SAMPLERATE,
                               //10,
                               //true);

    connect(&decoder,&ALSENSignalDecoder::onEnterSample,
            this, &DecoderTestMain::onEnterSampleProc);
    connect(&decoder,&ALSENSignalDecoder::onCodeDetect0,
            this, &DecoderTestMain::onCodeDetect0proc);
    connect(&decoder,&ALSENSignalDecoder::onCodeDetect90,
            this, &DecoderTestMain::onCodeDetect90proc);

    //connect(&decoder,&ALSENSignalDecoder::onCodeDetectBits,
    //        this, &DecoderTestMain::onCodeDetectBitsProc);

    connect(&decoder,&ALSENSignalDecoder::onCodeDetect,
            this, &DecoderTestMain::onCodeDetectProc);

    connect(&decoder,&ALSENSignalDecoder::onAfterGen,
            this, &DecoderTestMain::onAfterGenProc);
    connect(&decoder,&ALSENSignalDecoder::onAfterMux,
            this, &DecoderTestMain::onAfterMuxProc);
    connect(&decoder,&ALSENSignalDecoder::onAfterIIR,
            this, &DecoderTestMain::onAfterIIRProc);
    connect(&decoder,&ALSENSignalDecoder::onY7_8,
            this, &DecoderTestMain::onY7_8Proc);
    connect(&decoder,&ALSENSignalDecoder::onY9_10,
            this, &DecoderTestMain::onY9_10Proc);
    connect(&decoder,&ALSENSignalDecoder::onPll0,
            this, &DecoderTestMain::onPll0Proc);
    connect(&decoder,&ALSENSignalDecoder::onPll90,
            this, &DecoderTestMain::onPll90Proc);

    clearData();

    addMessageToLog("Запуск обработки");

    ALSENSignalIODevice device(decoder);
    device.open(QIODevice::WriteOnly);
    device.Stopped(false);

    if(ui->cbUseAudioInput->isChecked())
    {
        ui->pbStopRecord->setEnabled(true);
        FRecordRun = true;

        QSignalSpy spy(&decoder,&ALSENSignalDecoder::onCodeDetect);
        bool Res = spy.isValid();
        if(!Res) // не удалось прицепиться
        {
            device.close();
            addMessageToLog("Тест прерван - не удаломсь прицепиться к сигналу");
            on_pbStopRecord_clicked();
            return;
        }

        QAudioInput * FAudioRecorder = new QAudioInput(FAudioInfoCurrent,*FAudioFormat,this);
        FAudioRecorder->start(&device);

        while (FRecordRun)
        {
            bool Res = spy.wait(1000); // 5000 ms  //поставил 1000 чтобы можно было быстрее отключить прослушивание - для удобства простмотра графиков
            if(!Res) // сигнал не пришел
            {
                addMessageToLog("Истек таймаут ожидания сигнала - сигнал не пришел."); //< даже при наличии сигнала- это сообщение появляется - не разбирался почему
                continue;
            }

            // разбираем пришедший сигнал
            quint64 len    = qvariant_cast<quint8>(spy.at(0).at(0));
            quint8 Code0   = qvariant_cast<quint8>(spy.at(0).at(1));
            quint8 Group0  = qvariant_cast<quint8>(spy.at(0).at(2));
            quint8 Code90  = qvariant_cast<quint8>(spy.at(0).at(3));
            quint8 Group90 = qvariant_cast<quint8>(spy.at(0).at(4));

            addMessageToLog(QString("Пришел сигнал. "
                               "\n\t\tCode0 = 0x%1; "
                               "\tGroup0 = 0x%2; "
                               "\n\t\tCode90 = 0x%3; "
                               "\tGroup90 = 0x%4"
                               "\tДлительность: %5 с")
                       .arg(QString::number(Code0,16).toUpper().leftJustified(2,'0'))
                       .arg(QString::number(Group0,16).toUpper().leftJustified(2,'0'))
                       .arg(QString::number(Code90,16).toUpper().leftJustified(2,'0'))
                       .arg(QString::number(Group90,16).toUpper().leftJustified(2,'0'))
                       .arg((len * 1.0/SAMPLERATE),6,'f',4,QChar('0')));
        }

        FAudioRecorder->stop();
        delete FAudioRecorder;
        FAudioRecorder = nullptr;
    }
    else
    {
        // генератор сигала АЛСЕН
        alsenSignalGen sigGen(ui->spbAmplitude->value(),
                              SAMPLERATE,
                              ui->dspbCarFreq->value());
        sigGen.Code90(bauerCode[ui->cmbCode90->currentIndex()]);
        sigGen.Code0(bauerCode[ui->cmbCode0->currentIndex()]);
        uint CountDuration = ui->spbDuration->value() * sigGen.SamplRate();

        addMessageToLog(QString("Сгенерирован сигнал длительностью %1 с.;\tКоличество отсчетов: %2; "
                                "\n\t\t\t\t\t\tКод1: 0x%3;\t\tКод2: 0x%4;")
                        .arg(ui->spbDuration->value())
                        .arg(CountDuration)
                        .arg(QString::number(sigGen.Code90(),16).toUpper().leftJustified(2,'0'))
                        .arg(QString::number(sigGen.Code0(),16).toUpper().leftJustified(2,'0')));

        for(size_t i = 0; i < CountDuration; ++i)
        {
            device.writeRAWData(sigGen.genSample());
        }
        ui->pbStart->setEnabled(true);
    }

    device.Stopped(true);
    device.close();

    addMessageToLog("Обработка закончена");

    if(ui->cbShowCharts->isChecked()) makeAndShowCharts();
}

void DecoderTestMain::addMessageToLog(const QString AMessage)
{
    ui->teLog->append(QString("[%1]\t%2").arg(QTime().currentTime().toString("hh:mm:ss,zzz")).arg(AMessage));
}

void DecoderTestMain::clearData()
{
    FViewForm.clear();

    FSamplesVec.clear();
    FGen0Vec.clear();
    FGen90Vec.clear();
    FMux0Vec.clear();
    FMux90Vec.clear();
    FIRR0Vec.clear();
    FIRR90Vec.clear();
    FY7Vec.clear();
    FY8Vec.clear();
    FY9Vec.clear();
    FY10Vec.clear();
    FSync0Vec.clear();
    FBit0Vec.clear();
    FSync90Vec.clear();
    FBit90Vec.clear();
}

void DecoderTestMain::makeAndShowCharts()
{
    FViewForm.addChart("Отсчеты",
                       FSamplesVec.data(),
                       FSamplesVec.size(),
                       ui->spbSections->value());

    FViewForm.addChart("Gen0",
                       FGen0Vec.data(),
                       FGen0Vec.size(),
                       ui->spbSections->value());

    FViewForm.addChart("Gen90",
                       FGen90Vec.data(),
                       FGen90Vec.size(),
                       ui->spbSections->value());

    FViewForm.addChart("Mux0",
                       FMux0Vec.data(),
                       FMux0Vec.size(),
                       ui->spbSections->value());

    FViewForm.addChart("Mux90",
                       FMux90Vec.data(),
                       FMux90Vec.size(),
                       ui->spbSections->value());

    FViewForm.addChart("IRR0",
                       FIRR0Vec.data(),
                       FIRR0Vec.size(),
                       ui->spbSections->value());

    FViewForm.addChart("IRR90",
                       FIRR90Vec.data(),
                       FIRR90Vec.size(),
                       ui->spbSections->value());

    FViewForm.addChart("Y7",
                       FY7Vec.data(),
                       FY7Vec.size(),
                       ui->spbSections->value());

    FViewForm.addChart("Y8",
                       FY8Vec.data(),
                       FY8Vec.size(),
                       ui->spbSections->value());

    FViewForm.addChart("Y9",
                       FY9Vec.data(),
                       FY9Vec.size(),
                       ui->spbSections->value());

    FViewForm.addChart("Y10",
                       FY10Vec.data(),
                       FY10Vec.size(),
                       ui->spbSections->value());

    FViewForm.addChart("Sync0",
                       FSync0Vec.data(),
                       FSync0Vec.size(),
                       ui->spbSections->value());

    FViewForm.addChart("Bit0",
                       FBit0Vec.data(),
                       FBit0Vec.size(),
                       ui->spbSections->value());

    FViewForm.addChart("Sync90",
                       FSync90Vec.data(),
                       FSync90Vec.size(),
                       ui->spbSections->value());

    FViewForm.addChart("Bit90",
                       FBit90Vec.data(),
                       FBit90Vec.size(),
                       ui->spbSections->value());

    FViewForm.show();
}

static void display_msg( DecoderTestMain* decoder_test, double time, uint8_t ch, uint8_t code, uint8_t base_code, QString base)
{
    decoder_test->addMessageToLog(QString("Время: %1 с;\t Канал: %2;\t Code: 0x%3;\t Base: 0x%4;\t\t Запрашиваемый код: %5")
                                   .arg(time,3,'f',2,QChar('0'))
                                   .arg(ch,2,10,QChar('0'))
                                   .arg(base_code,2,16,QChar('0'))
                                   .arg(code,2,16,QChar('0'))
                                   .arg(base));
}

void DecoderTestMain::onCodeDetect0proc(const double time, const quint8 ACode0, const quint8 ABaseCode0)
{
    display_msg(this,time,0,ACode0,ABaseCode0,ui->cmbCode0->currentText());
}

void DecoderTestMain::onCodeDetect90proc(const double time, const quint8 ACode90, const quint8 ABaseCode90)
{
    display_msg(this,time,90,ACode90,ABaseCode90,ui->cmbCode90->currentText());
}

void DecoderTestMain::onCodeDetectBitsProc( const uint64_t sample_count,
                                            const bool bit0,
                                            const bool bit90 )
{
    addMessageToLog(QString("Получены биты. Интервал %1,\t Бит0: %2;\t Бит90: %3")
                    .arg(sample_count)
                    .arg(bit0 ? 1 : 0)
                    .arg(bit90 ? 1 : 0));
}

void DecoderTestMain::onCodeDetectProc(const quint64 sample_count,
                                       const quint8 ACode0,
                                       const quint8 ABaseCode0,
                                       const quint8 ACode90,
                                       const quint8 ABaseCode90)
{
    addMessageToLog(QString("Получены коды. Code0: 0x%1;\t Base0: 0x%2;\t Code90: 0x%3;\t Base90: 0x%4\t Длительность: %5 c")
                            .arg(ACode0,2,16,QChar('0'))
                            .arg(ABaseCode0,2,16,QChar('0'))
                            .arg(ACode90,2,16,QChar('0'))
                            .arg(ABaseCode90,2,16,QChar('0'))
                            .arg((sample_count * 1.0/SAMPLERATE),6,'f',4,QChar('0')));
}

void DecoderTestMain::onAfterGenProc(const double AValue0, const double AValue90)
{
    FGen0Vec.push_back(AValue0);
    FGen90Vec.push_back(AValue90);
}

void DecoderTestMain::onAfterMuxProc(const double AValue0, const double AValue90)
{
    FMux0Vec.push_back(AValue0);
    FMux90Vec.push_back(AValue90);
}

void DecoderTestMain::onAfterIIRProc(const double AValue0, const double AValue90)
{
    FIRR0Vec.push_back(AValue0);
    FIRR90Vec.push_back(AValue90);
}

void DecoderTestMain::onY7_8Proc(const double AY7, const double AY8)
{
    FY7Vec.push_back(AY7);
    FY8Vec.push_back(AY8);
}

void DecoderTestMain::onY9_10Proc(const double AY9, const double AY10)
{
    FY9Vec.push_back(AY9);
    FY10Vec.push_back(AY10);
}

void DecoderTestMain::onPll0Proc(const uint ASync, const uint ABit)
{
    FSync0Vec.push_back(ASync);
    FBit0Vec.push_back(ABit);
}

void DecoderTestMain::onPll90Proc(const uint ASync, const uint ABit)
{
    FSync90Vec.push_back(ASync);
    FBit90Vec.push_back(ABit);
}

void DecoderTestMain::on_cmbAudioInputList_currentIndexChanged(int index)
{
    FAudioInfoCurrent = FAudioDeviceList.at(index);
}

void DecoderTestMain::on_pbStopRecord_clicked()
{
    FRecordRun = false;
    ui->pbStart->setEnabled(true);
    ui->pbStopRecord->setEnabled(false);
}
