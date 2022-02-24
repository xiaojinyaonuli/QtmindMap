#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"customobject.h"
#include<QDebug>
#include<QRect>
#include<QEvent>
#include<QGraphicsDropShadowEffect>
#include<QHBoxLayout>
#include<QRegion>
#include<QDateTime>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,CursorCurrentState(NONE)
    ,OnSeeState(false)
    ,OnSeeState_Creat(false)
{


    ui->setupUi(this);

    ui->centralwidget->setMouseTracking(true);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    ui->mainwidget->setStyleSheet(QString("#mainwidget{background-color:#F0FFFF;border-radius:15px;}"));
    this->setMouseTracking(true);
    this->resize(1280,800);

    /*page=new QWidget(ui->mainwidget);
    page->resize(this->width()/2,this->height()-5);
    page->setStyleSheet("border-radius:15px;background-color:#EE7AE9;");*/

    initmousetrack();//设置mainwidget子控件跟踪
    initshadow();//初始化外边框阴影
    init_mainwidget_doublebutton();//初始化主界面双按钮
    SetAboutWidget();//设置关于作者按钮初始化
    setAboutAuthor();
    CommonSmallConnect();
    testinterface(); //测试
//    qDebug()<<this->height()<<"hah 2"<<endl;

    //QTimer::singleShot(1000, this, SLOT(initFormMask()));
    Assistant::SetPushButtonQss(ui->btnmin,5,"#FF00FF","","");
    Assistant::SetPushButtonQss(ui->btnmax,5,"#FF00FF","","");
    Assistant::SetPushButtonQss(ui->btnclose,5,"#FF00FF","","");

    mShadeWindow=new MaskWidget(ui->mainwidget);
    mShadeWindow->setGeometry(this->geometry());
    mShadeWindow->hide();
    connect(Creatbtn,&BigButton::clicked,this,[=](){

        //page->show();
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initmousetrack()
{
    QList<QWidget *> list=ui->centralwidget->findChildren<QWidget*>();

    ui->maindisplay->setMouseTracking(true);
    ui->mainwidget->setMouseTracking(true);

}

void MainWindow::init_mainwidget_doublebutton()
{



    Creatbtn=new BigButton(":/image/creat (2).png","ADD NEW",ui->maindisplay);


    Creatbtn->setscale(0.6);

    btn=new BigButton(":/image/openp.png","Open File",ui->maindisplay);

    btn->setscale(0.6);


    ui->horizontalLayout->setContentsMargins(150,200,150,150);

    ui->horizontalLayout->setSpacing(60);



    ui->horizontalLayout->addWidget(Creatbtn);

    ui->horizontalLayout->addWidget(btn);

    qDebug()<<Creatbtn->height()<<Creatbtn->width()<<endl;



}

///
/// \brief MainWindow::SetAboutWidget
///  设置about页按钮布局(主界面)
void MainWindow::SetAboutWidget()
{

   About=new QWidget(ui->maindisplay);
   About->setObjectName("ABOUT_PAGE");
   QHBoxLayout *Hlayout=new QHBoxLayout(About);
   SetButton=new CommonSmallButton("",":/image/shezhi.svg",360,true,15,About);//设置按钮
   AuthorButton=new CommonSmallButton("",":/image/author3.svg",360,true,15,About);//作者按钮
   SetButton->setMinimumSize(40,40);
   AuthorButton->setMinimumSize(40,40);

   //text
   QLabel *text=new QLabel(About);
   QFont font_= QFont("Consolas",20,75);//Corbel
   text->setFont(font_);
   text->setText(Authorinformation);
   text->setWordWrap(true);
   text->setMinimumWidth(25);
   text->setMinimumHeight(75);
   text->setAlignment(Qt::AlignCenter);

   //set layout
   About->setLayout(Hlayout);
   Hlayout->setSpacing(5);
   Hlayout->addWidget(text);
   Hlayout->addWidget(SetButton);
   Hlayout->addWidget(AuthorButton);
   Hlayout->setAlignment(Qt::AlignLeft);
   About->resize(ui->maindisplay->width()*0.3,ui->maindisplay->height()*0.15);

   About->move(50,0);

   About->show();


}

void MainWindow::testinterface()
{

}

void MainWindow::setAboutAuthor()
{

    AboutAuthor=new CustomPage(true,true,ui->mainwidget);
    AboutAuthor->setNormallColor("#F0FFFF");
    QVBoxLayout *vlayout=new QVBoxLayout(AboutAuthor);
    //Assistant::SetWidgetQss(AboutAuthor,15,"#F0FFFF")
    AboutAuthorBack=new CommonSmallButton("",":/image/qianjin.svg",180,true,15,AboutAuthor);//这里点击按钮一次后 图片旋转过来，就一直保持旋转的角度 没有复原 待改进

    AboutAuthorBack->setMinimumSize(40,40);

    Author=new InputText("Author:",QString("@jins"),false,AboutAuthor);
    MyGit=new InputText("GitHub:",QString("https://github.com/xiaojinyaonuli"),false,AboutAuthor);
    MybLog=new InputText("Blog:",QString("https://blog.csdn.net/m0_46472878"),false,AboutAuthor);
    Myersions=new InputText("Versions:",QString("1.0 "),false,AboutAuthor);
    AboutAuthor->setLayout(vlayout);
    AboutAuthorBack->move(AboutAuthor->width()-AboutAuthorBack->width()-5,0);
    vlayout->setSpacing(0);
    vlayout->setContentsMargins(0,0,50,350);

    vlayout->addWidget(AboutAuthorBack);
    vlayout->addWidget(Author);
    vlayout->addWidget(MyGit);
    vlayout->addWidget(MybLog);
    vlayout->addWidget(Myersions);
    //vlayout->setAlignment(Qt::AlignRight); //就是因为这句 布局出错 reasion: 暂时不知道
    AboutAuthor->resize(0,this->height()-40);
    AboutAuthor->setMouseTracking(true);
    AboutAuthor->pos()=ui->mainwidget->pos();
    //AboutAuthorBack->move(AboutAuthor->width()-10,this->height()-40-AboutAuthorBack->height()-5);
    //AboutAuthor->show();




    //creat  newpage
    Filenamethread=new MyThread(NULL);
    Desnamethread=new MyThread(NULL);
    CreatFile=new  CustomPage(true,true,ui->mainwidget);
    CreatFile->setNormallColor("#DEDEDE");
    occupiedwidget=new QWidget(CreatFile);//占位widget 在page中
    CreatFileBack=new CommonSmallButton("",":/image/down3.svg",0,false,15,CreatFile);
    CreatButton=new CommonSmallButton("creat","",0,false,5,CreatFile);
    CreatButton->setMinimumSize(100,50);
    CreatButton->setEnabled(false);
    CreatFileBack->setMinimumSize(40,40);
    occupiedwidget->setMinimumSize(0,400);
    Filename=new InputText("FileName:"," your filename",true,CreatFile);
    Filename->setMinimumSize(400,50);
    Filedescribe=new InputText("Describe:"," your filedescribe",true,CreatFile);
    Filedescribe->setMinimumSize(400,50);
    QVBoxLayout *Filevlayout=new QVBoxLayout(CreatFile);
    CreatFile->setLayout(Filevlayout);
    Filevlayout->setSpacing(50);
    Filevlayout->setContentsMargins(350,10,350,51);
    Filevlayout->setStretch(3,2);
    Filevlayout->addWidget(CreatFileBack);
    Filevlayout->addWidget(Filename);
    Filevlayout->addWidget(Filedescribe);
    Filevlayout->addWidget(occupiedwidget);

    Filevlayout->addWidget(CreatButton);
    CreatFile->setMouseTracking(true);
    CreatFile->hide();
    //CreatFile->pos()=QPoint(0,this->height()-39);






}


void MainWindow::CommonSmallConnect()
{
    connect(AuthorButton,&CommonSmallButton::clicked,AboutAuthor,[=](){
        mShadeWindow->show();
        mShadeWindow->stackUnder(AboutAuthor);
        AboutAuthor->show();

        animationAuthorpage=new QPropertyAnimation(AboutAuthor,"geometry",ui->maindisplay);

        animationAuthorpage->setStartValue(AboutAuthor->geometry());
        animationAuthorpage->setDuration(800);
        animationAuthorpage->setEasingCurve(QEasingCurve::InOutExpo);
        animationAuthorpage->setEndValue(QRect(0,0,ui->maindisplay->width()*0.3,this->height()-39));
        animationAuthorpage->start();
        OnSeeState=true;


    });


     connect(AboutAuthorBack,&CommonSmallButton::clicked,AboutAuthor,[=](){

         if(animationAuthorpageback==nullptr)
         {
             animationAuthorpageback=new QPropertyAnimation(AboutAuthor,"geometry",ui->maindisplay);

         }
         //QPropertyAnimation *animationAuthorpageback=new QPropertyAnimation(AboutAuthor,"geometry",ui->maindisplay);
         animationAuthorpageback->setStartValue(AboutAuthor->geometry());
         animationAuthorpageback->setDuration(800);
         animationAuthorpageback->setEasingCurve(QEasingCurve::InOutExpo);
         animationAuthorpageback->setEndValue(QRect(0,5,0,this->height()-39-10));
         animationAuthorpageback->start();
         OnSeeState=false;
         mShadeWindow->hide();
         //AboutAuthor->hide();//有问题  只是隐藏 resize还在动 待解决！

     });

      connect(Creatbtn,&BigButton::clicked,CreatFile,[=](){
         mShadeWindow->show();
         mShadeWindow->stackUnder(CreatFile);
         CreatFile->show();
//         if(_animationAuthorpage==nullptr)
//         {
//             qDebug()<<"weikong"<<endl;
//             _animationAuthorpage=new QPropertyAnimation(CreatFile,"geometry",ui->maindisplay);
//         }
         QPropertyAnimation *_animationAuthorpage=new QPropertyAnimation(CreatFile,"geometry",ui->maindisplay);
         _animationAuthorpage->setStartValue(CreatFile->geometry());
         _animationAuthorpage->setDuration(800);
         _animationAuthorpage->setEasingCurve(QEasingCurve::InOutExpo);
         _animationAuthorpage->setEndValue(QRect(0,(this->height()-39)*0.3,ui->maindisplay->width(),(this->height()-39)*0.7));
         _animationAuthorpage->start();

         OnSeeState_Creat=true;
         connect(_animationAuthorpage,&QPropertyAnimation::finished,CreatFile,[=]{delete _animationAuthorpage;});


      });


      connect(CreatFileBack,&CommonSmallButton::clicked,CreatFile,[=](){
          timer.stop();
//          QPropertyAnimation *animationCreatFile=nullptr;
//          if(animationCreatFile==nullptr)
//          {
//              qDebug()<<"初始化了一次"<<endl;
//              animationCreatFile=new QPropertyAnimation(CreatFile,"geometry",ui->maindisplay);
//          }
          QPropertyAnimation *animationCreatFile=new QPropertyAnimation(CreatFile,"geometry",ui->maindisplay);
          animationCreatFile->setStartValue(CreatFile->geometry());
          animationCreatFile->setDuration(400);
          animationCreatFile->setEasingCurve(QEasingCurve::InOutExpo);
          animationCreatFile->setEndValue(QRect(0,this->height()-39-1,ui->maindisplay->width(),0));
          animationCreatFile->start();
          OnSeeState_Creat=false;
          mShadeWindow->hide();
          //OnSeeState=false;
          connect(animationCreatFile,&QPropertyAnimation::finished,CreatFile,[=]{CreatFile->hide();delete animationCreatFile;});

      });


      //线程监视两个输入框部分 输入文字不能与预设文字一样 要进行更改，并且不能为空
       connect(Filename->gettextinput(),&QLineEdit::textEdited,Filenamethread,&MyThread::ThreadStart,Qt::UniqueConnection);
       connect(Filedescribe->gettextinput(),&QLineEdit::textEdited,Desnamethread,&MyThread::ThreadStart,Qt::UniqueConnection);
       connect(Filename->gettextinput(),&QLineEdit::editingFinished,Filenamethread,&MyThread::ThreadStop,Qt::UniqueConnection);
       connect(Filedescribe->gettextinput(),&QLineEdit::editingFinished,Desnamethread,&MyThread::ThreadStop,Qt::UniqueConnection);
       connect(Filenamethread,&MyThread::textinformation,this,[=](const QString &Filename,bool is){ this->FNAMEFINSH=is;FileName=Filename;});
       connect(Desnamethread,&MyThread::textinformation,this,[=](const QString &Desname,bool is){
           DescrName=Desname;
           this->DESCRIBEFINSH=is;
           if(FNAMEFINSH&&DESCRIBEFINSH)
           {
               CreatButton->setEnabled(true);
           }else{
               CreatButton->setEnabled(false);
           }
       });
       connect(btn,&BigButton::clicked,this,[=](){
           QString inputPath = QFileDialog::getOpenFileName(this, tr("Open jsh"), " ",  tr("jsh File(*.jsh)"));
           if(!inputPath.isEmpty())
           {
               MyCanvas *newCanvas=loadCanvas(inputPath);
               if(newCanvas==nullptr)
               {
                   return;
               }
               Canvasptr=newCanvas;
               newCanvas->resize(ui->mainwidget->width()+1,ui->mainwidget->height()+1);
               newCanvas->show();
               //mShadeWindow->show();

           }
       });

       connect(CreatButton,&CommonSmallButton::clicked,this,[=](){
           QDateTime curtime= QDateTime::currentDateTime();
           QString time=curtime.toString("yyyy-MM-ddhh:mm:ss");
           MyCanvas *canvas=new MyCanvas(FileName,DescrName,time,ui->mainwidget);
//           canvas->resize(this->size());
           //canvas->setGeometry(this->geometry());
           Canvasptr=canvas;
           canvas->resize(ui->mainwidget->width()+1,ui->mainwidget->height()+1);
           //canvas->move(this->geometry().x(),this->geometry().y());
           mShadeWindow->show();
           canvas->stackUnder(CreatFile);
           mShadeWindow->stackUnder(CreatFile);
           canvas->show();


           timer.start(500);

       });
       connect(&timer,&QTimer::timeout,CreatFileBack,&CommonSmallButton::clicked);




}



void MainWindow::CalculateWidgetRect()//计算主窗口的8个矩形区域位置
{
    topleft_rect=QRect(0,0,STRETCH_PADDING,STRETCH_PADDING);//左上角

    topright_rect=QRect(this->width()-STRETCH_PADDING,
                        0,STRETCH_PADDING,STRETCH_PADDING);//右上角

    downleft_rect=QRect(0,this->height()-STRETCH_PADDING,
                        STRETCH_PADDING,STRETCH_PADDING);//左下角

    downright_rect=QRect(this->width()-STRETCH_PADDING,
                         this->height()-STRETCH_PADDING,

                         STRETCH_PADDING,STRETCH_PADDING);//右下角
    top_rect=QRect(STRETCH_PADDING,0,
                   this->width()-STRETCH_PADDING*2,
                   STRETCH_PADDING);

    down_rect=QRect(STRETCH_PADDING,this->height()-STRETCH_PADDING,
                    this->width()-STRETCH_PADDING*2,
                    STRETCH_PADDING);

    left_rect=QRect(0,STRETCH_PADDING,STRETCH_PADDING,
                    this->height()-STRETCH_PADDING*2);

    right_rect=QRect(this->width()-STRETCH_PADDING,STRETCH_PADDING,
                     STRETCH_PADDING,this->height()-STRETCH_PADDING*2);

}

MainWindow::CursorPosition MainWindow::Get_CalculateCur_Position(const QPoint &cur_positon)
{
    CursorPosition C_position;
    if(top_rect.contains(cur_positon))
    {
        C_position=TOP_RECT;
    }else if(left_rect.contains(cur_positon))
    {
        C_position=LEFT_RECT;
    }else if(right_rect.contains(cur_positon))
    {
        C_position=RIGHT_RECT;
    }else if(down_rect.contains(cur_positon))
    {
        C_position=DOWN_RECT;
    }else if(topleft_rect.contains(cur_positon))
    {
        C_position=TOPLEFT_RECT;
    }else if(topright_rect.contains(cur_positon))
    {
        C_position=TOPRIGHT_RECT;
    }else if(downleft_rect.contains(cur_positon))
    {
        C_position=DOWNLEFT_RECT;
    }else if(downright_rect.contains(cur_positon))
    {
        C_position=DOWNRIGHT_RECT;
    }else{
        C_position=NONE;
    }

    return C_position;
}

void MainWindow::SetCurStyle(MainWindow::CursorPosition cur)
{
    switch (cur) {

    case NONE:
        setCursor(Qt::ArrowCursor);
        break;
     case TOP_RECT:
     case DOWN_RECT:
        setCursor(Qt::SizeVerCursor);
        break;
    case LEFT_RECT:
    case RIGHT_RECT:
        setCursor(Qt::SizeHorCursor);
        break;
    case TOPLEFT_RECT:
    case DOWNRIGHT_RECT:
        setCursor(Qt::SizeFDiagCursor);
        break;
    case TOPRIGHT_RECT:
    case DOWNLEFT_RECT:
        setCursor(Qt::SizeBDiagCursor);
        break;
    default:
        setCursor(Qt::ArrowCursor);
        break;
    }

}

void MainWindow::UpdateWindow()
{
   QRect window=LastWindow;

   int offset_x=C_StartPoint.x()-C_EndPoint.x();

   int offset_y=C_StartPoint.y()-C_EndPoint.y();

   if(CursorCurrentState==TOP_RECT)
   {
       QPoint rect=window.topLeft();
       rect.setY(rect.y()-offset_y);
       window.setTopLeft(rect);

   }else if(CursorCurrentState==DOWN_RECT)
   {
       QPoint rect=window.bottomRight();
       rect.setY(rect.y()-offset_y);
       window.setBottomRight(rect);
   }else if(CursorCurrentState==LEFT_RECT)
   {
       QPoint rect=window.topLeft();
       rect.setX(rect.x()-offset_x);
       window.setTopLeft(rect);
   }else if(CursorCurrentState==RIGHT_RECT)
   {
       QPoint rect=window.bottomRight();
       rect.setX(rect.x()-offset_x);
       window.setBottomRight(rect);
   }else if(CursorCurrentState==TOPLEFT_RECT)
   {
       QPoint rect=window.topLeft();
       rect.setX(rect.x()-offset_x);
       rect.setY(rect.y()-offset_y);
       window.setTopLeft(rect);
   }else if(CursorCurrentState==TOPRIGHT_RECT)
   {
       QPoint rect=window.topRight();
       rect.setX(rect.x()-offset_x);
       rect.setY(rect.y()-offset_y);
       window.setTopRight(rect);
   }//还有右下角没写


   this->setGeometry(window);

}

void MainWindow::initshadow()
{
    QGraphicsDropShadowEffect  *widget_shadow=new QGraphicsDropShadowEffect(this);
    widget_shadow->setOffset(0,0);

    widget_shadow->setColor(QColor("#080808"));

    widget_shadow->setBlurRadius(18);

    ui->mainwidget->setGraphicsEffect(widget_shadow);
}



MyCanvas *MainWindow::loadCanvas(const QString &path)
{
    QFile input(path);
    input.open(QIODevice::ReadOnly);
    QTextStream ts(&input);
    QString SignString = ts.readLine();
    if(SignString!="STARTAFNTHYRTY=")
        return nullptr;
    MyCanvas *newCanvas=new MyCanvas(ts,ui->mainwidget);
    input.close();
    return newCanvas;

}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(CursorCurrentState==NONE&&event->buttons()&Qt::LeftButton)
    {
        QPoint off_temp;
        off_temp=event->globalPos()-offest;
//        qDebug()<<"点击事件传递"<<endl;
        move(off_temp);
    }
    if(!isMousepressed)
    {
        CursorCurrentState=Get_CalculateCur_Position(event->pos());
        SetCurStyle(CursorCurrentState);
    }else{
        C_EndPoint=this->mapToGlobal(event->pos());
        if(C_EndPoint!=C_StartPoint)
        {
            UpdateWindow();
        }
    }

    return QWidget::mouseMoveEvent(event);

}



void MainWindow::mousePressEvent(QMouseEvent *event)
{

    if(CursorCurrentState!=NONE&&event->button()==Qt::LeftButton)
    {
        //鼠标已经在边缘矩形区域中，已经按下按键
        isMousepressed=true;

        C_StartPoint=this->mapToGlobal(event->pos());

        LastWindow=this->geometry();

    }else if(event->button()==Qt::LeftButton)
    {
//       qDebug()<<this->geometry().x();
        offest=event->globalPos()-pos();

    }





}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    isMousepressed=false;

    CalculateWidgetRect();//松开时计算一下窗口大小

    return QWidget::mouseReleaseEvent(event);
}

void MainWindow::showEvent(QShowEvent *event)
{

    CalculateWidgetRect();
    About->resize(ui->maindisplay->width()*0.3,ui->maindisplay->height()*0.15);
    AboutAuthor->resize(0,this->height()-39);//760  layoutmargin 是20  上下两个margin是40所以800-40就是现在看到的主窗口的高度
    AboutAuthorBack->move(AboutAuthor->width()-AboutAuthorBack->width()-2,0);
    CreatFile->resize(ui->maindisplay->width(),(this->height()-39)*0.7);
    CreatFile->move(0,(this->height()-39));
    mShadeWindow->resize(ui->mainwidget->width()+2,ui->mainwidget->height());
    return QWidget::showEvent(event);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
//     Creatbtn->setscale(0.6);
    if(OnSeeState)
    {
        AboutAuthor->resize(ui->maindisplay->width()*0.3,this->height()-39);
    }
    if(OnSeeState_Creat)
    {
        CreatFile->move(0,(this->height()-39)*0.3);
        CreatFile->resize(ui->maindisplay->width(),(this->height()-39)*0.7);
    }
    mShadeWindow->resize(ui->mainwidget->width()+1,ui->mainwidget->height());
    About->resize(ui->maindisplay->width()*0.3,ui->maindisplay->height()*0.15);
    if(Canvasptr!=nullptr)
    {
        Canvasptr->resize(ui->mainwidget->width()+1,ui->mainwidget->height()+1);

    }


//    AboutAuthorBack->move(AboutAuthor->width()-AboutAuthorBack->width()-2,0);

}





