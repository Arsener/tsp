#include "paintedwidget.h"

PaintedWidget::PaintedWidget()
{
    readyToDraw = false;
    resize(800, 600);

}


void PaintedWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if(readyToDraw)
    {
        QPen pen;
        QPointF *pointf = new QPointF[pointsNumber];
        pen.setWidth(6);
        painter.setPen(pen); // 设置画笔
        for (int i=0; i<pointsNumber; ++i)
        {
            pointf[i].setX(2.0+i*10.0);
            pointf[i].setY(130.0);
        }

        painter.drawPoints(pointf, pointsNumber);

        delete [] pointf;
    }

    QWidget::paintEvent(event);
}

void PaintedWidget::setDraw(bool flag)
{
    readyToDraw = flag;
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
