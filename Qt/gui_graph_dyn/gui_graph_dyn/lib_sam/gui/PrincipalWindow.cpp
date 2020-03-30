#include "PrincipalWindow.h"
#include "ui_PrincipalWindow.h"
#include <QtCharts/QSplineSeries>
#include <QDebug>

PrincipalWindow::PrincipalWindow(QWidget *parent) :
    QMainWindow(parent),ui(new Ui::PrincipalWindow),m_chart_v_i(0),m_chart_coulomb(0),m_timer(0),
    m_coeff_v(1),m_coeff_i(1),m_series_v(0),m_series_i(0),m_usb_com(0)
{
    qDebug()<<endl<<"Bonjour qDebug";

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &PrincipalWindow::send_usb_tm_request);
    m_timer->start(1500);//ms.

    ui->setupUi(this);

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

    //m_series_v = new QSplineSeries(this);
    //m_series_i = new QSplineSeries(this);
    //??????
    //m_chart_v_i->get_series(m_series_v,m_series_i);
    //qreal a = 20,b=2;
    //qDebug()<<"Principal : m_series_v = "<<m_series_v;
    //m_series_v->append(a,b);
}
//__________________________________________________________________________________________________

PrincipalWindow::~PrincipalWindow()
{
    delete  m_chart_v_i;
    delete   m_usb_com;
    delete  ui;
}
//__________________________________________________________________________________________________

void PrincipalWindow::send_usb_tm_request(){
/* Lancer la TM de l'USB vers le PIC.
 * Récupérer et décoder la data port COM.
 *
 */
    qreal x_v = 0.0, x_i = 0.0, y_v = 0.0, y_i = 0.0;

    //TM request for vbat :
    m_usb_com->send_tm_request(M_TM_VBAT);
    m_usb_com->get_tm_i2c_float(&x_v,&y_v);

    //TM request for ibat :
    m_usb_com->send_tm_request(M_TM_IBAT);
    m_usb_com->get_tm_i2c_float(&x_i,&y_i);

    //Set variable members of the Chart class.
    m_chart_v_i->set_xy_v_i(x_v,y_v,x_i,y_i);

    //Set flag for connect in Chart class.
    m_chart_v_i->set_flag_data_ready(true);

     ui->textEdit->append("Vbat = " + QString::number(y_v) + " V : " + QString::number(x_v) +
                          " s \n" + "ibat = " + QString::number(y_i) + " A : " +
                          QString::number(x_i) + " s \n\n");
}
//__________________________________________________________________________________________________
