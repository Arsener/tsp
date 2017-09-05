#ifndef TSP_H
#define TSP_H
#include "group.h"
#include <QPointF>
//#include <string>
//#include <cstdlib>
#include <QtCore/qmath.h>
#include <QTime>
//#include <algorithm>

class Tsp
{
public:
    Tsp(int pointsNumber, QPointF *pointf);
    ~Tsp();

    const int MAXGENERATE = 10000;
    const double BREEDPRO = 0.8;  //交配概率
    const double VARIPRO = 0.05; //变异概率
    const static int GROUPNUM = 1000;  //种群的大小
    int judge();
    void choose();
    void variation();
    void breed();
    int* getOrder(int anwser);

private:
    int pointsNumber;
    double **pointDistance;//城市之间的距离
    Group group[GROUPNUM];
    Group groupTemp[GROUPNUM];
    QPointF *pointf;
};

#endif // TSP_H
