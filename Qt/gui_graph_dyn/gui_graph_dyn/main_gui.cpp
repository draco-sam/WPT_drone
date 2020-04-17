
/***************************************************************************************************
 * File name        : main_gui.cpp
 * Date             : 27/02/2020
 * Author           : Samuel LORENZINO.
 *
 * Links            :
 *                  :
 *
 * Comments         :
 **************************************************************************************************/

#include <QApplication>
#include <QtCharts>
#include <QDebug>
//#include <QTest>
#include "lib_sam/gui/PrincipalWindow.h"


int main(int argc, char *argv[])
{
    QApplication    app(argc, argv);

    PrincipalWindow main_window;
    main_window.show();


    return app.exec();

}//End of main.
//__________________________________________________________________________________________________

