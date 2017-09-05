#ifndef MYTHREAD_H
#define MYTHREAD_H

#include "tsp.h"
#include <QThread>
#include <QWidget>
#include <QLineEdit>
#include <QPainter>
#include <QPen>
#include <QPointF>

class MyThread : public QThread
{
public:
    MyThread(Tsp *tsp, int pointsNumber, QPointF *pointf, QWidget *w);

protected:
    void run();

private:
    Tsp *tsp;
    int pointsNumber;
    QPointF *pointf;
    QWidget *w;
};

#endif // MYTHREAD_H
