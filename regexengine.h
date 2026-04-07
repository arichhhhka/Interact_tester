#ifndef REGEXENGINE_H
#define REGEXENGINE_H

#include <QString>
#include <QList>
#include <QRegularExpression>

// Структура для хранения данных одного найденного совпадения
struct RegexMatch {
    int start;          // Позиция начала совпадения в тексте
    int length;         // Длина найденного фрагмента
    QString text;       // Сам найденный текст
};

// Структура полного результата проверки выражения
struct RegexResult {
    bool isValid;           // Флаг корректности синтаксиса регулярного выражения
    QString error;          // Текст ошибки, если выражение невалидно
    QList<RegexMatch> matches; // Список всех найденных совпадений
};

// Отдельный класс для работы с регулярными выражениями
// Вынесен из главного окна для разделения логики и интерфейса
class RegexEngine
{
public:
    RegexEngine() = default;

    // Проверка синтаксической корректности регулярного выражения
    bool isValid(const QString& pattern) const;

    // Возврат текста ошибки при невалидном выражении
    QString getError(const QString& pattern) const;

    // Основной метод поиска совпадений в тексте
    RegexResult test(const QString& pattern, const QString& text);
};

#endif // REGEXENGINE_H