/********************************************************************************
** Form generated from reading UI file 'decodertestmain.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DECODERTESTMAIN_H
#define UI_DECODERTESTMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DecoderTestMain
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QPushButton *pbStopRecord;
    QLabel *label_4;
    QSpinBox *spbAmplitude;
    QSpinBox *spbSections;
    QPushButton *pbStart;
    QDoubleSpinBox *dspbCarFreq;
    QPushButton *pbLogClear;
    QLabel *lDuration;
    QCheckBox *cbShowCharts;
    QSpinBox *spbDuration;
    QTextEdit *teLog;
    QComboBox *cmbCode90;
    QLabel *lcmbCode90;
    QComboBox *cmbCode0;
    QLabel *lcmbCode0;
    QComboBox *cmbAudioInputList;
    QCheckBox *cbUseAudioInput;

    void setupUi(QMainWindow *DecoderTestMain)
    {
        if (DecoderTestMain->objectName().isEmpty())
            DecoderTestMain->setObjectName(QStringLiteral("DecoderTestMain"));
        DecoderTestMain->resize(800, 600);
        centralwidget = new QWidget(DecoderTestMain);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pbStopRecord = new QPushButton(centralwidget);
        pbStopRecord->setObjectName(QStringLiteral("pbStopRecord"));

        gridLayout->addWidget(pbStopRecord, 0, 1, 1, 1);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 6, 1, 1);

        spbAmplitude = new QSpinBox(centralwidget);
        spbAmplitude->setObjectName(QStringLiteral("spbAmplitude"));
        spbAmplitude->setValue(1);

        gridLayout->addWidget(spbAmplitude, 0, 2, 1, 1);

        spbSections = new QSpinBox(centralwidget);
        spbSections->setObjectName(QStringLiteral("spbSections"));
        spbSections->setMinimum(1);
        spbSections->setValue(5);

        gridLayout->addWidget(spbSections, 1, 7, 1, 1);

        pbStart = new QPushButton(centralwidget);
        pbStart->setObjectName(QStringLiteral("pbStart"));

        gridLayout->addWidget(pbStart, 0, 0, 1, 1);

        dspbCarFreq = new QDoubleSpinBox(centralwidget);
        dspbCarFreq->setObjectName(QStringLiteral("dspbCarFreq"));
        dspbCarFreq->setMaximum(250);
        dspbCarFreq->setValue(174.89);

        gridLayout->addWidget(dspbCarFreq, 0, 3, 1, 1);

        pbLogClear = new QPushButton(centralwidget);
        pbLogClear->setObjectName(QStringLiteral("pbLogClear"));

        gridLayout->addWidget(pbLogClear, 7, 0, 1, 8);

        lDuration = new QLabel(centralwidget);
        lDuration->setObjectName(QStringLiteral("lDuration"));

        gridLayout->addWidget(lDuration, 0, 4, 1, 1);

        cbShowCharts = new QCheckBox(centralwidget);
        cbShowCharts->setObjectName(QStringLiteral("cbShowCharts"));
        cbShowCharts->setChecked(true);

        gridLayout->addWidget(cbShowCharts, 0, 7, 1, 1);

        spbDuration = new QSpinBox(centralwidget);
        spbDuration->setObjectName(QStringLiteral("spbDuration"));
        spbDuration->setMinimum(1);
        spbDuration->setValue(5);

        gridLayout->addWidget(spbDuration, 0, 5, 1, 1);

        teLog = new QTextEdit(centralwidget);
        teLog->setObjectName(QStringLiteral("teLog"));
        QFont font;
        font.setFamily(QStringLiteral("Courier New"));
        teLog->setFont(font);

        gridLayout->addWidget(teLog, 6, 0, 1, 8);

        cmbCode90 = new QComboBox(centralwidget);
        cmbCode90->setObjectName(QStringLiteral("cmbCode90"));

        gridLayout->addWidget(cmbCode90, 1, 5, 1, 1);

        lcmbCode90 = new QLabel(centralwidget);
        lcmbCode90->setObjectName(QStringLiteral("lcmbCode90"));
        lcmbCode90->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(lcmbCode90, 1, 4, 1, 1);

        cmbCode0 = new QComboBox(centralwidget);
        cmbCode0->setObjectName(QStringLiteral("cmbCode0"));

        gridLayout->addWidget(cmbCode0, 1, 3, 1, 1);

        lcmbCode0 = new QLabel(centralwidget);
        lcmbCode0->setObjectName(QStringLiteral("lcmbCode0"));
        lcmbCode0->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(lcmbCode0, 1, 2, 1, 1);

        cmbAudioInputList = new QComboBox(centralwidget);
        cmbAudioInputList->setObjectName(QStringLiteral("cmbAudioInputList"));

        gridLayout->addWidget(cmbAudioInputList, 1, 1, 1, 1);

        cbUseAudioInput = new QCheckBox(centralwidget);
        cbUseAudioInput->setObjectName(QStringLiteral("cbUseAudioInput"));

        gridLayout->addWidget(cbUseAudioInput, 1, 0, 1, 1);

        DecoderTestMain->setCentralWidget(centralwidget);

        retranslateUi(DecoderTestMain);

        cmbCode90->setCurrentIndex(2);
        cmbCode0->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(DecoderTestMain);
    } // setupUi

    void retranslateUi(QMainWindow *DecoderTestMain)
    {
        DecoderTestMain->setWindowTitle(QApplication::translate("DecoderTestMain", "DecoderTestMain", Q_NULLPTR));
        pbStopRecord->setText(QApplication::translate("DecoderTestMain", "\320\236\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214", Q_NULLPTR));
        label_4->setText(QApplication::translate("DecoderTestMain", "spbSections", Q_NULLPTR));
        pbStart->setText(QApplication::translate("DecoderTestMain", "\320\227\320\260\320\277\321\203\321\201\321\202\320\270\321\202\321\214", Q_NULLPTR));
        pbLogClear->setText(QApplication::translate("DecoderTestMain", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \320\273\320\276\320\263", Q_NULLPTR));
        lDuration->setText(QApplication::translate("DecoderTestMain", "\320\224\320\273\320\270\321\202\320\265\320\273\321\214\320\275\320\276\321\201\321\202\321\214:", Q_NULLPTR));
        cbShowCharts->setText(QApplication::translate("DecoderTestMain", "cbShowCharts", Q_NULLPTR));
        cmbCode90->clear();
        cmbCode90->insertItems(0, QStringList()
         << QApplication::translate("DecoderTestMain", "0x01", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0x1F", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0x2C", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0x32", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0x4A", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0x54", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0x67", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0x79", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0x86", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0x98", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0xAB", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0xB5", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0xCD", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0xD3", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0xE0", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0xFE", Q_NULLPTR)
        );
        lcmbCode90->setText(QApplication::translate("DecoderTestMain", "Code90:", Q_NULLPTR));
        cmbCode0->clear();
        cmbCode0->insertItems(0, QStringList()
         << QApplication::translate("DecoderTestMain", "0x01", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0x1F", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0x2C", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0x32", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0x4A", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0x54", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0x67", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0x79", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0x86", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0x98", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0xAB", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0xB5", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0xCD", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0xD3", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0xE0", Q_NULLPTR)
         << QApplication::translate("DecoderTestMain", "0xFE", Q_NULLPTR)
        );
        lcmbCode0->setText(QApplication::translate("DecoderTestMain", "Code0:", Q_NULLPTR));
        cbUseAudioInput->setText(QApplication::translate("DecoderTestMain", "cbUseAudioInput", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DecoderTestMain: public Ui_DecoderTestMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DECODERTESTMAIN_H
