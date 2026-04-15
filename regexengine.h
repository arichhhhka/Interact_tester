#ifndef REGEXENGINE_H
#define REGEXENGINE_H

#include <QString>
#include <QList>
#include <QRegularExpression> // Qt класс для регулярных выражений

// Структура для хранения данных одного найденного совпадения
struct RegexMatch {
    int start;          // Позиция начала совпадения в тексте
    int length;         // Длина символов
    QString text;       // Список совпадения
};

// Результат проверки регулярки
struct RegexResult {
    bool isValid;           // Флаг корректности регулярного выражения
    QString error;          // Текст ошибки, если она сеть
    QList<RegexMatch> matches; // Список всех найденных совпадений
};

// Класс для работы с регулярными выражениями
class RegexEngine
{
public:
    RegexEngine() = default; // Констуктор по умолчанию

    // Проверка корректности регулярного выражения
    bool isValid(const QString& pattern) const;

    // Текст ошибки при неправильном выражении
    QString getError(const QString& pattern) const;

    // Основной метод поиска совпадений в тексте
    RegexResult test(const QString& pattern, const QString& text);
};

#endif