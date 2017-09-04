#ifndef PAINTEDWIDGET_H
#define PAINTEDWIDGET_H
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QPointF>

class PaintedWidget : public QWidget
{
public:
        PaintedWidget();
        void setDraw(bool flag);
        void setPointsNumber(int number);
        int getPointsNumber();
//public slots:
//        void paintLines();

protected:
        void paintEvent(QPaintEvent *event);

private:
        bool readyToDraw;
        int pointsNumber;
};

#endif // PAINTEDWIDGET_H
