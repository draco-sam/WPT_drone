#include "chart_sam.h"
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>


Chart::Chart():
    m_series(0),
    m_axis_x(new QValueAxis()),
    m_axis_y(new QValueAxis()),
    //m_step(0),
    m_x(0),
    m_y(2),
    m_coeff(1),
    m_flag_timer(false)
{
    QObject::connect(&m_timer, &QTimer::timeout, this, &Chart::toggle_f_timer);
    m_timer.setInterval(1500);//[ms].

    //QSplineSeries automatically calculates spline segment control points
    //that are needed to properly draw the spline.
    m_series = new QSplineSeries(this);
    m_series->setName("spline_Vbat");
    QPen red_pen(Qt::red);
    red_pen.setWidth(3);
    m_series->setPen(red_pen);
    m_series->append(m_x, m_y);

    addSeries(m_series);

    addAxis(m_axis_x,Qt::AlignBottom);
    addAxis(m_axis_y,Qt::AlignLeft);
    m_series->attachAxis(m_axis_x);
    m_series->attachAxis(m_axis_y);
    m_axis_x->setTickCount(11);//Number of lines : Step = x_max_range / (tick_count - 1).
    m_axis_x->setRange(0,200);
    m_axis_y->setRange(-15, 15);

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
    m_y = m_y + (2 * m_coeff);

    if(m_y <= -10){
        m_coeff = 1;
        m_y = m_y + (2 * m_coeff);
    }
    else if(m_y >= 10){
        m_coeff = -1;
        m_y = m_y + (2 * m_coeff);
    }

    m_series->append(m_x, m_y);
    if (m_x >= 150){
        m_timer.stop();
    }

}
//__________________________________________________________________________________________________

void Chart::set_data_xy(float x,float y)
{
    m_x = x;
    m_x = y;
}
//__________________________________________________________________________________________________

void Chart::get_data_xy(float *x,float *y)
{
    *x = m_x;
    *y = m_y;
}
//__________________________________________________________________________________________________

void Chart::toggle_f_timer(){
    m_flag_timer = !m_flag_timer;

    add_data();
}
//__________________________________________________________________________________________________

void Chart::get_f_timer(bool *flag){
    *flag = m_flag_timer;
}
void Chart::set_f_timer(bool flag){
    m_flag_timer = flag;
}
//__________________________________________________________________________________________________


