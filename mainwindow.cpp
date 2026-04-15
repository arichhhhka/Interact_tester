#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStyleHints>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

// Конструктор главного окна
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setStyleSheet("background-color: #fce4ec;");
    ui->line_Regex->setStyleSheet("background-color: #f5f5f5; color: black;");
    ui->text_Input->setStyleSheet("background-color: #f5f5f5; color: black;");
    ui->text_Result->setStyleSheet("background-color: #f5f5f5; color: black;");
    ui->btn_Check->setStyleSheet("background-color: #e0e0e0; color: black;");

    // Одикнаковый стиль для всех остальных кнопок
    ui->btn_Load->setStyleSheet(ui->btn_Check->styleSheet());
    ui->btn_Save->setStyleSheet(ui->btn_Check->styleSheet());
    ui->btn_Help->setStyleSheet(ui->btn_Check->styleSheet());
    ui->btn_Clear->setStyleSheet(ui->btn_Check->styleSheet());
}

// Деструктор окна (чистим память)
MainWindow::~MainWindow()
{
    delete ui;
}

// Обработка нажатия кнопки "Проверить"
void MainWindow::on_btn_Check_clicked()
{
    QString pattern = ui->line_Regex->toPlainText();
    QString text = ui->text_Input->toPlainText();

    // Проверка на пустое регулярное выражение
    if (pattern.isEmpty()) {
        ui->text_Result->setPlainText("Введите регулярное выражение");
        return;
    }

    // Вызов метода поиска RegexEngine
    RegexResult result = regex.test(pattern, text);

    // Обработка ошибок регулярного выражения
    if (!result.isValid) {
        QString errorText = "Ошибка в регулярном выражении!\n";
        errorText += "Возможные причины:\n";
        errorText += " - незакрытая скобка или кавычка\n";
        errorText += " - неправильный спецсимвол\n";
        errorText += "Техническая информация:\n" + result.error;
        ui->text_Result->setPlainText(errorText);
        return;
    }

    // Сброс предыдущей подсветки текста
    ui->text_Input->setExtraSelections({});
    QList<QTextEdit::ExtraSelection> highlights;
    int count = 0;
    QString foundList;

    // Проходим по всем найденным совпадениям
    for (int i = 0; i < result.matches.size(); ++i) {
        // Берём одно совпадение
        RegexMatch match = result.matches[i];

        // Настраиваем подсветку в тексте
        QTextEdit::ExtraSelection selection;
        selection.cursor = ui->text_Input->textCursor();
        selection.cursor.setPosition(match.start);
        selection.cursor.setPosition(match.start + match.length, QTextCursor::KeepAnchor);

        // Цвет подсветки
        selection.format.setBackground(QColor("#e0e0e0"));
        selection.format.setForeground(QColor("#000000"));
        selection.format.setFontWeight(QFont::Bold);
        highlights.append(selection);

        // Формируем строку со списком найденных значений
        foundList += QString("%1. \"%2\"\n").arg(++count).arg(match.text);
    }

    // Применяем подсветку
    ui->text_Input->setExtraSelections(highlights);

    // Вывод результата
    if (count == 0) {
        ui->text_Result->setPlainText("Совпадений не найдено");
    } else {
        ui->text_Result->setPlainText(QString("Найдено совпадений: %1\n%2")
                                          .arg(count).arg(foundList));
    }
}

// Обработка нажатия кнопки "Сохранить"
void MainWindow::on_btn_Save_clicked()
{
    // Открытие диалога выбора пути для сохранения файла
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить тест"), "", tr("Файлы тестов (*.test);;Все файлы (*)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        // Открывает файл в режиме записи
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << ui->line_Regex->toPlainText() << "\n";// Записывает регулярное выражение в первую строку
            out << ui->text_Input->toPlainText(); // Записывает тестируемый текст
            file.close();
            ui->text_Result->setPlainText("Тест сохранён в файл:\n" + fileName);
        } else {
            ui->text_Result->setPlainText("Не удалось сохранить файл");
        }
    }
}

// Обработка нажатия кнопки "Загрузить"
void MainWindow::on_btn_Load_clicked()
{
    // Открытие диалога выбора файла
    QString fileName = QFileDialog::getOpenFileName(this, tr("Загрузить файл"), "", tr("Все файлы (*.txt *.test);;Текстовые файлы (*.txt);;Файлы тестов (*.test)"));
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    // Проверка успешности открытия файла
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->text_Result->setPlainText("Не удалось открыть файл");
        return;
    }

    QTextStream in(&file);
    // Разная логика загрузки в зависимости от расширения файла
    if (fileName.endsWith(".test")) {
        // Для файлов теста: первая строка - регулярка, остальное - текст
        QString pattern = in.readLine();
        QString text = in.readAll();
        ui->line_Regex->setPlainText(pattern);
        ui->text_Input->setPlainText(text);
        ui->text_Result->setPlainText("Загружен тест из файла:\n" + fileName);
        ui->text_Input->setExtraSelections({});
    } else {
        // Для обычных текстовых файлов загружаем только текст
        QString text = in.readAll();
        ui->text_Input->setPlainText(text);
        ui->text_Result->setPlainText("Загружен текст из файла:\n" + fileName);
    }
    file.close();
}

// Обработка нажатия кнопки "Помощь"
void MainWindow::on_btn_Help_clicked()
{
    QString helpText = "Инструкция:\n";
    helpText += "Вы можете:\n";
    helpText += " - загрузить готовый тестовый файл формата (*.test)\n";
    helpText += " - загрузить обычный текстовый файл (*.txt) для поиска\n";
    helpText += " - сохранить результат текущей работы\n";

    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle("Помощь");
    msgBox.setText(helpText);
    // Принудительно задаем белый фон для окна справки, чтобы не наследовался цвет главного окна
    msgBox.setStyleSheet("QMessageBox { background-color: white; }");
    msgBox.exec();
}

// Обработка нажатия кнопки "Очистить"
void MainWindow::on_btn_Clear_clicked()
{
    ui->line_Regex->clear();
    ui->text_Input->clear();
    ui->text_Result->clear();
    // Убираем подсветку совпадений
    ui->text_Input->setExtraSelections({});
    ui->text_Result->setPlainText("Все поля очищены");
}