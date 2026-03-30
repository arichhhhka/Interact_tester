/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *btn_Check;
    QTextEdit *text_Input;
    QTextEdit *text_Result;
    QPlainTextEdit *line_Regex;
    QPushButton *btn_Save;
    QPushButton *btn_Load;
    QPushButton *btn_Help;
    QPushButton *btn_Clear;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1356, 861);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        btn_Check = new QPushButton(centralwidget);
        btn_Check->setObjectName("btn_Check");
        btn_Check->setGeometry(QRect(40, 350, 111, 41));
        text_Input = new QTextEdit(centralwidget);
        text_Input->setObjectName("text_Input");
        text_Input->setGeometry(QRect(10, 70, 821, 269));
        text_Result = new QTextEdit(centralwidget);
        text_Result->setObjectName("text_Result");
        text_Result->setGeometry(QRect(10, 420, 821, 151));
        text_Result->setReadOnly(false);
        line_Regex = new QPlainTextEdit(centralwidget);
        line_Regex->setObjectName("line_Regex");
        line_Regex->setGeometry(QRect(10, 10, 821, 41));
        btn_Save = new QPushButton(centralwidget);
        btn_Save->setObjectName("btn_Save");
        btn_Save->setGeometry(QRect(30, 580, 171, 41));
        btn_Load = new QPushButton(centralwidget);
        btn_Load->setObjectName("btn_Load");
        btn_Load->setGeometry(QRect(160, 350, 111, 41));
        btn_Help = new QPushButton(centralwidget);
        btn_Help->setObjectName("btn_Help");
        btn_Help->setGeometry(QRect(270, 350, 21, 31));
        btn_Clear = new QPushButton(centralwidget);
        btn_Clear->setObjectName("btn_Clear");
        btn_Clear->setGeometry(QRect(40, 630, 111, 41));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1356, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\230\320\275\321\202\320\265\321\200\320\260\320\272\321\202\320\270\320\262\320\275\321\213\320\271 \321\202\320\265\321\201\321\202\320\265\321\200 \321\200\320\265\320\263\321\203\320\273\321\217\321\200\320\275\321\213\320\271 \320\262\321\213\321\200\320\260\320\266\320\265\320\275\320\270\320\271", nullptr));
        btn_Check->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\262\320\265\321\200\320\270\321\202\321\214", nullptr));
        text_Input->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\202\320\265\320\272\321\201\321\202 \320\264\320\273\321\217 \320\277\321\200\320\276\320\262\320\265\321\200\320\272\320\270", nullptr));
        text_Result->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202", nullptr));
        line_Regex->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\200\320\265\320\263\321\203\320\273\321\217\321\200\320\275\320\276\320\265 \320\262\321\213\321\200\320\260\320\266\320\265\320\275\320\270\320\265...", nullptr));
        btn_Save->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202", nullptr));
        btn_Load->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214", nullptr));
        btn_Help->setText(QCoreApplication::translate("MainWindow", "?", nullptr));
        btn_Clear->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
