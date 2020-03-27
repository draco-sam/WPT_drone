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
    qreal           m_x;
    qreal           m_y_vbat;
    qreal           m_y_ibat;
    short           m_coeff;
};
