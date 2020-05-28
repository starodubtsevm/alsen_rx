/********************************************************************************
** Form generated from reading UI file 'chartViewDinamicForm.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARTVIEWDINAMICFORM_H
#define UI_CHARTVIEWDINAMICFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChartViewDinamicForm
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *vlMain;

    void setupUi(QWidget *ChartViewDinamicForm)
    {
        if (ChartViewDinamicForm->objectName().isEmpty())
            ChartViewDinamicForm->setObjectName(QStringLiteral("ChartViewDinamicForm"));
        ChartViewDinamicForm->resize(1232, 267);
        gridLayout = new QGridLayout(ChartViewDinamicForm);
        gridLayout->setSpacing(2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(1, 1, 1, 1);
        vlMain = new QVBoxLayout();
        vlMain->setSpacing(1);
        vlMain->setObjectName(QStringLiteral("vlMain"));

        gridLayout->addLayout(vlMain, 0, 0, 1, 1);


        retranslateUi(ChartViewDinamicForm);

        QMetaObject::connectSlotsByName(ChartViewDinamicForm);
    } // setupUi

    void retranslateUi(QWidget *ChartViewDinamicForm)
    {
        ChartViewDinamicForm->setWindowTitle(QApplication::translate("ChartViewDinamicForm", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ChartViewDinamicForm: public Ui_ChartViewDinamicForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARTVIEWDINAMICFORM_H
