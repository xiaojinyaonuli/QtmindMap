#include "custompage.h"
#include "qapplication.h"
#include<QResizeEvent>
#include<QPalette>
#include<QPainter>
#include<QDebug>
#include<QTimer>
#include<QPropertyAnimation>
#include<QGraphicsDropShadowEffect>
#include<QMutex>
#include<QVBoxLayout>
#include <QSplitter>
#include"customobject.h"
#include"customitem.h"


CustomPage::CustomPage(bool isshadow,bool isroundrect,QWidget *parent) :
    IsShadow(isshadow),
    IsRoundrect(isroundrect),
    QWidget(parent)


{

    widget_shadow=new QGraphicsDropShadowEffect(this);
    widget_shadow->setOffset(2,0);

    widget_shadow->setColor(QColor("#080808"));

    widget_shadow->setBlurRadius(10);
    this->setMouseTracking(true);


}

void CustomPage::setNormallColor(const QString &color)
{
    this->normallcolor=color;

}


void CustomPage::resizeEvent(QResizeEvent *event)
{
    update();
}

void CustomPage::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);//重写绘画事件，绘制widget背景颜色，与圆角边框
    painter.setRenderHint(QPainter::Antialiasing);//反锯齿
    painter.setPen(Qt::NoPen);
    painter.setBrush(normallcolor);
    QRect rect=this->rect();
    rect.setWidth(rect.width()-1);
    rect.setHeight(rect.height()-1);
    if(IsRoundrect)
    {
        painter.drawRoundedRect(rect,15,15);

    }else
    {

        painter.drawRect(rect);

    }
    this->setGraphicsEffect(widget_shadow);

    QWidget::paintEvent(event);



}







//------------------------------------------------------------------------------------------------



void MyCanvas::InitObject()
{
    appearbtn=new QPushButton(this);
    appearbtn->setFixedSize(25,42);
    appearbtn->setIconSize(QSize(25,42));
    appearbtn->setIcon(QIcon(":/image/appear.png"));
    appearbtn->setStyleSheet("border:none;");
    appearbtn->hide();


    view->setStyleSheet("border:0px");
    view->setGeometry(20,20,200,200);
    view->setDragMode(QGraphicsView::NoDrag);
    view->show();
    setOptionsMenu();
    InfomationPage();
    CommonbtnConnects();

}

void MyCanvas::saveToFile(const QString &path)
{
    QFile output(path);
    output.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream ts(&output);
    ts << "STARTAFNTHYRTY=\n";
    ts << _canvasname << "\n";
    ts << _canvasdesc << "\n";
    ts << _time << "\n";
//    ts << structure_type << " " << type << "\n";
    view->saveToFile(ts);
    output.close();

}

MyCanvas::MyCanvas(QString CanvasName, QString CanvasDescribe, QString Time,QWidget *parent)
    :QWidget(parent),
     _canvasname(CanvasName),
     _canvasdesc(CanvasDescribe),
     _time(Time)

{
    this->setMouseTracking(true);
    view=new QWGraphicsView(true,this);
    InitObject();

}

MyCanvas::MyCanvas(QTextStream &ts, QWidget *parent)
    :QWidget(parent)
{
    this->setMouseTracking(true);
    _canvasname=ts.readLine();
    _canvasdesc=ts.readLine();
    _time=ts.readLine();
    view=new QWGraphicsView(false,this);
    InitObject();
    this->view->readFromFile(ts);

}

void MyCanvas::setOptionsMenu()
{
    Optionsmeun=new CustomPage(false,false,this);
    Optionsmeun->setNormallColor("#CDC9A5");
    QVBoxLayout *layout=new QVBoxLayout(Optionsmeun);
    //Optionsmeun->setLayout(layout);
    backbtn=new CommonSmallButton("",":/image/zuoceoption.svg",0,false,10,Optionsmeun);
    optionInfo =new CommonSmallButton("",":/image/information.svg",0,false,10,Optionsmeun);
    Savebtn=new CommonSmallButton("",":/image/save.svg",0,false,10,Optionsmeun);
    MainPage=new CommonSmallButton("",":/image/main.svg",0,false,10,Optionsmeun);
    btnlist.append(backbtn);
    btnlist.append(optionInfo);
    btnlist.append(Savebtn);
    btnlist.append(MainPage);
    foreach (CommonSmallButton *btn, btnlist) {
        btn->setFixedSize(30,30);
        btn->SetBgcolor("#CDC9A5");
        btn->Setleavecolor("#CDC9A5");
    }

    //layout->addWidget(backbtn);
    Optionsmeun->show();

}

void MyCanvas::CommonbtnConnects()
{
    connect(appearbtn,&QPushButton::clicked,Optionsmeun,[=](){
        if(appearpageani==nullptr)
        {
            appearpageani=new QPropertyAnimation(Optionsmeun,"geometry",this);
        }
        appearbtn->hide();
        Optionsmeun->show();
        appearpageani->setStartValue(Optionsmeun->geometry());
        appearpageani->setDuration(400);
        appearpageani->setEasingCurve(QEasingCurve::InOutExpo);
        appearpageani->setEndValue(QRect(this->geometry().width()-(this->geometry().width()*0.03),this->rect().height()*0.15,
                                       this->geometry().width()*0.05,this->rect().height()*0.7));
        appearpageani->start();
        opIsresize=true;
    });

    connect(backbtn,&CommonSmallButton::clicked,Optionsmeun,[=](){
        if(backpageani==nullptr)
        {
            backpageani=new QPropertyAnimation(Optionsmeun,"geometry",this);
        }
        backpageani->setStartValue(Optionsmeun->geometry());
        backpageani->setDuration(400);
        backpageani->setEasingCurve(QEasingCurve::InOutExpo);
        backpageani->setEndValue(QRect(this->geometry().width(),this->rect().height()*0.15,
                                       this->geometry().width()*0.05,this->rect().height()*0.7));
        backpageani->start();

        opIsresize=false;
        connect(backpageani,&QPropertyAnimation::finished,appearbtn,[=](){
            Optionsmeun->hide();
            appearbtn->show();
        });


        connect(optionInfo,&CommonSmallButton::clicked,InfoPage,[=](){

            InfoPage->show();
            if(InfoPageani==nullptr)
            {
                InfoPageani=new QPropertyAnimation(InfoPage,"geometry",this);
            }
            InfoPageani->setStartValue(InfoPage->geometry());
            InfoPageani->setDuration(400);
            InfoPageani->setEasingCurve(QEasingCurve::InOutExpo);
            InfoPageani->setEndValue(QRect(0,0,this->geometry().width()*0.3,this->height()));
            InfoPageani->start();


        });
        connect(InfoPageBack,&CommonSmallButton::clicked,InfoPage,[=](){
            if(InfoPageaniback==nullptr)
            {
                InfoPageaniback=new QPropertyAnimation(InfoPage,"geometry",this);
            }
            InfoPageaniback->setStartValue(InfoPage->geometry());
            InfoPageaniback->setDuration(400);
            InfoPageaniback->setEasingCurve(QEasingCurve::InOutExpo);
            InfoPageaniback->setEndValue(QRect(0,0,0,this->height()));
            InfoPageaniback->start();
        });

        connect(Savebtn,&CommonSmallButton::clicked,this,[=](){
            QString Path = QFileDialog::getSaveFileName(this, tr("Save jsh"), " ", tr("jsh file(*.jsh)"));
            if(!Path.isEmpty())
                saveToFile(Path);
        });
        connect(MainPage,&CommonSmallButton::clicked,this,[=](){
            this->hide();
            delete this;
        });



    });



}

void MyCanvas::InfomationPage()
{
    InfoPage=new CustomPage(false,true,this);
    InfoPage->setNormallColor("#F0FFFF");
    QVBoxLayout *vlayout=new QVBoxLayout(InfoPage);
    //Assistant::SetWidgetQss(InfoPage,15,"#F0FFFF")
    InfoPageBack=new CommonSmallButton("",":/image/qianjin.svg",180,true,15,InfoPage);//这里点击按钮一次后 图片旋转过来，就一直保持旋转的角度 没有复原 待改进

    InfoPageBack->setMinimumSize(40,40);

    FileName=new InputText("FileName:",_canvasname,false,InfoPage);
    FileDescribe=new InputText("FileDescribe:",_canvasdesc,false,InfoPage);
    CreatTime=new InputText("CreatTime:",_time,false,InfoPage);

    InfoPage->setLayout(vlayout);
    InfoPageBack->move(InfoPage->width()-InfoPageBack->width()-5,0);
    vlayout->setSpacing(0);
    vlayout->setContentsMargins(0,0,50,350);

    vlayout->addWidget(InfoPageBack);
    vlayout->addWidget(FileName);
    vlayout->addWidget(FileDescribe);
    vlayout->addWidget(CreatTime);
    //vlayout->setAlignment(Qt::AlignRight); //就是因为这句 布局出错 reasion: 暂时不知道
    InfoPage->resize(0,this->height());
    InfoPage->setMouseTracking(true);
    InfoPage->hide();

}

void MyCanvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);//重写绘画事件，绘制widget背景颜色，与圆角边框
    painter.setRenderHint(QPainter::Antialiasing);//反锯齿
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#F0FFFF"));//#F0FFFF#FF83FA
    QRect rect=this->rect();
    rect.setWidth(rect.width()-1);
    rect.setHeight(rect.height()-1);
    painter.drawRoundedRect(rect,15,15);
    QWidget::paintEvent(event);


}

void MyCanvas::showEvent(QShowEvent *event)
{
    Optionsmeun->move(this->geometry().width()-(this->geometry().width()*0.03),this->rect().height()*0.15);


}

void MyCanvas::resizeEvent(QResizeEvent *event)
{

   Optionsmeun->resize(this->geometry().width()*0.05,this->rect().height()*0.7);

   Optionsmeun->move(this->geometry().width()-(this->geometry().width()*0.03),this->rect().height()*0.15);

   InfoPage->resize(0,this->height());
   for (int i=1;i<btnlist.count()+1;++i) {
       btnlist[i-1]->move(OFFESTSIZE,OFFESTSIZE*6*(i-1)+OFFESTSIZE*(i-1));
   }
   view->resize(this->geometry().width()-40,this->rect().height()-40);
   appearbtn->move(this->geometry().width()-25,this->geometry().height()/2);
   //resizeEvent(event);
}




//--------------------------------------------------------------------------------

MaskWidget::MaskWidget(QWidget *parent):QWidget(parent)
{
    this->setPalette(Qt::black);
    this->setWindowOpacity(0.2);//设置窗口透明度
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉标题栏

}

void MaskWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);//重写绘画事件，绘制widget背景颜色，与圆角边框
    painter.setRenderHint(QPainter::Antialiasing);//反锯齿
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.setOpacity(0.4);
    QRect rect=this->rect();
    rect.setWidth(rect.width()-1);
    rect.setHeight(rect.height()-1);
    painter.drawRoundedRect(rect,15,15);
    QWidget::paintEvent(event);
}




