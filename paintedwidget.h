#ifndef PAINTEDWIDGET_H
#define PAINTEDWIDGET_H
#include "tsp.h"
#include "mythread.h"
#include <QPen>
#include <QTime>
#include <QPointF>
#include <QWidget>
#include <QPainter>
#include <QtGlobal>
#include <QPaintEvent>

class PaintedWidget : public QWidget
{
public:
        PaintedWidget(QWidget* w);
        ~PaintedWidget();
        int getPointsNumber();
        void setAns(int *ans);
        void setDraw(bool flag);
        void setLink(bool flag);
        void setLinking(bool flag);
        void setPainted(bool flag);
        void setPointsNumber(int number, int xPos, int yPos);
        QPointF* getPoints();

protected:
        void paintEvent(QPaintEvent *event);

private:
        bool readyToDrawPoints, readyToLink, linking, painted;
        int xPos, yPos;
        int pointsNumber;
        int *ans;
        QPointF *pointf;
};

#endif // PAINTEDWIDGET_H
