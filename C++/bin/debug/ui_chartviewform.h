/********************************************************************************
** Form generated from reading UI file 'chartviewform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARTVIEWFORM_H
#define UI_CHARTVIEWFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChartViewForm
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hlChart;

    void setupUi(QWidget *ChartViewForm)
    {
        if (ChartViewForm->objectName().isEmpty())
            ChartViewForm->setObjectName(QStringLiteral("ChartViewForm"));
        ChartViewForm->resize(1019, 250);
        ChartViewForm->setMinimumSize(QSize(0, 250));
        gridLayout = new QGridLayout(ChartViewForm);
        gridLayout->setSpacing(1);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(1, 1, 1, 1);
        hlChart = new QHBoxLayout();
        hlChart->setSpacing(1);
        hlChart->setObjectName(QStringLiteral("hlChart"));

        gridLayout->addLayout(hlChart, 0, 0, 1, 1);


        retranslateUi(ChartViewForm);

        QMetaObject::connectSlotsByName(ChartViewForm);
    } // setupUi

    void retranslateUi(QWidget *ChartViewForm)
    {
        ChartViewForm->setWindowTitle(QApplication::translate("ChartViewForm", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ChartViewForm: public Ui_ChartViewForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARTVIEWFORM_H
