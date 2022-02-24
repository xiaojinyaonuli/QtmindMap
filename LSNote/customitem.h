#ifndef CUSTOMITEM_H
#define CUSTOMITEM_H
#include<QAbstractGraphicsShapeItem>
#include<QPointF>
#include<QObject>
#include<QWidget>
#include<QPainter>
#include<QLineEdit>
#include<QGraphicsTextItem>
#include<QFocusEvent>
#include<QGraphicsSceneMouseEvent>
#include<QApplication>
#include<QObject>
#include<QDebug>
#include<QTimer>
#include<QPainterPath>
#include<QGraphicsScene>
#include<QStyleOptionGraphicsItem>
#include<QGraphicsView>


class BPointitem:public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    enum  PointType{
        CENTER=0,//中心点
        EDGE   //边缘点
    };

    BPointitem(QGraphicsItem *parent,QPointF p,PointType type);
    QPointF getPoint() { return point; }
    void setPoint(QPointF p) { point = p;
                             this->scene()->update();}

private:
    QPointF  point;
    PointType pointtype;
protected:
    virtual  QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;




};







class myQGraphicsLineItem;
class my_graphicsTextItem: public QGraphicsTextItem
{
    Q_OBJECT
private:
    QFont font;
    QRectF _rect;
    int _fontwidth;
    int _fontHeight;
    QTimer *timer;
    BPointitem *BackPoint,*FrontPoint;
    int id;
    bool Ishasfous=false;

    //int NormallWidth;
public:
    my_graphicsTextItem(QRectF rect, const QString &s,int ID,QWidget *parent = nullptr);

    int getUserType() const
    {
        return this->UserType+1;
    }
    BPointitem* getFrontPoint() const
    {
        return this->FrontPoint;
    }
    BPointitem* getBackPoint() const
    {
        return this->BackPoint;
    }
    int getBoundRectWidth() const
    {
        return BoundRectWidth;
    }

    int getItemId() const
    {
        return this->id;
    }
    qreal getpos()
    {
        return this->boundingRect().x();
    }
    int getFatherId()
    {

        if(this->parent()!=nullptr)
        {
            return static_cast<my_graphicsTextItem *>(this->parent())->getItemId();
        }else
            return NULL;


    }

    QString getdata(){return QString::asprintf("%g %g %g %g %d %d %g %g\n",
                                               this->boundingRect().x()
                                               ,this->boundingRect().y()
                                               ,this->boundingRect().width()
                                               ,this->boundingRect().height()
                                               ,this->id
                                               ,getFatherId()
                                               ,this->pos().x()
                                               ,this->pos().y()
                                               )+toPlainText();}



    ~my_graphicsTextItem(){}

    void UpdateItemSize();
    QString m_store_str;//用于保存
    QTextCursor* curptr;
    QList<myQGraphicsLineItem *> FrontList;
    QList<myQGraphicsLineItem *> BackList;

    QList<my_graphicsTextItem *> childrens;
    QString Temptext;
    int BoundRectWidth=0;
    bool ispress=false;

    void myupdateFontInfo();

    void _setRect(const QRectF &rect)
    {
        _rect=rect;
        //this->scene()->update();


    }

    void PushChildrens(QList<QGraphicsItem*> list)
    {
        for(int i=0;i<list.count();i++)
        {
            if(list.at(i)->type()==UserType+1)
                childrens.append(static_cast<my_graphicsTextItem*>(list[i]));
        }
    }
    const QList<my_graphicsTextItem *> & getChildrens()
    {
         return this->childrens;
    }
signals:
    void EditStatus(bool);
    void TESTEDIT();
    void ChangeLinePosition();

public slots:
      void UpdateLinePosition();

protected:

    bool eventFilter(QObject *obj, QEvent *ev) override;

    virtual int type() const override{return UserType+1;};

    virtual QPainterPath shape() const override{
             QPainterPath path;
             path.addRoundedRect(boundingRect(),15,15);
             return path;
    }
    bool contains(const QPointF &point) const override{
        if(boundingRect().contains(point))
            return true;
    }

    virtual QRectF boundingRect() const override{
        return _rect;
    }
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget) override;

    void focusInEvent(QFocusEvent *event) override;


    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;


    void focusOutEvent(QFocusEvent *event) override;



    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)override;


    void keyPressEvent(QKeyEvent *event) override;



    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;



};

//----------------------------------------------------------------




class myQGraphicsLineItem:public QObject ,public QGraphicsLineItem
{
    Q_OBJECT
public:
    myQGraphicsLineItem(QPointF StartPoint,QPointF ndPoint,QGraphicsItem *parent=nullptr);

    void setPointSE(QPointF start,QPointF end)
    {
        m_startpoint=start;
        m_endpoint=end;
    }

    void setLineId(int i){this->ID=i;};
    int getLineId();
    QPointF getStartPoint(){return this->m_startpoint;}
    QPointF getEndPoint(){return this->m_endpoint;}
    QString getdataline(){return QString::asprintf("%g %g %g %g %d\n",m_startpoint.x(),m_startpoint.y()
                         ,m_endpoint.x(),m_endpoint.y(),this->ID);}
private:
    QPointF m_startpoint,m_endpoint;
    QPen defaultpen;
    QColor defaultcolor=Qt::black;
    qreal defaultpenwidth=2;
    int ID;


protected:
    virtual  QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    int     type() const
    {
        return UserType+2;
    }
};



class CustomScene_:public QGraphicsScene
{
public:
    CustomScene_(QGraphicsScene* parent);
    CustomScene_();
protected:
    // 左键：添加item  右键：移除item
    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
    // Backspace键移除item
    void keyPressEvent(QKeyEvent *event)override;
    void drawBackground(QPainter *painter, const QRectF &rect) override;
};







class QWGraphicsView:public QGraphicsView{

    Q_OBJECT
public:

    QWGraphicsView(bool isdefault,QWidget  *parent=nullptr);
     bool eventFilter(QObject *obj, QEvent *event) override;
     void saveToFile( QTextStream &ts);
     void readFromFile(QTextStream &ts);
     QString getFrontBackId(int Id);
     my_graphicsTextItem* AddItemText(QRectF rect,int Id,QString text);
     my_graphicsTextItem* AddItemLoad(QRectF rect,int Id,int FatherId,QString text,const QPointF pos);
     void AddLineLoad(QPointF start,QPointF end,int Id,int FId,int BId);
     //void AddItemLine();
     void test();
     void addText();
     static int lineID;
private:
    bool IsHasItem,canADD,IsDefault;
    my_graphicsTextItem  *itempos=nullptr;
    CustomScene_ *sence;
    int ItemID=0;
    //静态

    QVector<my_graphicsTextItem *> VTexts;
    QVector<myQGraphicsLineItem *> Lines;
protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;


signals:
    void OnUpdateLine();
public slots:
    void zoomIn(){scale(1.2,1.2);}
    void zoomOut(){scale(1/1.2,1/1.2);}
    void UpdateLine();



};





#endif // CUSTOMITEM_H
