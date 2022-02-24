#include "customobject.h"
#include"mainwindow.h"
#include<QDebug>
#include<QResizeEvent>
#include<QMouseEvent>
#define ASSISTANT
CustomObject::CustomObject()
{

}

///
/// \brief BigButton::BigButton
/// \param iconpath
/// \param describe
/// \param parent
///
BigButton::BigButton(const QString &iconpath, const QString &describe, QWidget *parent)
 :QWidget(parent)
 ,ispressed(false)
{


    iconimage=new QPixmap(iconpath);

    iconlabel=new QLabel(this);

    iconlabel->setPixmap(*iconimage);
    iconlabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    iconlabel->setMinimumSize(100,100);
    iconlabel->setAlignment(Qt::AlignCenter);


    QFont font_= QFont("Consolas",13,75);
    textlabel=new QLabel(this);
    textlabel->setFont(font_);
    textlabel->setText(describe);
    textlabel->setWordWrap(true);
    textlabel->setMinimumHeight(100);
    textlabel->setAlignment(Qt::AlignCenter);

    //#04000000

    indicator=new QWidget(this);
    indicator->resize(50,10);
    indicator->move(this->width()-3,this->height()-20);
    indicator->setStyleSheet(getindiacatorstyle()+QString("background-color:%1").arg(getindiacatorNormallColor()));


    bgwidget=new QWidget(this);

    bgwidget->resize(this->size());//#EE7AE9

    bgwidget->setStyleSheet(getbgstyle()+QString("background-color:%1").arg(getbgNormallColor()));

    bgwidget->lower();

    bgwidget->move(iconlabel->pos());

    bgwidget->show();

    qDebug()<<bgwidget->pos()<<endl;


    QVBoxLayout *layout=new QVBoxLayout(this);

    this->setLayout(layout);

    layout->setContentsMargins(15,35,10,35);

    layout->setSpacing(0);

    layout->addWidget(iconlabel);

    layout->addWidget(textlabel);

    layout->setAlignment(Qt::AlignCenter);

    this->setMinimumHeight(200);




}
///
/// \brief BigButton::setscale
/// \param scale
///
void BigButton::setscale(qreal scale)
{
    iconimage=new QPixmap(iconimage->scaled( iconimage->size()*scale,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    iconlabel->setPixmap(*iconimage);
}

QString BigButton::getbgEnterColor()
{
    return  this->bgentercolor;
}

QString BigButton::getbgNormallColor()
{
    return this->bgnormallcolor;
}

QString BigButton::getbgstyle()
{
    return this->bgstyle;
}

QString BigButton::getindiacatorstyle()
{
    return this->indiacator_style;
}

QString BigButton::getindiacatorNormallColor()
{
    return this->indiactorNormallColor;
}

QString BigButton::getindiactorEnterColor()
{
    return this->indiactorEnterColor;
}

QString BigButton::getbgPressedColor()
{
    return this->bgpressedcolor;
}


void BigButton::enterEvent(QEvent *event)
{
     bgwidget->setStyleSheet(getbgstyle()
                             +QString("background-color:%1").arg(getbgEnterColor()));
     indicator->setStyleSheet(getindiacatorstyle()
                              +QString("background-color:%1").arg(getindiactorEnterColor()));
     animation_indicator=new QPropertyAnimation(indicator,"geometry",this);
     animation_indicator->setDuration(150);
     animation_indicator->setStartValue(indicator->geometry());
     animation_indicator->setEndValue(QRect(this->width()*0.2,this->height()-20,this->width()*0.6,10));
     animation_indicator->setEasingCurve(QEasingCurve::OutBack);
     animation_indicator->start();


}

void BigButton::leaveEvent(QEvent *event)
{
     bgwidget->setStyleSheet(getbgstyle()
                             +QString("background-color:%1").arg(getbgNormallColor()));
     animation_indicator_back=new QPropertyAnimation(indicator,"geometry",this);
     animation_indicator_back->setDuration(150);
     animation_indicator_back->setStartValue(indicator->geometry());
     animation_indicator_back->setEndValue(QRect(this->width()*0.47,this->height()-20,this->width()*0.1,10));
     animation_indicator_back->setEasingCurve(QEasingCurve::OutBack);
     animation_indicator_back->start();

     indicator->setStyleSheet(getindiacatorstyle()
                              +QString("background-color:%1").arg(getindiacatorNormallColor()));



}

void BigButton::resizeEvent(QResizeEvent *event)
{
    qDebug()<<"大小发生改变"<< event->size()<<endl;//布局会默认改变widget的大小尽管你刚开始指定了其大小与位置，通过resizeevent事件去判断是否进行了改变

    //bgwidget->resize(this->size());
    bgwidget->setFixedSize(this->size());

    indicator->resize(this->width()*0.1,10);
    indicator->move(this->width()*0.46,this->height()-20);

}

void BigButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        qDebug()<<"按下"<<endl;
        bgwidget->setStyleSheet(getbgstyle()+QString("background-color:%1").arg(getbgPressedColor()));
        ispressed=true;
        emit clicked();
    }

}

void BigButton::mouseMoveEvent(QMouseEvent *event)
{
    if(ispressed)
    {
        event->accept();//接受bgwidget鼠标移动事件，避免点击bigbutton会出现主界面移动问题
                        //原理：事件的传递顺序 在此接受此事件，便不会传递给bigbutton的父部件
    }
}

void BigButton::mouseReleaseEvent(QMouseEvent *event)
{
    ispressed=false;
    bgwidget->setStyleSheet(getbgstyle()+QString("background-color:%1").arg(getbgEnterColor()));
}






///
/// \brief Assistant::SetPushButtonQss
/// \param btn
/// \param radius
/// \param bgnormallcolor
/// \param bghovercolor
/// \param pressedColor
///
#ifdef ASSISTANT
void Assistant::SetPushButtonQss(QPushButton *btn,
                                 int radius,
                                 const QString &bgnormallcolor,
                                 const QString &bghovercolor,
                                 const QString &pressedColor)
{
    QStringList btnqss;

    btnqss.append(QString("QPushButton{border-radius:%1px;background-color:%2;}").arg(radius).arg(bgnormallcolor));

    QString qss=btnqss.join(" ");
    btn->setStyleSheet(qss);

}

void Assistant::SetWidgetQss(QWidget *widget, int radius, const QString &background)
{
    QStringList btnqss;

    btnqss.append(QString("QWidget{border-radius:%1px;background-color:%2;}").arg(radius).arg(background));

    QString qss=btnqss.join(" ");
    widget->setStyleSheet(qss);
}
#endif

///
/// \brief CommonSmallButton::CommonSmallButton
/// \param btnname
/// \param iconpath
/// \param parent
///

CommonSmallButton::CommonSmallButton(const QString &btnname,
                                     const QString &iconpath,
                                     const qreal &wantrotateangle,
                                     const bool isrotate,
                                     const int radius,
                                     QWidget *parent):QPushButton(parent),
                                     m_btnname(btnname),
                                     BgColor(LeaveColor),
                                     rotateangle(0),
                                     ispressed(false),
                                     isrotate_(isrotate),
                                     radius(radius),
                                     wantrotateangle_(wantrotateangle)
{


     renderer=new QSvgRenderer();
     renderer->load(iconpath);
     QSize size=renderer->defaultSize();
     this->setText(btnname);
     iconlabel=new QLabel(this);
     iconimage=new QPixmap(size);
     iconimage->fill(Qt::transparent);//设置背景透明
     QPainter painter(iconimage);
     painter.setRenderHints(QPainter::Antialiasing);
     renderer->render(&painter);
     QFont font= QFont("Consolas",12,70);
     this->setFont(font);
     QFontMetrics fm(font);
     QRect rec = fm.boundingRect(m_btnname);

     //字符串所占的像素宽度,高度
     btnnametWidth = rec.width();
     btnnameHeight= fm.lineSpacing();
     rotate=new QPropertyAnimation(this,"rotationAngle");

     connect(rotate,SIGNAL(valueChanged(QVariant)),this,SLOT(slot_paintline(QVariant))
             );
     //connect(rotate,SIGNAL(finished()),this,SLOT(Slot_AnimationFinsh()));


}

void CommonSmallButton::SetBgcolor(const QColor &color)
{
    BgColor=color;
}

void CommonSmallButton::Setleavecolor(const QColor color)
{
    this->LeaveColor=color;
}

void CommonSmallButton::setRotationAngle(qreal angle)
{
    rotateangle = angle;update();
}

void CommonSmallButton::paintEvent(QPaintEvent *)
{
    resize(height(), height());
    QPainter painterbg(this);
    painterbg.save();
    painterbg.setPen(Qt::NoPen);
    painterbg.setBrush(BgColor);
    painterbg.setRenderHint(QPainter::Antialiasing,true);
    painterbg.drawRoundedRect(this->rect(),radius,radius);
    painterbg.restore();


    QPainter p(this);
    p.save();
    p.setRenderHint(QPainter::Antialiasing);
    p.translate(width()/2,height()/2);
    p.rotate(rotateangle);
    p.translate(-width()/2,-height()/2);//将原点复位  qt坐标轴向上是- 向左是-
    int w = iconSizeRate * width();
    int h = iconSizeRate * height();
    p.drawPixmap(width() / 2 - w / 2, height() / 2 - h / 2, w, h, *iconimage);
    p.drawText(width()/2-btnnametWidth/2,height()/2+btnnameHeight/2-5,m_btnname);

    p.restore();
}

void CommonSmallButton::enterEvent(QEvent *event)
{
    if(this->isEnabled())
    {
        SetBgcolor(EnterColor);
        update();
    }



}

void CommonSmallButton::leaveEvent(QEvent *event)
{
    SetBgcolor(LeaveColor);
    update();
}

void CommonSmallButton::mousePressEvent(QMouseEvent *event)
{

    iconSizeRate-=0.1;
    ispressed=true;
    if(ispressed)
    {
        SetBgcolor(PressColor);
    }
    setFocus();

   if(isrotate_&&ispressed)
   {
       rotate=new QPropertyAnimation(this,"rotationAngle");
       rotate->setStartValue(0);
       rotate->setDuration(800);
       rotate->setEasingCurve(QEasingCurve::OutBack);
       rotate->setEndValue(wantrotateangle_);
       rotate->start();
       connect(rotate,SIGNAL(finished()),this,SLOT(Slot_AnimationFinsh()));
   }
   if(!isrotate_&&ispressed)
   {

       emit clicked();
   }

}

void CommonSmallButton::mouseMoveEvent(QMouseEvent *event)
{
    if(ispressed)
    {
        event->accept();
    }
}

void CommonSmallButton::mouseReleaseEvent(QMouseEvent *event)
{

    iconSizeRate+=0.1;
    ispressed=false;
    if(!ispressed)
    {
        SetBgcolor(LeaveColor);
    }

}

void CommonSmallButton::resizeEvent(QResizeEvent *event)
{
    update();
}

void CommonSmallButton::Slot_AnimationFinsh()
{
    emit clicked();

}

void CommonSmallButton::slot_paintline(QVariant a)
{

}

void CommonSmallButton::slot_Isrotatefinsh()
{
    ispressed=true;


}

void CommonSmallButton::slot_animationfinsh()
{
    this->isrotate_=false;

}








///
/// \brief InputText::InputText       InPutText
/// \param Qlabelname
/// \param parent
///

InputText::InputText(const QString &Qlabelname,const QString &inputstring,bool Enable,QWidget *parent)
    :QWidget(parent),
    firstinput(inputstring),
    IsPressed(false),
    EnableEndit(Enable)

{
    QFont font=QFont("Consolas",12);
    describe=new QLabel(this);
    QFontMetrics fm(Qlabelname);
    qreal height = fm.lineSpacing();
    describe->setFont(font);
    describe->setText(Qlabelname);
    describe->setFixedHeight(height+10);
    describe->setStyleSheet("color:#1c1c1c;background-color:#00000000;");


    QFont textfont=QFont("Consolas",12);
    textinput=new QLineEdit(this);
    textinput->setFont(textfont);
    textinput->setText(inputstring);
    textinput->setReadOnly(true);
    textinput->setFixedHeight(height);
    textinput->setStyleSheet("color:#5c5c5c;background-color:#00000000;border-style:none;");


    bgwidget=new QWidget(this);
    bgwidget->resize(this->size());
    Assistant::SetWidgetQss(bgwidget,5,"#00000000");
    bgwidget->lower();
    bgwidget->show();


    indicator=new QWidget(this);
    indicator->setFixedHeight(6);
    Assistant::SetWidgetQss(indicator,5,"#4876FF");
    indicator->show();

//    monitor=new MyThread(NULL);
    emit Etext(firstinput);
    this->setFixedHeight(describe->height()+10);

    LinetextConnect();

}

void InputText::EnterAnimation()
{

    textinput->setCursorPosition(textinput->text().length());
    textinput->setStyleSheet("color:#080808;background-color:#00000000;border-style:none;");
    EnterGroup=new QParallelAnimationGroup(this);
    Eindicatoranimation=new QPropertyAnimation(indicator,"geometry",this);
    Etextinputanimation=new QPropertyAnimation(textinput,"geometry",this);

    Eindicatoranimation->setDuration(600);
    Eindicatoranimation->setStartValue(indicator->geometry());
    Eindicatoranimation->setEasingCurve(QEasingCurve::InOutExpo);
    Eindicatoranimation->setEndValue(QRect(this->width()*0.3+2,this->height()-7,this->width()*0.7,6));

    Etextinputanimation->setDuration(600);
    Etextinputanimation->setStartValue(textinput->geometry());
    Etextinputanimation->setEasingCurve(QEasingCurve::InOutExpo);
    Etextinputanimation->setEndValue(QRect(this->width()*0.3,this->height()/2-textinput->height()/2,this->width()*0.7,textinput->height()));

    EnterGroup->addAnimation(Eindicatoranimation);
    EnterGroup->addAnimation(Etextinputanimation);
    EnterGroup->start();

}

void InputText::LeaveAnimation()
{
    textinput->setStyleSheet("color:#5c5c5c;background-color:#00000000;border-style:none;");
    textinput->setCursorPosition(0);
    LeaveGroup=new QParallelAnimationGroup(this);
    Lindicatoranimation=new QPropertyAnimation(indicator,"geometry",this);
    Ltextinputanimation=new QPropertyAnimation(textinput,"geometry",this);

    Lindicatoranimation->setDuration(600);
    Lindicatoranimation->setStartValue(indicator->geometry());
    Lindicatoranimation->setEasingCurve(QEasingCurve::InOutExpo);
    Lindicatoranimation->setEndValue(QRect(this->width(),this->height()-7,this->width()*0.1,6));

    int width = QFontMetrics(textinput->font()).size(Qt::TextSingleLine, textinput->text()).width()+1;

    Ltextinputanimation->setDuration(600);
    Ltextinputanimation->setStartValue(textinput->geometry());
    Ltextinputanimation->setEasingCurve(QEasingCurve::InOutExpo);
    width>this->width()*0.7?Ltextinputanimation->setEndValue(QRect(this->width()*0.3+30,this->height()/2-textinput->height()/2,this->width()*0.7,textinput->height()))
                          :Ltextinputanimation->setEndValue(QRect(this->width()-width,this->height()/2-textinput->height()/2,this->width()*0.5,textinput->height()));

    LeaveGroup->addAnimation(Lindicatoranimation);
    LeaveGroup->addAnimation(Ltextinputanimation);
    LeaveGroup->start();

}

void InputText::LinetextConnect()
{

    connect(textinput,&QLineEdit::editingFinished,this,&InputText::EditFinshed);



}

void InputText::SetResize(QWidget *parent)
{
    //

}

void InputText::SetTextLine(const QString &text)
{
    textinput->setText(text);

}

QString InputText::getText() const
{
    return textinput->text();

}

QLineEdit *InputText::gettextinput() const
{
    return this->textinput;

}

//void InputText::setLinetext(const QString &text)
//{
//    textinput->setText(text);

//}

void InputText::enterEvent(QEvent *event)
{

    Assistant::SetWidgetQss(bgwidget,5,"#E0EEEE");



}

void InputText::resizeEvent(QResizeEvent *event)
{
    int width = QFontMetrics(textinput->font()).size(Qt::TextSingleLine, textinput->text()).width()+1;
    describe->move(5,this->height()/2-describe->height()/2);
    width>this->width()*0.7?textinput->resize(this->width()*0.7,textinput->height())
                          : textinput->resize(this->width()*0.4,textinput->height());
    width>this->width()*0.7?textinput->move(this->width()*0.3+30,this->height()/2-textinput->height()/2)
                          :textinput->move(this->width()-width,this->height()/2-textinput->height()/2);

    indicator->resize(this->width()*0.1,indicator->height());
    indicator->move(this->width(),this->height()-7);
    Assistant::SetWidgetQss(indicator,10,"#4876FF");
    bgwidget->resize(this->size());

}

void InputText::leaveEvent(QEvent *event)
{
    IsPressed=false;
    if(!IsEdit)
    {
        Assistant::SetWidgetQss(bgwidget,5,"#00000000");
    }

}

void InputText::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        IsPressed=true;

    }

}

void InputText::mouseReleaseEvent(QMouseEvent *event)
{
    if(IsPressed&&EnableEndit)
    {
       EnterAnimation();
       IsPressed=false;
       textinput->setReadOnly(false);
       textinput->raise();
       textinput->setFocus();

//       qDebug()<<"当前线程"<<(int)GetCurrentThread()<<endl;
       IsEdit=true;
    }



}

void InputText::mouseMoveEvent(QMouseEvent *event)
{
    if(IsPressed)
    {
        event->accept();
    }

}

void InputText::EditFinshed()
{
    LeaveAnimation();
    IsEdit=false;
    textinput->setReadOnly(true);


}

void InputText::EditJudge()
{
    if(textinput->text()!=firstinput)
    {
        emit Judge(true);
    }

}







///--------------------------------------------------------------------------
/// \brief MyThread::MyThread
///子线程--------------------------------------------------------------------
MyThread::MyThread(QObject *par):QThread(par)
{

    isStop=false;


}

void MyThread::ThreadStart(const QString & s)
{

    if(!this->isRunning())
    {

        this->start();
        str=s;
    }
    else
    {
        str=s;
        return;
    }



}


void MyThread::ThreadStop()
{
    QMutexLocker loker(&mutex);
    isStop=true;
}

void MyThread::run()
{
    isStop=false;
    while(!isStop)
    {
//        qDebug()<<"子线程在运行"<<(int)currentThread()<<endl;
//        qDebug()<<str<<endl;
        mutex.lock();

        if(str!=""&&str!=FirstText)
        {
            emit textinformation(str,true);
        }else
        {
            emit textinformation(str,false);
        }
        mutex.unlock();

        msleep(500);
    }


}

void MyThread::Judgetext(const QString text)
{
    this->FirstText=text;

}


///-------------------------------------------------------------------
/// \brief GraphItemThread::GraphItemThread 判断item文字线程
/// -------------------------------------------------------------------
///

GraphItemThread::GraphItemThread(QObject *par):QThread(par)
{

    isStop=false;

}

void GraphItemThread::ThreadStart(const QString &s)
{


}

void GraphItemThread::ThreadStop()
{

}

void GraphItemThread::run()
{

}
