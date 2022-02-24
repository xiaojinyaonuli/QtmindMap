#ifndef CUSTOMOBJECT_H
#define CUSTOMOBJECT_H

#include <QObject>
#include <QWidget>
#include<QPushButton>
#include<QPropertyAnimation>
#include<QColor>
#include<QLabel>
#include<QPixmap>
#include<QVBoxLayout>
#include<QtSvg>
#include<QEvent>
#include<QEnterEvent>
#include<QThread>
#include <QMutex>
class MyThread;
class CustomObject
{

public:
    CustomObject();
};



class BigButton:public QWidget
{
    Q_OBJECT
public:
    explicit BigButton(const QString& iconpath,const QString& describe,QWidget *parent=nullptr);
    //~BigButton();
    void setscale(qreal scale);
    QString getbgEnterColor();
    QString getbgNormallColor();
    QString getbgstyle();
    QString getindiacatorstyle();
    QString getindiacatorNormallColor();
    QString getindiactorEnterColor();
    QString getbgPressedColor();
private:
    QWidget *bgwidget;
    QWidget *indicator;
    QPropertyAnimation *animation_indicator;
    QPropertyAnimation *animation_indicator_back;
    QPixmap *iconimage;
    QLabel *iconlabel;
    QLabel *textlabel;
    const QString bgnormallcolor="#F0FFFF";
    const QString bgentercolor="#E0EEEE";
    const QString bgpressedcolor="#E0E0E0";
    const QString bgstyle="border-radius:25px;";
    const QString indiactorNormallColor="#afafaf";
    const QString indiactorEnterColor="#4876FF";
    const QString indiacator_style="border-radius:3px;";
    bool ispressed;
protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
signals:
    void clicked();

};






class  Assistant
{

public:
    Assistant()
    {

    }
public:
    static void SetPushButtonQss(QPushButton *btn,
                          int radius,
                          const QString &bgnormallcolor,
                          const QString &bghovercolor,
                          const QString &pressedColor
                          );
    static void SetWidgetQss(QWidget *widget,
                             int radius,
                             const QString &background
                             );


};







class CommonSmallButton:public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(qreal rotationAngle READ rotationAngle WRITE setRotationAngle NOTIFY rotationAngleChanged)

public:
    CommonSmallButton(const QString &btnname,const QString& iconpath,
                      const qreal &wantrotateangle,const bool isrotate,
                      const int radius,
                      QWidget *parent=nullptr);
    void SetBgcolor(const QColor& color);
    void Setleavecolor(const QColor color);
    void setRotationAngle(qreal angle = 0);
    qreal rotationAngle() const {return rotateangle;}
private:
    QLabel *iconlabel;
    QPixmap *iconimage;
    QSvgRenderer *renderer;
    QString m_btnname;
    QColor LeaveColor="#F0FFFF";
    QColor BgColor;
    QColor EnterColor="#E0EEEE";
    QColor PressColor="#DEDEDE";
    qreal iconSizeRate = 0.8;
    QLabel *labeltext;
    int btnnametWidth=0;
    int btnnameHeight=0;
    qreal rotateangle;//旋转角
    bool ispressed;
    QPropertyAnimation *rotate;
    QPropertyAnimation *backrotate;
    bool isrotate_;
    int radius;
    qreal wantrotateangle_;
protected:
    void paintEvent(QPaintEvent *) override;
    void enterEvent(QEvent *event) override; //QEnterEvent 不行 解决：还不知道为什么
    void leaveEvent(QEvent* event)override;
    void  mousePressEvent(QMouseEvent *event)override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;


public slots:
    void Slot_AnimationFinsh();
    void slot_paintline(QVariant a);
    void slot_Isrotatefinsh();
    void slot_animationfinsh();
signals:
    void rotationAngleChanged();
    void clicked();


};







class InputText:public QWidget
{

    Q_OBJECT
public:
    InputText(const QString& Qlabelname,const QString &inputstring,bool Enable,QWidget *parent=nullptr);
    void EnterAnimation();
    void LeaveAnimation();
    void LinetextConnect();
    void SetResize(QWidget * parent);
    void SetTextLine(const QString &text);
    QString getText()const ;
    QLineEdit *gettextinput()const ;
private:
    QWidget *bgwidget;
    QLabel  *describe;
    QLineEdit *textinput;
    QWidget *indicator;
    QString firstinput;
    QColor EnterColor="#E0EEEE";
    QColor LeaveColor="#00000000";
    bool IsPressed;
    bool IsEdit;
    bool EnableEndit;
    QParallelAnimationGroup *EnterGroup,*LeaveGroup;
    QPropertyAnimation *Eindicatoranimation,*Etextinputanimation;
    QPropertyAnimation *Lindicatoranimation,*Ltextinputanimation;
//    MyThread *monitor=nullptr;


protected:
    void enterEvent(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
signals:
    void Judge(bool change);
    void Etext(const QString &t);
public slots:
    void EditFinshed();
    void EditJudge();

};


class MyThread:public QThread
{
    Q_OBJECT
private:
    bool isStop;
    QString str;
    QMutex mutex;
    QString FirstText;
public:
    MyThread(QObject *par);
    void ThreadStart(const QString &s);
    void ThreadStop();
protected:
    void run() override;
signals:
    void textinformation(const QString & str,bool cancreat);
 public slots:
     void Judgetext(const QString text);

};


class GraphItemThread:public QThread
{
    Q_OBJECT
private:
    bool isStop;
    QString str;
    QMutex mutex;
    QString FirstText;
public:
    GraphItemThread(QObject *par);
    void ThreadStart(const QString &s);
    void ThreadStop();

protected:
    void run() override;
signals:


};

class CollectThread:public QThread
{
    Q_OBJECT


};




#endif // CUSTOMOBJECT_H
