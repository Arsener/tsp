#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paintedwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    w = new QWidget(this);
//    setCentralWidget(&w);
//    paintedWidget = new PaintedWidget();
//    numberLineEdit = new QLineEdit();
//    paintPointsButton = new QPushButton();
//    linkButton = new QPushButton();
//    vLayout = new QVBoxLayout();
//    hLayout = new QHBoxLayout();

    QPalette Pal(palette()); // TODO: learn this

    Pal.setColor(QPalette::Background, Qt::white);
    ui->paintedWidget->setAutoFillBackground(true);
    ui->paintedWidget->setPalette(Pal);
//    paintedWidget.show();

//    paintPointsButton.setText("Start Painting!");
//    linkButton.setText("Start Linking!");
//    hLayout.addWidget(&numberLineEdit);
//    hLayout.addWidget(&paintPointsButton);
//    hLayout.addWidget(&linkButton);
//    vLayout.addWidget(&paintedWidget);
//    vLayout.addLayout(&hLayout);
    t = new MyThread();

    connect(ui->paintPointsButton, SIGNAL(clicked()), this, SLOT(startPainting()));
    connect(ui->linkButton, SIGNAL(clicked()), this, SLOT(prepareLinking()));
    connect(t, SIGNAL(returnResult(int*)), this, SLOT(startLinking(int*)));

//    w.setLayout(&vLayout);
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
    linking = false;
}
