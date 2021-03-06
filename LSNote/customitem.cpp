#include "customitem.h"
#include<QGraphicsItem>
#include<QStaticText>
#include<QPainter>
#include<QDebug>
#include<QGraphicsProxyWidget>


BPointitem::BPointitem(QGraphicsItem *parent, QPointF p,PointType type)
    :QGraphicsItem(parent)
    ,point(p)
    ,pointtype(type)
{
    this->setPos(point);
    this->setFlags(QGraphicsItem::ItemIsSelectable |

                  QGraphicsItem::ItemIsFocusable);


}

QRectF BPointitem::boundingRect() const
{
    return QRectF(-4,-4,8,8);
}

void BPointitem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);


    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(QColor("#B23AEE"));
    this->setPos(point);
    painter->drawEllipse(-4,-4,8,8);
//    painter->drawStaticText()


}

void BPointitem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);

}



//------------------------------------------------------------------







my_graphicsTextItem::my_graphicsTextItem(QRectF rect, const QString &s, int ID, QWidget *parent)
{


        this->setFlags(QGraphicsItem::ItemIsMovable |
                 QGraphicsItem::ItemIsSelectable |
                 QGraphicsItem::ItemIsFocusable );
        this->setObjectName(s);
        this->installEventFilter(this);
        font = QFont("SimSun", 15);
         _rect=rect;
        BackPoint=new BPointitem(this,QPoint(_rect.x()/2+_rect.width(),(_rect.y()+_rect.height()-8)/2),BPointitem::EDGE);
        FrontPoint=new BPointitem(this,QPoint(_rect.x()/2,(_rect.y()+_rect.height()-8)/2),BPointitem::CENTER);
        id=ID;
        //NormallWidth=100;
        this->setFont (font);
        m_store_str  =s;
        BoundRectWidth=_rect.width();
        QFontMetricsF *fm=new QFontMetricsF(font);
        int _fontwidth=fm->width(s);
        int _fontHeight =fm->height();
         timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, [=](){
            myupdateFontInfo();
        },Qt::UniqueConnection);
        connect(this,&my_graphicsTextItem::ChangeLinePosition,this,&my_graphicsTextItem::UpdateLinePosition);


}

void my_graphicsTextItem::UpdateItemSize()
{


}

void my_graphicsTextItem::myupdateFontInfo()
{

    m_store_str=toPlainText();
    QFontMetricsF *fm=new QFontMetricsF(font);
    int fontwidth=fm->width(m_store_str);
    //qDebug()<<"????????????"<<fontwidth<<endl;
    int fontHeight =fm->height();
    //?????????????????????????????????
    if (fontwidth > boundingRect().width())
    {
        qreal adjust = 20;
        this->_setRect(QRectF(boundingRect().x(), boundingRect().y(), fontwidth + adjust,boundingRect().height()));
        this->update();
        //po->setPoint(QPointF(boundingRect().x()+this->boundingRect().width(),(boundingRect().y()+boundingRect().height()))/2);
        //qDebug()<<"fontwidth + adjust"<<fontwidth + adjust<<endl;
       // qDebug()<<"this->boundingRect().width()"<<this->boundingRect().width()<<endl;

        BackPoint->setPoint((QPointF(boundingRect().x()+this->boundingRect().width()*2,(boundingRect().y()+boundingRect().height()-8))/2));
        QPointF Back=mapToScene(BackPoint->pos());
        //qDebug()<<"BackPoint->scenePos()"<<BackPoint->scenePos()<<endl;
        //qDebug()<<"Back"<<Back<<endl;
        FrontPoint->setPoint((QPointF(boundingRect().x(),(boundingRect().y()+boundingRect().height()-8))/2));
        //this->update();
        int count=this->BackList.count();
        for(int i=0;i<count;i++)
        {
            BackList[i]->setPointSE(QPointF(Back.x()+adjust+3,Back.y()),static_cast<my_graphicsTextItem*>(children()[i+2])->getFrontPoint()->scenePos());
        }
        //emit ChangeLinePosition();
        //qDebug()<<"this->pos()"<<this->pos()<<endl;
       // qDebug()<<"po->pos()"<<BackPoint->pos()<<endl;
       // qDebug()<<"boundingRect().x()+this->boundingRect().width()*2"<<mapToScene(boundingRect().x()+this->boundingRect().width()*2,2)<<endl;
        this->setFont(font);
        this->setPlainText(m_store_str);
        BoundRectWidth=fontwidth + adjust;
        //???????????????????????????????????????????????????????????????
        QTextCursor cursor = this->textCursor();
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor, 1);
        this->setTextCursor(cursor);
    }else if(fontwidth < boundingRect().width())
    {

    }


}

void my_graphicsTextItem::UpdateLinePosition()
{

//    int count=this->BackList.count();
//    for(int i=0;i<count;i++)
//    {
//        BackList[i]->setPointSE(this->BackPoint->scenePos(),static_cast<my_graphicsTextItem*>(children()[i+2])->FrontList[i]->scenePos());
//    }

}


bool my_graphicsTextItem::eventFilter(QObject *obj, QEvent *ev)
{
    if(QEvent::KeyPress==ev->type())
    {
        //????????????????????????


         QKeyEvent *keyEvent = dynamic_cast<QKeyEvent *>(ev);

         switch (keyEvent->key())
         {
           case Qt::Key_Backspace:
             {
             QTextCursor cursor = this->textCursor();
             if(cursor.hasSelection())//????????????????????????????????????????????????
                     cursor.clearSelection();
             cursor.deletePreviousChar();
             this->setTextCursor(cursor);
             break;}
           case Qt::Key_Left:
             {

              QTextCursor cursor = this->textCursor();
              if(cursor.hasSelection())//????????????????????????????????????????????????
                      cursor.clearSelection();
              cursor.movePosition(QTextCursor::Left,QTextCursor::MoveAnchor,1);
              this->setTextCursor(cursor);
              break;
             }
           case Qt::Key_Right:
           {

            QTextCursor cursor = this->textCursor();
            if(cursor.hasSelection())//????????????????????????????????????????????????
                    cursor.clearSelection();
            cursor.movePosition(QTextCursor::Right,QTextCursor::MoveAnchor,1);
            this->setTextCursor(cursor);
            break;
           }




         }
    }

}



void my_graphicsTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor pencolor=Qt::black;
    const qreal penw=2;
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(pencolor, penw, Qt::SolidLine));
    painter->setBrush(QColor("#FFFFFF"));

    painter->drawRoundedRect(boundingRect(),10,10);
    QStyleOptionGraphicsItem op;
    op.initFrom(widget);

    //?????????????????? ???????????????State_None
    if(option->state&QStyle::State_Selected)
    {
        op.state=QStyle::State_None;
    }else{
        op.state=QStyle::State_None;
    }

    QGraphicsTextItem::paint(painter,&op,widget);

    //???????????????
    if(option->state&QStyle::State_Selected)
    {
        const qreal penwidth=4;
        // ??????????????????
        QColor color = QColor("#87CEFA");
        // ????????????
        painter->setPen(QPen(color, penwidth, Qt::SolidLine));
        painter->setBrush(Qt::NoBrush);
        painter->drawRoundedRect(boundingRect().adjusted(0.001,0.001,-0.001,-0.001),12.5,12.5);
    }

}





void my_graphicsTextItem::focusInEvent(QFocusEvent *event)
{
    if(event->reason() != Qt::PopupFocusReason){

    }

    QGraphicsTextItem::focusInEvent(event);
}






void my_graphicsTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    ispress=true;
    if(ispress)
    {


    }
    QGraphicsTextItem::mousePressEvent(event);
}






void my_graphicsTextItem::focusOutEvent(QFocusEvent *event)
{
    if(event->reason() == Qt::MouseFocusReason && QApplication::mouseButtons()==Qt::RightButton)
    {
        //update();
        //?????????????????????????????????????????????????????????????????????????????????
        //setPlainText(m_store_str);

        setTextInteractionFlags(Qt::NoTextInteraction);//????????????????????????
        emit EditStatus(false);//????????????(??????????????????)
    }
    else if(event->reason() == Qt::PopupFocusReason)
    {
        //?????????????????????????????????
    }
    else
    {  //??????????????????????????????????????????????????????????????????????????????????????????

        setTextInteractionFlags(Qt::NoTextInteraction);
        emit EditStatus(false);//????????????(??????????????????)
         //myupdateFontInfo();

    }
    QGraphicsTextItem::focusOutEvent(event);
}



void my_graphicsTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

    Ishasfous=true;
    if(event->button() == Qt::LeftButton){//????????????????????????????????????????????????
    if(Ishasfous)
    {

    timer->start(500);
    setTextInteractionFlags(Qt::TextEditorInteraction);

    Temptext=toPlainText();
    setFocus();
    emit EditStatus(true);//????????????


    }
    //timer->start(300); // ??????1s

}
    QGraphicsTextItem::mouseDoubleClickEvent(event);
}



void my_graphicsTextItem::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return||event->key() == Qt::Key_Enter)
    {
    //???????????????????????????????????????????????????FocusOutEvent??????
        Ishasfous=false;
        m_store_str=toPlainText();
        clearFocus();
        timer->stop();
         //myupdateFontInfo();
    }

     QGraphicsTextItem::keyPressEvent(event);

}

void my_graphicsTextItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
     QGraphicsItem::mouseMoveEvent(event);
}



//-----------------------------------------------------------------------------------------
//??????
//-----------------------------------------------------------------------------------------


myQGraphicsLineItem::myQGraphicsLineItem(QPointF StartPoint, QPointF EndPoint, QGraphicsItem *parent)
    :QGraphicsLineItem(parent)
    ,m_startpoint(StartPoint)
    ,m_endpoint(EndPoint)
{


    defaultpen.setWidth(this->defaultpenwidth);
    defaultpen.setColor(defaultcolor);

}

int myQGraphicsLineItem::getLineId()
{
    { return this->ID;}

}

QRectF myQGraphicsLineItem::boundingRect() const
{
    return QRectF(m_startpoint,m_endpoint);
}

void myQGraphicsLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setPen(this->defaultpen);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawLine(m_startpoint,m_endpoint);

}




//-----------------------------------------------------------------------------------------
//???????????????scene???
//-----------------------------------------------------------------------------------------

CustomScene_::CustomScene_(QGraphicsScene *parent):QGraphicsScene(parent)
{

}

CustomScene_::CustomScene_()
{

}

void CustomScene_::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Custom scene clicked.";
//        QGraphicsScene::mousePressEvent(event);
         if (!event->isAccepted()){
             if (event->button() == Qt::LeftButton) {
                         // ??? Scene ???????????????????????? item
                          event->ignore();
                     }
             else if (event->button() == Qt::RightButton) {
                 // ???????????????????????? item
                 QGraphicsItem *itemToRemove = NULL;
                 foreach (QGraphicsItem *item, items(event->scenePos())) {
                     if (item->type() == QGraphicsItem::UserType+1) {
                         itemToRemove = item;
                         break;
                     }
                 }
                 // ??? Scene ????????? item
                            if (itemToRemove != NULL)
                                removeItem(itemToRemove);
         }
    }
         QGraphicsScene::mousePressEvent(event);
}



void CustomScene_::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << "Custom scene moved.";
    //event->accept();
    event->ignore();
    QGraphicsScene::mouseMoveEvent(event);

}

void CustomScene_::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"scene??????"<<endl;
//    if (event->key() == Qt::Key_Backspace) {
//            // ????????????????????? items
//            qDebug() << "selected items " << selectedItems().size();
//            while (!selectedItems().isEmpty()) {
//                removeItem(selectedItems().front());
//            }
//        }

    QGraphicsScene::keyPressEvent(event);
}

void CustomScene_::drawBackground(QPainter *painter, const QRectF &rect)
{
    QPen pen;
    pen.setColor("#00F5FF");
    pen.setWidth(3);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);
    qreal left=rect.left();
    for(int i=left;i<1024;i+=50)
        {
            painter->drawLine(left,i,1024,i);
        }
    for(int i=left;i<1024;i+=50)
        {
            painter->drawLine(i,left,i,1024);
        }
    painter->drawRoundedRect(rect,15,15);

}






//-----------------------------------------------------------------------------------------
//???????????????View???
//-----------------------------------------------------------------------------------------

int QWGraphicsView::lineID=1;
QWGraphicsView::QWGraphicsView(bool isdefault,QWidget  *parent)
    :QGraphicsView(parent)
    ,IsHasItem(false)
    ,IsDefault(isdefault)
{

  //GlobalItem::getInstance()=*this;
  sence=new CustomScene_();
  this->setScene(sence);
  this->setMouseTracking(true);
  if(IsDefault)
  {
      my_graphicsTextItem *item=new my_graphicsTextItem(QRectF(0,-10,120,50),"?????????",ItemID++);
      VTexts.push_back(item);
      item->setPlainText("??????view");
      this->scene()->addItem(item);
  }

  this->setDragMode(QGraphicsView::RubberBandDrag);

  setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);//view???????????????
  this->installEventFilter(this);

   connect(this,&QWGraphicsView::OnUpdateLine,this,&QWGraphicsView::UpdateLine);

}

bool QWGraphicsView::eventFilter(QObject *obj, QEvent *event)
{
    //qDebug()<<"Qgraphview ?????????????????????"<<endl;
    Q_UNUSED(obj);
    QKeyEvent *keyevent=static_cast<QKeyEvent *>(event);

    if(keyevent->key()==Qt::Key_Tab&&IsHasItem)
    {
        addText();

    }
}

void QWGraphicsView::saveToFile( QTextStream &ts)
{
    //itemtext
    ts<< VTexts.size()<< "\n";
    for(int i=0;i<VTexts.size();i++)
    {

        ts << VTexts[i]->getdata() << "\n";
    }

    //itemline

    ts<<Lines.size() << "\n";
    for (int i=0;i<Lines.size();i++) {
        ts << Lines[i]->getdataline();
        ts << getFrontBackId(Lines[i]->getLineId());
    }




}

void QWGraphicsView::readFromFile(QTextStream &ts)
{
    int size=ts.readLine().toInt();
    for(int i=0;i<size;i++)
    {
        double x,y,widget,height,Posx,Posy;
        int Id,FatherId,tempid;
        ts >> x >> y >> widget >> height >> Id >> FatherId >> Posx >> Posy;
        ts.readLine();
//        qDebug()<< x<< y<< widget<< height << Id << FatherId << Posx << Posy<<endl;
        tempid=Id;
        this->ItemID=++tempid;
        my_graphicsTextItem * readitem=AddItemLoad(QRectF(x,y,widget,height),Id,FatherId
                                                   ,"",QPointF(Posx,Posy));
        readitem->setPlainText(ts.readLine());
    }
    //line
    int lineSize=ts.readLine().toInt();
    for (int i=0;i<lineSize;i++) {
        double sx,sy,ex,ey;
        int Id,FId,BId,tempid;
        ts >> sx >> sy >> ex >> ey >>Id;
        tempid=Id;
        lineID=++tempid;
        ts.readLine();
//        qDebug() << sx << sy << ex << ey <<Id<<endl;

        ts >> FId >> BId;
        ts.readLine();
//        qDebug()<< FId << BId<<endl;
        AddLineLoad(QPointF(sx,sy),QPointF(ex,ey),Id,FId,BId);
    }




}

QString QWGraphicsView::getFrontBackId(int Id)
{
    int FId=0,BId=0;
    for(int i=0;i<VTexts.size();i++)
    {
        for(int j=0;j<VTexts[i]->BackList.size();j++)
        {
            if(VTexts[i]->BackList[j]->getLineId()==Id)
                  BId=VTexts[i]->getItemId();
        }
    }
    for(int i=0;i<VTexts.size();i++)
    {
        for(int j=0;j<VTexts[i]->FrontList.size();j++)
        {
            if(VTexts[i]->FrontList[j]->getLineId()==Id)
                FId= VTexts[i]->getItemId();
        }
    }

    return  QString::asprintf("%d %d\n",FId,BId);
}



my_graphicsTextItem* QWGraphicsView::AddItemText(QRectF rect, int Id, QString text)
{

    int TempID=Id;
    my_graphicsTextItem *newitem=new my_graphicsTextItem(rect,text,Id);
    newitem->setParent(itempos);
    this->scene()->addItem(newitem);
    newitem->setPlainText(text.arg(TempID));
    newitem->setPos(itempos->pos().x()+itempos->getBoundRectWidth()+50,itempos->y());
    VTexts.push_back(newitem);

    myQGraphicsLineItem *line=new myQGraphicsLineItem((static_cast<my_graphicsTextItem*>(newitem->parent())->getBackPoint()->scenePos())
                                                      , newitem->getFrontPoint()->scenePos());

    line->setLineId(lineID);
    Lines.push_back(line);
    lineID++;
    static_cast<my_graphicsTextItem *>(newitem->parent())->BackList.append(line);
    newitem->FrontList.append(line);
    this->scene()->addItem(line);
    return newitem;



}

my_graphicsTextItem *QWGraphicsView::AddItemLoad(QRectF rect, int Id,int FatherId,
                                                 QString text,const QPointF pos)
{

    my_graphicsTextItem *newitem=new my_graphicsTextItem(rect,text,Id);
    this->scene()->addItem(newitem);
    if(Id!=0)
    {
        for(int i=0;i<VTexts.count();i++)
        {
            if(VTexts[i]->getItemId()==FatherId)
            {
                newitem->setParent(VTexts[i]);
            }else
                continue;
        }
    }

    VTexts.push_back(newitem);
    newitem->setPos(pos);
    return newitem;


}

void QWGraphicsView::AddLineLoad(QPointF start, QPointF end, int Id,int FId,int BId)
{
    myQGraphicsLineItem *newline=new myQGraphicsLineItem(start,end);
    newline->setLineId(Id);
    for(int i=0;i<VTexts.size();i++)
    {
        if(VTexts[i]->getItemId()==FId)
        {
            VTexts[i]->FrontList.append(newline);
        }
        if(VTexts[i]->getItemId()==BId)
        {
             VTexts[i]->BackList.append(newline);
        }
    }
    this->scene()->addItem(newline);
    Lines.push_back(newline);

}

void QWGraphicsView::test()
{
    qDebug()<<"View ????????????????????????????????????"<<endl;
    qDebug()<<ItemID<<endl;

    VTexts.push_back(itempos);
    int TempID=ItemID;
    my_graphicsTextItem *newitem=new my_graphicsTextItem(QRectF(0,-10,120,50),QString("?????????%1").arg(ItemID),ItemID++);
//        qDebug()<<VTexts.count()<<"count"<<endl;
//        qDebug()<<ItemID<<"??????"<<endl;
    newitem->setParent(itempos);
    newitem->setPlainText(QString("?????????%1").arg(TempID));

    qDebug()<<newitem->getItemId()<<"???????????????"<<newitem->parent()->objectName()<<(static_cast<my_graphicsTextItem*>(newitem->parent()))->getItemId()<<endl;
    //qDebug()<<"itempos->getBoundRectWidth()"<<itempos->getBoundRectWidth()<<endl;
    newitem->setPos(itempos->pos().x()+itempos->getBoundRectWidth()+50,itempos->y());


    my_graphicsTextItem *parentitem=static_cast<my_graphicsTextItem*>(newitem->parent());

    this->scene()->addItem(newitem);
    qDebug()<<(static_cast<my_graphicsTextItem*>(newitem->parent())->getBackPoint()->scenePos())<<"**"<<newitem->scenePos()<<endl;

    myQGraphicsLineItem *line=new myQGraphicsLineItem((static_cast<my_graphicsTextItem*>(newitem->parent())->getBackPoint()->scenePos()), newitem->getFrontPoint()->scenePos());
    //Lines.push_back(line);
    //static_cast<my_graphicsTextItem *>(newitem->parent())->BackMap.insert(newitem->getItemId(),line);
    //newitem->FrontMap.insert((static_cast<my_graphicsTextItem*>(newitem->parent()))->getItemId(),line);

    static_cast<my_graphicsTextItem *>(newitem->parent())->BackList.append(line);
    newitem->FrontList.append(line);

    //line->setPointSE(QPointF(100,200),QPointF(300,400));
    this->scene()->addItem(line);
    //this->viewport()->update();
    IsHasItem=false;
}

void QWGraphicsView::addText()
{
    AddItemText(QRectF(0,-10,120,50),ItemID++,QString("?????????%1"));
    IsHasItem=false;

}

void QWGraphicsView::mouseMoveEvent(QMouseEvent *event)
{


    if(event->buttons()&Qt::LeftButton&&IsHasItem) //Question: ???????????????????????????????????????  ????????????????????????????????????????????????
    {

        emit OnUpdateLine();
        //event->accept();
    }else
    {

        IsHasItem=false;// ??????????????????false ?????????????????????????????? ???????????????tab ishasitem ???????????????fasle ??????
                        // ?????????????????????if??? ??????????????????????????????????????????????????? ?????????????????????????????????????????????

        event->ignore();
    }

//    event->accept();
    QGraphicsView::mouseMoveEvent(event);
}

void QWGraphicsView::mousePressEvent(QMouseEvent *event)
{

    if(event->button()==Qt::LeftButton)
    {
        QPointF senpoint=mapToScene(event->pos());
         my_graphicsTextItem *tempitem=nullptr;
         foreach (QGraphicsItem *item, items(event->pos())) {
             if (item->type() == QGraphicsItem::UserType+1) {
                 tempitem = static_cast<my_graphicsTextItem *>(item);;
                 itempos=static_cast<my_graphicsTextItem *>(item);
                 //qDebug()<<"???????????????????????????"<<itempos->objectName()<<endl;
                 IsHasItem=true;
                 //qDebug()<<"?????????"<<endl;
                 break;
             }
         }
    }

     QGraphicsView::mousePressEvent(event);

}

void QWGraphicsView::keyPressEvent(QKeyEvent *event)
{


    if(event->key()==Qt::Key_A)
    {
        //qDebug()<<VTexts.count()<<endl;
        foreach (auto var, VTexts) {
            //qDebug()<<var->getpos()<<var->getItemId()<<var->pos()<<endl;

        }
    }
    if(event->key()==Qt::Key_B)
    {
       for(int i=0;i<VTexts.size();i++)
       {
           for(int j=0;j<VTexts[i]->BackList.size();j++)
           {
               //qDebug()<<VTexts[i]->getItemId()<< VTexts[i]->BackList[j]->getLineId()<<endl;
           }
       }


    }
    if(event->key()==Qt::Key_C)
    {
      // qDebug()<<itempos->getFatherId()<<endl;



    }
//    if (event->key() == Qt::Key_Backspace) {
//            // ????????????????????? items
//            qDebug() << "selected items " << this ->scene()->selectedItems().size();
//            while (!this ->scene()->selectedItems().isEmpty()) {
//                for(int i=0;i<this ->scene()->selectedItems().size();i++)
//                {
//                    this ->scene()->removeItem(this ->scene()->selectedItems()[i]);
//                }

//            }
//        }


    QGraphicsView::keyPressEvent(event);
}

void QWGraphicsView::UpdateLine()
{

        //?????????????????????????????? ??????????????????????????????back???????????????
        my_graphicsTextItem * TempCurrentItem_OnMouse=itempos;
        //????????????????????????????????????????????? ???????????????????????? ????????????0???
        //????????????????????????Front????????????????????????Back??????
        QPointF objectpos_Front= TempCurrentItem_OnMouse->getFrontPoint()->scenePos();
        QPointF objectpos_Back=TempCurrentItem_OnMouse->getBackPoint()->scenePos();
        my_graphicsTextItem *test= static_cast<my_graphicsTextItem *>(TempCurrentItem_OnMouse->parent());
        for(int i=0;i<TempCurrentItem_OnMouse->FrontList.count();i++)
        {
            TempCurrentItem_OnMouse->FrontList[i]->setPointSE(test->getBackPoint()->scenePos(),objectpos_Front);
            this->scene()->update();
        } 
        for (int i=2;i<TempCurrentItem_OnMouse->children().count();i++) {
            //qDebug()<<static_cast<my_graphicsTextItem*>(TempCurrentItem_OnMouse->children()[i])->objectName()<<endl;
             TempCurrentItem_OnMouse->BackList[i-2]->setPointSE(objectpos_Back,static_cast<my_graphicsTextItem *>(TempCurrentItem_OnMouse->children()[i])->getFrontPoint()->scenePos());
             this->scene()->update();
        }
}
