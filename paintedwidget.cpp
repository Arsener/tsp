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
        int answer = tsp->judge();

        int t = 0;
        while(t++ < tsp->MAXGENERATE)
        {
            tsp->choose();
            tsp->breed();
            tsp->variation();
            answer = tsp->judge();
        }

        int *ans = tsp->getOrder(answer);

        // 反走样
        painter.setRenderHint(QPainter::Antialiasing, true);
        pen.setWidth(2);
        // 设置画笔颜色
        painter.setPen(QColor(0, 160, 230));

        for(int i = 0; i < pointsNumber - 1; i++)
        {
            // 绘制直线
            painter.drawLine(pointf[ans[i]], pointf[ans[i + 1]]);
        }
        painter.drawLine(pointf[ans[pointsNumber - 1]], pointf[ans[0]]);

        delete tsp;
        delete [] ans;
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
