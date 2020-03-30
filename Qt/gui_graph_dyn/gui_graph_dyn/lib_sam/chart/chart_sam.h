#include <QtCharts/QChart>
#include <QtCore/QTimer>

QT_CHARTS_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

//Class declaration who inherits from Qchart class :
class Chart: public QChart
{
    Q_OBJECT
public:
    Chart();
    virtual ~Chart();
    void get_xy_v_i(qreal *x_v, qreal *y_v, qreal *x_i, qreal *y_i);
    void set_xy_v_i(qreal x, qreal y_v, qreal x_i, qreal y_i);
    void get_series(QSplineSeries *series_v,QSplineSeries *series_i);
    void set_flag_data_ready(bool flag);

public slots:
    void add_data();

private:
    QTimer          m_timer;
    QSplineSeries   *m_series_v;
    QSplineSeries   *m_series_i;
    QStringList     m_titles;
    QValueAxis      *m_axis_x;
    QValueAxis      *m_axis_y_v;
    QValueAxis      *m_axis_y_i;
    //qreal           m_step;
    qreal           m_x_vbat;
    qreal           m_x_ibat;
    qreal           m_y_vbat;
    qreal           m_y_ibat;
    bool            m_f_data_ready;//Flag set by the main window.
    short           m_coeff_v;
    short           m_coeff_i;
};
