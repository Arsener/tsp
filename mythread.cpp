#include "mythread.h"

MyThread::MyThread()
{

}


MyThread::~MyThread()
{
    delete tsp;
    delete [] ans;
}


void MyThread::setAttr(int pointsNumber, QPointF *pointf)
{
    this->pointsNumber = pointsNumber;
    this->tsp = new Tsp(pointsNumber, pointf);
}


void MyThread::run()
{
    // 开始进行遗传计算
    int answer = tsp->judge();

    int t = 0;
    while(t++ < tsp->MAXGENERATE)
    {
        tsp->choose();
        tsp->breed();
        tsp->variation();
        answer = tsp->judge();

        // 将实时进度发射出去，更新进度条
        emit returnProgress(t);
    }

    this->ans = tsp->getOrder(answer);

    //将计算结果发射出去，开始连线
    emit returnResult(ans);
}
