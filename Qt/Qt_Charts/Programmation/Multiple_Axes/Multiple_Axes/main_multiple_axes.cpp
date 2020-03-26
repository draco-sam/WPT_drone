/***************************************************************************************************
 * File name        : main_multiple_axes.cpp
 * Date             : 26/03/2020
 * Author           : Samuel LORENZINO.
 *
 * Links            : https://doc.qt.io/qt-5/qtcharts-index.html
 *                  : https://doc.qt.io/qt-5/qtcharts-multiaxis-example.html
 *
 * Comments         :
 **************************************************************************************************/

#include <QApplication>
#include <QtCharts>
#include <QDebug>



int main(int argc, char *argv[])
{
    QApplication    app(argc, argv);

    //Create the QChart instance, hide the legend of the chart, and set its title.
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->setTitle("Multiaxis chart example");
    //---------------------------------------------------------------------------------

    //Creat horizontal axis shared between series.
    //Each series have only 1 vertical (and horizontal ??) axis.
    QValueAxis *axisX = new QValueAxis;
    axisX->setTickCount(10);//Grid of the X axis.
    chart->addAxis(axisX, Qt::AlignBottom);
    //-------------------------------------------------------------

    //Creat first series and add data to it.
    //Add series to the chart.
    //Instantiate its own Y axis.
    //Attach Y and X axis to the series.
    QSplineSeries *series_a = new QSplineSeries;
    *series_a << QPointF(1, 5) << QPointF(3.5, 18) << QPointF(4.8, 7.5) << QPointF(10, 2.5);
    chart->addSeries(series_a);

    QValueAxis *axis_y_a = new QValueAxis;
    axis_y_a->setLinePenColor(series_a->pen().color());//Same colore axis line and series.

    chart->addAxis(axis_y_a, Qt::AlignLeft);
    series_a->attachAxis(axisX);
    series_a->attachAxis(axis_y_a);
    //-----------------------------------------------------------------------------------------

    //Similar preparation to another series.
    QSplineSeries *series_b = new QSplineSeries;
    *series_b << QPointF(1, 0.5) << QPointF(1.5, 4.5) << QPointF(2.4, 2.5) << QPointF(4.3, 12.5)
            << QPointF(5.2, 3.5) << QPointF(7.4, 16.5) << QPointF(8.3, 7.5) << QPointF(10, 17);
    chart->addSeries(series_b);

    QValueAxis *axis_y_b = new QValueAxis;
    axis_y_b->setLinePenColor(series_b->pen().color());//Same colore axis line and series.

    chart->addAxis(axis_y_b, Qt::AlignRight);//Axies placed at the right of the chart.
    series_b->attachAxis(axisX);
    series_b->attachAxis(axis_y_b);
    //-------------------------------------------------------------------------------------------

    //Create QChartView object with QChart as parameter.
    //Enable Antialiasing for nice redering.
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    //----------------------------------------------------

    //Chart ready to be shown.
    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(800, 600);
    window.show();


    return app.exec();

}//End of main.
//__________________________________________________________________________________________________

