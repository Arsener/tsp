#include "paintedwidget.h"

PaintedWidget::PaintedWidget()
{
    readyToDrawPoints = false;
    readyToLink = false;
//    resize(8, 6);

}


PaintedWidget::~PaintedWidget()
{
    delete [] pointf;
    delete tsp;
}


void PaintedWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
//    painter.setBrush(Qt::white);

    if(readyToDrawPoints)
    {
        QPen pen;
        pointf = new QPointF[pointsNumber];
        pen.setWidth(6);
        painter.setPen(pen); // 设置画笔
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        for (int i=0; i<pointsNumber; ++i)
        {
            pointf[i].setX(qrand()%700 + 1);
            pointf[i].setY(qrand()%500 + 1);
        }
//        for(int i = 1; i < pointsNumber; i++)
//        {
//            if(i < 50)
//            {

//            }
//        }

        painter.drawPoints(pointf, pointsNumber);
    }


    if(readyToLink)
    {
        QPen pen;
        pen.setWidth(6);
        painter.setPen(pen); // 设置画笔
        painter.drawPoints(pointf, pointsNumber);

        tsp = new Tsp(pointsNumber, pointf);
        MyThread *t = new MyThread(tsp, pointsNumber, pointf, this);
        t->start();
    }

    QWidget::paintEvent(event);
}

void PaintedWidget::setDraw(bool flag)
{
    readyToDrawPoints = flag;
}

void PaintedWidget::setLink(bool flag)
{
    readyToLink = flag;
}

void PaintedWidget::setPointsNumber(int number)
{
    pointsNumber = number;
}

int PaintedWidget::getPointsNumber()
{
    return pointsNumber;
}

//void PaintedWidget::paintLines()
//{
//  readyToDraw = true;
//  update(); // This forces a repaint of the widget with paintEvent()
//}
