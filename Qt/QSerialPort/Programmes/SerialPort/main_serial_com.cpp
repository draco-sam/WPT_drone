/***************************************************************************************************
 * File name        : main_serial_com.cpp
 * Date             : 22/02/2020
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


    for(int i=0 ; i < listPortCom.size() ; i++){
        qDebug()<<listPortCom.at(i).portName()<<listPortCom.at(i).description()
                <<listPortCom.at(i).manufacturer()<<listPortCom.at(i).serialNumber()
                <<listPortCom.at(i).systemLocation()<<listPortCom.at(i).productIdentifier()
                <<listPortCom.at(i).vendorIdentifier();
    }

    //Configure de USB port COM4 :
    pic_usb_com.setPortName("COM4");
    pic_usb_com.setBaudRate(QSerialPort::Baud115200);
    pic_usb_com.setDataBits(QSerialPort::Data8);
    pic_usb_com.setParity(QSerialPort::NoParity);
    pic_usb_com.setStopBits(QSerialPort::OneStop);
    pic_usb_com.setFlowControl(QSerialPort::NoFlowControl);

    status_com_open = pic_usb_com.open(QIODevice::ReadWrite);
    qDebug()<<pic_usb_com.error();//Look if an error occure at the opening.



    qDebug()<<"hello";
    cout<<"bonjour"<<endl;


    pic_usb_com.close();

    return app.exec();
}
