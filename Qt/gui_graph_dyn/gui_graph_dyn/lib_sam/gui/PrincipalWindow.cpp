/***************************************************************************************************
 * File name        : PrincipalWindow.cpp
 * Date             : 06/04/2020
 * Author           : Samuel LORENZINO.
 *
 * Links            :
 *                  :
 *
 * Comments         :
 **************************************************************************************************/
#include "PrincipalWindow.h"
#include "ui_PrincipalWindow.h"
#include <QtCharts/QSplineSeries>
#include <QDebug>

PrincipalWindow::PrincipalWindow(QWidget *parent) :
    QMainWindow(parent),ui(new Ui::PrincipalWindow),m_chart_v_i(0),m_chart_coulomb(0),m_timer(0),
    m_coeff_v(1),m_coeff_i(1),m_series_v(0),m_series_i(0),m_usb_com(0),m_flag_start_charge(false)
{
    qDebug()<<endl<<"Bonjour qDebug";

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &PrincipalWindow::send_usb_tm_request);
    //m_timer->start(1500);//ms.

    ui->setupUi(this);

    QObject::connect(ui->button_start_charge,SIGNAL(clicked()),this,
                     SLOT(usb_tc_start_stop_charge()));

    ui->textEdit->setText("Bonjour, I2C LiPo bat graph \n");
    ui->textEdit->append("TM 1 : U/I bat");

    //Creat a USB virtual COM object to communicate with the PIC.
    m_usb_com = new UsbVirtualCom();

    //-----------------------------------------------------------------------------------
    //Code pour créer un graph dynamique à placer dans un onglet du GUI :
    //------------------------------------------------------------------
    m_chart_v_i = new Chart();//Allocation mémoire pour objet.
    m_chart_v_i->setTitle("Vbat and Ibat charge curve (dynamic chart)");
    //m_chart_v_i->legend()->hide();
    m_chart_v_i->setAnimationOptions(QChart::AllAnimations);

    //Create a QChartView object with QChart as a parameter.
    //With this way, we don't need to create a QGraphicsView scene ourselves.
    //Set Antialiasing ON to have the rendered lines look nicer.
    ui->graphicsView_1 = new QChartView(m_chart_v_i,ui->tab_1);
    ui->graphicsView_1->setObjectName(QString::fromUtf8("graphicsView_1"));
    ui->graphicsView_1->setRenderHint(QPainter::Antialiasing);

    ui->gridLayout->addWidget(ui->graphicsView_1, 0, 0, 1, 1);
    //-----------------------------------------------------------------------------------

     ui->statusbar->showMessage("bonjour statusbar");

    check_i2c_charge_on_off();

}
//__________________________________________________________________________________________________

PrincipalWindow::~PrincipalWindow()
{
    delete  m_chart_v_i;
    delete   m_usb_com;
    delete  ui;
}
//__________________________________________________________________________________________________

void PrincipalWindow::check_i2c_charge_on_off(){
/*
 */
    ui->statusbar->clearMessage();
    ui->statusbar->showMessage("test");
    QString str_0 = "",str_1="",str_2="",str_3="",str_4="",str_5="";

    m_usb_com->send_tm(TM_STATE);
    m_usb_com->get_tm_strings(&str_0,&str_1,&str_2,&str_3,&str_4,&str_5);

    if(str_1 == " ch susp : on "){
        ui->button_start_charge->setText("START charge");
        m_flag_start_charge = false;
    }
    else if(str_1 == " ch susp : off "){
        ui->button_start_charge->setText("STOP charge");
        m_flag_start_charge = true;
        m_timer->start(1500);
    }
    ui->textEdit->moveCursor(QTextCursor::End);//!!! Arreter si on clique dans le textEdit !!!
    ui->textEdit->ensureCursorVisible();
    ui->textEdit->append("\ncheck_charge_on_off : "+ str_1 + "\n");
}
//__________________________________________________________________________________________________

void PrincipalWindow::send_usb_tm_request(){
/* Lancer la TM de l'USB vers le PIC.
 * Récupérer et décoder la data port COM.
 *
 */
    qreal x_v = 0.0, x_i = 0.0, y_v = 0.0, y_i = 0.0;

    //TM request for vbat :
    m_usb_com->send_tm_request(TM_VBAT);
    m_usb_com->get_tm_i2c_float(&x_v,&y_v);

    //TM request for ibat :
    m_usb_com->send_tm_request(TM_IBAT);
    m_usb_com->get_tm_i2c_float(&x_i,&y_i);

    //Set variable members of the Chart class.
    m_chart_v_i->set_xy_v_i(x_v,y_v,x_i,y_i);

    //Set flag for connect in Chart class.
    m_chart_v_i->set_flag_data_ready(true);

    ui->line_vbat->setText("Vbat = " + QString::number(y_v) + " V : " + QString::number(x_v) +" s");
    ui->line_ibat->setText("ibat = " + QString::number(y_i) + " A : " +
                            QString::number(x_i) + " s ");

    ui->textEdit->moveCursor(QTextCursor::End);//!!! Arreter si on clique dans le textEdit !!!
    ui->textEdit->ensureCursorVisible();
    ui->textEdit->append("Vbat = " + QString::number(y_v) + " V : " + QString::number(x_v) +
                          " s ; ibat = " + QString::number(y_i) + " A : " +
                          QString::number(x_i) + " s ");
}
//__________________________________________________________________________________________________

void PrincipalWindow::usb_tc_start_stop_charge(){
/*
 */
    if(m_flag_start_charge == false){//Stop to start.
        ui->button_start_charge->setText("STOP charge");//Toggle texte button.
        m_flag_start_charge = true;//Charge starting.
        m_timer->start(1500);//ms.
    }
    else{//Start to stop.
        ui->button_start_charge->setText("START charge");//Toggle texte button.
        m_flag_start_charge = false;//Charge stopping.
        m_timer->stop();//ms.
    }
    m_usb_com->send_tc(TC_START_STOP_CHARGE);
    qDebug()<<"usb_tc_start_stop_charge";
}
//__________________________________________________________________________________________________



