#include "mywidget.h"
#include "ui_mywidget.h"
#include<QPalette>
#include<QPainter>
#include<QDebug>
#include<QTimer>
#include<QPropertyAnimation>
MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    this->setMouseTracking(true);
    ui->widget->setMouseTracking(true);
     //ui->widget->setStyleSheet(QString("#widget{background-color:#E0EEEE;border-radius:15px;}"));
//    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
//          animation->setDuration(5000);
//          animation->setStartValue(QRect(0, 0, 500,500 ));
//          animation->setEndValue(QRect(250, 250, 500, 500));

//          animation->start();
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);//重写绘画事件，绘制widget背景颜色，与圆角边框
    painter.setRenderHint(QPainter::Antialiasing);//反锯齿
    painter.setPen(Getwidgetnormallcolor());
    painter.setBrush(Getwidgetnormallcolor());
    QRect rect=this->rect();
    rect.setWidth(rect.width()-1);
    rect.setHeight(rect.height()-1);
    painter.drawRoundedRect(rect,15,15);
    QWidget::paintEvent(event);

}

void MyWidget::enterEvent(QEvent *event)
{



    qDebug()<<"鼠标进入!***********"<<endl;
    //this->Setwidgetnormallcolor(Getwdigetentercolor());
    update();

}

void MyWidget::leaveEvent(QEvent *event)
{
    this->Setwidgetnormallcolor(QColor("#E0EEEE"));
    qDebug()<<"鼠标离开!***********"<<endl;
    update();
}

QColor MyWidget::Getwidgetnormallcolor()
{
    return this->widgetnormallcolor;
}

QColor MyWidget::Getwdigetentercolor()
{
    return this->wdigetentercolor;
}

void MyWidget::Setwidgetnormallcolor(QColor color)
{
    this->widgetnormallcolor=color;

}


void MyWidget::on_pushButton_clicked()
{
    this->setGeometry(80,80,80,80);
}
