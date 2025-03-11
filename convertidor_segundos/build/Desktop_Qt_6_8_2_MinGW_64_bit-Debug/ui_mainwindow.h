/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *info;
    QLabel *resultado;
    QPushButton *boton;
    QLineEdit *dato;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(400, 300);
        MainWindow->setAutoFillBackground(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        info = new QLabel(centralwidget);
        info->setObjectName("info");
        info->setGeometry(QRect(50, 40, 301, 31));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        info->setFont(font);
        info->setAlignment(Qt::AlignmentFlag::AlignCenter);
        resultado = new QLabel(centralwidget);
        resultado->setObjectName("resultado");
        resultado->setGeometry(QRect(10, 230, 381, 31));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        resultado->setFont(font1);
        resultado->setAlignment(Qt::AlignmentFlag::AlignCenter);
        boton = new QPushButton(centralwidget);
        boton->setObjectName("boton");
        boton->setGeometry(QRect(150, 160, 101, 31));
        dato = new QLineEdit(centralwidget);
        dato->setObjectName("dato");
        dato->setGeometry(QRect(90, 80, 211, 51));
        dato->setFont(font1);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Convertidor", nullptr));
        info->setText(QCoreApplication::translate("MainWindow", "Ingrese el tiempo (en segundos)", nullptr));
        resultado->setText(QString());
        boton->setText(QCoreApplication::translate("MainWindow", "Convertir", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
