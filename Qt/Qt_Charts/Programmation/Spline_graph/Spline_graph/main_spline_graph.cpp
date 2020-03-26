/***************************************************************************************************
 * File name        : main_spline_graph.cpp
 * Date             : 26/02/2020
 * Author           : Samuel LORENZINO.
 *
 * Links            : https://doc.qt.io/qt-5/qtcharts-index.html
 *                  : https://doc.qt.io/qt-5/qtcharts-splinechart-example.html
 *
 * Comments         :
 **************************************************************************************************/

#include <QApplication>
#include <QtCharts>
#include <QDebug>
#include <QTest>
#include "chart_sam.h"


int main(int argc, char *argv[])
{
    QApplication    app(argc, argv);

    Chart *chart = new Chart;
    chart->setTitle("Vbat and Ibat charge curve (dynamic chart)");
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);
    //chart->setAnimationOptions(QChart::SeriesAnimations);

    //Create a QChartView object with QChart as a parameter.
    //With this way, we don't need to create a QGraphicsView scene ourselves.
    //Set Antialiasing ON to have the rendered lines look nicer.
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    //Set the QChartView as the windows's central widget.
    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();



    return app.exec();

}//End of main.
//__________________________________________________________________________________________________

