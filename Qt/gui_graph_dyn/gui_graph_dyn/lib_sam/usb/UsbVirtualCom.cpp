/***************************************************************************************************
 * File name        : UsbVirtualCom.cpp
 * Date             : 30/03/2020
 * Author           : Samuel LORENZINO.
 *
 * Links            :
 *
 * Comments         :
 **************************************************************************************************/
#include "UsbVirtualCom.h"

UsbVirtualCom::UsbVirtualCom() :
    m_serial_name(""),m_status_com_open(false),m_tm_i2c_str(""),m_com_name("COM4"),
    m_str_tm_0(""),m_str_tm_1(""),m_str_tm_2(""),m_str_tm_3(""),m_str_tm_4(""),m_str_tm_5(""),
    m_tm_v_double(0.0),m_tm_time_double(0.0)

{
    //Print informations of PIC USB virtual COM device :
    m_listPortCom = m_serialPortsInfo.availablePorts();
    for(int i=0 ; i < m_listPortCom.size() ; i++){
        qDebug()<<m_listPortCom.at(i).portName()<<m_listPortCom.at(i).description()
                <<m_listPortCom.at(i).manufacturer()<<m_listPortCom.at(i).serialNumber()
                <<m_listPortCom.at(i).systemLocation()<<m_listPortCom.at(i).productIdentifier()
                <<m_listPortCom.at(i).vendorIdentifier();
    }

    //Configure de USB port COM4 :
    m_pic_usb_com.setPortName(m_com_name);//setPortName(listPortCom.at(1)) si un seul port com ??
    m_pic_usb_com.setBaudRate(QSerialPort::Baud115200);
    m_pic_usb_com.setDataBits(QSerialPort::Data8);
    m_pic_usb_com.setParity(QSerialPort::NoParity);
    m_pic_usb_com.setStopBits(QSerialPort::OneStop);
    m_pic_usb_com.setFlowControl(QSerialPort::NoFlowControl);

    //Open port COM and check if erreor :
    m_status_com_open = m_pic_usb_com.open(QIODevice::ReadWrite);
    qDebug()<<m_pic_usb_com.error()<<endl;//Look if an error occure at the opening.

    send_enter();
    send_qt_mode_activation();
    //send_tm_request(M_TM_VBAT);

}
UsbVirtualCom::~UsbVirtualCom()
{
    m_pic_usb_com.close();
    qDebug()<<"!!! Destructeur de UsbVirtualCom !!!";

}
//__________________________________________________________________________________________________

void UsbVirtualCom::send_enter(){
    //ENTER and read double menu :
    m_pic_usb_com.write("\r\n");
    m_pic_usb_com.waitForBytesWritten();
    m_pic_usb_com.waitForReadyRead();
    m_pic_usb_com.waitForReadyRead();
    qDebug().noquote()<<"readALL 1 : "<<endl<<m_pic_usb_com.readAll();
}
//__________________________________________________________________________________________________

void UsbVirtualCom::send_qt_mode_activation(){
    QString pic_message = "";

    //Activate the Qt interface mode on PIC :
    m_pic_usb_com.write("\r\n20\r\n");
    m_pic_usb_com.waitForBytesWritten();
    m_pic_usb_com.waitForReadyRead();
    pic_message = m_pic_usb_com.readAll();

    //Resend menu 20 on pic if qt mode is OFF :
    if(pic_message[13] == "O" && pic_message[14] == "F"){
        m_pic_usb_com.write("\r\n20\r\n");
        m_pic_usb_com.waitForBytesWritten();
        m_pic_usb_com.waitForReadyRead();
        pic_message = m_pic_usb_com.readAll();
    }

    qDebug().noquote()<<"send_qt_mode_activation() : "<<pic_message;
}
//__________________________________________________________________________________________________

void UsbVirtualCom::tm_strings_to_double(QString tm_i2c_str,
                                         double *tm_data_float,double *tm_time_float){
/* Convert a I2C TM on QString format into 2 floats.
 */
    QString         tm_v_str            = "";
    QString         tm_time_str         = "";
    unsigned short  f_comma             = 0;
    int             i_float             = 0;

    for(int i_int=0 ; i_int < tm_i2c_str.size() ; i_int++){
        if(tm_i2c_str[i_int] == ';'){
            f_comma = 1;//Rise flag.
        }
        if(f_comma == 0){
            //tm_v_str[i_int] = tm_i2c_str[i_int];
            tm_v_str.append(tm_i2c_str[i_int]);
        }
        else if(f_comma == 1){
            if(tm_i2c_str[i_int] != ';' && tm_i2c_str[i_int] != '\xd'&& tm_i2c_str[i_int] != '\xa'){
                //tm_time_str[i_float] = tm_i2c_str[i_int];
                tm_time_str.append(tm_i2c_str[i_int]);
                i_float++;
            }
        }
    }
    *tm_data_float      = tm_v_str.toFloat();
    *tm_time_float   = tm_time_str.toFloat();
    qDebug()<<"tm_v_str = "<<tm_v_str<<" ; *tm_data_float = "<<*tm_data_float<<endl
           <<"tm_time_str = "<<tm_time_str<<" ; *tm_time_float = "<<*tm_time_float<<endl;
}
//__________________________________________________________________________________________________
void UsbVirtualCom::send_tm(QString usb_string){
/*
 * 5 : STATE ; ch susp : on ; prech : off ; cc_cv : off ; bat_miss : off ; bat_short : off
 */
    unsigned short  comma    = 0;

    m_pic_usb_com.write(usb_string.toUtf8().constData());
    m_pic_usb_com.waitForBytesWritten();
    m_pic_usb_com.waitForReadyRead();
    //Read TM in the COM buffer and convert it into 2 floats :
    m_tm_i2c_str = m_pic_usb_com.readAll();

    for(int i=0 ; i < m_tm_i2c_str.size() ; i++){
        if(m_tm_i2c_str[i] == ";"){
            comma++;
        }

        if(m_tm_i2c_str[i] != ";" && comma == 0){m_str_tm_0.append(m_tm_i2c_str[i]);}
        else if(m_tm_i2c_str[i] != ";" && comma == 1){m_str_tm_1.append(m_tm_i2c_str[i]);}
        else if(m_tm_i2c_str[i] != ";" && comma == 2){m_str_tm_2.append(m_tm_i2c_str[i]);}
        else if(m_tm_i2c_str[i] != ";" && comma == 3){m_str_tm_3.append(m_tm_i2c_str[i]);}
        else if(m_tm_i2c_str[i] != ";" && comma == 4){m_str_tm_4.append(m_tm_i2c_str[i]);}
        else if(m_tm_i2c_str[i] != ";" && comma == 5){m_str_tm_5.append(m_tm_i2c_str[i]);}
    }
    qDebug()<<m_str_tm_0 + " ; " + m_str_tm_1;
}
//__________________________________________________________________________________________________

void UsbVirtualCom::get_tm_strings(QString *str_0,QString *str_1,QString *str_2,QString *str_3,
                    QString *str_4,QString *str_5){
    *str_0 = m_str_tm_0;
    *str_1 = m_str_tm_1;
    *str_2 = m_str_tm_2;
    *str_3 = m_str_tm_3;
    *str_4 = m_str_tm_4;
    *str_5 = m_str_tm_5;
}
//__________________________________________________________________________________________________
void UsbVirtualCom::send_tm_request(QString usb_string){
/* Send TM request to the PIC.
 *
 * https://doc.qt.io/qt-5/qstring.html#converting-between-8-bit-strings-and-unicode-strings
 */
    m_pic_usb_com.write(usb_string.toUtf8().constData());
    m_pic_usb_com.waitForBytesWritten();
    m_pic_usb_com.waitForReadyRead();
    //Read TM in the COM buffer and convert it into 2 floats :
    m_tm_i2c_str = m_pic_usb_com.readAll();
    tm_strings_to_double(m_tm_i2c_str,&m_tm_v_double,&m_tm_time_double);
}
//__________________________________________________________________________________________________

void UsbVirtualCom::get_tm_i2c_float(double *tm_t,double *tm_v){
    *tm_v = m_tm_v_double;
    *tm_t = m_tm_time_double;
}
//__________________________________________________________________________________________________

void UsbVirtualCom::send_tc(QString usb_string){
/* Send TC (command) to the PIC.
 *
 *
 */
    m_pic_usb_com.write(usb_string.toUtf8().constData());
    m_pic_usb_com.waitForBytesWritten();
    m_pic_usb_com.waitForReadyRead();
    //Read TM in the COM buffer and put it on qDebug() console :
    m_tm_i2c_str = m_pic_usb_com.readAll();
    qDebug()<<m_tm_i2c_str;
}
//__________________________________________________________________________________________________



