#include "PrincipalWindow.h"
#include "ui_PrincipalWindow.h"

PrincipalWindow::PrincipalWindow(QWidget *parent) :
    QMainWindow(parent),ui(new Ui::PrincipalWindow),m_chart_v_i(0),m_chart_coulomb(0)
{
    ui->setupUi(this);

    //-----------------------------------------------------------------------------------
    //Code pour créer un graph dynamique à placer dans un onglet du GUI :
    //------------------------------------------------------------------
    m_chart_v_i = new Chart();//Allocation mémoire pour objet.

    m_chart_v_i->setTitle("Vbat and Ibat charge curve (dynamic chart)");
    //m_chart_v_i->legend()->hide();
    m_chart_v_i->setAnimationOptions(QChart::AllAnimations);

    //Create a QChartView object with QChart as a parameter.
    //With this way, we don't need to create a QGraphicsView scene ourselves.
    //Set Antialiasing ON to have the rendered lines look nicer.
    ui->graphicsView_1 = new QChartView(m_chart_v_i,ui->tab_1);
    ui->graphicsView_1->setObjectName(QString::fromUtf8("graphicsView_1"));
    ui->graphicsView_1->setRenderHint(QPainter::Antialiasing);

    ui->gridLayout->addWidget(ui->graphicsView_1, 0, 0, 1, 1);
    //-----------------------------------------------------------------------------------
}

PrincipalWindow::~PrincipalWindow()
{
    delete  m_chart_v_i;
    delete  ui;
}
