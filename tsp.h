#ifndef TSP_H
#define TSP_H
#include "group.h"
#include <QTime>
#include <QPointF>
#include <QtCore/qmath.h>

class Tsp
{
public:
    Tsp(int pointsNumber, QPointF *pointf);
    ~Tsp();

    const double BREEDPRO = 0.9;// 交配概率
    const double VARIPRO = 0.05;// 变异概率
    const static int GROUPNUM = 100;// 种群大小
    const static int MAXGENERATE = 10000;// 遗传代数
    int judge();
    void breed();
    void choose();
    void variation();
    double getDis(int *gene);
    int* getOrder(int anwser);

private:
    int pointsNumber;
    double **pointDistance;// 城市之间的距离
    QPointF *pointf;
    Group group[GROUPNUM];
    Group groupTemp[GROUPNUM];
};

#endif // TSP_H
