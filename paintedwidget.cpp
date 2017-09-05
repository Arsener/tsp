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

        painter.drawPoints(pointf, pointsNumber);
    }


    if(readyToLink)
    {
        QPen pen;
        pen.setWidth(6);
        painter.setPen(pen); // 设置画笔
        painter.drawPoints(pointf, pointsNumber);

        // 反走样
        painter.setRenderHint(QPainter::Antialiasing, true);
        pen.setWidth(2);
        // 设置画笔颜色
        painter.setPen(QColor(0, 160, 230));

        for(int i = 0; i < pointsNumber - 1; i++)
        {
            // 绘制直线
            painter.drawLine(pointf[i], pointf[i + 1]);
        }
//        painter.drawLine(pointf[pointsNumber - 1], pointf[0]);
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
