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

    // Определение темы оформления системы (светлая или темная)
    bool isDarkTheme = false;
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    QStyleHints *styleHints = qApp->styleHints();
    if (styleHints->colorScheme() == Qt::ColorScheme::Dark) {
        isDarkTheme = true;
    }
#endif

    // Применение цветовой схемы в зависимости от темы системы
    if (isDarkTheme) {
        // Настройки для темной темы
        this->setStyleSheet("background-color: #2b2b2b;");
        ui->line_Regex->setStyleSheet("background-color: #3c3f41; color: white;");
        ui->text_Input->setStyleSheet("background-color: #3c3f41; color: white;");
        ui->text_Result->setStyleSheet("background-color: #3c3f41; color: white;");
        ui->btn_Check->setStyleSheet("background-color: #bb86fc; color: black;");
    } else {
        // Настройки для светлой темы
        this->setStyleSheet("background-color: #fce4ec;");
        ui->line_Regex->setStyleSheet("background-color: #f5f5f5; color: black;");
        ui->text_Input->setStyleSheet("background-color: #f5f5f5; color: black;");
        ui->text_Result->setStyleSheet("background-color: #f5f5f5; color: black;");
        ui->btn_Check->setStyleSheet("background-color: #e0e0e0; color: black;");
    }

    // Применяем стиль кнопки проверки ко всем остальным кнопкам для единообразия
    ui->btn_Load->setStyleSheet(ui->btn_Check->styleSheet());
    ui->btn_Save->setStyleSheet(ui->btn_Check->styleSheet());
    ui->btn_Help->setStyleSheet(ui->btn_Check->styleSheet());
    ui->btn_Clear->setStyleSheet(ui->btn_Check->styleSheet());
}

// Деструктор окна
MainWindow::~MainWindow()
{
    delete ui;
}

// Обработчик нажатия кнопки "Проверить"
void MainWindow::on_btn_Check_clicked()
{
    QString pattern = ui->line_Regex->toPlainText();
    QString text = ui->text_Input->toPlainText();

    // Проверка на пустое регулярное выражение
    if (pattern.isEmpty()) {
        ui->text_Result->setPlainText("Введите регулярное выражение!");
        return;
    }

    // Вызов метода поиска из вынесенного класса RegexEngine
    RegexResult result = m_regexEngine.test(pattern, text);

    // Обработка синтаксических ошибок регулярного выражения
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

    // Перебор найденных совпадений с помощью цикла for
    // Данные уже собраны в список result.matches, поэтому используем стандартный перебор
    for (const auto& match : result.matches) {
        QTextEdit::ExtraSelection selection;
        selection.cursor = ui->text_Input->textCursor();
        selection.cursor.setPosition(match.start);
        // Выделяем найденный фрагмент текста
        selection.cursor.setPosition(match.start + match.length, QTextCursor::KeepAnchor);

        // Настройка визуального оформления выделения
        selection.format.setBackground(QColor("#e0e0e0"));
        selection.format.setForeground(QColor("#000000"));
        selection.format.setFontWeight(QFont::Bold);
        highlights.append(selection);

        // Формируем строку со списком найденных значений
        foundList += QString("%1. \"%2\"\n").arg(++count).arg(match.text);
    }

    // Применяем выделения к текстовому полю
    ui->text_Input->setExtraSelections(highlights);

    // Вывод результата поиска
    if (count == 0) {
        ui->text_Result->setPlainText("Совпадений не найдено.");
    } else {
        ui->text_Result->setPlainText(QString("Найдено совпадений: %1\n%2")
                                          .arg(count).arg(foundList));
    }
}

// Обработчик нажатия кнопки "Сохранить"
void MainWindow::on_btn_Save_clicked()
{
    // Открытие диалога выбора пути для сохранения файла
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить тест"), "", tr("Файлы тестов (*.test);;Все файлы (*)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        // Открываем файл в режиме записи
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            // Записываем регулярное выражение в первую строку
            out << ui->line_Regex->toPlainText() << "\n";
            // Записываем тестируемый текст
            out << ui->text_Input->toPlainText();
            file.close();
            ui->text_Result->setPlainText("Тест сохранён в файл:\n" + fileName);
        } else {
            ui->text_Result->setPlainText("Не удалось сохранить файл!");
        }
    }
}

// Обработчик нажатия кнопки "Загрузить"
void MainWindow::on_btn_Load_clicked()
{
    // Открытие диалога выбора файла
    QString fileName = QFileDialog::getOpenFileName(this, tr("Загрузить файл"), "", tr("Все файлы (*.txt *.test);;Текстовые файлы (*.txt);;Файлы тестов (*.test)"));
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    // Проверка успешности открытия файла
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->text_Result->setPlainText("Не удалось открыть файл!");
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

// Обработчик нажатия кнопки "Помощь"
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
    msgBox.setStyleSheet("QMessageBox { background-color: white; }"
                         "QMessageBox QLabel { color: black; font-size: 13px; }");
    msgBox.exec();
}

// Обработчик нажатия кнопки "Очистить"
void MainWindow::on_btn_Clear_clicked()
{
    ui->line_Regex->clear();
    ui->text_Input->clear();
    ui->text_Result->clear();
    // Убираем подсветку совпадений
    ui->text_Input->setExtraSelections({});
    ui->text_Result->setPlainText("Все поля очищены.");
}