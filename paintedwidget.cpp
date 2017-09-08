#include "paintedwidget.h"

PaintedWidget::PaintedWidget(QWidget* w) : QWidget(w)
{
    readyToDrawPoints = false;
    readyToLink = false;
    linking = false;
    painted = false;

    // 随机数种子
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
}


PaintedWidget::~PaintedWidget()
{
    delete [] pointf;
    delete [] ans;
}


void PaintedWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // 描点
    if(readyToDrawPoints)
    {
        pointf = new QPointF[pointsNumber + 1];
        painter.setPen(QPen(QColor(0, 0, 0), 6)); // 设置画笔

        // 随机产生点
        for (int i=0; i<pointsNumber; ++i)
        {
            pointf[i].setX(qrand()%500 + 1);
            pointf[i].setY(qrand()%400 + 1);
        }

        // 出发点
        pointf[pointsNumber].setX(this->xPos);
        pointf[pointsNumber].setY(this->yPos);

        painter.drawPoints(pointf, pointsNumber);

        // 出发点单独绘制，颜色为红色
        painter.setPen(QPen(QColor(255, 0, 0), 6));
        painter.drawPoint(this->xPos, this->yPos);
        readyToDrawPoints = false;
        painted = true;
    }

    // 当处于连线状态和描点结束状态时，保证面板失焦后不重绘
    if(linking || painted)
    {
        painter.setPen(QPen(QColor(0, 0, 0), 6));
        painter.drawPoints(pointf, pointsNumber);
        painter.setPen(QPen(QColor(255, 0, 0), 6));
        painter.drawPoint(this->xPos, this->yPos);
    }

    // 计算出结果之后开始连线
    if(readyToLink)
    {
        painter.setPen(QPen(QColor(0, 0, 0), 6));
        painter.drawPoints(pointf, pointsNumber);
        painter.setPen(QPen(QColor(255, 0, 0), 6));
        painter.drawPoint(this->xPos, this->yPos);

        // 直线无锯齿
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(QColor(0, 160, 230), 2));

        for(int i = 0; i < pointsNumber; i++)
        {
            // 绘制直线
            painter.drawLine(pointf[ans[i]], pointf[ans[i + 1]]);
        }
        painter.drawLine(pointf[ans[pointsNumber]], pointf[ans[0]]);
        painted = false;
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

void PaintedWidget::setPainted(bool flag)
{
    painted = flag;
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
