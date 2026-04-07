#include "regexengine.h"

// Проверка корректности синтаксиса регулярного выражения
bool RegexEngine::isValid(const QString& pattern) const
{
    return QRegularExpression(pattern).isValid();
}

// Получение описания ошибки синтаксиса
QString RegexEngine::getError(const QString& pattern) const
{
    QRegularExpression re(pattern);
    // Если выражение верное, возвращаем пустую строку, иначе - сообщение об ошибке
    return re.isValid() ? QString() : re.errorString();
}

// Поиск всех совпадений регулярного выражения в переданном тексте
RegexResult RegexEngine::test(const QString& pattern, const QString& text)
{
    RegexResult result;
    QRegularExpression re(pattern);

    // Первичная проверка валидности выражения
    result.isValid = re.isValid();
    result.error = re.errorString();

    // Если синтаксис неверный, дальнейший поиск не имеет смысла
    if (!result.isValid) {
        return result;
    }

    // Поиск совпадений с помощью итератора Qt
    // Итератор используется внутри движка для эффективного перебора без лишней нагрузки на память
    auto matchIterator = re.globalMatch(text);
    while (matchIterator.hasNext()) {
        auto match = matchIterator.next();

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