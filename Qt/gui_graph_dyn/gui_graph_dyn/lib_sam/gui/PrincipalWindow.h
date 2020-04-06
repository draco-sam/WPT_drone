#ifndef PRINCIPALWINDOW_H
#define PRINCIPALWINDOW_H

#include <QMainWindow>
#include "lib_sam/chart/chart_sam.h"
#include "lib_sam/usb/UsbVirtualCom.h"

namespace Ui {
class PrincipalWindow;
}

class PrincipalWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit PrincipalWindow(QWidget *parent = nullptr);
        ~PrincipalWindow();
        void check_i2c_charge_on_off();


    public slots:
        void send_usb_tm_request();
        void usb_tc_start_stop_charge();

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
        UsbVirtualCom   *m_usb_com;
        bool            m_flag_start_charge;//stop=false,start=true.

};

#endif // PRINCIPALWINDOW_H
