#include "regexengine.h"

// Проверка корректности регулярного выражения
bool RegexEngine::isValid(const QString& pattern) const
{
    QRegularExpression re(pattern);
    return re.isValid();
}

// Получение ошибки
QString RegexEngine::getError(const QString& pattern) const
{
    QRegularExpression re(pattern);
    // Если выражение верное, возвращаем пустую строку, иначе - сообщение об ошибке
    if (re.isValid()) {
        return "";
    } else {
        return re.errorString();
    }
}

// Поиск всех совпадений регулярного выражения в тексте
RegexResult RegexEngine::test(const QString& pattern, const QString& text)
{
    RegexResult result;
    QRegularExpression re(pattern);

    // Проверяем, правильная ли регулярка
    result.isValid = re.isValid();
    result.error = re.errorString();

    // Если ошибка, дальше не ищем
    if (!result.isValid) {
        return result;
    }

    // Создаём "переборщик" — объект, который будет выдавать нам все найденные совпадения по одному
    QRegularExpressionMatchIterator it= re.globalMatch(text);
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();

        // Формируем структуру с данными о текущем совпадении
        RegexMatch m;
        m.start = match.capturedStart();
        m.length = match.capturedLength();
        m.text = match.captured();

        // Добавляем в итоговый список для передачи в интерфейс
        result.matches.append(m);
    }

    return result;
}