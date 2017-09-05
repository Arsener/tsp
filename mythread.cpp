#include "mythread.h"

MyThread::MyThread(Tsp *tsp, int pointsNumber, QPointF *pointf, QWidget *w)
{
    this->tsp = tsp;
    this->pointsNumber = pointsNumber;
    this->pointf = pointf;
    this->w = w;
}


void MyThread::run()
{
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


    QPen pen;
    QPainter painter(w);
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

    delete [] ans;

}
