#ifndef USBVIRTUALCOM_H
#define USBVIRTUALCOM_H

#include <QString>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>

class UsbVirtualCom
{
    public :
    UsbVirtualCom();
    ~UsbVirtualCom();

    private :
    QString                     m_serial_name;
    bool                        m_status_com_open;
    QList<QSerialPortInfo>      m_listPortCom;
    QSerialPortInfo             m_serialPortsInfo;
    QSerialPort                 m_pic_usb_com;

};

#endif // USBVIRTUALCOM_H
