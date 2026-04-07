# Подключаем модуль виджетов Qt для построения графического интерфейса
QT += widgets

# Указываем стандарт C++17 для использования современного синтаксиса
CONFIG += c++17

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

# Настройки путей установки для разных ОС (стандартный шаблон Qt)
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target