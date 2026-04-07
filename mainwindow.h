#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "regexengine.h" // Подключаем класс обработки регулярных выражений

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// Класс главного окна приложения
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    // Обработчики нажатий кнопок интерфейса
    void on_btn_Check_clicked();
    void on_btn_Load_clicked();
    void on_btn_Save_clicked();
    void on_btn_Help_clicked();
    void on_btn_Clear_clicked();

private:
    Ui::MainWindow *ui;        // Указатель на сгенерированный класс интерфейса
    RegexEngine m_regexEngine; // Экземпляр движка для обработки регулярных выражений
};

#endif