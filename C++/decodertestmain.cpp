#include "decodertestmain.h"
#include "ui_decodertestmain.h"

#include "alsenSignalGen.h"
#include "alsensignaldecoder.h"
#include "alsensignaliodevice.h"
#include "digitalfilter.h"
#include <vector>

#include "alsen_sig_const.h"

#include <QTime>

const quint8 bauerCode[16] = { 0x01, 0x1F, 0x2C, 0x32, 0x4A, 0x54, 0x67, 0x79, 0x86, 0x98, 0xAB, 0xB5, 0xCD, 0xD3, 0xE0, 0xFE };

DecoderTestMain::DecoderTestMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DecoderTestMain)
{
    ui->setupUi(this);
}

DecoderTestMain::~DecoderTestMain()
{
    delete ui;
}

void DecoderTestMain::on_pbLogClear_clicked()
{
    ui->teLog->clear();
}

void DecoderTestMain::on_pbStart_clicked()
{
    ui->pbStart->setEnabled(false);

    addMessageToLog("Запуск измерения.");
    // генератор сигала АЛСЕН
    alsenSignalGen sigGen;
    sigGen.Code1(bauerCode[ui->cmbCode1->currentIndex()]);
    sigGen.Code2(bauerCode[ui->cmbCode2->currentIndex()]);
    uint CountDuration = ui->spbDuration->value() * sigGen.SamplRate();

    addMessageToLog(QString("Сгенерирован сигнал длительностью %1 с. Количество отсчетов: %2 Код1: %3 Код2: %4")
                    .arg(ui->spbDuration->value())
                    .arg(CountDuration)
                    .arg(QString::number(bauerCode[ui->cmbCode1->currentIndex()],16))
                    .arg(QString::number(bauerCode[ui->cmbCode2->currentIndex()],16)));

    DigitalFilterNoFilter ViewFilter;
    DigitalFilterNoFilter WorkFilter;

    ALSENSignalDecoder    decoder;
    connect(&decoder,&ALSENSignalDecoder::onCodeDetect0,
            this, &DecoderTestMain::onCodeDetect0proc);
    connect(&decoder,&ALSENSignalDecoder::onCodeDetect90,
            this, &DecoderTestMain::onCodeDetect90proc);
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


    ALSENSignalIODevice device(ViewFilter,WorkFilter,decoder);

    device.Stopped(false);

    clearData();

    addMessageToLog("Запуск обработки");

    for(size_t i = 0; i < CountDuration; ++i)
    {
        double Sample = sigGen.genSample();
        FSamplesVec.push_back(Sample);
        device.writeRAWData(Sample);
    }

    addMessageToLog("Обработка закончена");

    ui->pbStart->setEnabled(true);

    makeAndShowCharts();
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

void DecoderTestMain::onCodeDetect0proc(const quint8 ACode0, const quint8 AGroup0)
{
    addMessageToLog(QString("Канал 0: код %1; базовый код %2").arg(QString::number(ACode0,16)).arg(QString::number(AGroup0,16)));
}

void DecoderTestMain::onCodeDetect90proc(const quint8 ACode90, const quint8 AGroup90)
{
    addMessageToLog(QString("Канал 90: код %1; базовый код %2").arg(QString::number(ACode90,16)).arg(QString::number(AGroup90,16)));
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
