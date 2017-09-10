#ifndef MYTHREAD_H
#define MYTHREAD_H

#include "tsp.h"
#include <QPen>
#include <QThread>
#include <QPointF>
#include <QPainter>
#include <QLineEdit>

class MyThread : public QThread
{
    Q_OBJECT

public:
    MyThread();
    ~MyThread();
    void setAttr(int pointsNumber, QPointF *pointf);

signals:
    void returnResult(int*);
    void returnProgress(int);

protected:
    void run();

private:
    int pointsNumber;
    int *ans;
    Tsp *tsp;
};

#endif // MYTHREAD_H
