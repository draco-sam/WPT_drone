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

void tm_strings_to_floats(QString tm_i2c_str,float *tm_data_float,float *tm_time_float);

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


    QString         tm_i2c_str      = "";
    float           tm_v_float      = 0.0;
    float           tm_time_float   = 0.0;

    //Send TM request to the PIC :
    pic_usb_com.write("\r\n1\r\n");
    pic_usb_com.waitForBytesWritten();
    pic_usb_com.waitForReadyRead();
    //Read TM in the COM buffer and convert it into 2 floats :
    tm_i2c_str = pic_usb_com.readAll();
    tm_strings_to_floats(tm_i2c_str,&tm_v_float,&tm_time_float);

    //Send TM request to the PIC :
    pic_usb_com.write("\r\n1\r\n");
    pic_usb_com.waitForBytesWritten();
    pic_usb_com.waitForReadyRead();
    //Read TM in the COM buffer and convert it into 2 floats :
    tm_i2c_str = pic_usb_com.readAll();
    tm_strings_to_floats(tm_i2c_str,&tm_v_float,&tm_time_float);




    qDebug()<<endl<<"hello";
    cout<<"bonjour"<<endl;


    pic_usb_com.close();

    return app.exec();
}//End of main.
//__________________________________________________________________________________________________

void tm_strings_to_floats(QString tm_i2c_str,float *tm_data_float,float *tm_time_float){
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







