#ifndef MYTHREAD_H
#define MYTHREAD_H

#include "tsp.h"
#include <QThread>
#include <QLineEdit>
#include <QPainter>
#include <QPen>
#include <QPointF>

class MyThread : public QThread
{
    Q_OBJECT

public:
    MyThread();
    int *ans;
    void setAttr(Tsp *tsp, int pointsNumber, QPointF *pointf);

signals:
    void returnResult(int*);


protected:
    void run();

private:
    Tsp *tsp;
    int pointsNumber;
    QPointF *pointf;
};

#endif // MYTHREAD_H
