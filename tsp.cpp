#include "tsp.h"

Tsp::Tsp(int pointsNumber, QPointF *pointf)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    this->pointsNumber = pointsNumber;
    this->pointf = pointf;

    pointDistance = new double*[pointsNumber];
    for (int i = 0; i < pointsNumber; i++){
        pointDistance[i] = new double[pointsNumber];
    }

    for (int m = 0; m < pointsNumber; m++) {
        for (int n = 0; n < pointsNumber; n++) {
            if (m == n)
                pointDistance[m][n] = 0;
            else {
                double x = pointf[m].rx() - pointf[n].rx();
                double y = pointf[m].ry() - pointf[n].ry();
                double tmp = qSqrt(qPow(x, 2) + qPow(y, 2));
                pointDistance[m][n] = tmp;
                pointDistance[n][m] = tmp;
            }
        }
    }

    for (int i = 0; i < GROUPNUM; i++)  //初始化
    {
        group[i].point = new int[pointsNumber];
        groupTemp[i].point = new int[pointsNumber];
        for (int j = 0; j < pointsNumber; j++)
        {
            group[i].point[j] = -1;
            groupTemp[i].point[j] = -1;
        }
    }

    for (int i = 0; i < GROUPNUM; i++)
    {
        //产生10个不相同的数字
        for (int j = 0; j < pointsNumber; j++)
        {
            group[i].point[j] = j;
        }
        for(int j = 0; j < pointsNumber; j++)
        {
           int r = j + qrand() % (pointsNumber - j);
           int temp = group[i].point[j];
           group[i].point[j] = group[i].point[r];
           group[i].point[r] = temp;
        }
    }
}

Tsp::~Tsp()
{
    delete [] pointf;
    for(int i = 0; i < pointsNumber; i++)
    {
        delete [] pointDistance[i];
    }
    delete [] pointDistance;
}

int Tsp::judge()
{
    double sumDistance;
    double maxDis = 0;
    double maxPro = 0;
    for (int i = 0; i < GROUPNUM; i++)
    {
        sumDistance = 0;
        for (int j = 1; j < pointsNumber; j++)
        {
            sumDistance += pointDistance[group[i].point[j - 1]][group[i].point[j]];
        }
        sumDistance += pointDistance[group[i].point[pointsNumber - 1]][group[i].point[0]];
        group[i].adapt = sumDistance; //每条染色体的路径总和
                                      //printf("%d",group[i].adapt);
        maxDis += sumDistance; //种群的总路径
    }
    //计算染色体的幸存能力,路劲越短生存概率越大
    for (int i = 0; i < GROUPNUM; i++)
    {
        group[i].pro = 1 - group[i].adapt / maxDis;
        maxPro += group[i].pro;
    }

    for (int i = 0; i < GROUPNUM; i++) {
        group[i].pro = group[i].pro / maxPro;
    }//在种群中的幸存概率,总和为1
     //求最佳路径

    int bestSolution = 0;
    for (int i = 0; i < GROUPNUM; i++)
    {
        if (group[i].pro > group[bestSolution].pro)
        {
            bestSolution = i;
        }
    }
    return bestSolution;
}

void Tsp::choose()
{
    double gradient[GROUPNUM];//梯度概率
    double choosePro[GROUPNUM];//选择染色体的随机概率
    int choosed[GROUPNUM];//选择了的染色体
                  //初始化梯度概率
    for (int i = 0; i < GROUPNUM; i++)
    {
        gradient[i] = 0.0;
        choosePro[i] = 0.0;
    }
    gradient[0] = group[0].pro;

    for (int i = 1; i < GROUPNUM; i++)
    {
        gradient[i] = gradient[i - 1] + group[i].pro;
    }

    //随机产生染色体的存活概率
    for (int i = 0; i < GROUPNUM; i++)
    {
        choosePro[i] = (qrand() % 100) / 100.0;
    }

    //选择能生存的染色体
    for (int i = 0; i < GROUPNUM; i++)
    {
        for (int j = 0; j < GROUPNUM; j++)
        {
            if (choosePro[i] < gradient[j])
            {
                choosed[i] = j; //第i个位置存放第j个染色体
                break;
            }
        }
    }
    //拷贝种群
    for (int i = 0; i < GROUPNUM; i++)
    {
        groupTemp[i].adapt = group[i].adapt;
        groupTemp[i].pro = group[i].pro;
        for (int j = 0; j < pointsNumber; j++)
        {
            groupTemp[i].point[j] = group[i].point[j];
        }
    }
    //数据更新
    for (int i = 0; i < GROUPNUM; i++)
    {
        int temp = choosed[i];
        group[i].adapt = groupTemp[temp].adapt;
        group[i].pro = groupTemp[temp].pro;
        for (int j = 0; j < pointsNumber; j++)
        {
            group[i].point[j] = groupTemp[temp].point[j];

        }
    }
}

void Tsp::variation()
{
    double variationPro[GROUPNUM]; //染色体的变异概率
    int variationFlag[GROUPNUM];//染色体的变异情况
    for (int i = 0; i < GROUPNUM; i++)//初始化
    {
        variationFlag[i] = 0;
    }

    //随机产生变异概率
    for (int i = 0; i < GROUPNUM; i++)
    {
        variationPro[i] = (qrand() % 100) / 100.0;
    }
    //确定可以变异的染色体
    for (int i = 0; i < GROUPNUM; i++)
    {
        if (variationPro[i] < VARIPRO)
        {
            variationFlag[i] = 1;
        }
    }
    //变异操作,即交换染色体的两个节点
    for (int i = 0; i < GROUPNUM; i++)
    {
        if (variationFlag[i] == 1)
        {
            int temp1 = qrand() % pointsNumber;
            int temp2 = qrand() % pointsNumber;
            int point = group[i].point[temp1];
            group[i].point[temp1] = group[i].point[temp2];
            group[i].point[temp2] = point;
        }
    }
}

void Tsp::breed()
{
    int *map1 = new int[pointsNumber];
    int *map2 = new int[pointsNumber];
    double breedPro[GROUPNUM];//染色体的交配概率
    int breedFlag[GROUPNUM];//染色体的可交配情况
    int flag = 0;
    //初始化
    for (int i = 0; i < GROUPNUM; i++)
    {
        breedFlag[i] = 0;
    }

    //随机产生交配概率
    for (int i = 0; i < GROUPNUM; i++)
    {
        breedPro[i] = (qrand() % 100) / 100.0;
    }

    //确定可以交配的染色体
    int t = 0;
    for (int i = 0; i < GROUPNUM; i++)
    {
        if (breedPro[i] < BREEDPRO)
        {
            breedFlag[i] = 1;
            t++;
        }
    }
    t -= t % 2;//t必须为偶数,产生t/2个0-9交配断点
    int dad = 0, mom = 0;     //temp1号染色体和temp2染色体交配
    for (int i = 0; i < t / 2; i++)  //如果有5个染色体需要交配，但是实际上t/2代表只有4个染色体会真正的交配，剩下的1个再加上5个不需要交配的染色体直接进入下一代。
    {
        int head = qrand() % pointsNumber;//交配点1
        int tail = qrand() % pointsNumber;//交配点2
                                 //选出一个需要交配的染色体1
        for (int j = dad; j < GROUPNUM; j++)
        {
            if (breedFlag[j] == 1)
            {
                dad = j;
                break;
            }
        }
        //选出另一个需要交配的染色体2与1交配
        for (int j = dad + 1; j < GROUPNUM; j++)
        {
            if (breedFlag[j] == 1)
            {
                mom = j;
                break;
            }
        }
        //进行基因交配
        if (head > tail) //保证point1<=point2
        {
            int temp = head;
            head = tail;
            tail = temp;
        }
        //初始化
        for(int i = 0; i < pointsNumber; i++)
        {
            map1[i] = -1;
            map2[i] = -1;
        }
//        memset(map1, -1, sizeof(map1));
//        memset(map2, -1, sizeof(map2));
        //断点之间的基因产生映射
        for (int j = head; j <= tail; j++)
        {
            map1[group[dad].point[j]] = group[mom].point[j];
            map2[group[mom].point[j]] = group[dad].point[j];
        }
        //断点两边的基因互换
        for (int j = 0; j < head; j++)
        {
            int temp = group[dad].point[j];
            group[dad].point[j] = group[mom].point[j];
            group[mom].point[j] = temp;
        }
        for (int j = tail + 1; j < pointsNumber; j++)
        {
            int temp = group[dad].point[j];
            group[dad].point[j] = group[mom].point[j];
            group[mom].point[j] = temp;
        }
        //printf("处理冲突---------------------\n");
        //处理染色体1产生的冲突基因
        for (int j = 0; j < pointsNumber; j++)
        {
            if (j >= head && j <= tail)
            {
                continue;
            }
            for (int k = head; k <= tail; k++)
            {
                if (group[dad].point[j] == group[dad].point[k])
                {
                    group[dad].point[j] = map1[group[dad].point[j]];  //如果相等则进行映射操作
                                                                        //find
                    for (int h = head; h <= tail; h++)
                    {
                        if (group[dad].point[j] == group[dad].point[h])  //考虑如果映射一次仍然具有相同的城市，则再进行一次映射操作
                        {
                            flag = 1;
                            break;
                        }
                    }
                    if (flag == 1)  //flag不断判断同一染色体中是否还存在相同的城市
                    {
                        k = head - 1;
                        flag = 0;
                    }
                    else
                    {
                        flag = 0;
                        break;
                    }
                }
            }

        }

        //处理2染色体产生的冲突基因
        for (int j = 0; j < pointsNumber; j++)
        {
            if (j >= head && j <= tail)
            {
                continue;
            }
            for (int k = head; k <= tail; k++)
            {
                if (group[mom].point[j] == group[mom].point[k])
                {
                    group[mom].point[j] = map2[group[mom].point[j]];
                    //find
                    for (int h = head; h <= tail; h++)
                    {
                        if (group[mom].point[j] == group[mom].point[h])
                        {
                            flag = 1;
                            break;
                        }
                    }
                    if (flag == 1)
                    {
                        k = head - 1;
                        flag = 0;
                    }
                    else
                    {
                        flag = 0;
                        break;
                    }
                }
            }
        }
        dad = mom + 1;
    }

    delete [] map1;
    delete [] map2;
}

int* Tsp::getOrder(int answer)
{
    return group[answer].point;
}

