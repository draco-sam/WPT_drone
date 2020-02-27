#include "UsbVirtualCom.h"

UsbVirtualCom::UsbVirtualCom() :
    m_serial_name(""),m_status_com_open(false)

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
    m_pic_usb_com.setPortName("COM4");//setPortName(listPortCom.at(1)) si un seul port com ??
    m_pic_usb_com.setBaudRate(QSerialPort::Baud115200);
    m_pic_usb_com.setDataBits(QSerialPort::Data8);
    m_pic_usb_com.setParity(QSerialPort::NoParity);
    m_pic_usb_com.setStopBits(QSerialPort::OneStop);
    m_pic_usb_com.setFlowControl(QSerialPort::NoFlowControl);

    //Open port COM and check if erreor :
    m_status_com_open = m_pic_usb_com.open(QIODevice::ReadWrite);
    qDebug()<<m_pic_usb_com.error()<<endl;//Look if an error occure at the opening.


}
UsbVirtualCom::~UsbVirtualCom()
{
    m_pic_usb_com.close();
    qDebug()<<"!!! Destructeur de UsbVirtualCom !!!";

}
//__________________________________________________________________________________________________
