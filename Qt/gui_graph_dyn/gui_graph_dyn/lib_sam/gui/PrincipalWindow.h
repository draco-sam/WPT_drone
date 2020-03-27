#ifndef PRINCIPALWINDOW_H
#define PRINCIPALWINDOW_H

#include <QMainWindow>
#include "lib_sam/chart/chart_sam.h"

namespace Ui {
class PrincipalWindow;
}

class PrincipalWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit PrincipalWindow(QWidget *parent = nullptr);
        ~PrincipalWindow();


    public slots:
        void send_usb_tm_request();

    private:
        Ui::PrincipalWindow *ui;
        Chart           *m_chart_v_i;
        Chart           *m_chart_coulomb;
        //QTimer      m_timer;
        QTimer          *m_timer;
        short           m_coeff_v;
        short           m_coeff_i;
        QSplineSeries   *m_series_v;
        QSplineSeries   *m_series_i;

};

#endif // PRINCIPALWINDOW_H
