#include "paintedwidget.h"

PaintedWidget::PaintedWidget(QWidget* w) : QWidget(w)
{
    readyToDrawPoints = false;
    readyToLink = false;
    linking = false;
//    resize(8, 6);

}


PaintedWidget::~PaintedWidget()
{
    delete [] pointf;
//    delete tsp;
}


void PaintedWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
//    painter.setBrush(Qt::white);

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
//        for(int i = 1; i < pointsNumber; i++)
//        {
//            if(i < 50)
//            {

//            }
//        }

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

//        tsp = new Tsp(pointsNumber, pointf);
//        MyThread *t = new MyThread(tsp, pointsNumber, pointf);
//        t->start();
//        int *ans = t->ans;

//        t->quit();
//        t->wait();
//        delete t;

        // TODO: 解决线程问题
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

//void PaintedWidget::paintLines()
//{
//  readyToDraw = true;
//  update(); // This forces a repaint of the widget with paintEvent()
//}
