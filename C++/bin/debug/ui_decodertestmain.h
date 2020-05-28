/********************************************************************************
** Form generated from reading UI file 'decodertestmain.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DECODERTESTMAIN_H
#define UI_DECODERTESTMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DecoderTestMain
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTextEdit *teLog;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbLogClear;
    QHBoxLayout *horizontalLayout;
    QPushButton *pbStart;
    QLabel *label;
    QSpinBox *spbDuration;
    QLabel *label_2;
    QComboBox *cmbCode1;
    QLabel *label_3;
    QComboBox *cmbCode2;
    QLabel *label_4;
    QSpinBox *spbSections;

    void setupUi(QMainWindow *DecoderTestMain)
    {
        if (DecoderTestMain->objectName().isEmpty())
            DecoderTestMain->setObjectName(QStringLiteral("DecoderTestMain"));
        DecoderTestMain->resize(800, 600);
        centralwidget = new QWidget(DecoderTestMain);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        teLog = new QTextEdit(centralwidget);
        teLog->setObjectName(QStringLiteral("teLog"));

        gridLayout->addWidget(teLog, 1, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(665, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        pbLogClear = new QPushButton(centralwidget);
        pbLogClear->setObjectName(QStringLiteral("pbLogClear"));

        gridLayout->addWidget(pbLogClear, 2, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pbStart = new QPushButton(centralwidget);
        pbStart->setObjectName(QStringLiteral("pbStart"));

        horizontalLayout->addWidget(pbStart);

        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        spbDuration = new QSpinBox(centralwidget);
        spbDuration->setObjectName(QStringLiteral("spbDuration"));
        spbDuration->setMinimum(1);
        spbDuration->setValue(3);

        horizontalLayout->addWidget(spbDuration);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        cmbCode1 = new QComboBox(centralwidget);
        cmbCode1->setObjectName(QStringLiteral("cmbCode1"));

        horizontalLayout->addWidget(cmbCode1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        cmbCode2 = new QComboBox(centralwidget);
        cmbCode2->setObjectName(QStringLiteral("cmbCode2"));

        horizontalLayout->addWidget(cmbCode2);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);

        spbSections = new QSpinBox(centralwidget);
        spbSections->setObjectName(QStringLiteral("spbSections"));
        spbSections->setMinimum(1);
        spbSections->setValue(5);

        horizontalLayout->addWidget(spbSections);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 3);

        DecoderTestMain->setCentralWidget(centralwidget);

        retranslateUi(DecoderTestMain);

        cmbCode1->setCurrentIndex(2);
        cmbCode2->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(DecoderTestMain);
    } // setupUi

    void retranslateUi(QMainWindow *DecoderTestMain)
    {
        DecoderTestMain->setWindowTitle(QApplication::translate("DecoderTestMain", "DecoderTestMain", Q_NULLPTR));
        pbLogClear->setText(QApplication::translate("DecoderTestMain", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \320\273\320\276\320\263", Q_NULLPTR));
        pbStart->setText(QApplication::translate("DecoderTestMain", "\320\227\320\260\320\277\321\203\321\201\321\202\320\270\321\202\321\214", Q_NULLPTR));
        label->setText(QApplication::translate("DecoderTestMain", "\320\224\320\273\320\270\321\202\320\265\320\273\321\214\320\275\320\276\321\201\321\202\321\214", Q_NULLPTR));
        label_2->setText(QApplication::translate("DecoderTestMain", "Code1", Q_NULLPTR));
        cmbCode1->clear();
        cmbCode1->insertItems(0, QStringList()
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
        label_3->setText(QApplication::translate("DecoderTestMain", "Code2", Q_NULLPTR));
        cmbCode2->clear();
        cmbCode2->insertItems(0, QStringList()
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
        label_4->setText(QApplication::translate("DecoderTestMain", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DecoderTestMain: public Ui_DecoderTestMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DECODERTESTMAIN_H
