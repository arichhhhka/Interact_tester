#include "regexengine.h"

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

    // Ищет совпадение
   for (const QRegularExpressionMatch& match : re.globalMatch(text)) {

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