#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include<QHoverEvent>
#include<QColor>
namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

private:
    Ui::MyWidget *ui;
    QColor widgetnormallcolor=QColor("#E0EEEE");
    QColor wdigetentercolor=QColor(70, 70, 70, 150);
    QTimer* hovTimer;
protected:
    void paintEvent(QPaintEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
public:
    QColor Getwidgetnormallcolor();
    QColor Getwdigetentercolor();
    void Setwidgetnormallcolor(QColor color);


private slots:
    void on_pushButton_clicked();
};

#endif // MYWIDGET_H
