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

    FAudioFormat->setSampleRate(8000);
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

    ALSENSignalDecoder decoder(bauerCode[ui->cmbCode0->currentIndex()],   //Code0
                               bauerCode[ui->cmbCode90->currentIndex()]); //Code90

    connect(&decoder,&ALSENSignalDecoder::onEnterSample,
            this, &DecoderTestMain::onEnterSampleProc);
    connect(&decoder,&ALSENSignalDecoder::onCodeDetect0,
            this, &DecoderTestMain::onCodeDetect0proc);
    connect(&decoder,&ALSENSignalDecoder::onCodeDetect90,
            this, &DecoderTestMain::onCodeDetect90proc);
//    connect(&decoder,&ALSENSignalDecoder::onCodeDetect,
//            this, &DecoderTestMain::onCodeDetect);

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
            bool Res = spy.wait(); // 5000 ms
            if(!Res) // сигнал не пришел
            {
                addMessageToLog("Истек таймаут ожидания сигнала - сигнал не пришел.");
                continue;
            }

            // разбираем пришедший сигнал
            quint8 Code0   = qvariant_cast<quint8>(spy.at(0).at(0));
            quint8 Group0  = qvariant_cast<quint8>(spy.at(0).at(1));
            quint8 Code90  = qvariant_cast<quint8>(spy.at(0).at(2));
            quint8 Group90 = qvariant_cast<quint8>(spy.at(0).at(3));

            addMessageToLog(QString("Пришел сигнал. "
                               "\n\t\tCode0 = 0x%1; "
                               "\tGroup0 = 0x%2; "
                               "\n\t\tCode90 = 0x%3; "
                               "\tGroup90 = 0x%4")
                       .arg(QString::number(Code0,16).toUpper())
                       .arg(QString::number(Group0,16).toUpper())
                       .arg(QString::number(Code90,16).toUpper())
                       .arg(QString::number(Group90,16).toUpper()));
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
                        .arg(QString::number(sigGen.Code90(),16).toUpper())
                        .arg(QString::number(sigGen.Code0(),16).toUpper()));

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

static void display_msg( DecoderTestMain* decoder_test, double time, uint8_t ch, uint8_t code, uint8_t base_code, uint32_t index)
{
    QString s = "%1с Канал: %2 Code: 0x%3 Byte: 0x%4 Base: 0x%5";

    s = s.arg(time,3,'f',2,QChar('0')).arg(ch,2,10,QChar('0')).arg(base_code,2,16,QChar('0')).arg(code,2,16,QChar('0')).arg(bauerCode[index],2,16,QChar('0'));

    decoder_test->addMessageToLog( s );
}


void DecoderTestMain::onCodeDetect0proc(const double time, const quint8 ACode0, const quint8 ABaseCode0)
{
    display_msg(this,time,0,ACode0,ABaseCode0,ui->cmbCode0->currentIndex());
}

void DecoderTestMain::onCodeDetect90proc(const double time, const quint8 ACode90, const quint8 ABaseCode90)
{
    display_msg(this,time,90,ACode90,ABaseCode90,ui->cmbCode90->currentIndex());
}

//void DecoderTestMain::onCodeDetect(const quint8 ACode0, const quint8 AGroup0, const quint8 ACode90, const quint8 AGroup90)
//{
//    addMessageToLog(QString("Оба канала. Канал 0: Код 0x%1; Базовый код 0x%2\n"
//                            "\t\t\t Канал 90: Код 0x%3; Базовый код 0x%4")
//                    .arg(QString::number(ACode0,16).toUpper())
//                    .arg(QString::number(AGroup0,16).toUpper())
//                    .arg(QString::number(ACode90,16).toUpper())
//                    .arg(QString::number(AGroup90,16).toUpper()));
//}

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
