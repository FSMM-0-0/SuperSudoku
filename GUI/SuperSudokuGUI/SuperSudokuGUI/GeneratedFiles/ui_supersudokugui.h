/********************************************************************************
** Form generated from reading UI file 'supersudokugui.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUPERSUDOKUGUI_H
#define UI_SUPERSUDOKUGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SuperSudokuGUIClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SuperSudokuGUIClass)
    {
        if (SuperSudokuGUIClass->objectName().isEmpty())
            SuperSudokuGUIClass->setObjectName(QString::fromUtf8("SuperSudokuGUIClass"));
        SuperSudokuGUIClass->resize(600, 400);
        menuBar = new QMenuBar(SuperSudokuGUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        SuperSudokuGUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SuperSudokuGUIClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        SuperSudokuGUIClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(SuperSudokuGUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        SuperSudokuGUIClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(SuperSudokuGUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SuperSudokuGUIClass->setStatusBar(statusBar);

        retranslateUi(SuperSudokuGUIClass);

        QMetaObject::connectSlotsByName(SuperSudokuGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *SuperSudokuGUIClass)
    {
        SuperSudokuGUIClass->setWindowTitle(QApplication::translate("SuperSudokuGUIClass", "SuperSudokuGUI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SuperSudokuGUIClass: public Ui_SuperSudokuGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUPERSUDOKUGUI_H
