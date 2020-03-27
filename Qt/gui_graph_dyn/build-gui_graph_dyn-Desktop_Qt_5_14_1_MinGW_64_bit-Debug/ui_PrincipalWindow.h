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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
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
    QTextEdit *textEdit;
    QVBoxLayout *verticalLayout;
    QComboBox *comboBox;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QTabWidget *tabWidget;
    QWidget *tab_1;
    QGridLayout *gridLayout;
    QChartView *graphicsView_1;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QWidget *tab_2;
    QGridLayout *gridLayout_3;
    QChartView *graphicsView_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
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
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setMaximumSize(QSize(16777215, 150));

        gridLayout_2->addWidget(textEdit, 1, 0, 1, 2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout->addWidget(comboBox);

        radioButton = new QRadioButton(centralwidget);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));

        verticalLayout->addWidget(radioButton);

        radioButton_2 = new QRadioButton(centralwidget);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        verticalLayout->addWidget(radioButton_2);

        radioButton_3 = new QRadioButton(centralwidget);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));

        verticalLayout->addWidget(radioButton_3);

        radioButton_4 = new QRadioButton(centralwidget);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));

        verticalLayout->addWidget(radioButton_4);


        gridLayout_2->addLayout(verticalLayout, 0, 1, 1, 1);

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
        pushButton = new QPushButton(tab_1);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(tab_1);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(tab_1);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(tab_1);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        horizontalLayout->addWidget(pushButton_4);


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
        textEdit->setHtml(QCoreApplication::translate("PrincipalWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("PrincipalWindow", "I2C_start", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("PrincipalWindow", "TM_vbat", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("PrincipalWindow", "TM_ibat", nullptr));

        radioButton->setText(QCoreApplication::translate("PrincipalWindow", "RadioButton", nullptr));
        radioButton_2->setText(QCoreApplication::translate("PrincipalWindow", "RadioButton", nullptr));
        radioButton_3->setText(QCoreApplication::translate("PrincipalWindow", "RadioButton", nullptr));
        radioButton_4->setText(QCoreApplication::translate("PrincipalWindow", "RadioButton", nullptr));
        pushButton->setText(QCoreApplication::translate("PrincipalWindow", "PushButton", nullptr));
        pushButton_2->setText(QCoreApplication::translate("PrincipalWindow", "PushButton", nullptr));
        pushButton_3->setText(QCoreApplication::translate("PrincipalWindow", "PushButton", nullptr));
        pushButton_4->setText(QCoreApplication::translate("PrincipalWindow", "PushButton", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QCoreApplication::translate("PrincipalWindow", "Graph U/I", nullptr));
        pushButton_5->setText(QCoreApplication::translate("PrincipalWindow", "PushButton", nullptr));
        pushButton_6->setText(QCoreApplication::translate("PrincipalWindow", "PushButton", nullptr));
        pushButton_7->setText(QCoreApplication::translate("PrincipalWindow", "PushButton", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("PrincipalWindow", "Graph Coulomb Counter", nullptr));
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
