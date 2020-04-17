/***************************************************************************************************
 * File name        : PrincipalWindow.cpp
 * Date             : 20/04/2020
 * Author           : Samuel LORENZINO.
 *
 * Links            :
 *                  :
 *
 * Comments         :   - Vin chargeur à afficher.
 *                      - Coder onglet config.
 *                      - Récupérer l'heure PC et configurer le RTCC dans le PIC RX.
 *                      - Configurer min/max abscisse en fct de l'heure.
 *                      - Bouton reset COM reset le PIC RX.
 **************************************************************************************************/
#include "PrincipalWindow.h"
#include "ui_PrincipalWindow.h"
#include <QtCharts/QSplineSeries>
#include <QDebug>

PrincipalWindow::PrincipalWindow(QWidget *parent) :
    QMainWindow(parent),ui(new Ui::PrincipalWindow),m_chart_v_i(0),m_chart_coulomb(0),m_timer(0),
    m_coeff_v(1),m_coeff_i(1),m_series_v(0),m_series_i(0),m_usb_com(0),m_flag_start_charge(false),
    m_data_usb_str(""),m_vin_str(""),m_vbat_str(""),m_ibat_str(""),m_vbat_time_str(""),
    m_ibat_time_str(""),m_charge_state_suspended_str(""),m_charge_state_precharge_str(""),
    m_charge_status_str(""),m_bat_temp_ntc_str(""),m_charge_temp_die_str(""),m_mouse_click(false)
{
    qDebug()<<endl<<"Bonjour qDebug";

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &PrincipalWindow::usb_tm_multiple);
    //m_timer->start(1500);//ms.

    ui->setupUi(this);

    QObject::connect(ui->button_start_charge,SIGNAL(clicked()),this,
                     SLOT(usb_tc_start_stop_charge()));

    //Stop auto down scrolling of object textEdit with a signal.
    QObject::connect(ui->textEdit,SIGNAL(selectionChanged()),this,SLOT(text_edit_scroll_off()));

    ui->textEdit->setText("Bonjour, I2C LiPo bat graph \n");
    ui->textEdit->append("TM 1 : U/I bat");

    //Creat a USB virtual COM object to communicate with the PIC.
    m_usb_com = new UsbVirtualCom();

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

    ui->statusbar->showMessage("bonjour statusbar");

    check_i2c_charge_on_off();

}
//__________________________________________________________________________________________________

PrincipalWindow::~PrincipalWindow()
{
    delete  m_chart_v_i;
    delete   m_usb_com;
    delete  ui;
}
//__________________________________________________________________________________________________

void PrincipalWindow::check_i2c_charge_on_off(){
/*
 */
    ui->statusbar->clearMessage();
    ui->statusbar->showMessage("test");
    QString str_0 = "",str_1="",str_2="",str_3="",str_4="",str_5="";

    m_usb_com->send_tm(TM_STATE);
    m_usb_com->get_tm_strings(&str_0,&str_1,&str_2,&str_3,&str_4,&str_5);

    if(str_1 == " ch susp : on "){
        ui->button_start_charge->setText("START charge");
        m_flag_start_charge = false;
    }
    else if(str_1 == " ch susp : off "){
        ui->button_start_charge->setText("STOP charge");
        m_flag_start_charge = true;
        m_timer->start(1500);
    }
    ui->textEdit->moveCursor(QTextCursor::End);//!!! Arreter si on clique dans le textEdit !!!
    ui->textEdit->ensureCursorVisible();
    ui->textEdit->append("\ncheck_charge_on_off : "+ str_1 + "\n");
}
//__________________________________________________________________________________________________

void PrincipalWindow::usb_tm_multiple(){
/* Lancer la TM de l'USB vers le PIC.
 * Récupérer et décoder la data port COM.
 *
 */
    qreal x_v = 0.0, x_i = 0.0, y_v = 0.0, y_i = 0.0;
    unsigned int bat_ntc_ratio      = 0;
    unsigned short num_semicolon    = 0;//Compteur de point virgule.
    unsigned short i_str            = 0;

    //Reset all string.
    m_data_usb_str                  = "";
    m_vin_str                       = "";
    m_vbat_str                      = "";
    m_vbat_time_str                 = "";
    m_ibat_str                      = "";
    m_ibat_time_str                 = "";
    m_charge_state_suspended_str    = "";
    m_charge_state_precharge_str    = "";
    m_charge_status_str             = "";
    m_bat_temp_ntc_str              = "";
    m_charge_temp_die_str           = "";;


    //TM request for vbat :
    m_data_usb_str = m_usb_com->send_tm_request(TM_VBAT_MULTIPLE);

    qDebug()<<"m_data_usb_str = "<<endl<<m_data_usb_str;

    //Extract multiple data I2C sending on port USB---------------------------------
    for(int i=0; i < m_data_usb_str.size() ; i++){
        if(m_data_usb_str[i] != '\n'){
            if(m_data_usb_str[i] == ';'){
                num_semicolon++;
                i_str = 0;//Reset index.
            }
            else if(num_semicolon == 0){//Vin charger.
                m_vin_str[i_str] = m_data_usb_str[i];
                i_str++;
            }
            else if(num_semicolon == 1){//Vbat.
                m_vbat_str[i_str] = m_data_usb_str[i];
                i_str++;
            }
            else if(num_semicolon == 2){//Vbat time.
                m_vbat_time_str[i_str] = m_data_usb_str[i];
                i_str++;
            }
            else if(num_semicolon == 3){//Ibat.
                m_ibat_str[i_str] = m_data_usb_str[i];
                i_str++;
            }
            else if(num_semicolon == 4){//Ibat time.
                m_ibat_time_str[i_str] = m_data_usb_str[i];
                i_str++;
            }
            else if(num_semicolon == 5){//Charge state.
                m_charge_state_suspended_str[i_str] = m_data_usb_str[i];
                i_str++;
            }
            else if(num_semicolon == 6){//Charge state.
                m_charge_state_precharge_str[i_str] = m_data_usb_str[i];
                i_str++;
            }
            else if(num_semicolon == 7){//Charge status.
                m_charge_status_str[i_str] = m_data_usb_str[i];
                i_str++;
            }
            else if(num_semicolon == 8){//Bat NTC temperature.
                m_bat_temp_ntc_str[i_str] = m_data_usb_str[i];
                i_str++;
            }
            else if(num_semicolon == 9){//Charge die temperature.
                m_charge_temp_die_str[i_str] = m_data_usb_str[i];
                i_str++;
            }
        }
    }
    //------------------------------------------------------------------------------

    //Convert string to float fort chart.
    y_v = m_vbat_str.toFloat();
    x_v = m_vbat_time_str.toFloat();
    y_i = m_ibat_str.toFloat();
    x_i = m_ibat_time_str.toFloat();

    //Set variable members of the Chart class.
    m_chart_v_i->set_xy_v_i(x_v,y_v,x_i,y_i);

    //Set flag for connect in Chart class.
    m_chart_v_i->set_flag_data_ready(true);

    //Convert string digital value of battery NTC RATIO temperature.
    //get string of the battery temperature with a .csv file.
    bat_ntc_ratio       = m_bat_temp_ntc_str.toInt();
    m_bat_temp_ntc_str  = "";//Reset the string before get_...
    m_bat_temp_ntc_str  = get_string_temp_on_file(bat_ntc_ratio);

    ui->line_vbat->setText("Vbat = " + m_vbat_str + " V : " + m_vbat_time_str +" s");
    ui->line_ibat->setText("ibat = " + m_ibat_str + " A : " + m_ibat_time_str + " s ");
    ui->line_temp_bat->setText("Bat T° = " + m_bat_temp_ntc_str + " °C");
    ui->line_temp_die->setText("Die T° = " + m_charge_temp_die_str + " °C");

    if(m_mouse_click == false){//false = click OFF.
        ui->textEdit->moveCursor(QTextCursor::End);//!!! Arreter si on clique dans le textEdit !!!
    }

    ui->textEdit->ensureCursorVisible();
//    ui->textEdit->append("Vbat = " + QString::number(y_v) + " V : " + QString::number(x_v) +
//                          " s ; ibat = " + QString::number(y_i) + " A : " +
//                          QString::number(x_i) + " s ");
    ui->textEdit->append(m_data_usb_str);

    //textEdit for state and status.....

    ui->statusbar->clearMessage();
    ui->statusbar->showMessage("Charge suspended = " + m_charge_state_suspended_str + " ; " +
                               "Precharge = " + m_charge_state_precharge_str + "; " +
                               "Charge status = " + m_charge_status_str);
}
//__________________________________________________________________________________________________

QString PrincipalWindow::get_string_temp_on_file(unsigned int i_num){
/* Get the string temperature of the battery NTC sensor with a .csv file
 * who contains tabulation temperatures calculated with Steinhart and Hart interpolation laws.
 * The "i_num" input parameter is the number of the virtual box of the table of the file.
 * Each virtual box is separated by a ";".
 */
    //offset = 3258 for first temperature, 70.01 °C, on .csv file.
    //3258 is the digital value of the NTC_RATIO register on LTC4015.
    unsigned short  i_table     = i_num - 3258;
    QString         data_string = "";
    unsigned short  semicolon        = 0;
    QFile file("../gui_graph_dyn/ntc_temp.csv");

    if (!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug()<<"!!! Impossible d'ouvrir le fichier";
        return "file not readable";
    }

    QTextStream text_stream_in (&file);
    QString     text = text_stream_in.readAll();

    //qDebug()<<".csv entier"<<text;

    for(int i=0;i < text.size(); i++){
        if(text[i] == ';'){
            semicolon++;
        }
        else if(text[i] != '\n' & semicolon == i_table){
            data_string.append(text[i]);
        }
    }

    file.close();

    return data_string;

}
//__________________________________________________________________________________________________

void PrincipalWindow::usb_tc_start_stop_charge(){
/*
 */
    if(m_flag_start_charge == false){//Stop to start.
        ui->button_start_charge->setText("STOP charge");//Toggle texte button.
        m_flag_start_charge = true;//Charge starting.
        m_timer->start(1000);//ms.
    }
    else{//Start to stop.
        ui->button_start_charge->setText("START charge");//Toggle texte button.
        m_flag_start_charge = false;//Charge stopping.
        m_timer->stop();//ms.
    }
    m_usb_com->send_tc(TC_START_STOP_CHARGE);
    qDebug()<<"usb_tc_start_stop_charge";
}
//__________________________________________________________________________________________________

void PrincipalWindow::text_edit_scroll_off(){
/* Slot for click event on textEdit obect.
 */
    m_mouse_click = true;
    qDebug()<<" !!! CLICK !!!";
}
//__________________________________________________________________________________________________



