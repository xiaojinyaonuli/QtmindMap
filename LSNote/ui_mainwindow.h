/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_4;
    QWidget *mainwidget;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QWidget *bar;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnmin;
    QPushButton *btnmax;
    QPushButton *btnclose;
    QSpacerItem *horizontalSpacer_2;
    QWidget *maindisplay;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(810, 583);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(20, 20, 20, 20);
        mainwidget = new QWidget(centralwidget);
        mainwidget->setObjectName(QString::fromUtf8("mainwidget"));
        verticalLayout_6 = new QVBoxLayout(mainwidget);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        bar = new QWidget(mainwidget);
        bar->setObjectName(QString::fromUtf8("bar"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(bar->sizePolicy().hasHeightForWidth());
        bar->setSizePolicy(sizePolicy);
        bar->setMinimumSize(QSize(0, 30));
        horizontalLayout_3 = new QHBoxLayout(bar);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btnmin = new QPushButton(bar);
        btnmin->setObjectName(QString::fromUtf8("btnmin"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnmin->sizePolicy().hasHeightForWidth());
        btnmin->setSizePolicy(sizePolicy1);
        btnmin->setMaximumSize(QSize(12, 12));

        horizontalLayout_2->addWidget(btnmin);

        btnmax = new QPushButton(bar);
        btnmax->setObjectName(QString::fromUtf8("btnmax"));
        sizePolicy1.setHeightForWidth(btnmax->sizePolicy().hasHeightForWidth());
        btnmax->setSizePolicy(sizePolicy1);
        btnmax->setMaximumSize(QSize(12, 12));

        horizontalLayout_2->addWidget(btnmax);

        btnclose = new QPushButton(bar);
        btnclose->setObjectName(QString::fromUtf8("btnclose"));
        sizePolicy1.setHeightForWidth(btnclose->sizePolicy().hasHeightForWidth());
        btnclose->setSizePolicy(sizePolicy1);
        btnclose->setMinimumSize(QSize(0, 0));
        btnclose->setMaximumSize(QSize(12, 12));

        horizontalLayout_2->addWidget(btnclose);

        horizontalSpacer_2 = new QSpacerItem(15, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_5->addWidget(bar);

        maindisplay = new QWidget(mainwidget);
        maindisplay->setObjectName(QString::fromUtf8("maindisplay"));
        maindisplay->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(maindisplay->sizePolicy().hasHeightForWidth());
        maindisplay->setSizePolicy(sizePolicy2);
        verticalLayout_7 = new QVBoxLayout(maindisplay);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(50, 50, 50, 50);

        verticalLayout_7->addLayout(horizontalLayout);


        verticalLayout_5->addWidget(maindisplay);


        verticalLayout_6->addLayout(verticalLayout_5);


        verticalLayout_4->addWidget(mainwidget);


        gridLayout_2->addLayout(verticalLayout_4, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnmin->setText(QString());
        btnmax->setText(QString());
        btnclose->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
