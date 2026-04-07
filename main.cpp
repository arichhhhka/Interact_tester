#include "mainwindow.h"
#include <QApplication>

// Точка входа в программу
int main(int argc, char *argv[])
{
    // Создаем объект приложения Qt, передаем аргументы командной строки
    QApplication a(argc, argv);

    // Создаем и показываем главное окно
    MainWindow w;
    w.show();

    // Запускаем главный цикл обработки событий (ожидание действий пользователя)
    return QCoreApplication::exec();
}