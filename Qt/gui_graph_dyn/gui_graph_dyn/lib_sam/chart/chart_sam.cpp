/***************************************************************************************************
 * File name        : chart_sam.cpp
 * Date             : 06/04/2020
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
    m_x_vbat(0),m_x_ibat(0),m_y_vbat(0),m_y_ibat(0),m_x_min(56400),m_x_max(56460),
    m_f_data_ready(false),m_coeff_v(1),m_coeff_i(1)
{
    /*****************************************************************************************
     * Creat 2 series and add it to the chart.
     * Set color to the series and its own Y axis.
     * Attach X and Y axies to the series
     ***********************************************/

    //QSplineSeries automatically calculates spline segment control points
    //that are needed to properly draw the spline.
    m_series_v = new QSplineSeries(this);
    m_series_v->setName("Vbat [V]");
    QPen pen_red(Qt::red);
    pen_red.setWidth(3);
    m_series_v->setPen(pen_red);
    //m_series_v->append(m_x_vbat, m_y_vbat);//!!! Commenter si non bug 1er sample !!!
    Chart::addSeries(m_series_v);

    //Idem for i series :
    m_series_i = new QSplineSeries(this);
    m_series_i->setName("Ibat [A]");
    QPen pen_green(Qt::green);
    pen_green.setWidth(3);
    m_series_i->setPen(pen_green);
    //m_series_i->append(m_x_ibat, m_y_ibat);//!!! Commenter si non bug 1er sample !!!
    Chart::addSeries(m_series_i);

    //Same colore axis line and series :
    m_axis_y_v->setLinePenColor(m_series_v->pen().color());
    m_axis_y_i->setLinePenColor(m_series_i->pen().color());
    m_axis_x->setTitleText("Time [s]");
    //Add axis, attach series to its and set range :
    addAxis(m_axis_x,Qt::AlignBottom);
    addAxis(m_axis_y_v,Qt::AlignLeft);
    m_series_v->attachAxis(m_axis_x);
    m_series_v->attachAxis(m_axis_y_v);
    m_axis_x->setTickCount(11);//Number of lines : Step = x_max_range / (tick_count - 1).
    m_axis_x->setRange(m_x_min,m_x_max);//23h59min59s<->86399s.
    m_axis_y_v->setRange(2.5, 4.5);
    m_axis_y_v->setTickCount(11);

    //idem for i series :
    addAxis(m_axis_y_i,Qt::AlignRight);
    m_series_i->attachAxis(m_axis_x);
    m_series_i->attachAxis(m_axis_y_i);
    m_axis_y_i->setRange(0, 2.5);
    m_axis_y_i->setTickCount(11);
    /****************************************************************************************/
    //m_series_v->clear();
    //m_series_v->remove(25,7.5);
    //m_series_v->removePoints(1,1);
    //Chart::addSeries(m_series_v);


    QObject::connect(&m_timer, &QTimer::timeout, this, &Chart::add_data);
    m_timer.setInterval(1100);//[ms].
    m_timer.start();
}
//__________________________________________________________________________________________________

Chart::~Chart()
{

}
//__________________________________________________________________________________________________

void Chart::get_xy_v_i(qreal *x_v, qreal *y_v, qreal *x_i, qreal *y_i){
    *x_v    = m_x_vbat;
    *y_v    = m_y_vbat;
    *x_i    = m_x_ibat;
    *y_i    = m_y_ibat;
}
//__________________________________________________________________________________________________

void Chart::set_xy_v_i(qreal x_v,qreal y_v, qreal x_i, qreal y_i){
    m_x_vbat    = x_v;
    m_y_vbat    = y_v;
    m_x_ibat    = x_i;
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
    //series_i->append((x-5),(y+5));
}
//__________________________________________________________________________________________________

void Chart::add_data(){
/* Add data to the chart if PrincipalWindow write a valide data to
 * m_x, m_y_vbat and m_y_ibat.
 *
 * Before adding data, check if data is ready.
 */
    if(m_f_data_ready == true){
        if(m_x_ibat > m_x_max){
            m_x_max = m_x_max + 60;//Add 60s at max abscisse.
            m_axis_x->setRange(m_x_min,m_x_max);//23h59min59s<->86399s.
        }

        m_series_v->append(m_x_vbat, m_y_vbat);
        m_series_i->append(m_x_ibat, m_y_ibat);


        m_f_data_ready = false;//Reset flag.
    }

    if (m_x_vbat >= 87000)
        m_timer.stop();
}
//__________________________________________________________________________________________________

void Chart::set_flag_data_ready(bool flag){
    m_f_data_ready = flag;
}
//__________________________________________________________________________________________________
