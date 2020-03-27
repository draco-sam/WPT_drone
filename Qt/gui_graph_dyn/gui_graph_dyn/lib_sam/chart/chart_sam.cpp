/***************************************************************************************************
 * File name        : chart_sam.cpp
 * Date             : 27/03/2020
 * Author           : Samuel LORENZINO.
 *
 * Links            :
 *                  :
 *
 * Comments         : Création d'un slot personnel "add_data" pour rajouter des données en temps
 *                  : réel toutes les x ms grâce au signal QTimer::timeout.
 **************************************************************************************************/
#include "chart_sam.h"
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>


Chart::Chart():
    m_series_v(0),m_series_i(0),
    m_axis_x(new QValueAxis()),m_axis_y_v(new QValueAxis()),m_axis_y_i(new QValueAxis()),
    m_x(0),m_y_vbat(2),m_y_ibat(0),m_f_data_ready(false),
    m_coeff_v(1),m_coeff_i(1)
{
    QObject::connect(&m_timer, &QTimer::timeout, this, &Chart::add_data);
    m_timer.setInterval(1500);//[ms].

    /*****************************************************************************************
     * Creat 2 series and add it to the chart.
     * Set color to the series and its own Y axis.
     * Attach X and Y axies to the series
     ***********************************************/

    //QSplineSeries automatically calculates spline segment control points
    //that are needed to properly draw the spline.
    m_series_v = new QSplineSeries(this);
    m_series_v->setName("spline_Vbat");
    QPen pen_red(Qt::red);
    pen_red.setWidth(3);
    m_series_v->setPen(pen_red);
    m_series_v->append(m_x, m_y_vbat);
    Chart::addSeries(m_series_v);

    //Idem for i series :
    m_series_i = new QSplineSeries(this);
    m_series_i->setName("spline_Ibat");
    QPen pen_green(Qt::green);
    pen_green.setWidth(3);
    m_series_i->setPen(pen_green);
    m_series_i->append(m_x, m_y_ibat);
    Chart::addSeries(m_series_i);

    //Same colore axis line and series :
    m_axis_y_v->setLinePenColor(m_series_v->pen().color());
    m_axis_y_i->setLinePenColor(m_series_i->pen().color());

    //Add axis, attach series to its and set range :
    addAxis(m_axis_x,Qt::AlignBottom);
    addAxis(m_axis_y_v,Qt::AlignLeft);
    m_series_v->attachAxis(m_axis_x);
    m_series_v->attachAxis(m_axis_y_v);
    m_axis_x->setTickCount(11);//Number of lines : Step = x_max_range / (tick_count - 1).
    m_axis_x->setRange(0,200);
    m_axis_y_v->setRange(-15, 15);

    //idem for i series :
    addAxis(m_axis_y_i,Qt::AlignRight);
    m_series_i->attachAxis(m_axis_x);
    m_series_i->attachAxis(m_axis_y_i);
    m_axis_y_i->setRange(-10, 10);
    /****************************************************************************************/

    m_timer.start();
}
//__________________________________________________________________________________________________

Chart::~Chart()
{

}
//__________________________________________________________________________________________________

void Chart::get_xy_v_i(qreal *x, qreal *y_v, qreal *y_i){
    *x      = m_x;
    *y_v    = m_y_vbat;
    *y_i    = m_y_ibat;
}
//__________________________________________________________________________________________________

void Chart::set_xy_v_i(qreal x,qreal y_v, qreal y_i){
    m_x         = x;
    m_y_vbat    = y_v;
    m_y_ibat    = y_i;
}
//__________________________________________________________________________________________________

void Chart::get_series(QSplineSeries *series_v,QSplineSeries *series_i){
    series_v = m_series_v;
    series_i = m_series_i;

    qDebug()<<"series_v = "<<series_v;

    qreal x = 20,y=2;
    //m_series_v->append(x,y);
    //series_v->append(x,y);
    series_i->append((x-5),(y+5));
}
//__________________________________________________________________________________________________

void Chart::add_data(){

//    m_x = m_x + 5;
//    m_y_vbat = m_y_vbat + (2 * m_coeff_v);
//    m_y_ibat = m_y_ibat + (1.5 * m_coeff_i);

//    //For vbat :
//    if(m_y_vbat <= -10){
//        m_coeff_v = 1;
//        m_y_vbat = m_y_vbat + (2 * m_coeff_v);
//    }
//    else if(m_y_vbat >= 10){
//        m_coeff_v = -1;
//        m_y_vbat = m_y_vbat + (2 * m_coeff_v);
//    }
//    //----------------------------------------

//    //For ibat :
//    if(m_y_vbat <= -10){
//        m_coeff_i = 1;
//        m_y_vbat = m_y_vbat + (1.5 * m_coeff_i);
//    }
//    else if(m_y_vbat >= 10){
//        m_coeff_i = -1;
//        m_y_vbat = m_y_vbat + (1.5 * m_coeff_i);
//    }
//    //-----------------------------------------

    if(m_f_data_ready == true){
        qDebug()<<"Class Chart add_data : m_x = "<<m_x<<" ; m_y_vbat = "<<m_y_vbat<<" ; m_y_ibat = "<<m_y_ibat;
        m_series_v->append(m_x, m_y_vbat);
        m_series_i->append(m_x, m_y_ibat);

        m_f_data_ready = false;//Reset flag.
    }

    if (m_x >= 150)
        m_timer.stop();
}
//__________________________________________________________________________________________________

void Chart::set_flag_data_ready(bool flag){
    m_f_data_ready = flag;
}
//__________________________________________________________________________________________________