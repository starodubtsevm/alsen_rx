/********************************************************************************
** Form generated from reading UI file 'ChartsViewFform.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARTSVIEWFFORM_H
#define UI_CHARTSVIEWFFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChartsViewForm
{
public:
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_2;
    QWidget *ChartsWidget;
    QGridLayout *gridLayout_3;
    QVBoxLayout *vlCharts;

    void setupUi(QWidget *ChartsViewForm)
    {
        if (ChartsViewForm->objectName().isEmpty())
            ChartsViewForm->setObjectName(QStringLiteral("ChartsViewForm"));
        ChartsViewForm->resize(1008, 603);
        gridLayout = new QGridLayout(ChartsViewForm);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        scrollArea = new QScrollArea(ChartsViewForm);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 988, 583));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(2, 2, 2, 2);
        ChartsWidget = new QWidget(scrollAreaWidgetContents);
        ChartsWidget->setObjectName(QStringLiteral("ChartsWidget"));
        gridLayout_3 = new QGridLayout(ChartsWidget);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(2, 2, 2, 2);
        vlCharts = new QVBoxLayout();
        vlCharts->setObjectName(QStringLiteral("vlCharts"));

        gridLayout_3->addLayout(vlCharts, 0, 0, 1, 1);


        gridLayout_2->addWidget(ChartsWidget, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 0, 0, 1, 1);


        retranslateUi(ChartsViewForm);

        QMetaObject::connectSlotsByName(ChartsViewForm);
    } // setupUi

    void retranslateUi(QWidget *ChartsViewForm)
    {
        ChartsViewForm->setWindowTitle(QApplication::translate("ChartsViewForm", "\320\223\321\200\320\260\321\204\320\270\320\272\320\270", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ChartsViewForm: public Ui_ChartsViewForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARTSVIEWFFORM_H
