/***************************************************************************************************
 * File name        : Chart_sam.h
 * Date             : 27/02/2020
 * Author           : Samuel LORENZINO.
 *
 * Links            :
 *
 * Comments         :
 **************************************************************************************************/
#include <QtCharts/QChart>
#include <QtCore/QTimer>
#include "UsbVirtualCom.h"

QT_CHARTS_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

//Class declaration who inherits from Qchart class :
class Chart: public QChart
{
    Q_OBJECT//Macro for compilator and slot created by the user.
public:
    Chart();
    virtual ~Chart();
    void set_data_xy(float x,float y);
    void get_data_xy(float *x,float *y);
    void add_data();

public slots:
    //void add_data();
    //void toggle_f_timer();

private:
    QTimer          m_timer;
    QSplineSeries   *m_series;
    QStringList     m_titles;
    QValueAxis      *m_axis_x;
    QValueAxis      *m_axis_y;
    //qreal           m_step;
    qreal           m_x;
    qreal           m_y;
    short           m_coeff;
    bool            m_flag_timer;
    UsbVirtualCom   *m_usb_com;
};
