#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paintedwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPalette Pal(palette()); // TODO: learn this

    Pal.setColor(QPalette::Background, Qt::white);
    ui->paintedWidget->setAutoFillBackground(true);
    ui->paintedWidget->setPalette(Pal);

    ui->progressBar->setRange(0, Tsp::MAXGENERATE);
    ui->progressBar->setValue(0);
    t = new MyThread();

    connect(ui->paintPointsButton, SIGNAL(clicked()), this, SLOT(startPainting()));
    connect(ui->linkButton, SIGNAL(clicked()), this, SLOT(prepareLinking()));
    connect(t, SIGNAL(returnResult(int*)), this, SLOT(startLinking(int*)));
    connect(t, SIGNAL(returnProgress(int)), this, SLOT(setProgressBar(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startPainting()
{
    if(linking)
    {
        QMessageBox::warning(this, "Error!", "You can't repaint now!");
        return;
    }
    else
    {
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
        int number = ui->numberLineEdit->text().toInt();

        int xPos = ui->xPosLineEdit->text().toInt();
        int yPos = ui->yPosLineEdit->text().toInt();

        if(number < 0)
        {
            QMessageBox::warning(this, "Error!", "The number of points must be largger than 0 and less than 100!");
            return;
        }

        if(xPos < 0 || xPos >= 500 || yPos < 0 || yPos >= 400)
        {
            QMessageBox::warning(this, "Error!", "Your are not in the right position!");
            return;
        }

        ui->progressBar->setValue(0);
        ui->paintedWidget->setPointsNumber(number, xPos, yPos);
        ui->paintedWidget->setDraw(true);
        ui->paintedWidget->setLink(false);
        ui->paintedWidget->update();
    }
}

void MainWindow::prepareLinking()
{
    if(linking)
    {
        QMessageBox::warning(this, "Error!", "I'm busy now!");
        return;
    }

    linking = true;
    ui->paintedWidget->setDraw(false);
    ui->paintedWidget->setLinking(true);
    Tsp *tsp = new Tsp(ui->numberLineEdit->text().toInt() + 1, ui->paintedWidget->getPoints());
    t->setAttr(tsp, ui->numberLineEdit->text().toInt() + 1, ui->paintedWidget->getPoints());
    t->start();
}

void MainWindow::startLinking(int *ans)
{
    ui->paintedWidget->setAns(ans);
    ui->paintedWidget->setLinking(false);
    ui->paintedWidget->setLink(true);
    ui->paintedWidget->update();
//    QFile f("d:\\city.txt");
//    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
//    {

//    }
//    else
//    {
//        f.open(QIODevice::WriteOnly | QIODevice::Text);
//        QTextStream txtOutput(&f);
//        QString s1("123");
//        quint32 n1(123);

//        txtOutput << s1 << '\n';
//        txtOutput << n1 << '\n';

//        f.close();
//    }
    linking = false;
}

void MainWindow::setProgressBar(int value)
{
    ui->progressBar->setValue(value);
}
