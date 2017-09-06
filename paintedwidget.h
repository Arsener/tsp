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
        PaintedWidget(QWidget* w);
        ~PaintedWidget();
        void setDraw(bool flag);
        void setLink(bool flag);
        void setLinking(bool flag);
        void setPointsNumber(int number, int xPos, int yPos);
        int getPointsNumber();
        QPointF* getPoints();
        void setAns(int *ans);

protected:
        void paintEvent(QPaintEvent *event);

private:
        bool readyToDrawPoints, readyToLink, linking;
        int pointsNumber;
        QPointF *pointf;
        int *ans;
        int xPos, yPos;
};

#endif // PAINTEDWIDGET_H
