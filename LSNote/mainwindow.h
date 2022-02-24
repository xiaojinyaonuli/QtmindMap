#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMouseEvent>
#include<QRect>
#include"customobject.h"
#include"custompage.h"
#include"mywidget.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initmousetrack();
    void init_mainwidget_doublebutton();
    void SetAboutWidget();
    void testinterface();
    void setAboutAuthor();



public:
    //8个矩形边距枚举类型
    enum CursorPosition{
        TOP_RECT=0,
        DOWN_RECT,
        LEFT_RECT,
        RIGHT_RECT,
        TOPLEFT_RECT,
        TOPRIGHT_RECT,
        DOWNLEFT_RECT,
        DOWNRIGHT_RECT,
        NONE
    };
private:
    Ui::MainWindow *ui;

    BigButton *Creatbtn=nullptr ,*btn=nullptr;

    MaskWidget*   mShadeWindow;

    QPoint offest;

    const int STRETCH_PADDING=20;

    bool  isMousepressed;

    CursorPosition CursorCurrentState;
    bool OnSeeState;
    bool OnSeeState_Creat;

    QRect top_rect,
          down_rect,
          left_rect,
          right_rect,
          topleft_rect,
          downleft_rect,
          topright_rect,
          downright_rect;
    QPoint C_StartPoint,C_EndPoint;//鼠标按下开始的点，结束的点

    QRect LastWindow;//前一次窗口的大小

    QWidget* page;


    MyCanvas *Canvasptr=nullptr;


    CommonSmallButton *btnsmall,*SetButton,*AuthorButton;

    QList<CommonSmallButton *> SMALLBUTTONS;

    const QString Authorinformation="ABOUT";

    QWidget *About; //about页面

    CustomPage *AboutAuthor,*CreatFile;//about弹出页面,创建页面

    InputText *test;

    InputText *Author,*MyGit,*MybLog,*Myersions;

    InputText *Filename,*Filedescribe;

    QList<InputText *> AboutAuthorTextInputList;// Inputtext

    CommonSmallButton *AboutAuthorBack,*CreatFileBack,*CreatButton;

    QWidget *occupiedwidget;
    QPropertyAnimation * animationAuthorpage=nullptr,*animationAuthorpageback=nullptr;

    bool Filenamefinsh,describefinsh;
    MyThread * Filenamethread=nullptr;
    MyThread * Desnamethread=nullptr;

    //画布文件描述 +文件名字
    QString FileName,DescrName;



    bool FNAMEFINSH,DESCRIBEFINSH;

    QTimer timer;//自动点击创建文件返回按钮

signals:
    void filenameFinsh(bool);
    void filedescribeFinsh(bool);





private:
    void CalculateWidgetRect();//计算主窗口的8个矩形区域位置
    CursorPosition Get_CalculateCur_Position(const QPoint &cur_positon);//获取当前鼠标在窗口的位置
    void SetCurStyle(CursorPosition cur);//设置鼠标形状根据其所在的位置
    void UpdateWindow();
    void initshadow();//设置外边框阴影
    MyCanvas* loadCanvas(const QString &path);

protected:
     virtual void mouseMoveEvent(QMouseEvent *event);
     virtual void mousePressEvent(QMouseEvent *event);

     virtual void mouseReleaseEvent(QMouseEvent *event);

     virtual void showEvent(QShowEvent *event);

     virtual void resizeEvent(QResizeEvent *event);

     void CommonSmallConnect();
     //void InputTextConnect();


private slots:


};
#endif // MAINWINDOW_H
