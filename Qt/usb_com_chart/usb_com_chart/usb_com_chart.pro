SOURCES += \
    Chart_sam.cpp \
    UsbVirtualCom.cpp \
    main_usb_com_chart.cpp

QT+=widgets

QT+=serialport

QT += charts
QT += testlib

HEADERS += \
    Chart_sam.h \
    UsbVirtualCom.h
