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

int main(int argc, char *argv[])
{
    QApplication    app(argc, argv);

    //QSplineSeries automatically calculates spline segment control points
    //that are needed to properly draw the spline.
    QSplineSeries   *series     = new QSplineSeries();

    series->setName("spline");

    //Add data points to the series :
    series->append(0, 6);
    series->append(2, -4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);

    //Other way to put datas.
    //Using floating point numbers for accuracy
    //*series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

    //Create a QChart object and add the data series to it.
    //Title and the values range on the y-axis.
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle("LiPo battery charching curve");
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(-10,10);//setRange(min,max).
    chart->axes(Qt::Horizontal).first()->setRange(0,200);

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
}
