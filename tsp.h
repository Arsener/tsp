#ifndef TSP_H
#define TSP_H
#include "group.h"
#include <QPointF>
#include <QtCore/qmath.h>
#include <QTime>

class Tsp
{
public:
    Tsp(int pointsNumber, QPointF *pointf);
    ~Tsp();

    const static int MAXGENERATE = 5000;
    const double BREEDPRO = 0.75;  //交配概率
    const double VARIPRO = 0.04; //变异概率
    const static int GROUPNUM = 500;  //种群的大小
    int judge();
    void choose(int t);
    void variation();
    void breed();
    int* getOrder(int anwser);

private:
    int pointsNumber;
    double **pointDistance;//城市之间的距离
    Group group[GROUPNUM];
    Group groupTemp[GROUPNUM];
    QPointF *pointf;
    Group bestIndivisual;
};

#endif // TSP_H
