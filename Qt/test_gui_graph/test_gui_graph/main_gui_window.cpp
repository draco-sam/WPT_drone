/***************************************************************************************************
 * File name        : main_gui_window.cpp
 * Date             : 26/02/2020
 * Author           : Samuel LORENZINO.
 *
 * Links            : https://doc.qt.io/qt-5/qtcharts-index.html
 *                  : https://doc.qt.io/qt-5/qtcharts-splinechart-example.html
 *
 * Comments         : Premier essai interface IHM.
 **************************************************************************************************/

#include <QApplication>
#include <QWidget>
#include <QDebug>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication    app(argc, argv);


    MainWindow main_gui_window;
    main_gui_window.show();


    return app.exec();

}//End of main.
//__________________________________________________________________________________________________
