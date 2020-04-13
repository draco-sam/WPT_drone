/********************************************************************************
** Form generated from reading UI file 'PrincipalWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRINCIPALWINDOW_H
#define UI_PRINCIPALWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qchartview.h"

QT_BEGIN_NAMESPACE

class Ui_PrincipalWindow
{
public:
    QAction *actionNouveau;
    QAction *actionOuvrir;
    QAction *actionQuitter;
    QAction *actionColler;
    QAction *actiontest;
    QAction *actionAbout;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_5;
    QComboBox *comboBox;
    QPushButton *pushButton_9;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QComboBox *comboBox_2;
    QPushButton *pushButton_8;
    QPushButton *pushButton_10;
    QTextEdit *textEdit;
    QTabWidget *tabWidget;
    QWidget *tab_1;
    QGridLayout *gridLayout;
    QChartView *graphicsView_1;
    QHBoxLayout *horizontalLayout;
    QLineEdit *line_vbat;
    QLineEdit *line_ibat;
    QLineEdit *line_temp_bat;
    QLineEdit *line_temp_die;
    QPushButton *button_start_charge;
    QWidget *tab_2;
    QGridLayout *gridLayout_3;
    QChartView *graphicsView_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QWidget *tab;
    QMenuBar *menubar;
    QMenu *menuFichier;
    QMenu *menuEdition;
    QMenu *menuAide;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *PrincipalWindow)
    {
        if (PrincipalWindow->objectName().isEmpty())
            PrincipalWindow->setObjectName(QString::fromUtf8("PrincipalWindow"));
        PrincipalWindow->resize(1035, 708);
        actionNouveau = new QAction(PrincipalWindow);
        actionNouveau->setObjectName(QString::fromUtf8("actionNouveau"));
        actionOuvrir = new QAction(PrincipalWindow);
        actionOuvrir->setObjectName(QString::fromUtf8("actionOuvrir"));
        actionQuitter = new QAction(PrincipalWindow);
        actionQuitter->setObjectName(QString::fromUtf8("actionQuitter"));
        actionColler = new QAction(PrincipalWindow);
        actionColler->setObjectName(QString::fromUtf8("actionColler"));
        actiontest = new QAction(PrincipalWindow);
        actiontest->setObjectName(QString::fromUtf8("actiontest"));
        actionAbout = new QAction(PrincipalWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        centralwidget = new QWidget(PrincipalWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        gridLayout_5 = new QGridLayout(groupBox);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        comboBox = new QComboBox(groupBox);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout_5->addWidget(comboBox, 0, 0, 1, 1);

        pushButton_9 = new QPushButton(groupBox);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));

        gridLayout_5->addWidget(pushButton_9, 1, 0, 1, 1);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        comboBox_2 = new QComboBox(groupBox_2);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        gridLayout_4->addWidget(comboBox_2, 0, 0, 1, 1);

        pushButton_8 = new QPushButton(groupBox_2);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));

        gridLayout_4->addWidget(pushButton_8, 1, 0, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        pushButton_10 = new QPushButton(centralwidget);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));

        verticalLayout->addWidget(pushButton_10);


        gridLayout_2->addLayout(verticalLayout, 0, 1, 1, 1);

        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setMaximumSize(QSize(16777215, 150));
        textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        textEdit->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        gridLayout_2->addWidget(textEdit, 1, 0, 1, 2);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_1 = new QWidget();
        tab_1->setObjectName(QString::fromUtf8("tab_1"));
        gridLayout = new QGridLayout(tab_1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        graphicsView_1 = new QChartView(tab_1);
        graphicsView_1->setObjectName(QString::fromUtf8("graphicsView_1"));

        gridLayout->addWidget(graphicsView_1, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        line_vbat = new QLineEdit(tab_1);
        line_vbat->setObjectName(QString::fromUtf8("line_vbat"));
        line_vbat->setMaximumSize(QSize(250, 16777215));

        horizontalLayout->addWidget(line_vbat);

        line_ibat = new QLineEdit(tab_1);
        line_ibat->setObjectName(QString::fromUtf8("line_ibat"));
        line_ibat->setMaximumSize(QSize(250, 16777215));

        horizontalLayout->addWidget(line_ibat);

        line_temp_bat = new QLineEdit(tab_1);
        line_temp_bat->setObjectName(QString::fromUtf8("line_temp_bat"));
        line_temp_bat->setMaximumSize(QSize(250, 16777215));

        horizontalLayout->addWidget(line_temp_bat);

        line_temp_die = new QLineEdit(tab_1);
        line_temp_die->setObjectName(QString::fromUtf8("line_temp_die"));
        line_temp_die->setMaximumSize(QSize(250, 16777215));

        horizontalLayout->addWidget(line_temp_die);

        button_start_charge = new QPushButton(tab_1);
        button_start_charge->setObjectName(QString::fromUtf8("button_start_charge"));

        horizontalLayout->addWidget(button_start_charge);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        tabWidget->addTab(tab_1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_3 = new QGridLayout(tab_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        graphicsView_2 = new QChartView(tab_2);
        graphicsView_2->setObjectName(QString::fromUtf8("graphicsView_2"));

        gridLayout_3->addWidget(graphicsView_2, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_5 = new QPushButton(tab_2);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        horizontalLayout_2->addWidget(pushButton_5);

        pushButton_6 = new QPushButton(tab_2);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));

        horizontalLayout_2->addWidget(pushButton_6);

        pushButton_7 = new QPushButton(tab_2);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));

        horizontalLayout_2->addWidget(pushButton_7);


        gridLayout_3->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);

        PrincipalWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PrincipalWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1035, 31));
        menuFichier = new QMenu(menubar);
        menuFichier->setObjectName(QString::fromUtf8("menuFichier"));
        menuEdition = new QMenu(menubar);
        menuEdition->setObjectName(QString::fromUtf8("menuEdition"));
        menuAide = new QMenu(menubar);
        menuAide->setObjectName(QString::fromUtf8("menuAide"));
        PrincipalWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(PrincipalWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        PrincipalWindow->setStatusBar(statusbar);

        menubar->addAction(menuFichier->menuAction());
        menubar->addAction(menuEdition->menuAction());
        menubar->addAction(menuAide->menuAction());
        menuFichier->addSeparator();
        menuFichier->addAction(actionNouveau);
        menuFichier->addAction(actionOuvrir);
        menuFichier->addSeparator();
        menuFichier->addAction(actionQuitter);
        menuEdition->addAction(actionColler);
        menuAide->addAction(actiontest);
        menuAide->addSeparator();
        menuAide->addAction(actionAbout);

        retranslateUi(PrincipalWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PrincipalWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PrincipalWindow)
    {
        PrincipalWindow->setWindowTitle(QCoreApplication::translate("PrincipalWindow", "MainWindow", nullptr));
        actionNouveau->setText(QCoreApplication::translate("PrincipalWindow", "Nouveau", nullptr));
        actionOuvrir->setText(QCoreApplication::translate("PrincipalWindow", "Ouvrir", nullptr));
        actionQuitter->setText(QCoreApplication::translate("PrincipalWindow", "Quitter", nullptr));
        actionColler->setText(QCoreApplication::translate("PrincipalWindow", "Coller", nullptr));
        actiontest->setText(QCoreApplication::translate("PrincipalWindow", "test", nullptr));
        actionAbout->setText(QCoreApplication::translate("PrincipalWindow", "About Sam GUI", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PrincipalWindow", "TM", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("PrincipalWindow", "I2C_start", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("PrincipalWindow", "TM_vbat", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("PrincipalWindow", "TM_ibat", nullptr));

        pushButton_9->setText(QCoreApplication::translate("PrincipalWindow", "Send TM", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("PrincipalWindow", "Command", nullptr));
        pushButton_8->setText(QCoreApplication::translate("PrincipalWindow", "Send CMD", nullptr));
        pushButton_10->setText(QCoreApplication::translate("PrincipalWindow", "Restart COM", nullptr));
        textEdit->setHtml(QCoreApplication::translate("PrincipalWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        button_start_charge->setText(QCoreApplication::translate("PrincipalWindow", "START Charge", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QCoreApplication::translate("PrincipalWindow", "Graph U/I", nullptr));
        pushButton_5->setText(QCoreApplication::translate("PrincipalWindow", "PushButton", nullptr));
        pushButton_6->setText(QCoreApplication::translate("PrincipalWindow", "PushButton", nullptr));
        pushButton_7->setText(QCoreApplication::translate("PrincipalWindow", "PushButton", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("PrincipalWindow", "Graph Coulomb Counter", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("PrincipalWindow", "Configuration", nullptr));
        menuFichier->setTitle(QCoreApplication::translate("PrincipalWindow", "Fichier", nullptr));
        menuEdition->setTitle(QCoreApplication::translate("PrincipalWindow", "Edition", nullptr));
        menuAide->setTitle(QCoreApplication::translate("PrincipalWindow", "Aide", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PrincipalWindow: public Ui_PrincipalWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRINCIPALWINDOW_H
