#ifndef GROUP_H
#define GROUP_H
class Group
{
public:
    Group();
    ~Group();

    int *point;// 基因
    double pro;// 存活概率
    double adapt;// 适应度
};

#endif // GROUP_H
