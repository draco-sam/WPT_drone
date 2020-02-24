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

    pic_usb_com.write("\r\n");
    while(pic_usb_com.waitForReadyRead() != true){};
    qDebug().noquote()<<"readALL 1 : "<<endl<<pic_usb_com.readAll();

    pic_usb_com.write("\r\n 1");
    while(pic_usb_com.waitForReadyRead() != true){};
    qDebug().noquote()<<endl<<"readAll 2 : "<<endl<<pic_usb_com.readAll()<<endl;
    pic_usb_com.write("\r\n");
    while(pic_usb_com.waitForReadyRead() != true){};
    qDebug().noquote()<<"readAll 3 : "<<endl<<pic_usb_com.readAll()<<endl;


    /******************************************************
     * Test en cours :
     * --------------
     */
    QByteArray  test_sam("hello \r\n mister");
    QString     s_sam = "";
    for(int i=0 ; i < test_sam.size() ; i++){
        qDebug()<<i<<" : "<<test_sam[i]<<endl;
        if(test_sam[i] == '\n'){
            s_sam = s_sam + '\n';
        }
        else if (test_sam[i] != '\r'){
            s_sam = s_sam + test_sam[i];
        }
    }
    qDebug()<<s_sam<<endl;
    /*****************************************************/


    qDebug()<<endl<<"hello";
    cout<<"bonjour"<<endl;


    pic_usb_com.close();

    return app.exec();
}
