QT += widgets # Подключает модуль для кнопок и окон
CONFIG += c++17 # Для стандарта C++17

# Исходные файлы проекта
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    regexengine.cpp    #Класс обработки регулярных выражений

# Заголовочные файлы
HEADERS += \
    mainwindow.h \
    regexengine.h      # Объявление класса обработки регулярных выражений

# Файлы интерфейса (разметка окна)
FORMS += \
    mainwindow.ui
