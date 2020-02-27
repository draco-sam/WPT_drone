/***************************************************************************************************
 * File name        : usb_com_chart.cpp
 * Date             : 27/02/2020
 * Author           : Samuel LORENZINO.
 *
 * Links            : https://doc.qt.io/qt-5/qserialport.html
 *
 * Comments         :
 **************************************************************************************************/

#include <QApplication>
#include <QList>
#include <QtCharts>
#include <iostream>
#include "chart_sam.h"
#include "UsbVirtualCom.h"

using namespace std;//Utilisation de l'espace de noms de la bibliothèque standard.

void tm_strings_to_floats(QString tm_i2c_str,float *tm_data_float,float *tm_time_float);

int main(int argc, char *argv[])
{
    QApplication    app(argc, argv);
    UsbVirtualCom   usbVirtualCom;


//    //ENTER and read double menu :
//    pic_usb_com.write("\r\n");
//    pic_usb_com.waitForBytesWritten();
//    pic_usb_com.waitForReadyRead();
//    pic_usb_com.waitForReadyRead();
//    qDebug().noquote()<<"readALL 1 : "<<endl<<pic_usb_com.readAll();

//    //Activate the Qt interface mode on PIC :
//    pic_usb_com.write("\r\n20\r\n");
//    pic_usb_com.waitForBytesWritten();
//    pic_usb_com.waitForReadyRead();
//    qDebug().noquote()<<pic_usb_com.readAll();


//    QString         tm_i2c_str      = "";
//    float           tm_v_float      = 0.0;
//    float           tm_time_float   = 0.0;

//    //Send TM request to the PIC :
//    pic_usb_com.write("\r\n1\r\n");
//    pic_usb_com.waitForBytesWritten();
//    pic_usb_com.waitForReadyRead();
//    //Read TM in the COM buffer and convert it into 2 floats :
//    tm_i2c_str = pic_usb_com.readAll();
//    tm_strings_to_floats(tm_i2c_str,&tm_v_float,&tm_time_float);

//    //Send TM request to the PIC :
//    pic_usb_com.write("\r\n1\r\n");
//    pic_usb_com.waitForBytesWritten();
//    pic_usb_com.waitForReadyRead();
//    //Read TM in the COM buffer and convert it into 2 floats :
//    tm_i2c_str = pic_usb_com.readAll();
//    tm_strings_to_floats(tm_i2c_str,&tm_v_float,&tm_time_float);

//    pic_usb_com.close();


    qDebug()<<endl<<"hello";
    cout<<"bonjour"<<endl;





    Chart *chart = new Chart;
    chart->setTitle("Vbat and Ibat charge curve (dynamic chart)");
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);
    //chart->setAnimationOptions(QChart::SeriesAnimations);

    //Create a QChartView object with QChart as a parameter.
    //With this way, we don't need to create a QGraphicsView scene ourselves.
    //Set Antialiasing ON to have the rendered lines look nicer.
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    //Set the QChartView as the windows's central widget.
    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    //window.setWindowModality(Qt::WindowModal);
    window.show();





//    float           d_x         = 5.0;
//    float           d_y         = 0.0;
//    unsigned int    i_while     = 0;
//    bool            f_main      = false;

//    while(i_while < 10){
//        for(unsigned long i_for=0 ; i_for < 100e6 ; i_for++){}
//        i_while++;
//        qDebug()<<"i_while = "<<i_while;
//    }



    return app.exec();
    //return 0;
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







