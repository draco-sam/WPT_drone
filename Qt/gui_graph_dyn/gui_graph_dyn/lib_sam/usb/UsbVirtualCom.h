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

#define TM_VBAT                 "\r\n3\r\n"
#define TM_IBAT                 "\r\n4\r\n"
#define TM_STATE                "\r\n5\r\n"
#define TM_VBAT_MULTIPLE        "\r\n9\r\n"//Vbat,t_vbat,Ibat,t_ibat,status,state,T°_NTC,T°_die.
#define TC_START_STOP_CHARGE    "\r\n11\r\n"


class UsbVirtualCom
//class UsbVirtualCom
{
    public :

    UsbVirtualCom();
    ~UsbVirtualCom();
    void send_enter();
    void send_qt_mode_activation();
    //void send_tm_request(QString usb_string);
    QString send_tm_request(QString usb_string);
    void send_tm(QString usb_string);
    void send_tc(QString usb_string);
    void tm_strings_to_double(QString tm_i2c_str,double *tm_data_float,double *tm_time_float);
    void get_tm_i2c_float(double *tm_t,double *tm_v);
    void get_tm_strings(QString *str_0,QString *str_1,QString *str_2,QString *str_3,
                        QString *str_4,QString *str_5);

    private :

    QString                     m_serial_name;
    bool                        m_status_com_open;
    QList<QSerialPortInfo>      m_listPortCom;
    QSerialPortInfo             m_serialPortsInfo;
    QSerialPort                 m_pic_usb_com;
    QString                     m_tm_i2c_str;
    QString                     m_com_name;
    QString                     m_str_tm_0;
    QString                     m_str_tm_1;
    QString                     m_str_tm_2;
    QString                     m_str_tm_3;
    QString                     m_str_tm_4;
    QString                     m_str_tm_5;
    double                      m_tm_v_double;
    double                      m_tm_time_double;
};

#endif // USBVIRTUALCOM_H
