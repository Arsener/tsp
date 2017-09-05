#ifndef PAINTEDWIDGET_H
#define PAINTEDWIDGET_H
#include "tsp.h"
#include "mythread.h"
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QPointF>
#include <QtGlobal>
#include <QTime>

class PaintedWidget : public QWidget
{
public:
        PaintedWidget();
        ~PaintedWidget();
        void setDraw(bool flag);
        void setLink(bool flag);
        void setPointsNumber(int number);
        int getPointsNumber();
//public slots:
//        void paintLines();

protected:
        void paintEvent(QPaintEvent *event);

private:
        bool readyToDrawPoints, readyToLink;
        int pointsNumber;
        QPointF *pointf;
        Tsp *tsp;
};

#endif // PAINTEDWIDGET_H
