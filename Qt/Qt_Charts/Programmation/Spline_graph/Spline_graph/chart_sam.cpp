/***************************************************************************************************
 * File name        : chart_sam.cpp
 * Date             : 26/03/2020
 * Author           : Samuel LORENZINO.
 *
 * Links            :
 *                  :
 *
 * Comments         :
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
    //m_step(0),
    m_x(0),m_y_vbat(2),m_y_ibat(0),
    m_coeff(1)
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
    addSeries(m_series_v);

    //Idem for i series :
    m_series_i = new QSplineSeries(this);
    m_series_i->setName("spline_Ibat");
    QPen pen_green(Qt::green);
    pen_green.setWidth(3);
    m_series_i->setPen(pen_green);
    m_series_i->append(m_x, m_y_ibat);
    addSeries(m_series_i);

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

void Chart::add_data()
{
    m_x = m_x + 5;
    m_y_vbat = m_y_vbat + (2 * m_coeff);
    m_y_ibat = m_y_ibat + (1.5 * m_coeff);

    //For vbat :
    if(m_y_vbat <= -10){
        m_coeff = 1;
        m_y_vbat = m_y_vbat + (2 * m_coeff);
    }
    else if(m_y_vbat >= 10){
        m_coeff = -1;
        m_y_vbat = m_y_vbat + (2 * m_coeff);
    }
    //----------------------------------------

    //For ibat :
    if(m_y_vbat <= -10){
        m_coeff = 1;
        m_y_vbat = m_y_vbat + (1.5 * m_coeff);
    }
    else if(m_y_vbat >= 10){
        m_coeff = -1;
        m_y_vbat = m_y_vbat + (1.5 * m_coeff);
    }
    //-----------------------------------------

    m_series_v->append(m_x, m_y_vbat);
    m_series_i->append(m_x, m_y_ibat);
    if (m_x >= 150)
        m_timer.stop();
}
//__________________________________________________________________________________________________
