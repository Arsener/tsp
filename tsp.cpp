#include "tsp.h"

Tsp::Tsp(int pointsNumber, QPointF *pointf)
{
    // 随机数种子
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    this->pointsNumber = pointsNumber;
    this->pointf = pointf;

    // 动态分配二维数组
    pointDistance = new double*[pointsNumber];
    for (int i = 0; i < pointsNumber; i++){
        pointDistance[i] = new double[pointsNumber];
    }

    // 设置距离矩阵
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

    // 初始化种群
    for (int i = 0; i < GROUPNUM; i++)
    {
        group[i].point = new int[pointsNumber];
        groupTemp[i].point = new int[pointsNumber];

        // 种群基因数组group[i].point存点的序号
        for (int j = 0; j < pointsNumber; j++)
        {
            group[i].point[j] = j;
            groupTemp[i].point[j] = -1;
        }
    }

    // 打乱基因数组
    for (int i = 0; i < GROUPNUM; i++)
    {
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

// 评价函数
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
        group[i].adapt = sumDistance; // 每条染色体的路径总和
        maxDis += sumDistance; // 种群的总路径
    }

    // 计算染色体的幸存能力，路径越短生存概率越大
    for (int i = 0; i < GROUPNUM; i++)
    {
        group[i].pro = 1 - group[i].adapt / maxDis;
        maxPro += group[i].pro;
    }

    // 对存活概率进行归一化
    for (int i = 0; i < GROUPNUM; i++) {
        group[i].pro = group[i].pro / maxPro;
    }

    // 求最佳路径，选择存活概率最大的个体
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

// 选择函数
void Tsp::choose()
{
    double gradient[GROUPNUM];// 梯度概率
    double choosePro[GROUPNUM];// 选择染色体的随机概率
    int choosed[GROUPNUM];// 选择了的染色体

    // 初始化梯度概率，利用轮盘赌模型
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

    // 随机产生染色体的存活概率
    for (int i = 0; i < GROUPNUM; i++)
    {
        choosePro[i] = (qrand() % 100) / 100.0;
    }

    // 选择能生存的染色体
    for (int i = 0; i < GROUPNUM; i++)
    {
        for (int j = 0; j < GROUPNUM; j++)
        {
            if (choosePro[i] < gradient[j])
            {
                choosed[i] = j; // 第i个位置存放第j个染色体
                break;
            }
        }
    }

    // 拷贝种群
    for (int i = 0; i < GROUPNUM; i++)
    {
        groupTemp[i].adapt = group[i].adapt;
        groupTemp[i].pro = group[i].pro;
        for (int j = 0; j < pointsNumber; j++)
        {
            groupTemp[i].point[j] = group[i].point[j];
        }
    }

    // 数据更新
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

// 变异函数
void Tsp::variation()
{
    double variationPro[GROUPNUM]; // 染色体的变异概率
    int variationFlag[GROUPNUM];// 染色体的变异情况

    // 初始化
    for (int i = 0; i < GROUPNUM; i++)
    {
        variationFlag[i] = 0;
    }

    // 随机产生变异概率
    for (int i = 0; i < GROUPNUM; i++)
    {
        variationPro[i] = (qrand() % 100) / 100.0;
    }

    // 确定可以变异的染色体
    for (int i = 0; i < GROUPNUM; i++)
    {
        if (variationPro[i] < VARIPRO)
        {
            variationFlag[i] = 1;
        }
    }

    // 变异操作，即交换染色体的两个节点
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

// 繁殖函数
void Tsp::breed()
{
    // 记录交叉后父代从另一父代得到的基因
    int *map1 = new int[pointsNumber];
    int *map2 = new int[pointsNumber];

    double breedPro[GROUPNUM];// 染色体的交配概率
    int breedFlag[GROUPNUM];// 染色体的可交配情况

    // 初始化
    for (int i = 0; i < GROUPNUM; i++)
    {
        breedFlag[i] = 0;
    }

    // 随机产生交配概率
    for (int i = 0; i < GROUPNUM; i++)
    {
        breedPro[i] = (qrand() % 100) / 100.0;
    }

    // 确定可以交配的染色体
    int t = 0;
    for (int i = 0; i < GROUPNUM; i++)
    {
        if (breedPro[i] < BREEDPRO)
        {
            breedFlag[i] = 1;
            t++;
        }
    }
    t -= t % 2;// t必须为偶数，产生t/2个交配断点

    int dad = 0, mom = 0;// 记录交配的两个父代
    for (int i = 0; i < t / 2; i++)
    {
        int head = qrand() % pointsNumber;// 交配点1
        int tail = qrand() % pointsNumber;// 交配点2

        // 选出一个需要交配的染色体dad
        for (int j = dad; j < GROUPNUM; j++)
        {
            if (breedFlag[j] == 1)
            {
                dad = j;
                break;
            }
        }

        // 选出另一个需要交配的染色体mom与dad交配
        for (int j = dad + 1; j < GROUPNUM; j++)
        {
            if (breedFlag[j] == 1)
            {
                mom = j;
                break;
            }
        }

        // 进行基因交配，首先保证head>tail
        if (head > tail)
        {
            int temp = head;
            head = tail;
            tail = temp;
        }

        //初始化
        for(int i = 0; i < pointsNumber; i++)
        {
            map1[i] = 0;
            map2[i] = 0;
        }

        int *parent1 = new int[pointsNumber];
        int *parent2 = new int[pointsNumber];
        // 拷贝父代信息
        for(int j = 0; j < pointsNumber; j++)
        {
            parent1[j] = group[dad].point[j];
            parent2[j] = group[mom].point[j];
        }

        // 两交配点中间部分互换
        for (int j = head; j < tail; j++)
        {
            int temp = group[dad].point[j];
            group[dad].point[j] = group[mom].point[j];
            group[mom].point[j] = temp;
            map1[group[dad].point[j]] = 1;
            map2[group[mom].point[j]] = 1;
        }

        /*****************************************
         * 解决冲突
         * 尽量保留父代为交叉部分的顺序
         * 从第二个交叉点循环将剩余的元素添加到个体
         * 以两个父代个体为例：
         * （0 1 2 3 4 5 6 7 8）
         * （5 7 1 8 6 4 2 3 0）
         * 随机选择两个交叉的点，假如第一个点为位置3，第二个交叉点为位置6
         * 交换的点为point[3],point[4],point[5]
         * （下标从0开始）
         * 那么第一个父代个体中（3 4 5）被选中
         * 第二个父代个体中（6 8 7）被选中
         * 交换交叉区间内元素变为
         * （0 1 2 8 6 4 6 7 8）
         * （5 7 1 3 4 5 2 3 0）
         * 然后从第二个交叉点开始，将原来相应的父代按照顺序进行填充子代1
         * 从第6个元素开始，如果选择的元素已经存在在该子代中
         * 跳过该元素（6 7 8 跳过），选择下一个元素
         * 这种过程反复进行，直到所有的城市都被选择一次
         * 最终变换后的子代为
         * （3 5 7 8 6 4 0 1 2）
         * （6 2 0 3 4 5 7 1 8）
         * ***************************************/
        int k1 = tail, k2 = tail;
        for (int j = tail; j < pointsNumber; j++)
        {
            int cur = parent1[j];
            if(map1[cur] == 0)
            {
                group[dad].point[k1] = cur;
                k1++;
                if(k1>=pointsNumber)
                    k1 = 0;
                map1[cur] = 1;
            }

            cur = parent2[j];
            if(map2[cur] == 0)
            {
                group[mom].point[k2++] = cur;
                if(k2>=pointsNumber)
                    k2 = 0;
                map2[cur] = 1;
            }
        }
        for (int j = 0; j < tail; j++)
        {
            int cur = parent1[j];
            if(map1[cur] == 0)
            {
                group[dad].point[k1++] = cur;
                if(k1>=pointsNumber)
                    k1 = 0;
                map1[cur] = 1;
            }

            cur = parent2[j];
            if(map2[cur] == 0)
            {
                group[mom].point[k2++] = cur;
                if(k2>=pointsNumber)
                    k2 = 0;
                map2[cur] = 1;
            }
        }

        // 比较子代与父代，留下较好的一代
        double disDad = getDis(parent1);
        double disMom = getDis(parent2);
        double disSon1 = getDis(group[dad].point);
        double disSon2 = getDis(group[mom].point);

        /*****************************************
         * 假设父代A0和B0交配产生两个子代A1和B1
         * 如果交换部分的长度小于总长度的一半
         * 那么A1和A0更像，B1和B0更像，依次比较
         * 否则，A1和B0更像，B1和A0更像，依次比较
         * ***************************************/
        if (tail - head < pointsNumber / 2)
        {
            if (disDad < disSon1)
            {
                for (int j = 0; j < pointsNumber; j++)
                {
                    group[dad].point[j] = parent1[j];
                }
            }

            if (disMom < disSon2)
            {
                for (int j = 0; j < pointsNumber; j++)
                {
                    group[mom].point[j] = parent2[j];
                }
            }
        }
        else
        {
            if (disDad < disSon2)
            {
                for (int j = 0; j < pointsNumber; j++)
                {
                    group[mom].point[j] = parent1[j];
                }
            }

            if (disMom < disSon1)
            {
                for (int j = 0; j < pointsNumber; j++)
                {
                    group[dad].point[j] = parent2[j];
                }
            }
        }

        delete [] parent1;
        delete [] parent2;

    }

    delete [] map1;
    delete [] map2;
}

int* Tsp::getOrder(int answer)
{
    return group[answer].point;
}

// 计算距离
double Tsp::getDis(int *gene)
{
    double sumDistance = 0;
    for (int j = 1; j < pointsNumber; j++)
    {
        sumDistance += pointDistance[gene[j - 1]][gene[j]];
    }
    sumDistance += pointDistance[gene[pointsNumber - 1]][gene[0]];

    return sumDistance;
}

