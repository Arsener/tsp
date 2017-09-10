#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paintedwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Tsp Linking");
    this->setWindowIcon(QIcon(":/new/prefix1/icon"));

    // 设置画板为白色
    QPalette Pal(palette()); // TODO: learn this
    Pal.setColor(QPalette::Background, Qt::white);
    ui->paintedWidget->setAutoFillBackground(true);
    ui->paintedWidget->setPalette(Pal);

    // 设置三个QLineEdit的输入类型为正整数
    ui->numberLineEdit->setValidator(new QIntValidator(1, 999999999, this));
    ui->xPosLineEdit->setValidator(new QIntValidator(0, 999999999, this));
    ui->yPosLineEdit->setValidator(new QIntValidator(0, 999999999, this));
    ui->progressBar->setRange(0, Tsp::MAXGENERATE);
    ui->progressBar->setValue(0);

    // 获取文件默认存储路径
    QFile dirctoryFile("C:\\Users\\arsener\\Documents\\Qt\\tsp\\file_directory.txt");
    if(!dirctoryFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    else
    {
        QTextStream txtInput(&dirctoryFile);
        fileDirectory = txtInput.readLine();
    }
    dirctoryFile.close();

    t = new MyThread();

    // 信号槽连接
    connect(ui->cleanButton, SIGNAL(clicked()), this, SLOT(clean()));
    connect(t, SIGNAL(returnResult(int*)), this, SLOT(startLinking(int*)));
    connect(ui->linkButton, SIGNAL(clicked()), this, SLOT(prepareLinking()));
    connect(t, SIGNAL(returnProgress(int)), this, SLOT(setProgressBar(int)));
    connect(ui->checkBox, SIGNAL(stateChanged(int)), this, SLOT(setChecked(int)));
    connect(ui->paintPointsButton, SIGNAL(clicked()), this, SLOT(startPainting()));
    connect(ui->setFileAction, SIGNAL(triggered(bool)), this, SLOT(setFileDirectory()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete t;
}

// 清除画布
void MainWindow::clean()
{
    if(linking)
    {
        QMessageBox::warning(this, "Error!", "You can't clean now!");
        return;
    }
    //恢复初始状态
    linking = false;
    painted = false;
    pointNumber = -1;
    ui->paintedWidget->setLink(false);
    ui->paintedWidget->setLinking(false);
    ui->paintedWidget->setPainted(false);
    ui->paintedWidget->setDraw(false);
    ui->progressBar->setValue(0);
    ui->paintedWidget->update();
}

// 开始描点
void MainWindow::startPainting()
{
    if(linking)
    {
        QMessageBox::warning(this, "Error!", "You can't repaint now!");
        return;
    }

    painted = true;
    if(ui->numberLineEdit->text() == "")
    {
        QMessageBox::warning(this, "Error!", "Please input the number!");
        return;
    }

    if(ui->xPosLineEdit->text() == "" || ui->yPosLineEdit->text() == "")
    {
        QMessageBox::warning(this, "Error!", "Please input your position!");
        return;
    }
    pointNumber = ui->numberLineEdit->text().toInt();

    int xPos = ui->xPosLineEdit->text().toInt();
    int yPos = ui->yPosLineEdit->text().toInt();

    if(pointNumber > 500)
    {
        QMessageBox::warning(this, "Error!", "Too many points!");
        return;
    }

    if(pointNumber == 0)
    {
        QMessageBox::warning(this, "Error!", "At least one point!");
        return;
    }

    if(xPos < 0 || xPos >= 500 || yPos < 0 || yPos >= 400)
    {
        QMessageBox::warning(this, "Error!", "Your are not in the right position!");
        return;
    }

    ui->progressBar->setValue(0);
    ui->paintedWidget->setPointsNumber(pointNumber, xPos, yPos);
    ui->paintedWidget->setDraw(true);
    ui->paintedWidget->setLink(false);
    ui->paintedWidget->update();

}

// 连线准备过程，用遗传算法进行计算
void MainWindow::prepareLinking()
{
    if(!painted)
    {
        QMessageBox::warning(this, "Error!", "Please paint some points first!");
        return;
    }

    if(linking)
    {
        QMessageBox::warning(this, "Error!", "I'm busy now!");
        return;
    }

    linking = true;
    ui->paintedWidget->setDraw(false);
    ui->paintedWidget->setLinking(true);
    t->setAttr(pointNumber + 1, ui->paintedWidget->getPoints());
    t->start();
}

// 计算出结果并开始连线
void MainWindow::startLinking(int *ans)
{
    ui->paintedWidget->setAns(ans);
    ui->paintedWidget->setLinking(false);
    ui->paintedWidget->setLink(true);
    ui->paintedWidget->update();


    linking = false;

    // 如果未选择生成文件并保存则直接返回
    if(!file)
    {
        return;
    }

    // 设置文件名
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), fileDirectory, tr("*.txt")); //选择路径
    if(filename.isEmpty())
    {
        return;
    }
    else
    {
        QFile f(filename);
        if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            return;
        }
        else
        {
            f.open(QIODevice::WriteOnly | QIODevice::Text);

            // 找到出发点在结果数组中的位置，从这一点开始按照连线顺序写入文件
            int startPoint;
            for(int i = 0; i < pointNumber + 1; i++)
            {
                if(ans[i] == pointNumber)
                {
                    startPoint = i;
                    break;
                }
            }

            QTextStream txtOutput(&f);
            for(int i = startPoint; i < pointNumber + 1; i++)
            {
                QString currentPoint("(" + QString::number(ui->paintedWidget->getPoints()[ans[i]].rx()) + "," + QString::number(ui->paintedWidget->getPoints()[ans[i]].ry()) + ")\n");
                txtOutput << currentPoint;
            }
            for(int i = 0; i < startPoint; i++)
            {
                QString currentPoint("(" + QString::number(ui->paintedWidget->getPoints()[ans[i]].rx()) + "," + QString::number(ui->paintedWidget->getPoints()[ans[i]].ry()) + ")\n");
                txtOutput << currentPoint;
            }

            f.close();
        }
    }
}

// 设置进度条
void MainWindow::setProgressBar(int value)
{
    ui->progressBar->setValue(value);
}

// 设置文件默认存储位置
void MainWindow::setFileDirectory()
{
    QString tmpFileDirectory = QFileDialog::getExistingDirectory(this, tr("Choose Directory"), fileDirectory, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(tmpFileDirectory.trimmed() != "")
    {
        fileDirectory = tmpFileDirectory;
    }

    QFile dirctoryFile("C:\\Users\\arsener\\Documents\\Qt\\tsp\\file_directory.txt");
    if(!dirctoryFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }
    else
    {
        // 将修改后的默认存储位置写入文件
        QTextStream txtoutput(&dirctoryFile);
        QString dir(fileDirectory);
        txtoutput << dir;
    }
    dirctoryFile.close();
}

void MainWindow::setChecked(int state)
{
    if (state == Qt::Checked) // "选中"
    {
        file = true;
    }
    else // "未选中"
    {
        file = false;
    }
}
