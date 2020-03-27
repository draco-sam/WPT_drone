#include "PrincipalWindow.h"
#include "ui_PrincipalWindow.h"
#include <QtCharts/QSplineSeries>
#include <QDebug>

PrincipalWindow::PrincipalWindow(QWidget *parent) :
    QMainWindow(parent),ui(new Ui::PrincipalWindow),m_chart_v_i(0),m_chart_coulomb(0),m_timer(0),
    m_coeff_v(1),m_coeff_i(1),m_series_v(0),m_series_i(0)
{
    qDebug()<<endl<<"Bonjour qDebug";

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &PrincipalWindow::send_usb_tm_request);
    m_timer->start(1500);//ms.

    ui->setupUi(this);

    ui->textEdit->setText("Bonjour, I2C LiPo bat graph \n");
    ui->textEdit->append("TM 1 : U/I bat");

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

PrincipalWindow::~PrincipalWindow()
{
    delete  m_chart_v_i;
    delete  ui;
}

void PrincipalWindow::send_usb_tm_request(){
/*
 *
 */
    //Lancer la TM de l'USB vers le PIC.
    //Récupérer et décoder la data port COM.

//    qreal x = 20, y_v = 5, y_i = 7;
//    m_chart_v_i->set_xy_v_i(x,y_v,y_i);
//    m_chart_v_i->set_flag_data_ready(true);

    qreal x = 0, y_v = 0, y_i = 0;

    m_chart_v_i->get_xy_v_i(&x,&y_v,&y_i);

    qDebug()<<"send top : x = "<<x<<" ; y_v = "<<y_v<<" ; y_i = "<<y_i;

    x = x + 5;
    y_v = y_v + (2 * m_coeff_v);
    y_i = y_i + (1.5 * m_coeff_i);

    //For vbat :
    if(y_v <= -10){
        m_coeff_v = 1;
        y_v = y_v + (2 * m_coeff_v);
    }
    else if(y_v >= 10){
        m_coeff_v = -1;
        y_v = y_v + (2 * m_coeff_v);
    }
    //----------------------------------------

    //For ibat :
    if(y_i <= -10){
        m_coeff_i = 1;
        y_i = y_i + (1.5 * m_coeff_i);
    }
    else if(y_i >= 10){
        m_coeff_i = -1;
        y_i = y_i + (1.5 * m_coeff_i);
    }
    //-----------------------------------------

    qDebug()<<"send bottom : x = "<<x<<" ; y_v = "<<y_v<<" ; y_i = "<<y_i;

    m_chart_v_i->set_xy_v_i(x,y_v,y_i);
    m_chart_v_i->set_flag_data_ready(true);//Set flag for connect in Chart class.
}
