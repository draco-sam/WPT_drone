#ifndef PRINCIPALWINDOW_H
#define PRINCIPALWINDOW_H

#include <QMainWindow>
#include <QFile>
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
        QString get_string_temp_on_file(unsigned int i_num);


    public slots:
        void usb_tm_multiple();
        void usb_tc_start_stop_charge();
        void text_edit_scroll_off();

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
        QString         m_data_usb_str;
        QString         m_vin_str;
        QString         m_vbat_str;
        QString         m_ibat_str;
        QString         m_vbat_time_str;
        QString         m_ibat_time_str;
        QString         m_charge_state_suspended_str;
        QString         m_charge_state_precharge_str;
        QString         m_charge_status_str;
        QString         m_bat_temp_ntc_str;
        QString         m_charge_temp_die_str;
        bool            m_mouse_click;

};

#endif // PRINCIPALWINDOW_H
