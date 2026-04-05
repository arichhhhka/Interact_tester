#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStyleHints> // Для определения темы системы
#include <QFileDialog> // Для диалогов выбора файлов
#include <QMessageBox> // Для окон с сообщениями
#include <QRegularExpression> // Для работы с регулярными выражениями
#include <QTextStream> // Для работы с цветами

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Проверка настройки системы ( темная/светлая тема)
    bool isDarkTheme = false;

#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    QStyleHints *styleHints = qApp->styleHints();
    if (styleHints->colorScheme() == Qt::ColorScheme::Dark) {
        isDarkTheme = true;
    }
#endif

    // Применение стилей
    if (isDarkTheme) {
        // Для темной темы
        this->setStyleSheet("background-color: #2b2b2b;");
        ui->line_Regex->setStyleSheet("background-color: #3c3f41; color: white;");
        ui->text_Input->setStyleSheet("background-color: #3c3f41; color: white;");
        ui->text_Result->setStyleSheet("background-color: #3c3f41; color: white;");
        ui->btn_Check->setStyleSheet("background-color: #bb86fc; color: black;");
    } else {
        // Для светлой темы
        this->setStyleSheet("background-color: #fce4ec;");
        ui->line_Regex->setStyleSheet("background-color: #f5f5f5; color: black;");
        ui->text_Input->setStyleSheet("background-color: #f5f5f5; color: black;");
        ui->text_Result->setStyleSheet("background-color: #f5f5f5; color: black;");
        ui->btn_Check->setStyleSheet("background-color: #e0e0e0; color: black;");
    }

    ui->btn_Load->setStyleSheet(ui->btn_Check->styleSheet());
    ui->btn_Save->setStyleSheet(ui->btn_Check->styleSheet());
    ui->btn_Help->setStyleSheet(ui->btn_Check->styleSheet());
    ui->btn_Clear->setStyleSheet(ui->btn_Check->styleSheet());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_Check_clicked() // Слот для кнопки Проверить
{
    // Получает регулярное выражение и текст
    QString pattern = ui->line_Regex->toPlainText();
    QString text = ui->text_Input->toPlainText();

    // Проверяет, не пустое ли регулярное выражение
    if (pattern.isEmpty()) {
        ui->text_Result->setPlainText(" Введите регулярное выражение!");
        return;
    }

    // Создает объект регулярного выражения
    QRegularExpression re(pattern);

    // Проверяет ошибки в самом выражении
    if (!re.isValid()) {
        QString errorText = "Ошибка в регулярном выражении!\n\n";
        errorText += "Возможные причины:\n";
        errorText += " - незакрытая скобка или кавычка\n";
        errorText += " - неправильный спецсимвол\n";
        errorText += " - пустое выражение в скобках\n\n";
        errorText += "Техническая информация:\n" + re.errorString();

        ui->text_Result->setPlainText(errorText);
        return;
    }

    // Очищает старую подсветку в тексте
    ui->text_Input->setExtraSelections({});

    // Посик всех совпадений в тексте
    auto matchIterator = re.globalMatch(text);
    QList<QTextEdit::ExtraSelection> highlights;
    int count = 0;
    QString foundList;

    while (matchIterator.hasNext()) {
        auto match = matchIterator.next();
        int start = match.capturedStart();
        int length = match.capturedLength();

        // Создает выделение для найденного совпадения
        QTextEdit::ExtraSelection selection;
        selection.cursor = ui->text_Input->textCursor();
        selection.cursor.setPosition(start);
        selection.cursor.setPosition(start + length, QTextCursor::KeepAnchor);

        // Задает цвет подсветки
        selection.format.setBackground(QColor("#e0e0e0"));
        selection.format.setForeground(QColor("#000000"));
        selection.format.setFontWeight(QFont::Bold);

        highlights.append(selection);

        // Добавляет в список найденного
        foundList += QString("%1. \"%2\"\n")
                         .arg(++count)
                         .arg(match.captured());
    }

    // Применяет подсветку к полю ввода
    ui->text_Input->setExtraSelections(highlights);

    // 11. Выводим результат
    if (count == 0) {
        ui->text_Result->setPlainText("Совпадений не найдено.");
    } else {
        ui->text_Result->setPlainText(QString(" Найдено совпадений: %1\n\n%2")
                                          .arg(count)
                                          .arg(foundList));
    }
}



void MainWindow::on_btn_Save_clicked()
{
    // Открываем диалог сохранения файла
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Сохранить тест"), "", tr("Файлы тестов (*.test);;Все файлы (*)"));

    // Если пользователь не нажал "Отмена"
    if (!fileName.isEmpty()) {
        // 3. Создаем файл для записи
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            // 4. Пишем данные в файл
            QTextStream out(&file);
            out << ui->line_Regex->toPlainText() << "\n";     // 1 строка: регулярка
            out << ui->text_Input->toPlainText();       // 2 строка: текст

            file.close();

            ui->text_Result->setPlainText(" Тест сохранён в файл:\n" + fileName);
        } else {
            ui->text_Result->setPlainText(" Не удалось сохранить файл!");
        }
    }
}





void MainWindow::on_btn_Load_clicked()
{
    // 1. Открываем диалог выбора файла
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Загрузить файл"), "",
                                                    tr("Все файлы (*.txt *.test);;Текстовые файлы (*.txt);;Файлы тестов (*.test)"));

    // 2. Если файл выбран
    if (fileName.isEmpty()) {
        return;
    }

    // 3. Открываем файл
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->text_Result->setPlainText("Не удалось открыть файл!");
        return;
    }

    QTextStream in(&file);

    // 4. Определяем тип файла по расширению
    if (fileName.endsWith(".test")) {
        // Это файл ТЕСТА — загружаем регулярку и текст
        QString pattern = in.readLine();        // Первая строка — регулярка
        QString text = in.readAll();            // Остальное — текст

        ui->line_Regex->setPlainText(pattern);
        ui->text_Input->setPlainText(text);

        ui->text_Result->setPlainText("Загружен тест из файла:\n" + fileName);
        ui->text_Input->setExtraSelections({}); // Очищаем подсветку
    } else {
        // Это обычный ТЕКСТ — загружаем только текст
        QString text = in.readAll();

        ui->text_Input->setPlainText(text);

        ui->text_Result->setPlainText(" Загружен текст из файла:\n" + fileName);
    }

    file.close();
}


void MainWindow::on_btn_Help_clicked()
{
    QString helpText = " Инструкция:\n\n";
    helpText += " Вы можете: \n";
    helpText += " - загрузить готовый тестовый файл формата (*txt).\n";
    helpText += " - загрузить ранее сохраненный тестер для продолжения работы.\n";
    helpText += " - сохранить результат текущей работы\n\n";

    // Создаем окно сообщения
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle("Помощь");
    msgBox.setText(helpText);

    // ВАЖНО: Сбрасываем стили, чтобы фон был белым (стандартным),
    // а не наследовал розовый цвет от главного окна
    msgBox.setStyleSheet("QMessageBox { background-color: white; }"
                         "QMessageBox QLabel { color: black; font-size: 13px; }");

    msgBox.exec();
}


void MainWindow::on_btn_Clear_clicked()
{
    // 1. Очищаем поле регулярного выражения
    ui->line_Regex->clear();

    // 2. Очищаем поле ввода текста
    ui->text_Input->clear();

    // 3. Очищаем поле результатов
    ui->text_Result->clear();

    // 4. Удаляем подсветку (если была)
    ui->text_Input->setExtraSelections({});

    // 5. Пишем сообщение пользователю
    ui->text_Result->setPlainText(" Все поля очищены.");
}

