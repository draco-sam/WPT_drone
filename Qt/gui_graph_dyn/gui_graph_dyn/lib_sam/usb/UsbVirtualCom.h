/***************************************************************************************************
 * File name        : UsbVirtualCom.h
 * Date             : 30/03/2020
 * Author           : Samuel LORENZINO.
 *
 * Links            :
 *
 * Comments         :
 **************************************************************************************************/
#ifndef USBVIRTUALCOM_H
#define USBVIRTUALCOM_H

#include <QString>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>

#define M_TM_VBAT "\r\n3\r\n"
#define M_TM_IBAT "\r\n4\r\n"

class UsbVirtualCom
//class UsbVirtualCom
{
    public :

    UsbVirtualCom();
    ~UsbVirtualCom();
    void send_enter();
    void send_qt_mode_activation();
    void send_tm_request(QString usb_string);
    void tm_strings_to_double(QString tm_i2c_str,double *tm_data_float,double *tm_time_float);
    void get_tm_i2c_float(double *tm_t,double *tm_v);

    private :

    QString                     m_serial_name;
    bool                        m_status_com_open;
    QList<QSerialPortInfo>      m_listPortCom;
    QSerialPortInfo             m_serialPortsInfo;
    QSerialPort                 m_pic_usb_com;
    QString                     m_tm_i2c_str;
    QString                     m_com_name;
    double                      m_tm_v_double;
    double                      m_tm_time_double;
    //QString                     M_TM_VBAT;
    //QString                     M_TM_IBAT;
    //QString                     M_TM_VIN;
};

#endif // USBVIRTUALCOM_H
