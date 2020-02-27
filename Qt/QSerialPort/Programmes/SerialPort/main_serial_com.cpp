/***************************************************************************************************
 * File name        : main_serial_com.cpp
 * Date             : 27/02/2020
 * Author           : Samuel LORENZINO.
 *
 * Links            : https://doc.qt.io/qt-5/qserialport.html
 *
 * Comments         :
 **************************************************************************************************/

#include <QApplication>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QList>
#include <iostream>

using namespace std;//Utilisation de l'espace de noms de la bibliothèque standard.

int main(int argc, char *argv[])
{
    /****************************************************************
     * Declaration variables :
     * ----------------------
     */
    QString                     serial_name     = "";
    QString                     str             = "hello";
    bool                        status_com_open = false;
    QList<QSerialPortInfo>      listPortCom;
    QSerialPortInfo             serialPortsInfo;
    QSerialPort                 pic_usb_com;
    /***************************************************************/

    QApplication app(argc, argv);


    listPortCom = serialPortsInfo.availablePorts();

    //Print informations of PIC USB virtual COM device :
    for(int i=0 ; i < listPortCom.size() ; i++){
        qDebug()<<listPortCom.at(i).portName()<<listPortCom.at(i).description()
                <<listPortCom.at(i).manufacturer()<<listPortCom.at(i).serialNumber()
                <<listPortCom.at(i).systemLocation()<<listPortCom.at(i).productIdentifier()
                <<listPortCom.at(i).vendorIdentifier();
    }

    //Configure de USB port COM4 :
    pic_usb_com.setPortName("COM4");//setPortName(listPortCom.at(1)) si un seul port com ??
    pic_usb_com.setBaudRate(QSerialPort::Baud115200);
    pic_usb_com.setDataBits(QSerialPort::Data8);
    pic_usb_com.setParity(QSerialPort::NoParity);
    pic_usb_com.setStopBits(QSerialPort::OneStop);
    pic_usb_com.setFlowControl(QSerialPort::NoFlowControl);

    //Open port COM and check if erreor :
    status_com_open = pic_usb_com.open(QIODevice::ReadWrite);
    qDebug()<<pic_usb_com.error()<<endl;//Look if an error occure at the opening.


    //while(pic_usb_com.isDataTerminalReady() != true){};



//    QByteArray ba;
//    ba.resize(1);
//    ba[0] = '1';
//    ba[1] = '\n';
//    ba[2] = '\r';
//    ba[3] = '\n';
//    ba[4] = '\r';
    //pic_usb_com.write(ba);

    //ENTER and read double menu :
    pic_usb_com.write("\r\n");
    pic_usb_com.waitForBytesWritten();
    pic_usb_com.waitForReadyRead();
    pic_usb_com.waitForReadyRead();
    qDebug().noquote()<<"readALL 1 : "<<endl<<pic_usb_com.readAll();

    //Activate the Qt interface mode on PIC :
    pic_usb_com.write("\r\n20\r\n");
    pic_usb_com.waitForBytesWritten();
    pic_usb_com.waitForReadyRead();
    qDebug().noquote()<<pic_usb_com.readAll();

    //Send TM request to the PIC :
    pic_usb_com.write("\r\n1\r\n");
    pic_usb_com.waitForBytesWritten();
    pic_usb_com.waitForReadyRead();

    QString         tm_i2c_str          = "";
    QString         tm_v_str            = "";
    QString         tm_t                = "";
    unsigned short  f_comma             = 0;
    float           tm_i2c_float        = 0.0;

    //Read TM in the COM buffer :
    tm_i2c_str = pic_usb_com.readAll();
    qDebug()<<"tm_i2c_str = "<<tm_i2c_str<<"sizeof = "<<tm_i2c_str.size();
    qDebug()<<tm_i2c_str[0]<<tm_i2c_str[1]<<tm_i2c_str[2]<<tm_i2c_str[3];

    //Save string vbat (without time) :
    for(int i=0 ; i < tm_i2c_str.size() ; i++){
        if(tm_i2c_str[i] == ';'){
            f_comma = 1;//Rise flag.
        }
        if(f_comma == 0){
            tm_v_str[i] = tm_i2c_str[i];
        }
        qDebug()<<"i = "<<i<<" : tm_i2c_str[i] = "<<tm_i2c_str[i];
    }
    tm_v_str = "-3.100";
    tm_i2c_float = tm_v_str.toFloat();
    qDebug()<<"tm_v_str = "<<tm_v_str<<" ; tm_i2c_float = "<<tm_i2c_float;

    pic_usb_com.write("\r\n1\r\n");
    pic_usb_com.waitForBytesWritten();
    pic_usb_com.waitForReadyRead();
    qDebug().noquote()<<pic_usb_com.readAll();





    qDebug()<<endl<<"hello";
    cout<<"bonjour"<<endl;


    pic_usb_com.close();

    return app.exec();
}
