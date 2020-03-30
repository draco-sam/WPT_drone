SOURCES += \
    lib_sam/chart/chart_sam.cpp \
    lib_sam/gui/PrincipalWindow.cpp \
    lib_sam/usb/UsbVirtualCom.cpp \
    main_gui.cpp

QT+=widgets
QT += charts
QT+=serialport

HEADERS += \
    lib_sam/chart/chart_sam.h \
    lib_sam/gui/PrincipalWindow.h \ \
    lib_sam/usb/UsbVirtualCom.h



FORMS += \
    lib_sam/gui/PrincipalWindow.ui
