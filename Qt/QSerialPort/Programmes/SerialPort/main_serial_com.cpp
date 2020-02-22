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
    QList<QSerialPortInfo>      listPortCom;
    QSerialPortInfo             serialPortInfo;
    /***************************************************************/

    QApplication app(argc, argv);


    listPortCom = serialPortInfo.availablePorts();


    for(int i=0 ; i < listPortCom.size() ; i++){
        qDebug()<<listPortCom.at(i).portName()<<listPortCom.at(i).description()
                <<listPortCom.at(i).manufacturer()<<listPortCom.at(i).serialNumber()
                <<listPortCom.at(i).systemLocation()<<listPortCom.at(i).productIdentifier()
                <<listPortCom.at(i).vendorIdentifier();
    }






    qDebug()<<serial_name;

    qDebug()<<"hello";
    cout<<"bonjour"<<endl;

    return app.exec();
}
