TARGET = Calculator
TEMPLATE = app
QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += include/
VPATH += src/

SOURCES += \
    src/creditcalc.cpp \
    src/deposcalc.cpp \
    src/main.cpp \
    src/calculator.cpp \
    src/qcustomplot.cpp \
    src/s21_credit_calc.c \
    src/s21_depos_calc.c \
    src/s21_smart_calc.c \
    src/withreplsfield.cpp

HEADERS += \
    include/calculator.h \
    include/creditcalc.h \
    include/deposcalc.h \
    include/qcustomplot.h \
    include/s21_credit_calc.h \
    include/s21_depos_calc.h \
    include/s21_smart_calc.h \
    include/withreplsfield.h

FORMS += \
    ui/calculator.ui \
    ui/creditcalc.ui \
    ui/deposcalc.ui \
    ui/withreplsfield.ui

ICON = resource/newIcon.icns

# Default rules for deployment.
qnx: target.path = ${HOME}/$${TARGET}/
else: unix:!android: target.path = /${HOME}/$${TARGET}/
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc \
