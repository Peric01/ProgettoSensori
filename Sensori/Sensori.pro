QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += charts

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    SensorRepository.cpp \
    SensorViewer.cpp \
    SimulationManager.cpp \
    main.cpp \
    phsensor.cpp \
    sensor.cpp \
    sensorcreator.cpp \
    tempsensor.cpp \
    turbsensor.cpp

HEADERS += \
    SensorRepository.h \
    SensorViewer.h \
    SimulationManager.h \
    phsensor.h \
    sensor.h \
    sensorcreator.h \
    tempsensor.h \
    turbsensor.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
