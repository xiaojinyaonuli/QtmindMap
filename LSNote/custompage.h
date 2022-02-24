#ifndef CUSTOMPAGE_H
#define CUSTOMPAGE_H

#include <QWidget>
#include<QPushButton>
#include<QGraphicsDropShadowEffect>
#include"customobject.h"
#include"customitem.h"
class CustomPage : public QWidget
{
    Q_OBJECT
public:
    explicit CustomPage(bool isshadow,bool isroundrect, QWidget *parent = nullptr);
    void setNormallColor(const QString &color);

private:
    QColor normallcolor="#FF83FA";
    QGraphicsDropShadowEffect  *widget_shadow;
    bool IsShadow,IsRoundrect;

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

signals:

};

class MyCanvas:public QWidget
{
    Q_OBJECT
private:
    QString _canvasname,_canvasdesc,_time;
    CustomPage *Optionsmeun ,*InfoPage;
    float OFFESTSIZE=5;
    CommonSmallButton *backbtn,*InfoPageBack,*Savebtn,*MainPage;
    CommonSmallButton *optionInfo;
    QList<CommonSmallButton *> btnlist;
    InputText *FileName,*FileDescribe,*CreatTime;
    QWGraphicsView *view;
    QPushButton *appearbtn;
    bool opIsresize=false;
    QPropertyAnimation *backpageani=nullptr,*appearpageani=nullptr,*InfoPageani=nullptr,*InfoPageaniback=nullptr;
private:
    void InitObject();
    void saveToFile(const QString &path);

public:
    explicit MyCanvas( QString CanvasName, QString CanvasDescribe,
                       QString Time,
                       QWidget *parent=nullptr);
    explicit MyCanvas(QTextStream &ts,QWidget *parent=nullptr);
    QString getCanvasName() const{return _canvasname;};
    QString getCanvasDescribe() const{return _canvasdesc;};
    void setOptionsMenu();
    void CommonbtnConnects();
    void InfomationPage();
protected:
    void paintEvent(QPaintEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;



};


class MaskWidget:public QWidget
{
    Q_OBJECT
private:
public:
    explicit MaskWidget(QWidget *parent);
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // CUSTOMPAGE_H
