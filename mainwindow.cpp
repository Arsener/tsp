#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paintedwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    w = new QWidget(this);
    setCentralWidget(w);
    paintedWidget = new PaintedWidget();
    numberLineEdit = new QLineEdit();
    button = new QPushButton();
    vLayout = new QVBoxLayout();
    hLayout = new QHBoxLayout();

    button->setText("Start Painting!");
    hLayout->addWidget(numberLineEdit);
    hLayout->addWidget(button);
    vLayout->addWidget(paintedWidget);
    vLayout->addLayout(hLayout);

    connect(button, SIGNAL(clicked()), this, SLOT(startPainting()));

    w->setLayout(vLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startPainting()
{
    int number = numberLineEdit->text().toInt();

    if(number < 0)
    {
        QMessageBox::warning(this, "Error!", "The number must be largger than zero!");
        return;
    }
    paintedWidget->setPointsNumber(number);
    paintedWidget->setDraw(true);
    paintedWidget->update();
}
