#include "mythread.h"

MyThread::MyThread()
{

}


MyThread::~MyThread()
{
    delete tsp;
    delete [] ans;
    delete [] pointf;
}


void MyThread::setAttr(Tsp *tsp, int pointsNumber, QPointF *pointf)
{
    this->tsp = tsp;
    this->pointsNumber = pointsNumber;
    this->pointf = pointf;
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
        emit returnProgress(t);
    }

    this->ans = tsp->getOrder(answer);

    emit returnResult(ans);
}
