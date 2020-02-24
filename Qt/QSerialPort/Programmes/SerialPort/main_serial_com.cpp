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
    char                        t_com[128]      = "";
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



    QByteArray ba;
    ba.resize(2);
    ba[0] = '\r';
    ba[1] = '1';
    //ba[2] = '\n';//Idem à 0x0a pour LF.
    //pic_usb_com.write(ba);
    pic_usb_com.write("\r\n");
    while(pic_usb_com.waitForReadyRead() != true){};
    qDebug()<<pic_usb_com.readAll();
    //Attendre que le menu soit transmit.
    while(pic_usb_com.waitForReadyRead() != true){};
    qDebug()<<pic_usb_com.readAll();

//    pic_usb_com.write("\r\n");
//    while(pic_usb_com.waitForReadyRead() != true){};
//    qDebug()<<pic_usb_com.readAll();

    pic_usb_com.write("1");
    while(pic_usb_com.waitForReadyRead() != true){};
    qDebug()<<pic_usb_com.readAll()<<endl;
    pic_usb_com.write("\r\n");
    while(pic_usb_com.waitForReadyRead() != true){};
    qDebug()<<pic_usb_com.readAll()<<endl;
    while(pic_usb_com.waitForReadyRead() != true){};
    qDebug()<<pic_usb_com.readAll()<<endl;



    //pic_usb_com.write("bonjour Sam ^^");



    //pic_usb_com.read(t_com,sizeof(t_com));
    //qDebug()<<t_com;





//    pic_usb_com.write(ba);
//    while(pic_usb_com.waitForReadyRead() != true){};
//    qDebug()<<pic_usb_com.readAll();



//    while(pic_usb_com.waitForReadyRead() != true){};
//    qDebug()<<pic_usb_com.readAll();



    qDebug()<<"hello";
    cout<<"bonjour"<<endl;


    pic_usb_com.close();

    return app.exec();
}
