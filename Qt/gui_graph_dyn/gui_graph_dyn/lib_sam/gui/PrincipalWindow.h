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

    private:
        Ui::PrincipalWindow *ui;
        Chart       *m_chart_v_i;
        Chart       *m_chart_coulomb;

};

#endif // PRINCIPALWINDOW_H
