#include "paintedwidget.h"

PaintedWidget::PaintedWidget(QWidget* w) : QWidget(w)
{
    readyToDrawPoints = false;
    readyToLink = false;
    linking = false;

}


PaintedWidget::~PaintedWidget()
{
    delete [] pointf;
    delete [] ans;
}


void PaintedWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if(readyToDrawPoints)
    {
        QPen pen;
        pointf = new QPointF[pointsNumber + 1];
        pen.setWidth(6);
        painter.setPen(pen); // 设置画笔
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        for (int i=0; i<pointsNumber; ++i)
        {
            pointf[i].setX(qrand()%500 + 1);
            pointf[i].setY(qrand()%400 + 1);
        }
        pointf[pointsNumber].setX(this->xPos);
        pointf[pointsNumber].setY(this->yPos);

        painter.drawPoints(pointf, pointsNumber);
        painter.setPen(QPen(QColor(255, 0, 0), 6));
        painter.drawPoint(this->xPos, this->yPos);
    }

    if(linking)
    {
        QPen pen;
        pen.setWidth(6);
        painter.setPen(pen); // 设置画笔
        painter.drawPoints(pointf, pointsNumber);
        painter.setPen(QPen(QColor(255, 0, 0), 6));
        painter.drawPoint(this->xPos, this->yPos);
    }

    if(readyToLink)
    {
        QPen pen;
        pen.setWidth(6);
        painter.setPen(pen); // 设置画笔
        painter.drawPoints(pointf, pointsNumber);
        painter.setPen(QPen(QColor(255, 0, 0), 6));
        painter.drawPoint(this->xPos, this->yPos);

        // 反走样
        painter.setRenderHint(QPainter::Antialiasing, true);
        pen.setWidth(2);
        // 设置画笔颜色
        painter.setPen(QColor(0, 160, 230));

        for(int i = 0; i < pointsNumber; i++)
        {
            // 绘制直线
            painter.drawLine(pointf[ans[i]], pointf[ans[i + 1]]);
        }
        painter.drawLine(pointf[ans[pointsNumber]], pointf[ans[0]]);

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

void PaintedWidget::setLinking(bool flag)
{
    linking = flag;
}

void PaintedWidget::setPointsNumber(int number, int xPos, int yPos)
{
    pointsNumber = number;
    this->xPos = xPos;
    this->yPos = yPos;
}

int PaintedWidget::getPointsNumber()
{
    return pointsNumber;
}

QPointF* PaintedWidget::getPoints()
{
    return this->pointf;
}

void PaintedWidget::setAns(int *ans)
{
    this->ans = ans;
}
