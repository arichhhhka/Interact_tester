#include "mainwindow.h"
#include <QApplication>

// Точка входа в программу
int main(int argc, char *argv[])
{
    // Создает приложение, передает аргументы командной строки
    QApplication a(argc, argv);

    // Создает и показывает главное окно
    MainWindow w;
    w.show();

    // Запускает программу (ожидание действий пользователя)
    return QCoreApplication::exec();
}